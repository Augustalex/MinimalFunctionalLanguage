/*
 * File: env.c
 * ------------
 * This file implements the environment.h interface.
 */

#include "env.h"

#include "strlib.h"
#include "symtab.h"
#include "value.h"

typedef struct environmentCDT {
	symtabADT      definitions;
    environmentADT parent;
} *environmentADT;

/* Exported entries */

environmentADT NewEnvironment()
{
	environmentADT env = New(environmentADT);
	env->definitions   = NewSymbolTable();
    env->parent        = NULL;
	return env;
}

environmentADT NewClosure(environmentADT parent)
{
	environmentADT env = New(environmentADT);
	env->definitions   = NewSymbolTable();
    env->parent        = parent;
	return env;
}

valueADT GetIdentifierValue(environmentADT env, string name)
{
    valueADT val;

	/* The identifer names a function expression to capture the closure for its expression. */
	/* The closure is not evaluated here (lazy!) - it is up to the caller to do that if needed. */
    val = (valueADT)Lookup(env->definitions, name);
    if (val == UNDEFINED && env->parent) {
        val = GetIdentifierValue(env->parent, name);
	}
    if (val == UNDEFINED) {
        Error("Unknown identifier %s", name);
    }
	return val;
}

void DefineIdentifier(environmentADT env, string name, expADT exp, environmentADT context)
{
	/* The expression is stored as an argument-less function. */
    Enter(env->definitions, name, NewFuncValue(NULL, exp, context));
}
