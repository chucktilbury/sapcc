# Parser Description
This parser algorithm does not attempt to conform to a particular formalism. It is an attempt to create a parser that is as simple as possible. The resulting generated parser looks like a one that may have been hand-written using a table. The grammars for SAPCC are written using a modified BNF format that is much more simple and lacking many of the features of BNF. The syntax of the grammar is designed to be simple to parse and convert into a data structure that is easy to understand and use. The data structure makes heavy use of dynamically managed arrays.

The purpose of the generated parser is to recognize the input and generate an Abstract Syntax Table (AST). There is no provision to execute arbitrary code while the parser is running. Provisions are made to execute code before and after the parser is run. A set of visitor functions are generated with the parser. These are designed to be boilerplate. It is anticipated that several passes will me made on the resulting AST and the visitor should be copied and the function names changed for each pass.

A main table reflects the structure of the grammar but with the information that is required to find a specific rule. The table is a simple heap of integers.

It is desirable to not have the parser require external libraries, but for it to contain all of the code that is needed to run.

All of the Non-Terminal Symbols (NTS) in the grammar have a precedence. If the precedence is equal or less than the one on the top of the stack, then it is simply pushed on it. If it has a higher precedence then the stack is popped to a temporary location and replaced with the higher precednece NTS and then the lower NTS' are pushed back on. This is similar to the Shunting Yard algorithm for expressions, but it is used for all NTS' in this parser. The default precedence is 0, and a higher number indicates a higher precedence. Care must be taken to correctly set precedences to avoid changing the order of operations unexpectedly. The reason this exists is that the parsing algorithm does not deal with precedence in expressions, but it can also be used to patch the grammar in a way that simplifies conflicts.

All grammars have the purpose of defining how Terminal Symbols (TS) may be arranged to correctly for the syntax of that which is being parsed. Grammars use NTS' to create a hierarchy of rules that implement the syntax.

The parser takes the TS' one at a time and finds the rule that matches without any look-ahead and without any need to track past history. It is not possible for the grammar to contain "conflicts" for two reasons. First, the parser is stateful. It can only follow the hierarchy of NTS' that is defined in the grammar. Ultimately, it is a very simple FSM that uses the grammar and the input as one would expect. Second, every NTS has a precedence that is specified in the grammar. These two properties combined create a deterministic parser in which it is easy to detect and describe syntax errors and can parse any input that can be described by a grammar that it accepts.

There are 2 possible actions while parsing a rule. 1) store a TS 2) recurse on a NTS.

### PROBLEM:
The shunting yard algorithm may not work. All examples assume that the number and the operator come in separately, but this will combine them into a AST node. The expression must be a tree with precedence considered. So, it may not be possible to use the SY. However, it should be doable. Proceeding without it to get the other infrastructure working and then tackle that problem.

## Running
On start up, the parser receives a token, and it takes the first non-terminal to be the starting point in the grammar.
- When it begins to parse a new rule, all of the alternatives for the rule are stored in a cache.
- As tokens are read, they are matched to each line as a "possible match" using a common index.
  - If the token cannot match a line then the line is dropped from the cache.
  - If the token at the index in the line matches, then the line's score in incremented.
  - If the index is greater than the length of the line, then the line is kept until there are no more matches.
- When there are no more matches, and there is one line still in the cache, then that line is a match for the rule. The rule is returned as the match.
- If there are no more matches in the line and there are more than one lines still in the cache then the highest score is the match.
- If there are no more matches and are no lines in the cache then a syntax error occurred. To find out what was expected, then look at the lines at the current index and every token that is at the index in a line is an expected token.
- When a TS is encountered in the line, it is stored in the temporary cache until a match is made.
- If the item at the index is a NTS, then it is recursed and matched. The matched item is stored in the temporary cache.
- If an error is encountered, then an error token is returned from an NTS match. The NTS that didn't match is thrown away and error recovery takes place to keep parsing. The tokens that were scanned as a part of the NTS in error are discarded and parsing resumes from that point. As errors continue, tokens and NTS are discraded until one that succeeds is found, or until some number of errors take place.
- If the number of errors is exceeded then the parse is aborted. If an error is encountered, then the storing the resultant rule matches stops and no AST is returned at the end of the parse.
- When a TS or NTS matches, it is added to the current NTS as an attribute. When it is added, it is added using the Shunting Yard Algorithm (SYA) using the precedence of the item that is being added. Terminal and Non-Terminal Symbols always have the lowest precedence of 0. That causes them to be added to the temporary cache without modifying the order.
