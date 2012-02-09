#include <GGE/Core/utils/StringUtils.hpp>

namespace GGE
{

std::string ExtracNameFile(const std::string& TheDir)
{
	for (int i=0; i < TheDir.size(); i++)
	{
		if (TheDir[i] == '/')
		{
			return TheDir.substr(TheDir.find_last_of('/')+1);
		}
		if (TheDir[i] == '\\')
		{
			return TheDir.substr(TheDir.find_last_of('\\')+1);
		}
	}
	return TheDir;
}

} // Namespace GGE