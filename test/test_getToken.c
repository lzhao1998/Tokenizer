#include <stdlib.h>
#include <errno.h>
#include "unity.h"
#include "Common.h"
#include "Token.h"
#include "Error.h"
#include "Tokenizer.h"
#include "Exception.h"
#include <stdio.h>

void setUp(void) {}

void tearDown(void) {}

/*
void test_skipWhiteSpaces_given_empty_string_expect_to_skip_till_end_of_string() {
  char *endPtr = skipWhiteSpaces("               ");

  TEST_ASSERT_EQUAL(0, *endPtr);
}

void test_skipWhiteSpaces_given____Hello_string_expect_to_skip_till_H() {
  char *endPtr = skipWhiteSpaces("   Hello   ");

  TEST_ASSERT_EQUAL('H', *endPtr);
}*/

void xtest_getToken_given_123_expect_Integer_Token_123() {
  Token *token;
  IntegerToken *intToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer(" 123");
  token = getToken(tokenizer);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_NOT_NULL(intToken);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
  TEST_ASSERT_EQUAL(123, intToken->value);
  TEST_ASSERT_EQUAL_STRING("123", intToken->str);
  freeToken(intToken);
}

void xtest_getToken_given_0xface_expect_Integer_Token_0xface() {
  Token *token;
  IntegerToken *intToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer(" 0xface ");
  token = getToken(tokenizer);
  intToken = (IntegerToken *)token;

  TEST_ASSERT_NOT_NULL(intToken);
  TEST_ASSERT_EQUAL(TOKEN_INTEGER_TYPE, intToken->type);
  TEST_ASSERT_EQUAL_STRING("0xface", intToken->str);
  TEST_ASSERT_EQUAL(0xface, intToken->value);
  freeToken(intToken);
}

 //STRING
void test_getToken_given_string_hello_expect_String_Token_hello() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\"hello\"");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_space_hello_expect_String_Token_hello() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("    \"hello\"");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello_space_expect_String_Token_hello() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\"hello\"    ");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello_space_world_expect_String_Token_hello_world() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\"hello  world\"");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello  world", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello123_expect_String_Token_hello123() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\"hello123\"");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello123", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_123hello_expect_String_Token_hello123() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\"123hello\"");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("123hello", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_symbol_expect_String_Token_symbol() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\",./?,.\"");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING(",./?,.", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello_without_closing_ampersand_sign_expect_return_INVALID_STRING_TYPE() {
  CEXCEPTION_T ex;
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\"hello");

  Try{
    strToken = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expect Error but No");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_NOT_NULL(ex);
    TEST_ASSERT_EQUAL(ERR_INVALID_STRING, ex->errorCode);
  }
  freeToken(ex->data);
}

void test_getToken_given_string_a_expect_String_Token_symbol() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\"a\"");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("a", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello_using_quotation_expect_String_Token_hello() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'hello\'");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello_space_using_quotation_expect_String_Token_hello() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'hello\'    ");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello_world_using_quotation_expect_String_Token_hello_world() {
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'hello world\'");
  token = getToken(tokenizer);
  strToken = (StringToken *)token;

  TEST_ASSERT_NOT_NULL(strToken);
  TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
  TEST_ASSERT_EQUAL_STRING("hello world", strToken->str);
  freeToken(strToken);
}

void test_getToken_given_string_hello_without_closing_quotation_sign_expect_return_INVALID_STRING_TYPE() {
  CEXCEPTION_T ex;
  Token *token;
  StringToken *strToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'hello");

  Try{
    strToken = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expect Error but No");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_NOT_NULL(ex);
    TEST_ASSERT_EQUAL(ERR_INVALID_STRING, ex->errorCode);
  }
  freeToken(ex->data);
}
//Char
void test_getToken_given_char_A_space_expect_Char_Token_A() {
  Token *token;
  CharConstToken *charToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'A\'");
  token = getToken(tokenizer);
  charToken = (CharConstToken *)token;

  TEST_ASSERT_NOT_NULL(charToken);
  TEST_ASSERT_EQUAL(TOKEN_CHAR_TYPE, charToken->type);
  TEST_ASSERT_EQUAL_STRING("A", charToken->str);
  freeToken(charToken);
}

void test_getToken_given_char_d_space_expect_Char_Token_d() {
  Token *token;
  CharConstToken *charToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'d\'");
  token = getToken(tokenizer);
  charToken = (CharConstToken *)token;

  TEST_ASSERT_NOT_NULL(charToken);
  TEST_ASSERT_EQUAL(TOKEN_CHAR_TYPE, charToken->type);
  TEST_ASSERT_EQUAL_STRING("d", charToken->str);
  freeToken(charToken);
}

void test_getToken_given_char_symbol_expect_return_INVALID_CHAR_TYPE() {
  CEXCEPTION_T ex;
  Token *token;
  CharConstToken *charToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'$\'");

  Try{
    charToken = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expect Error but No");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_NOT_NULL(ex);
    TEST_ASSERT_EQUAL(ERR_INVALID_CHAR, ex->errorCode);
  }
  freeToken(ex->data);
}

void test_getToken_given_char_number_expect_return_INVALID_CHAR_TYPE() {
  CEXCEPTION_T ex;
  Token *token;
  CharConstToken *charToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("\'1\'");

  Try{
    charToken = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expect Error but No");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_NOT_NULL(ex);
    TEST_ASSERT_EQUAL(ERR_INVALID_CHAR, ex->errorCode);
  }
  freeToken(ex->data);
}
