/*
 * File: value.h
 * ------------
 */

#ifndef _value_h
#define _value_h

#include "exp.h"
#include "env.h"

/*
 * Type: valuetypeT
 * --------------
 * This enumeration type is used to differentiate the value types.
 */

typedef enum {
    FuncValue,
    IntValue
} valuetypeT;

/*
 * Type: valueADT
 * -------------------
 * This type is used to represent the abstract notion of any
 * value in MFL.
 */
typedef struct valueCDT *valueADT;

/* valueADT constructor functions */

valueADT NewFuncValue(string arg, expADT body, environmentADT closure);
valueADT NewIntegerValue(int val);

/* valueADT selector functions */
valuetypeT ValueType(valueADT value);

/*  For IntValue */
int GetIntValue(valueADT value);

/* For FuncValue */
environmentADT GetFuncValueClosure(valueADT value);
string         GetFuncValueFormalArg(valueADT value);
expADT         GetFuncValueBody(valueADT value);

#endif
