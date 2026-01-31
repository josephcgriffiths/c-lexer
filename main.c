#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#include "lexer.h"

int main(){
	const char* input = "=+(){},;";

	TokenType expected[] = {
		TokenTypeAssign,
		TokenTypePlus,
		TokenTypeLParen,
		TokenTypeRParen, 
		TokenTypeLBrace,
		TokenTypeRBrace,
		TokenTypeComma,
		TokenTypeSemicolon,
	};

	size_t len = sizeof(expected) / sizeof(expected[0]); // size of our array

	Lexer* l = New(input);
	assert(l!=NULL);

	for(int i = 0; i < len; i++){
		Token* tok = nextToken(l); 
		assert(tok!=NULL); 
		assert(tok->type==expected[i]);
		free(tok);
	}

	printf("Tokens passed the test!\n");

	// let five = 5;
	// let ten = 10;
	// let add = fn(x, y){ x + y };
	// let result = add(five, ten);

	const char* input2 = "let five = 5; let ten = 10; let add = fn(x, y){ x + y; }; let result = add(five, ten);";

	TokenType expected2[] = {
		TokenTypeLet,
		TokenTypeIdent,
		TokenTypeAssign,
		TokenTypeInt, 
		TokenTypeSemicolon,
		TokenTypeLet,
		TokenTypeIdent,
		TokenTypeAssign,
		TokenTypeInt, 
		TokenTypeSemicolon,
		TokenTypeLet,
		TokenTypeIdent,
		TokenTypeAssign,
		TokenTypeFunction,
		TokenTypeLParen,
		TokenTypeIdent,
		TokenTypeComma,
		TokenTypeIdent,
		TokenTypeRParen,
		TokenTypeLBrace,
		TokenTypeIdent,
		TokenTypePlus,
		TokenTypeIdent,
		TokenTypeSemicolon,
		TokenTypeLet,
		TokenTypeIdent,
		TokenTypeAssign,
		TokenTypeIdent,
		TokenTypeLParen,
		TokenTypeIdent,
		TokenTypeComma,
		TokenTypeIdent,
		TokenTypeRParen,
		TokenTypeSemicolon,
	};

	size_t len2 = sizeof(expected2) / sizeof(expected2[0]); // size of our array

	Lexer* l2 = New(input2);
	assert(l2!=NULL);

	for(int i = 0; i < len; i++){
		Token* tok = nextToken(l2); 
		assert(tok!=NULL); 
		assert(tok->type==expected2[i]);
		free(tok);
	}

	printf("Second tests have passed!\n");

}
