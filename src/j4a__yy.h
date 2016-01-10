/*
 * copyright (c) 2016 Zhang Rui <bbcallen@gmail.com>
 *
 * This file is part of jni4android.
 *
 * jni4android is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * jni4android is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with jni4android; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef J4A__YY__H
#define J4A__YY__H

#include <stdlib.h>
#include <stdio.h>
#include "j4a__def.h"

#define FLEX_LOGF printf
#define BISON_LOGF printf
#define BISON_DELETE(x__) do {delete x__; x__ = NULL;} while(0)

extern int yylex();
extern FILE *yyin;
extern FILE *yyout;
extern int yylineno;
inline static void yyerror(const char *s) { printf("ERROR: at line %d\n\t%s\n", yylineno, s);}

#endif
