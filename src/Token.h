#ifndef Token_H
#define Token_H

#include <stdint.h>
//#include "Common.h"
#include "CException.h"
#include "Exception.h"

typedef enum {
  TOKEN_UNKNOWN_TYPE,
  TOKEN_NULL_TYPE,
  TOKEN_INVALID_TYPE,
  TOKEN_INTEGER_TYPE,
  TOKEN_OPERATOR_TYPE,
  TOKEN_FLOAT_TYPE,
  TOKEN_STRING_TYPE,
  TOKEN_IDENTIFIER_TYPE,
} TokenType;

typedef enum {
  NO_AFFIX,
  PREFIX,
  INFIX,
  POSTFIX,
} Affix;

typedef enum {
  NO_ASSOCIATIVITY,
  LEFT_TO_RIGHT,
  RIGHT_TO_LEFT,
} Associativity;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
} Token;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  int value;
} IntegerToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  double value;
} FloatToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
} IdentifierToken, StringToken, CharConstToken;

typedef struct {
  TokenType type;
  uint32_t startColumn;
  uint32_t length;
  char *originalStr;         ///
  char *str;
  Token *token[0];
} OperatorToken;

typedef struct {
  char *str;
  int index;
  Token *currentToken;
} Tokenizer;

Token *createNullToken();
Token *createInvalidToken(char *originalString, int start, int len);
Token *createIntegerToken(int value, char *originalString);
Token *createFloatToken(double value, char *originalString);
Token *createIdentifierToken(char *str, char *originalString);
void freeToken(void *token);
void dumpTokenErrorMessage(CEXCEPTION_T ex, int lineNo);

#endif // Token_H

