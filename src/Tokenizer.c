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
  if(tokenizer->str[tokenizer->index] == '\0') //if it is NULL, create NULL token (DONE)
  {
    token = createNullToken();
    return token;
  }
  while(tokenizer->str[tokenizer->index] == ' ') //skip the unwanted space (DONE)
  {
    tokenizer->index++;
  }

  if(tokenizer->str[tokenizer->index] == '\0') //after skip space and become NULL, create NULL token (DONE)
  {
    token = createNullToken();
    return token;
  }
  else if(tokenizer->str[tokenizer->index] == '\"') //if detect " , check it is string or invalid token
  {
    tokenizer->index++;
    startColumn = tokenizer->index;
    while (tokenizer->str[tokenizer->index] != '\"') {
      if(tokenizer->str[tokenizer->index] == '\0')
      {
        length = i;
        //startColumn - 1 is because needed include " sign
        //length + 1 is because needed include " sign
        token = createInvalidToken(tokenizer->str, startColumn-1, length+1);
        throwException(ERR_INVALID_STRING, token, "ERROR!! INVALID TOKEN");
      }
      tokenizer->index++;
      i++;
    }
    char *temp = (char*)malloc((i+1) * sizeof (char));	//get the length of the string and last is for NULL/end of string
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
  }
  else if(tokenizer->str[tokenizer->index] == '\'')//if detect ' , check it is string, character or invalid token
  {
    tokenizer->index++;
    startColumn = tokenizer->index;
    while (tokenizer->str[tokenizer->index] != '\'') {
      if(tokenizer->str[tokenizer->index] == '\0')
      {
        length = i;
        //startColumn - 1 is because needed include " sign
        //length + 1 is because needed include " sign
        token = createInvalidToken(tokenizer->str, startColumn-1, length+1);
        throwException(ERR_INVALID_STRING, token, "ERROR!! INVALID STRING TOKEN");
      }
      tokenizer->index++;
      i++;
    }
    char *temp = (char*)malloc((i+1) * sizeof (char));	//get the length of the string and last is for NULL/end of string
    tokenizer->index++;
    length = i;     //length = i , because i start from 0 so length no need to equal i - 1
    //if length = 1 do char, else do string
    if(length == 1)
    {
      //if is char, create CHAR_TOKEN
      //else throw else
      if(isalpha(tokenizer->str[startColumn]) != 0){
        temp[0] = tokenizer->str[startColumn];
        temp[1] = '\0';
      }
      else{
        token = createInvalidToken(tokenizer->str, startColumn-1, length+1);
        throwException(ERR_INVALID_CHAR, token, "ERROR!! INVALID CHAR TOKEN");
      }
      token = createCharToken(startColumn, length, tokenizer->str, temp);
    }
    else
    {
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
    }
  }
  else if(isdigit(tokenizer->str[tokenizer->index]) == 1)   //if detect digit, check wether is integer, floating point or invalid token
  {
    token = createNullToken();
    return token;
  }
  else if(isalpha(tokenizer->str[tokenizer->index]) != 0 || tokenizer->str[tokenizer->index] == '_') //if detect _ or alpha, check is identifier or not
  {
    startColumn = tokenizer->index;
    i = 1; // for the 1st char/underscore
    //while is not space or NULL, keep checking until it hit the space or NULL
    while(isspace(tokenizer->str[tokenizer->index]) == 0 && tokenizer->str[tokenizer->index] != '\0') {
      tokenizer->index++;
      i++;
    }
    char *temp = (char*)malloc((i) * sizeof (char));	//get the length of the string and last is for NULL/end of string
    length = i - 1;     //length = i , because i start from 0 so length no need to equal i - 1
    for(int k = 0; k < i; k = k + 1)
    {
      if(k == (i-1))
      {
        temp[k] = '\0';
      }
      else
      {
        if(isalnum(tokenizer->str[startColumn + k]) != 0 || tokenizer->str[startColumn + k] == '_' )
        {
          temp[k] = tokenizer->str[startColumn + k];
        }
        else
        {
          length = i;
          token = createInvalidToken(tokenizer->str, startColumn, length);
          throwException(ERR_INVALID_IDENTIFIER, token, "ERROR!! INVALID TOKEN");
        }
      }
    }
    token = createIdentifierToken(startColumn, length, tokenizer->str, temp);
  }
  else if(ispunct(tokenizer->str[tokenizer->index]))   //if detect punctuation character, check wether is the operator or not
  {
    startColumn = tokenizer->index;
    i = 1; // for the 1st char/underscore
    //while is not space or NULL, keep checking until it hit the space or NULL
    while(isspace(tokenizer->str[tokenizer->index]) == 0 && tokenizer->str[tokenizer->index] != '\0' && ispunct(tokenizer->str[tokenizer->index]) != 0) {
      tokenizer->index++;
      i++;
    }
    char *temp = (char*)malloc((i) * sizeof (char));	//get the length of the string and last is for NULL/end of string
    if(i == 1) {length = i ;}     //length = i , because i start from 0 so length no need to equal i - 1
    else{length = i -1;}
    for(int k = 0; k < i; k++)
    {
      if(k == i-1)
      {
        temp[k] = '\0';
      }
      else
      {
        temp[k] = tokenizer->str[startColumn + k];
      }
    }
    token = createOperatorToken(startColumn, length, tokenizer->str, temp);
  }
  else{
    token = createNullToken();
  }
  return token;
}
