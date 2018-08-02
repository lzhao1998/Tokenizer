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

void test_getToken_given_NULL_expect_NULL_TOKEN() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("");
  token = getToken(tokenizer);

  TEST_ASSERT_NOT_NULL(token);
  TEST_ASSERT_EQUAL(TOKEN_NULL_TYPE, token->type);
  TEST_ASSERT_EQUAL_STRING(NULL, token->str);
  freeToken(token);
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


 //STRING
 void test_getToken_given_string_empty_expect_String_Token_empty() {
   Token *token;
   StringToken *strToken;
   Tokenizer *tokenizer;

   tokenizer = initTokenizer("\"\"");
   token = getToken(tokenizer);
   strToken = (StringToken *)token;

   TEST_ASSERT_NOT_NULL(strToken);
   TEST_ASSERT_EQUAL(TOKEN_STRING_TYPE, strToken->type);
   TEST_ASSERT_EQUAL_STRING("", strToken->str);
   TEST_ASSERT_EQUAL(2, tokenizer->index);
   freeToken(strToken);
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
  TEST_ASSERT_EQUAL(7, tokenizer->index);
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
  TEST_ASSERT_EQUAL(11, tokenizer->index);
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
  TEST_ASSERT_EQUAL(7, tokenizer->index);
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
  TEST_ASSERT_EQUAL(14, tokenizer->index);
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
  TEST_ASSERT_EQUAL(8, strToken->length);
  TEST_ASSERT_EQUAL_STRING("hello123", strToken->str);
  TEST_ASSERT_EQUAL(10, tokenizer->index);
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
  TEST_ASSERT_EQUAL(10, tokenizer->index);
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
  TEST_ASSERT_EQUAL(8, tokenizer->index);
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
  TEST_ASSERT_EQUAL(3, tokenizer->index);
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
  TEST_ASSERT_EQUAL(7, tokenizer->index);
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
  TEST_ASSERT_EQUAL(5, strToken->length);
  TEST_ASSERT_EQUAL_STRING("hello", strToken->str);
  TEST_ASSERT_EQUAL(7, tokenizer->index);
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
  TEST_ASSERT_EQUAL(13, tokenizer->index);
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
  TEST_ASSERT_EQUAL(3, tokenizer->index);
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
  TEST_ASSERT_EQUAL(1, charToken->length);
  TEST_ASSERT_EQUAL_STRING("d", charToken->str);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
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

//Identifier
void test_getToken_given_identifier_apple_expect_Identifier_Token_apple() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("apple");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("apple", IdToken->str);
  TEST_ASSERT_EQUAL(5, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier_value2_expect_Identifier_Token_value2() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("value2");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("value2", IdToken->str);
  TEST_ASSERT_EQUAL(6, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier__hp_expect_Identifier_Token__hp() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("_hp");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("_hp", IdToken->str);
  TEST_ASSERT_EQUAL(3, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier__hp_omen_expect_Identifier_Token__hp_omen() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("_hp_omen");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("_hp_omen", IdToken->str);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier__123_expect_Identifier_Token__123() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("_123");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("_123", IdToken->str);
  TEST_ASSERT_EQUAL(4, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier__Omg123__expect_Identifier_Token__Omg123_() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("_Omg123_");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL(8, IdToken->length);
  TEST_ASSERT_EQUAL_STRING("_Omg123_", IdToken->str);
  TEST_ASSERT_EQUAL(8, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier_hello_world_expect_Identifier_Token_hello_world() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("hello_world");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("hello_world", IdToken->str);
  TEST_ASSERT_EQUAL(11, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier_space_hello_world_expect_Identifier_Token_hello_world() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("    hello_world");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("hello_world", IdToken->str);
  TEST_ASSERT_EQUAL(15, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier_hello_world_space_expect_Identifier_Token_hello_world() {
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("hello_world    ");
  token = getToken(tokenizer);
  IdToken = (IdentifierToken *)token;

  TEST_ASSERT_NOT_NULL(IdToken);
  TEST_ASSERT_EQUAL(TOKEN_IDENTIFIER_TYPE, IdToken->type);
  TEST_ASSERT_EQUAL_STRING("hello_world", IdToken->str);
  TEST_ASSERT_EQUAL(11, tokenizer->index);
  freeToken(IdToken);
}

void test_getToken_given_identifier_zeez_symbol_expect_return_INVALID_IDENTIFIER_TYPE() {
  CEXCEPTION_T ex;
  Token *token;
  IdentifierToken *IdToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("_zeez#");

  Try{
    token = getToken(tokenizer);
    TEST_FAIL_MESSAGE("Expect Error but No");
  }Catch(ex){
    dumpTokenErrorMessage(ex, 1);
    TEST_ASSERT_NOT_NULL(ex);
    TEST_ASSERT_EQUAL(ERR_INVALID_IDENTIFIER, ex->errorCode);
  }
  freeToken(ex->data);
}

//OPERATOR
void test_getToken_given_operator_minus_expect_Operator_Token_minus() {
  Token *token;
  OperatorToken *OpToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("-");
  token = getToken(tokenizer);
  OpToken = (OperatorToken *)token;

  TEST_ASSERT_NOT_NULL(OpToken);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, OpToken->type);
  TEST_ASSERT_EQUAL_STRING("-", OpToken->str);
  TEST_ASSERT_EQUAL(1, tokenizer->index);
  freeToken(OpToken);
}

void test_getToken_given_operator_minus_plus_expect_Operator_Token_minus_plus() {
  Token *token;
  OperatorToken *OpToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("-+");
  token = getToken(tokenizer);
  OpToken = (OperatorToken *)token;

  TEST_ASSERT_NOT_NULL(OpToken);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, OpToken->type);
  TEST_ASSERT_EQUAL_STRING("-+", OpToken->str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  freeToken(OpToken);
}

void test_getToken_given_operator_and_expect_Operator_Token_and() {
  Token *token;
  OperatorToken *OpToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("&&");
  token = getToken(tokenizer);
  OpToken = (OperatorToken *)token;

  TEST_ASSERT_NOT_NULL(OpToken);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, OpToken->type);
  TEST_ASSERT_EQUAL_STRING("&&", OpToken->str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  freeToken(OpToken);
}

void test_getToken_given_space_power_and_expect_Operator_Token_power() {
  Token *token;
  OperatorToken *OpToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer(" ^");
  token = getToken(tokenizer);
  OpToken = (OperatorToken *)token;

  TEST_ASSERT_NOT_NULL(OpToken);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, OpToken->type);
  TEST_ASSERT_EQUAL_STRING("^", OpToken->str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  freeToken(OpToken);
}

void test_getToken_given_operator_bracket_expect_Operator_Token_bracket() {
  Token *token;
  OperatorToken *OpToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer("()");
  token = getToken(tokenizer);
  OpToken = (OperatorToken *)token;

  TEST_ASSERT_NOT_NULL(OpToken);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, OpToken->type);
  TEST_ASSERT_EQUAL_STRING("()", OpToken->str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  freeToken(OpToken);
}

void test_getToken_given_operator_space_dot123_expect_Operator_Token_dot() {
  Token *token;
  OperatorToken *OpToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer(" .123");
  token = getToken(tokenizer);
  OpToken = (OperatorToken *)token;

  TEST_ASSERT_NOT_NULL(OpToken);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, OpToken->type);
  TEST_ASSERT_EQUAL_STRING(".", OpToken->str);
  TEST_ASSERT_EQUAL(2, tokenizer->index);
  freeToken(OpToken);
}

void test_getToken_given_operator_symbol_expect_Operator_Token_symbol() {
  Token *token;
  OperatorToken *OpToken;
  Tokenizer *tokenizer;

  tokenizer = initTokenizer(" /*-+!@#$");
  token = getToken(tokenizer);
  OpToken = (OperatorToken *)token;

  TEST_ASSERT_NOT_NULL(OpToken);
  TEST_ASSERT_EQUAL(TOKEN_OPERATOR_TYPE, OpToken->type);
  TEST_ASSERT_EQUAL_STRING("/*-+!@#$", OpToken->str);
  TEST_ASSERT_EQUAL(9, tokenizer->index);
  freeToken(OpToken);
}
