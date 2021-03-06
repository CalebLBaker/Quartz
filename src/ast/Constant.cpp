#include <utility>

#include "Constant.h"


Constant::Constant(const TypeDefinition *bt) : TypeDefinition(), base_type(bt) {}


Constant::Constant(Constant&& old) : TypeDefinition(std::move(old)), base_type(old.base_type) {}


const TypeDefinition* Constant::stripConst() const {
	return base_type;
}


std::string Constant::toString() const {
	return "#" + base_type->toString();
}


Error Constant::assignRegisters(std::vector<int64_t> *registers) const {
	return base_type->assignRegisters(registers);
}

