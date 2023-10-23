#  Main Points

Two main kinds of approaches to building a compiler

1. Tools

   Bison/Flex (yacc/lex)
   ANTLR
   lemon
     - used in SQL lite (lots of data is stored this way).
     - can badly formed documents corrupt the parser?  in lemon the goal is no.

   Tools help you discover problems in a language, this is helpful so that you can
   build correct code for "white hat" users, and avoid "black hat" flaws.

   They prefer left-recursive grammars.
   
2. Hand-made

   No dependencies.  Simple approach.

   These prefer right-recursive grammars.


What that?

   E -> E + T | T   // as left recursive (good for shift-reduce parsers)
                    // -> bad: left recursive grammars break recursive-descent parsers.
   
   T -> T * F | F
   F -> number | ( E )

This is left recursive.

A right-recursive version would be:

   E -> T + E
   E -> T
   E -> T + E | T   // as right recursive (good for recursive-descenct parsers)
                    // -> poor: right recursive grammars slow shift-reduce parsers.
   T -> F * T | F
   F -> number | ( E )

By doing substitutions, do the non-terminals evenually end up on the left - or the right?

Ex:

3+4+5

Left recursive version:
   E
   |
   E +  T
   |    |
  E+T   F
  | |   |
  T F   5
  | |
  F 4
  |
  3
