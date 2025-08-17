%{
    #include <stdio.h>
    int forstart = 0;
    int forindent = 0;
    int ifindent = 0;

%}
id [A-Za-z][A-Za-z0-9_]*
val [0-9]+
symbols [<>=]+
op [*%+/-]
%s bm
%%
"#".*           {printf("<comment, %s>\n", yytext);}
("from".*)?"import".*   {printf("<import statement, %s>\n", yytext);}
^[ \t]+         {if(forstart==0) forindent=yyleng; else ifindent=yyleng;}
"for"[ \t]+{id}[ \t]+"in"[ \t]+"range"[ \t]*"("[ \t]*({id}|{val})","[ \t]*({id}|{val})[\t ]*"):"     {printf("<for-loop>\n"); forstart = 1;}
"if"[ \t]+(({id}|{val})[ \t]*{op}[ \t]*({id}|{val}))[ \t]*{symbols}[ \t]*({val}|{id})":"                {printf("<if-statement, %s>\n", yytext); if(forstart == 1 && forindent < ifindent){printf("if inside for loop\n"); forstart= 0; ifindent = 0; forindent=0;} else printf("if not inside for");}
"else:"         {printf("<else statement, %s>\n", yytext);}
"elif".*         {printf("<else if, %s>\n",yytext);}
"print".*        {printf("<print statement, %s>\n", yytext);}
"return".*       {printf("<return statement, %s>\n", yytext);}
"def".*           {printf("<fn defn, %s>\n", yytext);}
{id}            {printf("<identifier, %s>\n", yytext); BEGIN bm;}
\".*\"|\'.*\'          {printf("<string, %s>",yytext); BEGIN 0;}
({val}*|"0")"."({val}*|"0") {printf("<float const, %s>", yytext); BEGIN bm;}
{val}           {printf("<integer value, %s>\n", yytext); BEGIN bm;}
{op}"="            {printf("<shorthand op, %s>\n", yytext); BEGIN 0;}
"+"             {printf("<plus>\n"); BEGIN 0;}
<bm>"-"         {printf("<minus>\n"); BEGIN 0;}
"-"             {printf("<unary minus>\n"); BEGIN 0;}
"*"             {printf("<mul>\n"); BEGIN 0;}
"/"             {printf("<div>\n"); BEGIN 0;}
"%"             {printf("<modulus>\n"); BEGIN 0;}
{symbols}{1}"=" {printf("<logical, %s>\n", yytext); BEGIN 0;}
^"while".*      {printf("<while loop, %s>\n",yytext);}
.                      ;
%%
int main(int argc, char** argv){
    FILE* fin;
    fin= fopen(argv[1], "r");
    yyin= fin;
    yylex();
}
