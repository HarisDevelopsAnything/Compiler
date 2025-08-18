%{
#include <stdio.h>
#include <stdlib.h>

void yyerror(const char *s);
int yylex();
%}

%token ID PLUS MINUS MUL DIV OB CB NL

%%
S : S E NL { printf("Valid\n"); }
  |  E NL      { printf("Valid\n"); }
  ;

E : E PLUS T	{printf("E->E+T\n");}
  | E MINUS T	{printf("E->E-T\n");}
  | T		{printf("E->T\n");}
  ;

T : T MUL F	{printf("T->T*F\n");}
  | T DIV F	{printf("T->T/F\n");}
  | F		{printf("T->F\n");}
  ;

F : OB E CB	{printf("F->(E)\n");}
  | ID { printf("F->id\n");}
  ;
%%

void yyerror(const char *s) {
    printf("Invalid\n");
    exit(1);
}

int main() {
    return yyparse();
}
