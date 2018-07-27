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
  Tokenizer *token = NULL;
  token = (Tokenizer*)malloc(sizeof(Tokenizer));
  token->str = stringToTokenize;
  token->index = 0;					//start for index 0 to count
  return (Tokenizer*)token;
}

Token *getToken(Tokenizer *tokenizer) {
  int i = 0, startColumn = 0, length = 0;
  Token *token = NULL;
  token = (Token*)malloc(sizeof(Token));
  if(tokenizer->str[tokenizer->index] == NULL) //if it is NULL, create NULL token (DONE)
  {
    token = createNullToken();
    return token;
  }
  while(tokenizer->str[tokenizer->index] == ' ') //skip the unwanted space (DONE)
  {
    tokenizer->index++;
  }

  if(tokenizer->str[tokenizer->index] == NULL) //after skip space and become NULL, create NULL token (DONE)
  {
    token = createNullToken();
    return token;
  }
  else if(tokenizer->str[tokenizer->index] == '\"') //if detect " , check it is string or invalid token
  {
    tokenizer->index++;
    startColumn = tokenizer->index;
    while (tokenizer->str[tokenizer->index] != '\"') {
      if(tokenizer->str[tokenizer->index] == NULL)
      {
        length = i;
        printf("hello INVALID\n");
        token = createInvalidToken(tokenizer->str, startColumn, length);
        throwException(ERR_INVALID_STRING, token, "ERROR!! INVALID TOKEN");
      }
      tokenizer->index++;
      i++;
    }
    char *temp = (char*)malloc((i+1) * sizeof (char));	//get the length of the string and last is for NULL/end of string
    printf("i + 1 = %d\n",i+1);
    printf("length for temp is %d\n",strlen(temp));
    tokenizer->index++;
    length = i;     //length = i , because i start from 0 so length no need to equal i - 1
    for(int k = 0; k < (i+1); k = k + 1)
    {
      if(k == i)
      {
        temp[k] = '\0';
      }
      else
      {
        temp[k] = tokenizer->str[startColumn + k];
      }
    }
    token = createStringToken(startColumn, length, tokenizer->str, temp);
    //free(temp);
  //strcpy(token->currentToken->str,temp);
  //  free(temp);
    //divide to 2 or only one? '  or "
  }
  else if(tokenizer->str[tokenizer->index] == '\'')//if detect ' , check it is string, character or invalid token
  {

  }
  else if(isdigit(tokenizer->str[tokenizer->index]) == 1)   //if detect digit, check wether is integer, floating point or invalid token
  {

  }
  else if(ispunct(tokenizer->str[tokenizer->index]) == 1)   //if detect punctuation character, check wether is the operator or not
  {

  }
  else if(isalpha(tokenizer->str[tokenizer->index]) || tokenizer->str[tokenizer->index] == '_') //if detect _ or alpha, check is identifier or not
  {return NULL;}
  else{return NULL;}
	//return NULL;
  return token;
}
