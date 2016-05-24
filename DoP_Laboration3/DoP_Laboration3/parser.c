/*
* File: parser.c
* --------------
* This file implements a version of ReadExp that uses
* conventional precedence rules.  Thus, the expression
*
*        x = 2 * x + y
*
* is interpreted as if it had been written
*
*        x = ((2 * x) + y))
*
* This language can be parsed using the following ambiguous
* grammar:
*
*       E  ->  T
*       E  ->  E op E
*
*       T  ->  integer
*       T  ->  identifier
*       T  ->  ( E )
*
* Unfortunately, this grammar is not sufficient by itself.  The
* parser must also provide some way to determine what operators
* take precedence over others.  Moreover, it must avoid the
* problem of going into an infinite recursion of trying to read
* an expression by reading an expression, and so on forever.
*
* To solve these problems, this implementation passes a numeric
* value to the ReadE function that specifies the precedence
* level for the current subexpression.  As long as ReadE finds
* operators with a higher precedence, it will read in those
* operators along with the following subexpression.  If the
* precedence of the new operator is the same or lower than
* the prevailing precedence, ReadE returns to the next higher
* level in the recursive-descent parsing and reads the operator
* there.
*/

#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "strlib.h"
#include "simpio.h"
#include "scanadt.h"
#include "parser.h"
#include "exp.h"

/*
* Implementation notes: ParseExp
* ------------------------------
* This function just calls ReadE to read an expression and then
* checks to make sure no tokens are left over.
*/

expADT ParseExp(scannerADT scanner)
{
	expADT exp;

	string command = CheckCommandToken(scanner);
	if(StringEqual(command, "\0"))
		exp = ReadE(scanner, 0);
	else
		exp = ReadCommand(scanner, command);

	return (exp);
}

string CheckCommandToken(scannerADT scanner) {
	//May exist problems with not reading the entire command or reading too much
	string token = ReadToken(scanner);
	if (token[0] != ':') {
		SaveToken(scanner, token);
		token = "\0";
	}
	else
		token = Concat(token, ReadToken(scanner));

	return token;
}

expADT ReadCommand(scanner, command) {
	expADT exp;
	if (StringEqual(command, ":define")) {
		string id = ReadToken(scanner);
		string op = ReadToken(scanner);
		expADT val = ReadE(scanner);
		exp = NewCompoundExp(op[0], NewIdentifierExp(id), val);
	}
	else if (StringEqual(command, ":load")) {
		//Should read file here
		exp = NewIdentifierExp(":load");
	}
	else
		exp = NewIdentifierExp(command);

	return exp;
}

/*
* Implementation notes: ReadE
* Usage: exp = ReadE(scanner, prec);
* ----------------------------------
* This function reads an expression from the scanner stream,
* stopping when it encounters an operator whose precedence is
* less that or equal to prec.
*/

expADT ReadE(scannerADT scanner)
{
	expADT exp, rhs;
	string token;

	exp = ReadT(scanner);
	
	token = ReadToken(scanner);

	if (StringEqual(token, "+") || StringEqual(token, "-")) {
		rhs = ReadE(scanner);
		exp = NewCompoundExp(token[0], exp, rhs);
	}

	return (exp);
}

/*
* Function: ReadT
* Usage: exp = ReadT(scanner);
* ----------------------------
* This function reads a single term from the scanner by matching
* the input to one of the following grammatical rules:
*
*       T  ->  integer
*       T  ->  identifier
*       T  ->  ( E )
*
* In each case, the first token identifies the appropriate rule.
*/

expADT ReadT(scannerADT scanner)
{
	expADT exp, rhs;
	string token;

	exp = ReadC(scanner);

	token = ReadToken(scanner);
	
	if (StringEqual(token, "*") || StringEqual(token, "/")) {
		rhs = ReadT(scanner);
		exp = NewCompoundExp(token[0], exp, rhs);
	}
	else
		SaveToken(scanner, token);

	return exp;
}

expADT ReadC(scannerADT scanner) {
	expADT exp;
	//string token = ReadToken(scanner);
	exp = ReadF(scanner);

	string token = ReadToken(scanner);

	if (StringEqual(token, "("))
		exp = NewCallExp(GetCallExp(exp), ReadE(scanner, 0));
	else
		SaveToken(scanner, token);

	return exp;		
}

expADT ReadF(scannerADT scanner) {
	expADT exp;
	string token = ReadToken(scanner);

	if (StringEqual(token, "(")) {
		exp = ReadE(scanner);
		ReadToken(scanner);
	}
	else if (isdigit(token[0]))
		exp = NewIntegerExp(StringToInteger(token));
	else if (isalpha(token[0])) {
		if (StringEqual(token, "func")) {
			exp = ReadNewFunc(scanner);
		}
		else if (StringEqual(token, "if")) {
			exp = ReadControlStructure(scanner);
		}
		else {
			exp = NewIdentifierExp(token);
		}
	}
	else
		Error("Illegal term in expression");

	return exp;
}

expADT ReadNewFunc(scannerADT scanner) {
	expADT exp;

	ReadToken(scanner); // Read the "("

	string arg = ReadArguments(scanner);

	ReadToken(scanner); // Read the ")"
	ReadToken(scanner); // Read the "{"

	expADT body = ReadE(scanner);

	ReadToken(scanner); // Read the "{"

	exp = NewFuncExp(arg, body);

	ReadToken(scanner); // Read the "}"

	return exp;
}

string ReadArguments(scannerADT scanner) {
	string arg = ReadToken(scanner);
	return arg;
}

expADT ReadControlStructure(scannerADT scanner) {
	expADT exp;
	string token;

	token = ReadToken(scanner);
	if (StringEqual(token, "if"))
		token = ReadToken(scanner);

	expADT expPre = ReadE(scanner);
	string relOp = ReadToken(scanner);
	expADT expPost = ReadE(scanner);

	string thenKeyWord = ReadToken(scanner);
	if (!StringEqual(thenKeyWord, "then"))
		Error("Syntactical error in 'If' statement!");

	expADT expThen = ReadE(scanner);

	string elseKeyWord = ReadToken(scanner);
	if(!StringEqual(elseKeyWord, "else"))
		Error("Syntactical error in 'If' statement!");

	expADT expElse = ReadE(scanner);

	exp = NewIfExp(expPre, relOp, expPost, expThen, expElse);

	return exp;
}

int Precedence(string token)
{
	if (StringLength(token) > 1) return (0);
	switch (token[0]) {
	case '=': return (1);
	case '+': case '-': return (2);
	case '*': case '/': return (3);
	default:  return (0);
	}
}
