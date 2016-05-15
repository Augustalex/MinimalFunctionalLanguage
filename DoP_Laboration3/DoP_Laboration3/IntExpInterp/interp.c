/*
 * File: interp.c
 * --------------
 * This program simulates the top level of a programming
 * language interpreter.  The program reads an expression,
 * evaluates the expression, and displays the result.
 */

#include <stdio.h>
#include "genlib.h"
#include "exception.h"
#include "strlib.h"
#include "simpio.h"
#include "exp.h"
#include "eval.h"
#include "parser.h"
#include "scanadt.h"

/* Main program */

main()
{
    scannerADT scanner;
    expressionADT exp;
    string line;
    int value;

	printf("Expression interpreter (type \"quit\" to exit)\n\n");

    InitVariableTable();
    scanner = NewScanner();
    SetScannerSpaceOption(scanner, IgnoreSpaces);
    while (TRUE) {
        try {
            printf("=> ");
            line = GetLine();
            if (StringEqual(line, "quit")) exit(0);
            SetScannerString(scanner, line);
            exp = ParseExp(scanner);
            value = EvalExp(exp);
            printf("%d\n", value);
          except(ErrorException)
            printf("Error: %s\n", (string) GetExceptionValue());
        } endtry
    }
}


