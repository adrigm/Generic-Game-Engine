#include <GGE/Core/utils/pugixml.hpp>
#include <GGE/Core/utils/StringUtils.hpp>
#include <GGE/Core/tmx/tmxMap.hpp>
#include <iostream> // Quitar

namespace GGE
{

TmxMap::TmxMap()
{
}

TmxMap::~TmxMap()
{
}

void TmxMap::RegisterApp(App* theApp)
{
	mApp = theApp;
}

bool TmxMap::LoadFromFile(std::string& theFilename)
{
	// Cargamos el archivo de mapa
	pugi::xml_document doc;
	if (!doc.load_file(theFilename.c_str()))
	{
		mApp->mLog << "Map::LoadFromFile: Error al cargar el fichero xml " << theFilename << std::endl;
		return false;
	}

	// Cogemos el nodo principal
	pugi::xml_node root_node;
	if (!(root_node = doc.child("map")))
	{
		mApp->mLog << "Map::LoadFromFile: Error al leer el fichero xml en elemento map" << std::endl;
		return false;
	}

	// Obtetemos la version
	mVersion = root_node.attribute("version").as_double();

	// Obtenemos la Orientacion
	mOrientation = root_node.attribute("orientation").value();

	// Obtenemos el tamaño del mapa
	mWidth = root_node.attribute("width").as_uint();
	mHeight = root_node.attribute("height").as_uint();

	// Obtenemos el tamaño de los tiles
	mTileWidth = root_node.attribute("tilewidth").as_uint();
	mTileHeight = root_node.attribute("tileheight").as_uint();

	// Recorremos todos los nodos del mapa
	for (pugi::xml_node node = root_node.first_child(); node; node = node.next_sibling())
	{
		// Obtenemos el nombre del nodo
		std::string anNode = node.name();

		// Si es el nodo de propiedades
		if (anNode == "properties")
		{
			// Recorremos las propiedades
			for (pugi::xml_node property = node.first_child(); property; property = property.next_sibling())
			{
				std::string name = property.attribute("name").value();
				std::string value = property.attribute("value").value();
				mProperties.SetProperty(name, value);
			}
		}

		// Si es un nodo tileset
		if (anNode == "tileset")
		{
			// Creamos un objeto tileset
			TmxTileset anTileset;

			// Obtenemos el nombre del tileset
			anTileset.SetName(node.attribute("name").value());

			// Obtenemos el primer tile
			anTileset.SetFirstGid(node.attribute("firstgid").as_uint());

			// Obtenemos el ancho y el alto de los tiles
			anTileset.SetTileWidth(node.attribute("tilewidth").as_uint());
			anTileset.SetTileHeight(node.attribute("tileheight").as_uint());

			// Recorremos los nodos del tileset
			for (pugi::xml_node nodeTileset = node.first_child(); 
				nodeTileset; nodeTileset = nodeTileset.next_sibling())
			{
				std::string nodeTilesetName = nodeTileset.name();
				if (nodeTilesetName == "image")
				{
					// Obtenemos el archivo del tileset
					anTileset.SetFile(ExtracNameFile(nodeTileset.attribute("source").value()));

					// Obtenemos el ancho y alto del tileset
					anTileset.SetWidth(nodeTileset.attribute("width").as_uint());
					anTileset.SetHeight(nodeTileset.attribute("height").as_uint());

					// Obtenemos el color del tileset
					if (nodeTileset.attribute("trans"))
					{
						anTileset.SetColorkey(nodeTileset.attribute("trans").value());
					}
					else
					{
						anTileset.SetColorkey("");
					}
				}

				// Si es un nodo de tile
				if (nodeTilesetName == "tile")
				{
					// Obtemos el ID
					int anID = nodeTileset.attribute("id").as_uint();
					
					// Recorremos el nodo propiedades
					pugi::xml_node nodeProperties = nodeTileset.child("properties");

					// Recorremos las propiedades
					for (pugi::xml_node tileprop = nodeProperties.first_child(); 
						tileprop; tileprop = tileprop.next_sibling())
					{
						std::string name = tileprop.attribute("name").value();
						std::string value = tileprop.attribute("value").value();
						anTileset.SetTileProperty(anID, name, value);
					}
				}
			}
			this->mTilesets.push_back(anTileset);
		}

		// Si es un nodo layer
		if (anNode == "layer")
		{
			// Creamos un objeto Layer
			TmxLayer anLayer;

			// Obtenemos el nombre de la capa
			anLayer.SetName(node.attribute("name").value());
			
			// Obtenemos el tamaño de la capa
			anLayer.SetWidth(node.attribute("width").as_uint());
			anLayer.SetHeight(node.attribute("height").as_uint());

			// Obtenemos el nodo data
			pugi::xml_node nodeData = node.child("data");
			
			// Obtenemos la codificacion
			if (nodeData.attribute("encoding"))
				anLayer.SetEncoding(nodeData.attribute("encoding").value());
			
			// Obtenemos el modo de compresion
			if (nodeData.attribute("compression"))
				anLayer.SetCompression(nodeData.attribute("compression").value());

			// Obtenemos la cadena de datos
			anLayer.SetData(nodeData.child_value());
			// Descomprimimos las datos de la capa
			anLayer.DescompressData();

			// Obtenemos el nodo de propiedades
			pugi::xml_node nodeProperties = node.child("properties");
			
			// Recorremos las propiedades
			for (pugi::xml_node Layerprop = nodeProperties.first_child(); 
				Layerprop; Layerprop = Layerprop.next_sibling())
			{
				std::string name = Layerprop.attribute("name").value();
				std::string value = Layerprop.attribute("value").value();
				anLayer.mProperties.SetProperty(name, value);
			}

			mLayers.push_back(anLayer);
		}

		if (anNode == "objectgroup")
		{

		}
	}

	//std::cout << mTilesets[0].GetTileProperty(1, "tile") << std::endl;
	//std::cout << mTilesets[1].GetWidth() << std::endl;
}

} // Namespace GGE