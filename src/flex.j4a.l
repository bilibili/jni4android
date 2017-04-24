%{
#include <inttypes.h>
#include "j4a__yy.h"
#include "j4a_object.h"
#include "j4a_string.h"
#include "j4a_string_pool.h"
#include "bison.j4a.tab.hpp"
%}
%option yylineno
%option noyywrap

ID              ([a-zA-Z_][a-zA-Z0-9_]*)
INTEGER         ([0-9]*)
WHITESPACE      ([ \t\v\r\n])

%%

","                         {return yytext[0];}
"."                         {return yytext[0];}
";"                         {return yytext[0];}
"{"                         {return yytext[0];}
"}"                         {return yytext[0];}
"["                         {return yytext[0];}
"]"                         {return yytext[0];}
"("                         {return yytext[0];}
")"                         {return yytext[0];}
"@"                         {return yytext[0];}

"package"                   {return T_PACKAGE;}
"import"                    {return T_IMPORT;}

"boolean"                   {return T_BOOLEAN;}
"byte"                      {return T_BYTE;}
"float"                     {return T_FLOAT;}
"double"                    {return T_DOUBLE;}
"char"                      {return T_CHAR;}
"short"                     {return T_SHORT;}
"int"                       {return T_INT;}
"long"                      {return T_LONG;}
"void"                      {return T_VOID;}

"private"                   {return T_PRIVATE;}
"protected"                 {return T_PROTECTED;}
"public"                    {return T_PUBLIC;}

"abstract"                  {return T_ABSTRACT;}
"final"                     {return T_FINAL;}
"static"                    {return T_STATIC;}

"class"                     {return T_CLASS;}
"interface"                 {return T_INTERFACE;}

\n                          {yylineno++;}
{WHITESPACE}                {;}
{INTEGER}                   {FLEX_LOGF("<integer>:%s\n", yytext); yylval.string = j4a::make_managed_str_ptr(yytext); return T_INTEGER_LITERAL;}
{ID}                        {FLEX_LOGF("<id>:%s\n", yytext); yylval.string = j4a::make_managed_str_ptr(yytext); return T_ID;}
<<EOF>>                     {yyterminate(); return T_EOF;}
.                           {FLEX_LOGF("Unknown token at line %d: '%s'\n", yylineno, yytext); yyterminate();}

%%
