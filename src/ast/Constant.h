#ifndef CONSTANT_H
#define CONSTANT_H


#include "TypeDefinition.h"


class Constant : public TypeDefinition {

public:

	// Default Constructor
	Constant(const TypeDefinition *bt);

	// Move Constructor
	Constant(Constant&& old);

	const TypeDefinition* stripConst() const;

	std::string toString() const;

	Error assignRegisters(std::vector<int64_t> *registers) const;

private:
	const TypeDefinition *base_type;

};


#endif
