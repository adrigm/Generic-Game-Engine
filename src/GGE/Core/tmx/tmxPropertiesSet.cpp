#include <GGE/Core/tmx/tmxPropertiesSet.hpp>

namespace GGE
{

TmxProperties::TmxProperties() :
	mProperties()
{
}

TmxProperties::~TmxProperties()
{
}

void TmxProperties::SetProperty(const std::string& theName, const std::string& theValue)
{
	std::map<std::string, std::string>::const_iterator it = mProperties.find(theName);
	if (it == mProperties.end())
	{
		mProperties[theName] = theValue;
	}
}

std::string TmxProperties::GetProperty(const std::string& theName) const
{
	std::map<std::string, std::string>::const_iterator it = mProperties.find(theName);
	if (it != mProperties.end())
	{
		return it->second;
	}
	
	return "";
}

} // Namespace GGE