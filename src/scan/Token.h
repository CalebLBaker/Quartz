#ifndef TOKEN_H
#define TOKEN_H

#include "Location.h"

// Token is a struct used to represent symbols from the input file.
class Token {

public:

	// TokenType is an enumeration used to identify different types of symbols.
	enum TokenType {
		IDENTIFIER,
		LEFT_PAREN,
		RIGHT_PAREN,
		LEFT_BRACE,
		RIGHT_BRACE,
		END_OF_FILE,
		RETURN,
		SEMICOLON,
		INTEGER,
		CLASS,
		ERROR
	};

	union TokenValue {
		std::string *strValue;
		int64_t intValue;
	};

	// value is used to  store the value of an identifier.
	TokenValue value;

	// location is the location of the symbol.
	Location location;

	// type is used to identify what type of symbol this is.
	TokenType type;

	/**
	 * Token constructs a Token object
	 * param t:    The type of Token to construct
	 * param loc:  The location of the token
	 */
	Token(TokenType t = ERROR, const Location *loc = nullptr);

	/**
	 * Token constructs an Identifier Token object.
	 * param loc:  The location of the token
	 * param val:  The name of the identifier
	 */
	Token(const Location *loc, std::string&& val);

	/**
	 * Token constructs an Integer Token object.
	 * param loc:  The location of the token
	 * param val:  The value of the integer
	 */
	Token(const Location *loc, int64_t val);

	/**
	 * Token copy constructs a Token.
	 * param token: The Token to copy
	 */
	Token(const Token& token);

	/**
	 * Token move constructs a Token.
	 * param token: The Token to move
	 */
	Token(Token&& token);

	/**
	 * ~Token deallocates memory used by a Token.
	 */
	~Token();

	/**
	 * setValue sets the value field
	 * param val: the value to set the value field to
	 */
	void setStringValue(const std::string& val);

	/**
	 * toString converts a token into a string
	 * returns: the string representation of the token
	 */
	std::string toString() const;

	/**
	 * tokenTypeToString converts a token type enum into a string
	 * param type: the TokenType to convert to a string
	 * returns: the string representation of type
	 */
	static std::string tokenTypeToString(TokenType type);

};

#endif
