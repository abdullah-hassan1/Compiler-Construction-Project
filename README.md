# Compiler-Construction-Project


# Compiler Project

## Introduction

This project involves developing a simple C++ compiler that can parse basic arithmetic expressions and variable declarations into an abstract syntax tree (AST).

### Objective
- Develop a compiler capable of understanding and structuring basic programming constructs.

### Scope
- The project encompasses the implementation of lexical analysis, parsing, and AST generation for a basic subset of a programming language.

## Design and Architecture

### Compiler Architecture Overview
- **Lexer**: Responsible for breaking the source code into tokens, representing syntactical or lexical components like operators, identifiers, or literals.
- **Parser**: Uses the stream of tokens from the Lexer to build an AST that reflects the grammatical structure of the input code.

## Implementation Details

### Lexer (Lexical Analyzer)
- Implemented as a `Lexer` class that scans the input string character by character, categorizing parts of the string into tokens such as `INT`, `IDENTIFIER`, `NUMBER`, `ASSIGN`, etc.
- Special characters and sequences like '+', '-', '*', and '/' are individually checked and identified.

### Parser
- The `Parser` class uses these tokens to construct an AST. It recognizes patterns in the sequence of tokens that correspond to the grammatical rules of the language being compiled.
- Includes functions to parse expressions, terms, factors, and declarations.

### AST Nodes
- Node types like `NumberNode`, `IdentifierNode`, `BinaryOperationNode`, `AssignmentNode`, and `DeclarationNode` represent different constructs in the source code.
- These nodes help build a hierarchical structure that represents the input program.

## Testing and Validation

### Testing Strategies
- **Unit Testing**: Independent tests for each component (Lexer and Parser) to ensure they handle expected inputs correctly and manage error conditions.
- **Integration Testing**: Tests both Lexer and Parser together to ensure the system processes input correctly and produces the expected AST.

### Validation
- The correctness of the compiler is validated by comparing the output ASTs with expected outcomes for given inputs. Errors are reported to standard error to aid debugging.

## Results and Evaluation

### Performance Metrics
- Evaluated based on the speed of tokenization and parsing, and the memory overhead required to handle typical input sizes.

### Evaluation
- Discusses performance with examples, illustrating how the compiler handles complex expressions and nested statements.

## Conclusion

### Project Outcomes
- The project successfully implements the foundational aspects of a language processor, enabling the understanding and structuring of basic programming constructs.

### Challenges Faced
- Includes managing error reporting in the Lexer and Parser and ensuring the AST accurately represents various expressions and language constructs.

### Potential Future Enhancements
- Future work could extend the language's feature set, improve error diagnostics, and optimize the performance of the Lexer and Parser.
