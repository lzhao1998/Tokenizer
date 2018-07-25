#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <error.h>
#include <ctype.h>
#include "Common.h"
#include "Error.h"
#include "Tokenizer.h"
#include "CException.h"
#include "Exception.h"

Tokenizer *initTokenizer(char *stringToTokenize) {
  if(stringToTokenize == NULL)
  {
    return NULL; //throw error
  }
  int i = 0; //to get the string length
  Tokenizer *token = NULL;
  token = (Tokenizer*)malloc(sizeof(Tokenizer));
  token->str = stringToTokenize;
  token->index = 0;

  while(stringToTokenize[index] == ' ') //skip the space
  {
    index++;
  }

  if(stringToTokenize[index] == '"')//  || stringToTokenize[index] == ''')
  {
    token->currentToken->originalStr = stringToTokenize;
    token->currentToken->startColumn = index;
    while(stringToTokenize[index] != '"')
    {
      if(stringToTokenize[index] == '\0')
      {
        return 0;//RETURN ERROR
      }
      else
      {
        index++;
        i++;
      }
    }
    token->currentToken->type = TOKEN_STRING_TYPE;
    token->currentToken->length = i;
    char *temp = (char*)malloc(index - i + 1);
    int k =0;
    printf("length is %d\n", (i-index));
    for(i;i<(index+1);i++)
    {
      if(i == index)
      {
        temp[k] = '\0';
      }
      else
      {
        temp[k] = str[j];
        k++;
      }
    }
    strcpy(token->currentToken->str,temp);
    free(temp);
    return (Tokenizer*)token;
  }
  else
  {
    return (Tokenizer*)token;
  }
}

Token *getToken(Tokenizer *tokenizer) {
  if(tokenizer->currentToken->type == TOKEN_STRING_TYPE)
  {
    StringToken *strToken = NULL;
    strToken = (StringToken*)malloc(sizeof(StringToken));
    strToken->type = tokenizer->currentToken->type;
    strToken->startColumn = tokenizer->currentToken->startColumn;
    strToken->length = tokenizer->currentToken->length;
    strToken->originalStr = tokenizer->currentToken->originalStr;
    strToken->str = tokenizer->currentToken->str;
  }
  else
  {
    return NULL;
  }
}
