
%%

[Aa]+[bB]+ {printf("Valid String\n");}
.        {printf("Invalid String\n"); exit(0);}
%%
int yywrap(){
    return 0;
}

int main(){
    yylex();
    return 0;
}
