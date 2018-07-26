#include <stdlib.h>
#include <errno.h>
#include "unity.h"
#include "Common.h"
#include "Token.h"
#include "Error.h"
#include "Tokenizer.h"
#include "CException.h"
#include "Exception.h"

void setUp(void) {}

void tearDown(void) {}


void test_skipWhiteSpaces_given_empty_string_expect_to_skip_till_end_of_string() {
  char *endPtr = skipWhiteSpaces("               ");

  TEST_ASSERT_EQUAL(0, *endPtr);
}

void test_skipWhiteSpaces_given____Hello_string_expect_to_skip_till_H() {
  char *endPtr = skipWhiteSpaces("   Hello   ");

  TEST_ASSERT_EQUAL('H', *endPtr);
}

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

//for throw and catch
//dumpTokenErrorMessage(ex,1);
//TEST_FAIL_MESSAGE("throw throw");
