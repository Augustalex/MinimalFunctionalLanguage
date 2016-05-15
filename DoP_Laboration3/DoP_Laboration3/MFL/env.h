/*
 * File: env.h
 * ------------
 * This file is the interface to the environment module, which
 * represents the environment (set of definitions) available
 * in a certain lexical scope in MFL.
 */

#ifndef _environment_h
#define _environment_h

#include "genlib.h"

typedef struct environmentCDT *environmentADT;

/* Forward declare expADT and valueADT. */
typedef struct expCDT   *expADT;
typedef struct valueCDT *valueADT;

/*
 * Function: NewEnvironment
 * Usage: environmentT env = NewEnvironment();
 * ---------------------------
 * This function creates a new program environment.
 * All definitions are initially undefined.
 */
environmentADT NewEnvironment();

/*
 * Function: NewClosure
 * Usage: environmentT env = NewClosure(parent);
 * ---------------------------
 * This function creates a new program environment
 * that inherits definitions from its parent environment.
 * Inherited definitions can be overriden by local
 * definitions. The parent environment is not modified.
 */
environmentADT NewClosure(environmentADT parent);

/*
 * Function: GetIdentifierValue
 * Usage: value = GetIdentifierValue(env, name);
 * ----------------------------------------
 * This function returns the value of an identifier.
 * The value will be in the form of a function call
 * value, a closure, that when called evaluates the
 * the expression.
 */

valueADT GetIdentifierValue(environmentADT env, string name);

/*
 * Function: SetIdentifier
 * Usage: SetIdentifier(env, name, exp, ctx);
 * ---------------------------------------
 * This function sets the identifier to name the specified expression exp in
 * the environment env. The expression will be evaluated in the context ctx.
 * For global definitions env and ctx will be the same but this is not always
 * the case, e.g. for actual arguments in function calls.
 */

void DefineIdentifier(environmentADT env, string name, expADT exp, environmentADT context);

#endif
