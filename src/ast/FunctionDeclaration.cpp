#include "FunctionDeclaration.h"
#include "codeGen/Function.h"


FunctionDeclaration::FunctionDeclaration(Scope *s, Namespace *n) : Declaration(s, n),
                                                                   return_type(s, n), name(),
																   parameters(s, n), body(s, n) {}


FunctionDeclaration::FunctionDeclaration(FunctionDeclaration&& old)
   : Declaration(std::move(old)), return_type(std::move(old.return_type)), name(std::move(old.name)),
     parameters(std::move(old.parameters)), body(std::move(old.body)) {}


Error FunctionDeclaration::parse(Scanner *scanner) {
	location = scanner->next_token.location;
	Error error = return_type.parse(scanner);
	if (!error.ok()) {
		return error;
	}
	Token next_token = scanner->getNextToken();
	if (next_token.type == Token::IDENTIFIER) {
		name = std::move(*(next_token.value.strValue));
	}
	else {
		return Error(Error::EXPECTED_IDENTIFIER, std::move(next_token.location));
	}
	error = parameters.parse(scanner);
	if (!error.ok()) {
		return error;
	}
	return body.parse(scanner);
}


Error FunctionDeclaration::analyzeSignature() {
	return return_type.doSemanticAnalysis();
}


Error FunctionDeclaration::doSemanticAnalysis() {
	Error result = parameters.doSemanticAnalysis();
	if (!result.ok()) {
		return result;
	}
	return body.doSemanticAnalysis();
}


Error FunctionDeclaration::genCode(Function *low_level_func) {
	std::vector<BasicBlock> *blocks = &(low_level_func->blocks);
	blocks->emplace_back(BasicBlock());
	BasicBlock *block = &(blocks->back());
	block->addInstruction(Instruction(&name));
	block->addInstruction(Instruction(Instruction::RETURN));
	return Error();
}

