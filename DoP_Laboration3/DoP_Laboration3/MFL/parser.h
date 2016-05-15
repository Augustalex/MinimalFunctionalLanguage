/*
 * File: parser.h
 * --------------
 * This interface defines an parser for MFL.
 */

#ifndef _parser_h
#define _parser_h

#include "genlib.h"

#include "exp.h"
#include "scanadt.h"

/*
 * Function: ParseExp
 * Usage: exp = ParseExp(scanner);
 * -------------------------------
 * This function parses a MFL expression by reading tokens from
 * the scanner, which must be provided by the client.
 */

expADT ParseExp(scannerADT scanner);

#endif
