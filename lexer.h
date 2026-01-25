#ifndef __LEXERH__
#define __LEXERH__

typedef struct SLexer Lexer;

Lexer* New(const char* input);

typedef enum {
	TokenTypeIllegal,
	TokenTypeEOF,
	TokenTypeIdent,
	TokenTypeInt,
	TokenTypeAssign,
	TokenTypePlus,
	TokenTypeComma,
	TokenTypeSemicolon,
	TokenTypeLParen,
	TokenTypeRParen,
	TokenTypeLBrace,
	TokenTypeRBrace,
	TokenTypeFunction,
	TokenTypeLet,
}TokenType;

typedef struct SToken{
	TokenType type;
	char* Literal;
}Token;

Token* nextToken(Lexer* l);

#endif
