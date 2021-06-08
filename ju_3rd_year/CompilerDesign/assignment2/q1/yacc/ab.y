 %{
     #include <stdio.h>
     #include <math.h>
     #include <stdlib.h>
     int yylex();
     void yyerror(char *);
 %}

%token A B NL

 %%
ss : S NL  { printf("Valid, expression"); exit(0); }
S : A S B | 
 %%

int main(){
     yyparse();
}

void yyerror(char *s){
     printf("Invalid string\n");
}
