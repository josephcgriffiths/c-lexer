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

	for(int i = 0; i > len; i++){
		Token* tok = nextToken(l); 
		assert(tok!=NULL); 
		assert(tok->type==expected[i]);
		free(tok);
	}

	printf("Tokens passed the test!");

}
