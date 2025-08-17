%{
#include<stdio.h>
%}
alpha [A-Za-z]
digit [0-9]
%%
^(("ftp"|"http"|"https")"://")?({alpha}{1,3}".")?{alpha}+"."{alpha}{2,3}("."{alpha}{2,3})?(":"{digit}{4})?	printf("%s is a valid URL\n", yytext);
({alpha}|{digit})*	printf("%s is an invalid URL\n", yytext);
.		;
%%
int main(int argc, char** argv){
	FILE* fp;
	fp = fopen(argv[1], "r");
	yyin= fp;
	yylex();
}
