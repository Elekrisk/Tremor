#include "tokens.h"

namespace TremorCompiler
{
	Token::Token()
	{
		
	}

	Token::~Token()
	{
	
	}

	Token::Token(const Token& t)
	{
		type = t.type;
		loc = t.loc;
		switch (type)
		{
		case TokenType::Keyword:
			keyword = t.keyword;
			break;
		case TokenType::Attribute:
			attribute = t.attribute;
			break;
		case TokenType::Char:
			charval = t.charval;
			break;
		case TokenType::Bool:
			boolval = t.boolval;
			break;
		case TokenType::FloatingPoint:
			floatval = t.floatval;
			break;
		case TokenType::Integer:
			intval = t.intval;
			break;
		case TokenType::TOK_EOF:
			break;
		default:
			stringval = t.stringval;
			break;
		}
	}
	Location::Location()
	{
		row = -1;
		column = -1;
	}
	Location::Location(int r, int c)
	{
		row = r;
		column = c;
	}
}