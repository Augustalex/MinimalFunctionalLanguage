/*
 * File: value.c
 * ------------
 * This file implements the value.h interface. The exported
 * functions are standard constructor and selector functions
 * that require no individual documentation.
 */

#include "value.h"

/*
 * Type: valueCDT
 * --------------
 */
struct valueCDT {
    valuetypeT type;
    union {
        struct {
            string         arg;
            expADT         body;
            environmentADT closure;
        } funcRep;
        int intRep;
    } value;
};

/* Exported entries */

valueADT NewFuncValue(string arg, expADT body, environmentADT closure)
{
    valueADT value;

    value = New(valueADT);
    value->type = FuncValue;
	 /* NOTE: The string is not copied here as it is assumed to be either owned
	  * by the corresponding expADT value or NULL indicating a call without argument. */
    value->value.funcRep.arg     = arg;
    value->value.funcRep.body    = body;
    value->value.funcRep.closure = closure;

    return value;
}

valueADT NewIntegerValue(int val)
{
    valueADT value;

    value = New(valueADT);
    value->type = IntValue;
    value->value.intRep = val;

    return value;
}

valuetypeT ValueType(valueADT value)
{
    return value->type;
}

int GetIntValue(valueADT value)
{
    if (ValueType(value) != IntValue) {
        Error("Integer value required");
    }
	return value->value.intRep;
}

environmentADT GetFuncValueClosure(valueADT value)
{
    if (ValueType(value) != FuncValue) {
        Error("Function value required");
    }
    return value->value.funcRep.closure;
}

string GetFuncValueFormalArg(valueADT value)
{
    if (ValueType(value) != FuncValue) {
        Error("Function value required");
    }
    return value->value.funcRep.arg;
}

expADT GetFuncValueBody(valueADT value)
{
    if (ValueType(value) != FuncValue) {
        Error("Function value required");
    }
    return value->value.funcRep.body;
}

