#pragma once

#include <map>

namespace TremorCompiler
{
	enum class TokenType
	{
		Identifier,
		Keyword,
		String,
		Integer,
		FloatingPoint,
		Bool,
		Char,
		Attribute,
		TOK_EOF = -1
	};

	enum class Keyword
	{
		k_u8,
		k_u16,
		k_u32,
		k_u64,
		k_i8,
		k_i16,
		k_i32,
		k_i64,
		k_char,
		k_wchar,
		k_bool,
		k_f32,
		k_f64,
		k_func,
		k_class,
		k_enum,
		k_namespace,
		k_this,
		k_let,
		k_if,
		k_else,
		k_for,
		k_while,
		k_do,
		k_continue,
		k_break,
		k_private,
		k_public,
		k_constr,
		k_destr,
		k_extern
	};

	enum class Attribute
	{
		nomangle
	};

	class Location
	{
	public:
		int row;
		int column;

		Location();
		Location(int r, int c);
	};

	class Token
	{

	public:
		Token();
		~Token();
		Token(const Token&);

		TokenType type;
		Location loc;
		union
		{
			std::string stringval;
			char charval;
			Keyword keyword;
			Attribute attribute;
			long long intval;
			bool boolval;
			double floatval;
		};
	};
}