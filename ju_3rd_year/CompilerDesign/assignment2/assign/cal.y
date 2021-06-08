 %{
     #include <stdio.h>
     #include <stdlib.h>
     int yylex();
     void yyerror(char *);
     
 %}

%union{
    char string[100];
}
%token<string> morn itok am after NL name

%%
ss : S NL 
S : morn itok am name { printf("Good morning %s. How are you?", $4 );}
| S : after itok am name { printf("Good afternoon %s. How are you?", $4);} ;
%%

int main(){
     yyparse();
}

void yyerror(char *s){
     printf("Invalid string\n");
}