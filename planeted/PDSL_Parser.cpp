#include "PDSL_Parser.h"

namespace Planeted
{
    Parser::Parser(Lexer &lexer)
        : lexer(lexer)
    {
        this->next = this->lexer.Next();
        this->advance();
    }

    Program Parser::Parse()
    {
        Program result;

        while(this->currentToken.TokenType != TokenTypeEnum::End)
        {
            result.statements.push_back(this->parseStatement());
        }
        return result;
    }

    std::unique_ptr<Statement> Parser::parseStatement()
    {
        std::unique_ptr<Statement> result;

        if(this->currentToken.TokenType == TokenTypeEnum::Return)
        {
            result = this->parseReturnStatement();
            //ToDo: stop parsing. If not eof => unreachable code detected.
        }
        else
        {
            if(this->currentToken.TokenType == TokenTypeEnum::Import)
            {
                result = this->parseImportStatement();
            }
            else
            {
                if(this->next.TokenType == TokenTypeEnum::Equals)
                {
                    result = this->parseAssignmentStatement();
                }
                else
                {
                    result = this->parseExpressionStatement();
                }
            }
        }
        return result;
    }

    std::unique_ptr<ImportStatement> Parser::parseImportStatement()
    {
        this->expect(TokenTypeEnum::Import);

        std::string path = this->expect(TokenTypeEnum::StringLiteral).Lexeme;

        return std::make_unique<ImportStatement>(path);
    }

    std::unique_ptr<ReturnStatement> Parser::parseReturnStatement()
    {
        // return
        this->expect(TokenTypeEnum::Return);

        // expression
        std::unique_ptr<Expression> expression = this->parseExpression();

        // ;
        this->expect(TokenTypeEnum::Semicolon);

        return std::make_unique<ReturnStatement>(std::move(expression));
    }

    std::unique_ptr<AssignmentStatement> Parser::parseAssignmentStatement()
    {
        // identifier
        std::string name = this->expect(TokenTypeEnum::Identifier).Lexeme;

        // =
        this->expect(TokenTypeEnum::Equals);

        // expression
        std::unique_ptr<Expression> expression = this->parseExpression();

        // ;
        this->expect(TokenTypeEnum::Semicolon);

        return std::make_unique<AssignmentStatement>(name, std::move(expression));
    }

    std::unique_ptr<ExpressionStatement> Parser::parseExpressionStatement()
    {
        std::unique_ptr<Expression> expression = this->parseExpression();

        // ;
        this->expect(TokenTypeEnum::Semicolon);

        return std::make_unique<ExpressionStatement>(std::move(expression));
    }

    std::unique_ptr<Expression> Parser::parseExpression()
    {
        return this->parseUnaryExpression();
    }

    std::unique_ptr<Expression> Parser::parseUnaryExpression()
    {
        if(this->currentToken.TokenType == TokenTypeEnum::Minus)
        {
            this->advance();

            std::unique_ptr<Expression> operand = this->parseUnaryExpression();
            return std::make_unique<UnaryExpression>(TokenTypeEnum::Minus, std::move(operand));
        }
        return this->parsePrimaryExpression();
    }

    std::unique_ptr<Expression> Parser::parsePrimaryExpression()
    {
        if(this->currentToken.TokenType == TokenTypeEnum::Identifier)
        {
            if(this->next.TokenType == TokenTypeEnum::LParen)
            {
                return this->parseCallExpression();
            }
            std::string identifier = this->currentToken.Lexeme;
            this->advance();
            return std::make_unique<VariableExpression>(identifier);
        }
        if(this->currentToken.TokenType == TokenTypeEnum::LParen)
        {
            return this->parseTupleExpression();
        }
        if(this->currentToken.TokenType == TokenTypeEnum::LBrack)
        {
            return this->parseListExpression();
        }
        return this->parseLiteral();
    }

    std::unique_ptr<ConstantExpression> Parser::parseLiteral()
    {
        Value result;

        switch(this->currentToken.TokenType)
        {
        case TokenTypeEnum::IntLiteral:
            result = Value(std::stoi(this->currentToken.Lexeme));
            break;
        case TokenTypeEnum::FloatLiteral:
            result = Value(std::stof(this->currentToken.Lexeme));
            break;
        case TokenTypeEnum::BoolLiteral:
            result = Value(this->currentToken.Lexeme == "true");
            break;
        case TokenTypeEnum::StringLiteral:
            result = Value(this->currentToken.Lexeme);
            break;
        case TokenTypeEnum::NullLiteral:
            result = Value::Null();
            break;
        default:
            throw std::runtime_error("Invalid value type: " + TokenTypeToString(this->currentToken.TokenType));
            break;
        }

        this->advance();
        return std::make_unique<ConstantExpression>(result);
    }

    std::unique_ptr<CallExpression> Parser::parseCallExpression()
    {
        // identifier
        std::string name = this->expect(TokenTypeEnum::Identifier).Lexeme;

        // parse argument list:
        // (
        this->expect(TokenTypeEnum::LParen);

        std::vector<std::unique_ptr<Expression>> args;

        if(this->currentToken.TokenType != TokenTypeEnum::RParen)
        {
            while(true)
            {
                args.push_back(this->parseExpression());
                if(this->currentToken.TokenType == TokenTypeEnum::Comma)
                {
                    this->advance();
                    continue;
                }
                break;
            }
        }
        // )

        this->expect(TokenTypeEnum::RParen);
        return std::make_unique<CallExpression>(name, std::move(args));
    }

    std::unique_ptr<TupleExpression> Parser::parseTupleExpression()
    {
        // (
        this->expect(TokenTypeEnum::LParen);

        std::vector<std::unique_ptr<Expression>> args;

        if(this->currentToken.TokenType != TokenTypeEnum::RParen)
        {
            while(true)
            {
                args.push_back(this->parseExpression());
                if(this->currentToken.TokenType == TokenTypeEnum::Comma)
                {
                    this->advance();
                    continue;
                }
                break;
            }
        }
        // )

        this->expect(TokenTypeEnum::RParen);
        return std::make_unique<TupleExpression>(std::move(args));
    }
    std::unique_ptr<ListExpression> Parser::parseListExpression()
    {
        // [
        this->expect(TokenTypeEnum::LBrack);

        std::vector<std::unique_ptr<Expression>> args;

        if(this->currentToken.TokenType != TokenTypeEnum::RBrack)
        {
            while(true)
            {
                args.push_back(this->parseExpression());
                if(this->currentToken.TokenType == TokenTypeEnum::Comma)
                {
                    this->advance();
                    continue;
                }
                break;
            }
        }
        // ]

        this->expect(TokenTypeEnum::RBrack);
        return std::make_unique<ListExpression>(std::move(args));
    }

    void Parser::advance()
    {
        this->currentToken = this->next;
        this->next = this->lexer.Next();
    }

    Token Parser::expect(TokenTypeEnum tokenType)
    {
        if(this->currentToken.TokenType != tokenType)
        {
            throw std::runtime_error("Unexpected token: " + TokenTypeToString(this->currentToken.TokenType) + " (expected " + TokenTypeToString(tokenType) + ")");
        }

        Token result = this->currentToken;
        this->advance();

        return result;
    }
}
