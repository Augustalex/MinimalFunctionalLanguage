/*
 * File: exp.c
 * -----------
 * This file implements the exp.h interface.  The exported
 * functions are standard constructor and selector functions
 * that require no individual documentation.
 */

#include "exp.h"

#include <stdio.h>
#include "genlib.h"
#include "strlib.h"

/*
 * Type: expCDT
 * -------------------
 */
struct expCDT {
    exptypeT type;
    union {
        struct {
            string arg;
            expADT body;
        } funcRep;
		struct {
			expADT lhs;
			expADT rhs;
			char   relOp;
			expADT thenPart;
            expADT elsePart;
		} ifRep;
        struct {
            expADT func;
            expADT arg;
        } callRep;
        int intRep;
        string idRep;
        struct {
            char   op;
            expADT lhs;
            expADT rhs;
        } compoundRep;
    } value;
};

/* expADT constructor functions */

expADT NewFuncExp(string arg, expADT body)
{
	expADT exp;

    exp = New(expADT);
    exp->type = FuncExp;
    exp->value.funcRep.arg  = CopyString(arg);
    exp->value.funcRep.body = body;
    return exp;
}

expADT NewIfExp(expADT lhs, char relOp, expADT rhs, expADT thenPart, expADT elsePart)
{
	expADT exp;

    exp = New(expADT);
    exp->type = IfExp;
    exp->value.ifRep.lhs = lhs;
    exp->value.ifRep.rhs = rhs;
    exp->value.ifRep.relOp = relOp;
    exp->value.ifRep.thenPart = thenPart;
    exp->value.ifRep.elsePart = elsePart;

    return exp;
}

expADT NewCallExp(expADT func, expADT arg)
{
	expADT exp;

    exp = New(expADT);
    exp->type = CallExp;
    exp->value.callRep.func = func;
    exp->value.callRep.arg  = arg;

    return exp;
}

expADT NewIntegerExp(int n)
{
    expADT exp;

    exp = New(expADT);
    exp->type = ConstExp;
    exp->value.intRep = n;
    return (exp);
}

expADT NewIdentifierExp(string id)
{
    expADT exp;

    exp = New(expADT);
    exp->type = IdentifierExp;
    exp->value.idRep = CopyString(id);
    return (exp);
}

expADT NewCompoundExp(char op,
                         expADT lhs,
                         expADT rhs)
{
    expADT exp;

    exp = New(expADT);
    exp->type = CompoundExp;
    exp->value.compoundRep.op = op;
    exp->value.compoundRep.lhs = lhs;
    exp->value.compoundRep.rhs = rhs;
    return (exp);
}

/* expADT selector functions */

exptypeT ExpType(expADT exp)
{
	return exp->type;
}


string GetFuncFormalArg(expADT exp)
{
    if (ExpType(exp) != FuncExp) {
        Error("Function value expression required");
    }
	return exp->value.funcRep.arg;
}

expADT GetFuncBody(expADT exp)
{
    if (ExpType(exp) != FuncExp) {
        Error("Function value expression required");
    }
	return exp->value.funcRep.body;
}


expADT GetIfLHSExpression(expADT exp)
{
    if (ExpType(exp) != IfExp) {
        Error("If expression required");
    }
	return exp->value.ifRep.lhs;
}

expADT GetIfRHSExpression(expADT exp)
{
    if (ExpType(exp) != IfExp) {
        Error("If expression required");
    }
	return exp->value.ifRep.rhs;
}

char GetIfRelOp(expADT exp)
{
    if (ExpType(exp) != IfExp) {
        Error("If expression required");
    }
	return exp->value.ifRep.relOp;
}

expADT GetIfThenPart(expADT exp)
{
    if (ExpType(exp) != IfExp) {
        Error("If expression required");
    }
	return exp->value.ifRep.thenPart;
}

expADT GetIfElsePart(expADT exp)
{
    if (ExpType(exp) != IfExp) {
        Error("If expression required");
    }
	return exp->value.ifRep.elsePart;
}

expADT  GetCallExp(expADT exp)
{
    if (ExpType(exp) != CallExp) {
        Error("Call expression required");
    }
	return exp->value.callRep.func;
}

expADT GetCallActualArg(expADT exp)
{
    if (ExpType(exp) != CallExp) {
        Error("Call expression required");
    }
	return exp->value.callRep.arg;
}

int ExpInteger(expADT exp)
{
    if (ExpType(exp) != ConstExp) {
        Error("Integer expression required");
    }
    return (exp->value.intRep);
}

string ExpIdentifier(expADT exp)
{
    if (ExpType(exp) != IdentifierExp) {
        Error("Identifier expression required");
    }
    return (exp->value.idRep);
}

char ExpOperator(expADT exp)
{
    if (ExpType(exp) != CompoundExp) {
        Error("Compound expression required");
    }
    return (exp->value.compoundRep.op);
}

expADT ExpLHS(expADT exp)
{
    if (ExpType(exp) != CompoundExp) {
        Error("Compound expression required");
    }
    return (exp->value.compoundRep.lhs);
}

expADT ExpRHS(expADT exp)
{
    if (ExpType(exp) != CompoundExp) {
        Error("Compound expression required");
    }
    return (exp->value.compoundRep.rhs);
}
