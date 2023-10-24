# Recognize C-style strings in C

This will recognize C-style strings using C's regular expression library as an example for the
"parse string" example.

You should use a different language's regex library and their definition of C string literal.

Here is my chat-gpt discussion on C-99 strings:

### Prompt:
```
in C-99 what are allowed string literals?
```

### Response:
sented using `\u` followed by a 4-digit hexadecimal number or `\U` followed by an 8-digit hexadecimal number.

Example:

```c
char *string = "\u4F60\u597D";  // Ni Hao in Chinese
```

#### 4. Concatenation of String Literals
If you place two or more string literals adjacent to each other, they get concatenated automatically.

```c
char *string = "Hello, " "World!";
```

The above will be the same as `"Hello, World!"`.

#### Note on Immutability
String literals in C are immutable, meaning you shouldn't modify them. Doing so results in undefined behavior.

```c
char *string = "Hello, World!";
string[0] = 'h';  // Undefined behavior
```

#### Limitations
There are some limitations to what characters you can include in string literals, mainly based on the character set and encoding supported by the system you're working on.

For more detailed information on string literals in C99, you can refer to the ISO C99 standard documentation or this online reference: [C99 Standard](http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1256.pdf)

I hope this comprehensive explanation gives you a good understanding of string literals in C99.~

# Test

The test program `parse-string.c` runs against `matches.txt` and `mismatches.txt` you can run it with

```
gcc -o parse-strings parse-strings.c
./parse-strings
```

the output should be

```
"Hello, World!" matches pattern
"" matches pattern
"hi world" matches pattern
"Hello, \"World!\"\n" matches pattern
"\u4F60\u597D" does not match pattern
"\tthis is tabbed." matches pattern
unexpected results.
""" does not match pattern
"\" does not match pattern
not "\" does not match pattern
```

With a zero exit code.
