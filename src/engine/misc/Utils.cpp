#include "Utils.h"

namespace ForgeEngine
{
	namespace Utils
	{
		std::vector<std::string> ExtractLines(const std::string& pattern, std::string source)
		{
			std::vector<std::string> extractedLines{};

			size_t pos = 0;
			size_t eol = 0;
			std::string token;

			while ((pos = source.find(pattern)) != std::string::npos) {
				source.erase(0, pos);
				eol = source.find("\n");
				token = source.substr(0, eol);
				extractedLines.push_back(token);
				source.erase(0, eol);
			}

			return extractedLines;
		}

		std::vector<std::string> Split(const std::string& pattern, std::string source)
		{
			std::vector<std::string> extractedLines{};

			size_t pos = 0;
			std::string token;

			while ((pos = source.find(pattern)) != std::string::npos) {
				token = source.substr(0, pos);
				extractedLines.push_back(token);
				source.erase(0, pos + pattern.length());
			}
			extractedLines.push_back(source);

			return extractedLines;
		}
	}
}