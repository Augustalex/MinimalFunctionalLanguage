/*
 * File: eval.h
 * ------------
 * This file is the interface to the evaluator module, which
 * computes the value represented by a MFL expression.
 */

#ifndef _eval_h
#define _eval_h

#include "exp.h"
#include "value.h"
#include "env.h"

/*
 * Function: Eval
 * Usage: n = Eval(exp, env);
 * ------------------------
 * This function evaluates an expression in the given environment and returns its result.
 */

valueADT Eval(expADT exp, environmentADT env);

#endif
