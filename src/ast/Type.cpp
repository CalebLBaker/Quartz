#include "Type.h"
#include "Program.h"


Type::Type(Scope *s) : SyntaxNode(s), name(), definition(nullptr) {}


Type::Type(Type&& old) : SyntaxNode(std::move(old)), name(std::move(old.name)) {}


Type::Type(Scope *s, Token&& look_ahead) : SyntaxNode(s), name(), definition(nullptr), next_token(std::move(look_ahead)) {}


Error Type::parse(Scanner *scanner) {
	if (next_token.type == Token::ERROR) {
		next_token = scanner->getNextToken();
	}
	location = next_token.location;
	while (true) {
		switch (next_token.type) {
			case Token::LEFT_BRACKET: {
				TRY(scanner->matchNextToken(Token::RIGHT_BRACKET));
				modifiers.emplace_back(TypeModifier::SLICE);
				break;
			}
			case Token::CONST: {
				modifiers.emplace_back(TypeModifier::CONST);
				break;
			}
			case Token::IDENTIFIER: {
				name = std::move(*(next_token.value.str_value));
				return Error();
			}
			default: {
				std::string message = "Error: Expected type name; Found \"";
				message.append(next_token.toString() + "\".\n");
				return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
			}
		}
		next_token = scanner->getNextToken();
	}
}


Error Type::doSemanticAnalysis() {
	definition = scope->getDefinition(this);
	if (definition == nullptr) {
		std::string message = "Type \"" + name + "\" does not exist in this scope\n";
		return Error(Error::NO_SUCH_TYPE, location, message);
	}
	return Error();
}


Error Type::assignRegisters(std::vector<int64_t> *registers) const {
	return definition->assignRegisters(registers);
}

