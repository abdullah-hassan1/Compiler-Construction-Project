#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <cctype>

using namespace std;

enum TokenType {
    INT,
    IDENTIFIER,
    NUMBER,
    ASSIGN,
    PLUS,
    MINUS,
    MULTIPLY,
    DIVIDE,
    SEMICOLON,
    END
};

struct Token {
    TokenType type;
    string value;
};

class Lexer {
public:
    Lexer(const string& source) : source(source), position(0) {}

    vector<Token> tokenize() {
        vector<Token> tokens;
        while (position < source.size()) {
            char current = source[position];
            if (isspace(current)) {
                position++;
            } else if (current == '+') {
                tokens.push_back({PLUS, "+"});
                position++;
            } else if (current == '-') {
                tokens.push_back({MINUS, "-"});
                position++;
            } else if (current == '*') {
                tokens.push_back({MULTIPLY, "*"});
                position++;
            } else if (current == '/') {
                tokens.push_back({DIVIDE, "/"});
                position++;
            } else if (current == '=') {
                tokens.push_back({ASSIGN, "="});
                position++;
            } else if (current == ';') {
                tokens.push_back({SEMICOLON, ";"});
                position++;
            } else if (isdigit(current)) {
                tokens.push_back(number());
            } else if (isalpha(current)) {
                tokens.push_back(identifier());
            } else {
                cerr << "Unknown character: " << current << endl;
                position++;
            }
        }
        tokens.push_back({END, ""});
        return tokens;
    }

private:
    Token number() {
        string value;
        while (position < source.size() && isdigit(source[position])) {
            value += source[position++];
        }
        return {NUMBER, value};
    }

    Token identifier() {
        string value;
        while (position < source.size() && isalnum(source[position])) {
            value += source[position++];
        }
        if (value == "int") {
            return {INT, value};
        }
        return {IDENTIFIER, value};
    }

    string source;
    size_t position;
};

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct NumberNode : ASTNode {
    string value;
    explicit NumberNode(const string& value) : value(value) {}
};

struct IdentifierNode : ASTNode {
    string name;
    explicit IdentifierNode(const string& name) : name(name) {}
};

struct BinaryOperationNode : ASTNode {
    string op;
    unique_ptr<ASTNode> left;
    unique_ptr<ASTNode> right;

    BinaryOperationNode(string op, unique_ptr<ASTNode> left, unique_ptr<ASTNode> right)
        : op(op), left(move(left)), right(move(right)) {}
};

struct AssignmentNode : ASTNode {
    unique_ptr<IdentifierNode> identifier;
    unique_ptr<ASTNode> expression;

    AssignmentNode(unique_ptr<IdentifierNode> identifier, unique_ptr<ASTNode> expression)
        : identifier(move(identifier)), expression(move(expression)) {}
};

struct DeclarationNode : ASTNode {
    string type;
    unique_ptr<AssignmentNode> assignment;

    DeclarationNode(string type, unique_ptr<AssignmentNode> assignment)
        : type(type), assignment(move(assignment)) {}
};

struct CompoundNode : ASTNode {
    vector<unique_ptr<ASTNode>> declarations;

    CompoundNode(vector<unique_ptr<ASTNode>> declarations)
        : declarations(move(declarations)) {}
};

class Parser {
public:
    explicit Parser(const vector<Token>& tokens) : tokens(tokens), position(0) {}

    unique_ptr<ASTNode> parse() {
        unique_ptr<ASTNode> root = parseDeclarations();
        if (!isAtEnd()) {
            cerr << "Parsing error: unexpected tokens at the end." << endl;
            return nullptr;
        }
        return root;
    }

private:
    unique_ptr<ASTNode> parseDeclarations() {
        vector<unique_ptr<ASTNode>> declarations;
        while (!isAtEnd()) {
            unique_ptr<ASTNode> declaration = parseDeclaration();
            if (declaration) {
                declarations.push_back(move(declaration));
            } else {
                return nullptr;
            }
        }
        return make_unique<CompoundNode>(move(declarations));
    }

    unique_ptr<ASTNode> parseDeclaration() {
        if (match(INT)) {
            string type = previous().value;
            unique_ptr<IdentifierNode> identifier = make_unique<IdentifierNode>(consume(IDENTIFIER, "Expect identifier").value);
            consume(ASSIGN, "Expect '=' after variable name");
            unique_ptr<ASTNode> expression = parseExpression();
            consume(SEMICOLON, "Expect ';' after expression");
            return make_unique<DeclarationNode>(type, make_unique<AssignmentNode>(move(identifier), move(expression)));
        }
        return nullptr;
    }

    unique_ptr<ASTNode> parseExpression() {
        return parseTerm();
    }

    unique_ptr<ASTNode> parseTerm() {
        unique_ptr<ASTNode> node = parseFactor();
        while (match(PLUS) || match(MINUS)) {
            string op = previous().value;
            unique_ptr<ASTNode> right = parseFactor();
            node = make_unique<BinaryOperationNode>(op, move(node), move(right));
        }
        return node;
    }

    unique_ptr<ASTNode> parseFactor() {
        unique_ptr<ASTNode> node = parsePrimary();
        while (match(MULTIPLY) || match(DIVIDE)) {
            string op = previous().value;
            unique_ptr<ASTNode> right = parsePrimary();
            node = make_unique<BinaryOperationNode>(op, move(node), move(right));
        }
        return node;
    }

    unique_ptr<ASTNode> parsePrimary() {
        if (match(NUMBER)) {
            return make_unique<NumberNode>(previous().value);
        }
        if (match(IDENTIFIER)) {
            return make_unique<IdentifierNode>(previous().value);
        }
        cerr << "Unexpected token: " << peek().value << endl;
        return nullptr;
    }

    bool match(TokenType type) {
        if (check(type)) {
            advance();
            return true;
        }
        return false;
    }

    bool check(TokenType type) {
        if (isAtEnd()) return false;
        return peek().type == type;
    }

    Token advance() {
        if (!isAtEnd()) position++;
        return previous();
    }

    bool isAtEnd() {
        return peek().type == END;
    }

    Token peek() {
        return tokens[position];
    }

    Token previous() {
        return tokens[position - 1];
    }

    Token consume(TokenType type, const string& message) {
        if (check(type)) return advance();
        cerr << message << endl;
        return {};
    }

    const vector<Token>& tokens;
    size_t position;
};

int main() {
    string source = "int a = 5 int b = 4; int sum = a + b - 2  3 / 4;";

    Lexer lexer(source);
    vector<Token> tokens = lexer.tokenize();

    Parser parser(tokens);
    unique_ptr<ASTNode> syntaxTree = parser.parse();

    if (syntaxTree) {
        cout << "Parsing completed successfully." << endl;
    } else {
        cout << "Parsing failed." << endl;
    }

    return 0;
}


