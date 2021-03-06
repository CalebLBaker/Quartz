#ifndef TYPE_H
#define TYPE_H

#include <memory>
#include <vector>

#include "SyntaxNode.h"
#include "scan/Scanner.h"
#include "TypeDefinition.h"
#include "TypeModifier.h"

class Program;

// Type represents a reference to a data type
class Type : SyntaxNode {

public:

	// name is the name of the type
	std::string name;

	// modifiers modify the type by making it constant or turning it into a pointer, array,
	// or slice
	std::vector<TypeModifier::Modifier> modifiers;

	// definition is a pointer to the definition for the type
	const TypeDefinition *definition;
	
	// Default constructor
	Type(Scope *s = nullptr);

	// Look ahead constructor
	Type(Scope *s, Token&& look_ahead);

	// Move constructor
	Type(Type&& old);

	/**
	 * parse populates the Type object by parsing Tokens from a Scanner
	 * param scanner: the scanner to parse tokens from
	 * returns:       an Error object indicating what, if anything, went wrong
	 */
	Error parse(Scanner *scanner); 

	/**
	 * doSemanticAnalysis matches the type with the corresponding TypeDefinition
	 * param program: the program that the type is in
	 * returns: an error object indicating whether a definition was successfully found
	 */
	Error doSemanticAnalysis();

	/**
	 * assignRegisters generates a list of registers to be used by a variable of this type
	 * param registers: the container to save the list of registers to
	 * returns: an error flag indicating any error that might have occurred
	 */
	Error assignRegisters(std::vector<int64_t> *registers) const;

private:

	Token next_token;

};

#endif
