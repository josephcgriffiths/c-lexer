#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "lexer.h"

Token* newToken(TokenType type, char* literal);
void readChar(Lexer *l);


bool isLetter(char ch);
const char* readIdentifier(Lexer* l, size_t *len);
TokenType LookupIdent(const char* ident, size_t len);
void skipWhitespace(Lexer* l);

struct SLexer{
	const char* input;
	size_t inputLen;
	size_t position; // current position in input
	size_t readPosition; // current postion in input (after the current char)
	char ch; // current char under examination
};

Lexer* New(const char* input){
	size_t len = sizeof(Lexer); 
	Lexer* l = malloc(len);
	memset(l, 0, len);

	l->input = input;
	l->inputLen = strlen(input); 
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

	skipWhitespace(l);

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

	if(isLetter(l->ch)){
		size_t len = 0;
		char* literal = NULL;
		const char* ident = readIdentifier(l, &len);

		TokenType token = LookupIdent(ident, len);
		if(token==TokenTypeIdent){
			literal = strndup(ident, len);
		}
		
		tok = newToken(token, literal); 
		return tok;
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


const char* readIdentifier(Lexer* l, size_t *len){
	size_t position = l->position;

	while(isLetter(l->ch)){
		readChar(l);
	}

	if(len){
		*len = l->position - position;
	}

	return l->input + position;
}

bool isLetter(char ch){
	return 'a' <= ch && ch <= 'z' || 'A' <= ch && ch <= 'Z' || ch == '_';
}


TokenType LookupIdent(const char* ident, size_t len){
	if(strncmp(ident, "let", len) == 0){
		return TokenTypeLet;
	} else if(strncmp(ident, "fn", len) ==  0){
		return TokenTypeFunction;
	}

	return TokenTypeIdent;
}

void skipWhiteSpace(Lexer* l){
	while(l->ch == ' ' || l->ch == '\t' || l->ch == '\n'){
		readChar(l);
	}
}
