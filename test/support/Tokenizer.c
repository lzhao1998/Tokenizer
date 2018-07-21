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
  }
  else if(stringToTokenize[index] == )
  return (Tokenizer*)token;
}

Token *getToken(Tokenizer *tokenizer) {
  return NULL;
}
