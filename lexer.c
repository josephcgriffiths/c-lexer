#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "lexer.h"

Token* newToken(TokenType type, char* literal);
void readChar(Lexer *l);

struct SLexer{
	const char* input;
	size_t inputLen;
	size_t position; // current position in input
	size_t readPosition; // current postion in input (after the current char)
	char ch; // current char under examination
};

Lexer* New(const char* input){
	size_t len = sizeof(Lexer); // sizeof Lexer not input
	Lexer* l = malloc(len);
	memset(l, 0, len);

	l->input = input;
	l->inputLen = strlen(input); // should be strlen(input)
	l->position = 0;
	l->readPosition = 0;
	
	readChar(l);
	return l;
}

void readChar(Lexer* l){
	if(l->readPosition >= l->inputLen){
		l->ch = '\0';
	} else{
		l->ch = l->input[l->readPosition];
	}
	l->position = l->readPosition;
	l->readPosition++;
}

Token* nextToken(Lexer* l){
	Token* tok = NULL;

	switch(l->ch){
		case '=':
			tok = newToken(TokenTypeAssign, NULL);
			break;
		case ';':
			tok = newToken(TokenTypeSemicolon, NULL);
			break;
		case '(':
			tok = newToken(TokenTypeLParen, NULL);
			break;
		case ')':
			tok = newToken(TokenTypeRParen, NULL);
			break;
		case ',':
			tok = newToken(TokenTypeComma, NULL);
			break;
		case '+':
			tok = newToken(TokenTypePlus, NULL);
			break;
		case '{':
			tok = newToken(TokenTypeLBrace, NULL);
			break;
		case '}':
			tok = newToken(TokenTypeRBrace, NULL);
			break;
	}

	readChar(l);
	return tok;
}

Token* newToken(TokenType type, char* literal){
	size_t len = sizeof(Token);
	Token* tok = malloc(len);
	memset(tok, 0, len);

	tok->type = type;
	tok->Literal = literal;

	return tok;
}
