**Tokenizer**
Tokenizer is use to breaking up a sequence of strings into pieces such as words, keywords, phrases, symbols and other elements called tokens. 

In this project, I break up a sequence of strings into few tokens which is:
1. Integer - which include decimal, binary, octal and hexadecimal
````
   - decimal = 0,1,2,3,4,...
   - binary  = 0,1,10,11,100,...
   - octal   = 1,2,3,4,5,6,7,10,11,...
   - hex     = 0x09,0x0A,0xFF,...
````
2. Floating point
```
  - 0.12e+13
  - 1.013
  - 2.
```
3. String
````
  - "Hello"
  - 'Hello'
  - "E"
  - "a"
````
4. Character
```
  - 'a'
  - 'b'
```
5. Operator
```
  - &&,!,@,||,&@
```
6. Identifier
```
  - _value2_
  - AliBaba
  - _damnDaniel2
```

**Example:**
Input is " "Error" 132!  'z'   _not found  "in"  1.23e+2  'file'"

*Result*
``````
Integer token:          132
Floating point token:   1.23e+2
String token:           Error, in, file
Character token:        z
Operator token:         !
Identifier token:       _not
``````

That's all for my tokenizer. Thank you.
