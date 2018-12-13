#pragma once

#include <map>
#include <iostream>
#include <filesystem>

namespace TremorCompiler
{
	class Preprocessor
	{
		std::map<std::string, std::string> macros;

		size_t line;
		size_t column;

	public:
		Preprocessor();
		void define(const std::string &macro, const std::string &value);

		std::string process(const std::filesystem::path &path);
	};
}