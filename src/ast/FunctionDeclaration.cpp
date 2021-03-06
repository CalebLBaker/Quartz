#include "FunctionDeclaration.h"
#include "codeGen/Function.h"


FunctionDeclaration::FunctionDeclaration(Scope *s) : Declaration(s), name(), parameters(s), return_type(nullptr), body(s) {}


FunctionDeclaration::FunctionDeclaration(FunctionDeclaration&& old) : Declaration(std::move(old)), name(std::move(old.name)), parameters(std::move(old.parameters)), return_type(std::move(old.return_type)), body(std::move(old.body)) {}


Error FunctionDeclaration::parse(Scanner *scanner) {

	location = scanner->next_token.location;
	TRY(scanner->matchNextToken(Token::FUNC));
	TRY(parameters.parse(scanner));

	if (scanner->next_token.type == Token::RETURN_SPECIFIER) {
		scanner->matchNextToken(Token::RETURN_SPECIFIER);
		return_type = std::make_unique<Type>(scope);
		TRY(return_type->parse(scanner));
	}

	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER) {
		name = std::move(*(next_token.value.str_value));
	}
	else {
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}

	return body.parse(scanner);
}


Error FunctionDeclaration::analyzeSignature() {
	if (return_type == nullptr) {
		return Error();
	}
	TRY(return_type->doSemanticAnalysis());
	return parameters.doSemanticAnalysis();
}


Error FunctionDeclaration::doSemanticAnalysis() {
	return body.doSemanticAnalysis();
}


Error FunctionDeclaration::genCode(Function *low_level_func) {
	std::vector<BasicBlock> *blocks = &(low_level_func->blocks);
	blocks->emplace_back(BasicBlock());
	blocks->back().addInstruction(Instruction(&name));
	TRY(body.codeGen(blocks));
	blocks->back().addInstruction(Instruction(Instruction::RETURN));
	return Error();
}

