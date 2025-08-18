%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    int yylex(void);
    void yyerror(const char *s);
%}

%union {
    double dval;
    int ival;
}

%token <dval> FCONST
%token <ival> ICONST
%token ID PLUS MINUS MUL DIV EXP OB CB NL UMINUS

%left PLUS MINUS
%left MUL DIV
%right EXP
%right UMINUS

%type <dval> E T F G
%start S
%%
S: S E NL { printf("%g\n", $2); }
  | E NL  { printf("%g\n", $1); }
  ;
E: E PLUS T   { $$ = $1 + $3; }
  | E MINUS T { $$ = $1 - $3; }
  | T         { $$ = $1; }
  ;
T: T MUL F   { $$ = $1 * $3; }
  | T DIV F  { $$ = $1 / $3; }
  | F        { $$ = $1; }
  ;
F: F EXP G   { $$ = pow($1, $3); }
  | UMINUS F %prec UMINUS { $$ = -$2; }
  | G        { $$ = $1; }
  ;
G: OB E CB   { $$ = $2; }
  | FCONST   { $$ = $1; }
  | ICONST   { $$ = $1; }
  | ID       { /* You may want to handle variables here */ $$ = 0; }
  ;
%%
void yyerror(const char *s) {
    printf("Invalid\n");
    exit(1);
}
int main() {
    return yyparse();
}
