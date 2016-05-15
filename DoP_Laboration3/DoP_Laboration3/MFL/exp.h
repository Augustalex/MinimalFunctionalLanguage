/*
 * File: exp.h
 * -----------
 * This interface defines an abstract type for expressions in MFL,
 * which allows the client to represent and manipulate
 * expression trees.
 */

#ifndef _exp_h
#define _exp_h

#include "genlib.h"

/*
 * Type: expADT
 * -------------------
 * This type is used to represent the abstract notion of any
 * expression in MFL.
 *
 *   E -> T + E
 *   E -> T - E
 *   E -> T
 *
 *   T -> C * T
 *   T -> C / T
 *   T -> C
 *
 *   C -> F (E)
 *   C -> F
 *
 *   F -> (E)
 *   F -> if E RelOp E then E else E
 *   F -> func (identifier) { E }
 *   F -> integer
 *   F -> identifier
 *
 *   RelOp -> =
 *   RelOp -> <
 *   RelOp -> >
 *
 */

typedef struct expCDT *expADT;

/*
 * Type: exptypeT
 * --------------
 * This enumeration type is used to differentiate the expression types.
 */

typedef enum {
    FuncExp,
    IfExp,
    CallExp,
    ConstExp,
    IdentifierExp,
    CompoundExp
} exptypeT;

/* expADT constructor functions */

expADT NewFuncExp(string arg, expADT body);
expADT NewIfExp(expADT lhs, char relOp, expADT rhs, expADT ifPart, expADT elsePart);
expADT NewCallExp(expADT func, expADT arg);
expADT NewIntegerExp(int n);
expADT NewIdentifierExp(string id);
expADT NewCompoundExp(char op, expADT lhs, expADT rhs);

/* expADT selector functions */
exptypeT ExpType(expADT exp);

/*  For FuncExprExp */
string GetFuncFormalArg(expADT exp);
expADT GetFuncBody(expADT exp);

/*  For IfExp */
expADT GetIfLHSExpression(expADT exp);
expADT GetIfRHSExpression(expADT exp);
char   GetIfRelOp(expADT exp);
expADT GetIfThenPart(expADT exp);
expADT GetIfElsePart(expADT exp);

/*  For FuncCallExp */
expADT GetCallExp(expADT exp);
expADT GetCallActualArg(expADT exp);

/*  For ConstExp */
int ExpInteger(expADT exp);

/*  For IdentifierExp */
string ExpIdentifier(expADT exp);

/*  For CompoundExp */
char ExpOperator(expADT exp);
expADT ExpLHS(expADT exp);
expADT ExpRHS(expADT exp);

#endif
