#include "preprocessor.h"
#include <fstream>
#include <vector>

#include "exceptions.h"

void Preprocessor::processDirective(const std::string & line)
{
	if (line[0] != '#')
		return;
	size_t firstSpace = line.find(' ');
	auto directive = line.substr(1, (firstSpace != -1 ? firstSpace : line.find('\n')) - 1);
	if (directive == "define")
	{
		processDefine(line.substr(firstSpace));
	}
}

void Preprocessor::processIfdef(const std::string & line)
{
	if (line[0] == '\n')
	{
		error("Macro expected, line break found", row, line.length() - 1);
		return;
	}

	size_t startOfMacro;
	for (startOfMacro = 0; line[startOfMacro] == ' ' || line[startOfMacro] == '\t'; ++startOfMacro);
	if (line[startOfMacro] == '\n')
	{
		error("Macro expected, line break found", row, line.length() - 1);
		return;
	}
	if (!isalpha(line[startOfMacro]) && line[startOfMacro] != '_')
	{
		error("Unexpected character '" + std::string().append(line[startOfMacro]) + "', expected macro", row, startOfMacro);
		return;
	}
	std::string macro;
	size_t endOfMacro;
	for (endOfMacro = startOfMacro; isalnum(line[endOfMacro]) || line[endOfMacro] == '_'; ++endOfMacro)
	{
		macro += line[endOfMacro];
	}
	size_t eol;
	for (eol = endOfMacro; line[eol] == ' ' || line[eol] == '\t'; ++eol);
	if (line[eol] != '\n')
	{
		error("Unexpected character '" + std::string().append(line[eol]) + "', expected end of line", row, eol);
		return;
	}

	if (macros.find(macro) != macros.end())
	{
		while (true)
		{
			
		}
	}
}

void Preprocessor::processDefine(const std::string & line)
{
	if (line[0] == '\n')
	{
		error("No macro to define", row, 0);
		return;
	}

	size_t startOfMacro;
	for (startOfMacro = 0; line[startOfMacro] == ' ' || line[startOfMacro] == '\t'; ++startOfMacro);
	if (line[startOfMacro] == '\n')
	{
		error("No macro to define", row, 0);
		return;
	}
	if (!isalpha(line[startOfMacro]) && line[startOfMacro] != '_')
	{
		error("A macro must begin with a letter or an underscore", row, startOfMacro);
		return;
	}
	std::string macro;
	size_t endOfMacro;
	for (endOfMacro = startOfMacro; isalnum(line[endOfMacro]) || line[endOfMacro] == '_'; ++endOfMacro)
	{
		macro += line[endOfMacro];
	}
	if (line[endOfMacro] != ' ' && line[endOfMacro] != '\t')
	{
		if (line[endOfMacro] == '\n')
		{
			define(macro, "1");
		}
		else
		{
			error("A macro can only contain letters, numbers and underscores", row, endOfMacro);
			return;
		}
	}
	size_t startOfDef;
	for (startOfDef = endOfMacro; line[startOfDef] == ' ' || line[startOfDef] == '\t'; ++startOfDef);
	if (line[startOfDef] == '\n')
	{
		define(macro, "1");
		return;
	}
	std::string value;
	for (size_t i = startOfDef; line[i] != '\n'; ++i)
	{
		value += line[i];
	}
	define(macro, value);
}

void Preprocessor::replaceMacro(std::string & line)
{
	bool isValid = false;
	std::string possibleReplacement;
	size_t possibleReplacementStart = 0;
	for (size_t i = 0; i < line.length(); ++i)
	{
		if (!isValid && (isalpha(line[i]) || line[i] == '_'))
		{
			isValid = true;
			possibleReplacementStart = i;
		}
		if (isValid && (isalnum(line[i]) || line[i] == '_'))
		{
			possibleReplacement += line[i];
		}
		else if (isValid)
		{
			if (possibleReplacement.length() > 0)
			{
				for (auto macro : macros)
				{
					if (macro.first == possibleReplacement)
					{
						line = line.substr(0, possibleReplacementStart) + macro.second + line.substr(i, line.length() - i);
						i += possibleReplacementStart - i + macro.second.length();
					}
				}
				isValid = false;
				possibleReplacement = "";
			}
		}
	}
}

void Preprocessor::error(const std::string & msg, size_t row, size_t col) const
{
	std::cerr << "Preprocessor error:" << row << ":" << col << ": " << msg << std::endl;
}

Preprocessor::Preprocessor()
{

}

void Preprocessor::define(std::string macro, std::string value)
{
	macros[macro] = value;
}

std::string Preprocessor::process(const std::filesystem::path &path)
{
	std::vector<std::string> result;
	std::ifstream f(path);
	row = 0;
	while (f.is_open() && !f.eof())
	{
		++row;
		std::string line;
		std::getline(f, line);
		line += '\n';
		if (line[0] == '#')
		{
			processDirective(line);
		}
		else
		{
			replaceMacro(line);
			result.push_back(line);
		}
	}

	std::string res;
	for (std::string s : result)
	{
		res += s;
	}
	return res;
}