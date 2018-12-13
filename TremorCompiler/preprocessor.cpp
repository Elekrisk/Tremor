#include "preprocessor.h"
#include <fstream>
#include <vector>

#include "exceptions.h"

namespace TremorCompiler
{
	Preprocessor::Preprocessor()
	{

	}

	void Preprocessor::define(const std::string &macro, const std::string &value)
	{
		macros[macro] = value;
	}

	std::string Preprocessor::process(const std::filesystem::path &path)
	{
		std::vector<std::string> result;
		std::ifstream f(path);
		size_t lineLoc = 0;
		bool ignoreAllLines = false;
		while (f.is_open() && !f.eof())
		{
			bool ignoreLine = false;;
			std::string line;
			std::getline(f, line);
			line += '\n';
			if (line[0] == '#')
			{
				ignoreLine = true;
				std::string directive;
				size_t i;
				for (i = 1; i < line.length(); ++i)
				{
					if (line[i] == ' ' || line[i] == '\n')
					{
						break;
					}
					if (line[i] != '\r')
					{
						directive += line[i];
					}
				}
				
				if (directive == "define")
				{
					if (line[i] == '\n')
					{
						throw TremorException("No macro to define", Location(lineLoc, 0));
					}

					for (; line[i] == ' ' || line[i] == '\t'; ++i);


					if (line[i] == '\n')
					{
						throw TremorException("No macro to define", Location(lineLoc, 0));
					}
					std::string macro;
					for (; i < line.length(); ++i)
					{
						if (!(isalnum(line[i]) || line[i] == '_') || line[i] == '\n')
						{
							break;
						}
						if (line[i] != '\r')
						{
							macro += line[i];
						}
					}

					if (!(isalpha(macro[0]) || macro[0] == '_'))
					{
						throw TremorException("Macro must start with a letter or an underscore", Location(lineLoc, i - macro.length()));
					}
					for (; line[i] == ' '; ++i);
					if (i == '\n')
					{
						define(macro, "1");
					}
					else
					{
						std::string value;
						for (; line[i] != '\n'; ++i)
						{
							if (line[i] != '\r')
								value += line[i];
						}
						define(macro, value);
					}
				}
				else if (directive == "ifdef")
				{
					if (line[i] == '\n')
					{
						throw TremorException("No macro to check if defined", Location(lineLoc, 0));
					}
					for (; line[i] == ' ' || line[i] == '\t'; ++i);
					if (line[i] == '\n')
					{
						throw TremorException("No macro to check if defined", Location(lineLoc, 0));
					}
					std::string macro;
					for (; i < line.length(); ++i)
					{
						if (!(isalnum(line[i]) || line[i] == '_') || line[i] == '\n')
						{
							break;
						}
						if (line[i] != '\r')
						{
							macro += line[i];
						}
					}
					if (macros[macro] != "")
					{
						ignoreAllLines = true;
					}
				}
				else if (directive == "endif")
				{
					ignoreAllLines = false;
				}
			}
			else
			{
				std::string possibleMatch;
				size_t possibleMatchStart;
				bool isValid = false;

				for (size_t i = 0; i < line.length(); ++i)
				{
					if (!isValid && (isalpha(line[i]) || line[i] == '_'))
					{
						isValid = true;
						possibleMatchStart = i;
					}
					if (isValid && (isalnum(line[i]) || line[i] == '_'))
					{
						possibleMatch += line[i];
					}
					else if (possibleMatch.length() > 0)
					{
						for (std::pair<const std::string, std::string> macro : macros)
						{
							if (macro.first == possibleMatch)
							{
								line = line.substr(0, possibleMatchStart) + macro.second + line.substr(i, line.length() - i);
								i += (int)(possibleMatchStart - i) + (int)macro.second.length();
							}
						}
						possibleMatch = "";
						isValid = false;
					}
					else
					{
						possibleMatch = "";
						isValid = false;
					}
				}
			}
			if (!ignoreLine && !ignoreAllLines)
				result.push_back(line);
			++lineLoc;
		}

		std::string res;
		for (std::string s : result)
		{
			res += s;
		}
		return res;
	}
}