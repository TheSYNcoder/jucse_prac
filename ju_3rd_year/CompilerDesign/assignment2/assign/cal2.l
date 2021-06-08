%{
int type;
%}
%%

[ \t]*Morning,[ \t]* {printf("Good morning, ");}
[ \t]*Afternoon,[ \t]* { printf("Good evening, ");}
[ \t]*I[ \t]* {printf(" I ");}
[ \t]*am[ \t]* {printf(" am ");}
[ \t]*[a-zA-Z]*[ \t]* { yylval.string = strdup(yytext); return name;}
\n      ;
([a-zA-Z0-9])+ 	{printf("%s", yytext);}
.       ;

%%

int yywrap(void)
{
 return 1;
}

int main(){
	yylex();
	printf("Number of lines : %d\n", num_lines);
	printf("Number of characters : %d\n", num_chars);
	printf("Number of words : %d\n", num_words);
}