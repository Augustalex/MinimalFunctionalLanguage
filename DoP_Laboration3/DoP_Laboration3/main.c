#include "parser.h"
#include "print.h"
#include "symtab.h"
#include "exp.h"
#include "exception.h"
#include "value.h"


main()
{
	scannerADT scanner;
	expADT exp;
	string line;
	InitVariableTable();
	scanner = NewScanner();
	SetScannerSpaceOption(scanner, IgnoreSpaces);
	while (TRUE) {
		try {
			printf("=> ");
			line = GetLine();
			if (StringEqual(line, ":quit")) exit(0);
			SetScannerString(scanner, line);
			exp = ParseExp(scanner);
			valueADT value = EvalExp(exp);
			PrintValue(value);
			except(ErrorException)
				printf("Error: %s\n", (string)GetExceptionValue());
		} endtry
	}
}