
#ifndef TMX_PROPERTIES_SET_HPP
#define TMX_PROPERTIES_SET_HPP

#include <string>
#include <map>

namespace GGE
{

class TmxProperties
{
public:
	TmxProperties();
	~TmxProperties();

	void SetProperty(const std::string& theName, const std::string& theValue);
	std::string GetProperty(const std::string& theName) const;

private:
	std::map<std::string, std::string> mProperties;


}; // Class TmxProperties

} // Namespace GGE

#endif // TMX_PROPERTIES_SET_HPP