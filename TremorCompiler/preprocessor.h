#pragma once

#include <map>
#include <iostream>
#include <filesystem>

class Preprocessor
{
	std::map<std::string, std::string> macros;

	std::vector<std::string> lines;

	size_t row;

	void processDirective(const std::string& line);
	void processIfdef(const std::string& line);
	void processDefine(const std::string& line);
	void replaceMacro(std::string& line);

	void error(const std::string& msg, size_t row, size_t col) const;

public:
	Preprocessor();
	void define(std::string macro, std::string value);

	std::string process(const std::filesystem::path &path);
};