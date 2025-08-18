%{
#include "y.tab.h"
%}
alpha [a-zA-Z]
num [0-9]
%%
{alpha}({alpha}|{num}|"_")*   { return ID; }
"+"				{return PLUS; }
"-"				{return MINUS; }
"*"				{return MUL;}
"/"				{return DIV;}
"("				{return OB;}
")"				{return CB;}
"\n"            {return NL;}
[ \t]                  { /* ignore whitespace */ }
.                        { return yytext[0]; }
%%

