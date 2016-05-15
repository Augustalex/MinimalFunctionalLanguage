/*
 * File: print.h
 * -------------
 * Pretty printer for expressions and values.
 */

#ifndef _print_h
#define _print_h

#include "exp.h"
#include "value.h"

/* Pretty print a MFL expression. */
void PrintExp(expADT exp);

/* Pretty print a MFL value. */
void PrintValue(valueADT value);

#endif
