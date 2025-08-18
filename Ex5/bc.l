%{
    #include "y.tab.h"
    #include <string.h>
%}
digit [0-9]
int {digit}+
float {digit}+"."{digit}*|{digit}*"."{digit}+
%%
[ \t]+      ;
{float} {yylval.dval = atof(yytext); return FCONST;}
{int}   {yylval.ival = atoi(yytext); return ICONST;}
"^"     {return EXP;}
"*"     {return MUL;}
"/"     {return DIV;}
"+"     {return PLUS;}
"-"     {return MINUS;}
"("     {return OB;}
")"     {return CB;}
"\n"     {return NL;}
.       {return yytext[0];}
%%