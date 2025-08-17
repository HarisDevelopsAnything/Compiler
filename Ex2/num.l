%{
#include<stdio.h>
int nc=0;
int nw=0;
int nl=0;
int nic=0;
int nfc=0;
int nvi=0;
%}
num [0-9]
alpha [a-zA-Z]
%%
^{alpha}({alpha}|{num}|"_")*     {printf("<id, %s>\n", yytext); nc+=yyleng; nw+=1; nvi+=1;}
{num}+"."{num}+                   {printf("<float, %s>\n", yytext); nc+=yyleng; nw+=1; nfc+=1;}
{num}+                          {printf("<integer, %s>\n", yytext); nc+=yyleng; nw+=1; nic+=1;}
"\n"                            {printf("<newline>\n"); nl+=1;}
.				{nc+=yyleng;}
%%
int main(int argc, char** argv){
    FILE* fin;
    fin= fopen(argv[1], "r");
    yyin= fin;
    yylex();
    printf("No of characters= %d\n", nc);
    printf("No of words= %d\n", nw);
    printf("No of lines= %d\n", nl);
    printf("No of integer const= %d\n", nic);
    printf("No of float const= %d\n", nfc);
    printf("No of valid identifiers= %d\n", nvi);
}
