#pragma once

#include <string>
#include <vector>

namespace ForgeEngine
{
	namespace Utils
	{
		std::vector<std::string> ExtractLines(const std::string& pattern, std::string source);
		std::vector<std::string> Split(const std::string& pattern, std::string source);
	}
}