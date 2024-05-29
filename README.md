# Compiler-Construction-Project

Title: Compiler Project Report
Introduction
•	Objective: Develop a simple C++ compiler capable of parsing basic arithmetic expressions and variable declarations into an abstract syntax tree (AST).
•	Scope: The project covers the implementation of lexical analysis, parsing, and AST generation for a basic subset of a programming language.
Design and Architecture
•	Compiler Architecture Overview:
o	Lexer: Responsible for breaking the source code into tokens. Each token represents a syntactical or lexical component, such as operators, identifiers, or literals.
o	Parser: Takes the stream of tokens from the Lexer and builds an AST that reflects the grammatical structure of the input code. This structure helps in further processing, like code generation or optimization.
Implementation Details
•	Lexer (Lexical Analyzer):
o	Implemented as a Lexer class, which scans the input string character by character to categorize parts of the string into tokens such as INT, IDENTIFIER, NUMBER, ASSIGN, etc.
o	Special characters and sequences like '+', '-', '*', and '/' are individually checked and identified.
•	Parser:
o	The Parser class uses these tokens to construct an AST. The parsing process involves recognizing patterns in the sequence of tokens that correspond to grammatical rules of the language being compiled.
o	It features functions to parse expressions, terms, factors, and declarations based on the tokens received from the Lexer.
•	AST Nodes:
o	Various node types (NumberNode, IdentifierNode, BinaryOperationNode, AssignmentNode, and DeclarationNode) represent different constructs in the source code.
o	These nodes are used by the parser to build a hierarchical structure that represents the input program.
Testing and Validation
•	Testing Strategies:
o	Unit Testing: Each component (Lexer and Parser) is tested independently to ensure they handle expected inputs correctly and manage error conditions or unexpected inputs gracefully.
o	Integration Testing: Tests the Lexer and Parser working together to ensure the system as whole processes input correctly and produces the expected AST.
•	Validation:
o	The compiler's correctness is validated by comparing the output ASTs with expected outcomes for given inputs. Errors in the lexer or parser are reported to standard error, aiding in debugging.
Results and Evaluation
•	Performance Metrics:
o	The efficiency of the compiler is evaluated based on the speed of tokenization and parsing, as well as the memory overhead required to handle typical input sizes.
•	Evaluation:
o	Performance is discussed with examples, illustrating how the compiler handles complex expressions and nested statements.
Conclusion
•	Project Outcomes:
o	The compiler successfully implements the foundational aspects of a language processor, capable of understanding and structuring basic programming constructs.
•	Challenges Faced:
o	Challenges include managing error reporting in the Lexer and Parser, and ensuring the AST accurately represents various expressions and language constructs.
•	Potential Future Enhancements:
o	Future work could include extending the language's feature set, improving error diagnostics, and optimizing the performance of the Lexer and Parser.
