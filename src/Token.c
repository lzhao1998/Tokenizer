#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Token.h"
#include "Common.h"

Token *createNullToken() {
  Token *token = malloc(sizeof(Token));

  token->type = TOKEN_NULL_TYPE;
  token->str = token->originalStr = NULL;
  token->startColumn = token->length = 0;

  return token;
}

Token *createIntegerToken(int startColumn, int length, char *originalString, char *str, int value) {
  IntegerToken *token = malloc(sizeof(IntegerToken));

  token->type = TOKEN_INTEGER_TYPE;
  token->startColumn = startColumn;
  token->length = length;
  token->originalStr = originalString;      // need to use strcpy? cuz the str will not store forever;
  token->str = str;
  token->value = value;

  return (Token *)token;
}

Token *createFloatToken(int startColumn, int length, char *originalString, char *str, double value) {
  FloatToken *token = malloc(sizeof(FloatToken));

  token->type = TOKEN_FLOAT_TYPE;
  token->startColumn = startColumn;
  token->length = length;
  token->originalStr = originalString;      // need to use strcpy? cuz the str will not store forever;
  token->str = str;
  token->value = value;

  return (Token *)token;
}

Token *createIdentifierToken(int startColumn, int length, char *originalString, char *str) {
  IdentifierToken *token = malloc(sizeof(IdentifierToken));

  token->type = TOKEN_IDENTIFIER_TYPE;
  token->startColumn = startColumn;
  token->length = length;
  token->originalStr = originalString;      // need to use strcpy? cuz the str will not store forever;
  token->str = str;

  return (Token *)token;
}

Token *createStringToken(int startColumn, int length, char *originalString, char *str) {
  StringToken *token = malloc(sizeof(StringToken));

  token->type = TOKEN_STRING_TYPE;
  token->startColumn = startColumn;
  token->length = length;
  token->originalStr = originalString;      // need to use strcpy? cuz the str will not store forever;
  token->str = str;

  return (Token *)token;
}

Token *createOperatorToken(int startColumn, int length, char *originalString, char *str, Token *zoken) {
  OperatorToken *token = malloc(sizeof(OperatorToken));

  token->type = TOKEN_OPERATOR_TYPE;
  token->startColumn = startColumn;
  token->length = length;
  token->originalStr = originalString;      // need to use strcpy? cuz the str will not store forever;
  token->str = str;
  //token *[0]

  return (Token *)token;
}

Token *createInvalidToken(char *originalString, int start, int len) {
  char *endPtr;
  Token *token = malloc(sizeof(Token));

  token->type = TOKEN_INVALID_TYPE;
  token->originalStr = originalString;
  endPtr = skipNonWhiteSpaces(&originalString[start + len]);
  len = (int)(endPtr - originalString) - start;
  token->str = createSubstring(originalString, start, len);
//  printf("InvalidToken: %s\n", token->str);
  token->startColumn = start;
  token->length = len;

  return token;
}

void freeToken(void *token) {
  if(token) {
    if(((Token *)token)->str)
      free(((Token *)token)->str);
    free(token);
  }
}

void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo) {
  Token *token = (Token *)ex->data;
  int i = token->length - 1;
  if(i < 0) i = 0;

  printf("Error on line %d: ", lineNo);
  printf("%s\n", ex->msg);
  printf("%s\n", token->originalStr);
  printf("%*s", token->startColumn + 1, "^");
  while(i--)
    printf("~");
  putchar('\n');
}