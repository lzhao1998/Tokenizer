#ifndef Tokenizer_H
#define Tokenizer_H

#include "Common.h"
#include "Token.h"

typedef struct {
  char *str;
  int index;
  Token *currentToken;
} Tokenizer;

Tokenizer *initTokenizer(char *stringToTokenize);
Token *advanceToken(Tokenizer *tokenizer);
Token *getToken(Tokenizer *tokenizer);
Token *peepToken(Tokenizer *tokenizer);

#endif // Tokenizer_H
