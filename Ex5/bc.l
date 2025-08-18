%{
    #include "y.tab.h"
    #include <string.h>
%}
digit [0-9]
int {digit}+
float {digit}+"."{digit}*|{digit}*"."{digit}+
%s bm
%%
[ \t]+      ;
{float} {yylval.dval = atof(yytext); BEGIN bm; return FCONST;}
{int}   {yylval.ival = atoi(yytext); BEGIN bm; return ICONST;}
"^"     {BEGIN 0; return EXP;}
"*"     {BEGIN 0; return MUL;}
"/"     {BEGIN 0; return DIV;}
"+"     {BEGIN 0; return PLUS;}
<bm>"-" {BEGIN 0; return MINUS;}
"-"     {return UMINUS;}
"("     {BEGIN 0; return OB;}
")"     {BEGIN bm; return CB;}
"\n"     {BEGIN 0; return NL;}
.       {return yytext[0];}
%%