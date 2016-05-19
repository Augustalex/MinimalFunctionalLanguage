#include "print.h"

void PrintExp(expADT exp)
{
	if (ExpType(exp) == FuncExp) {
		string functionName = GetFuncBody;
		printf("%s ", functionName);
	}
}

void PrintValue(valueADT value)
{

}
