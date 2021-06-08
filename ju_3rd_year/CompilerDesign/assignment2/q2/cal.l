%{
    #include<math.h>
    #include"number.h"
    char INT_TYPE=1;
    char FLOAT_TYPE=2;
    int error_flag=0;
    #include"y.tab.h"
%}
%%
[0-9]+\.[0-9][0-9][0-9]+  {
                            printf("Float type match with more than 2 digs %s\n", yytext);
                            printf("ONLY 2 DECIMAL DIGITS SUPPORTED\n");
                            return ERROR;
                         }
[0-9]+\.[0-9][0-9]? {
                            //printf("Float type match with less than 2 digs %s\n" , yytext);
                            yylval.p.fval = atof(yytext);
    
                            yylval.p.type = 2;
                            yylval.p.ival = 0;
                            return num;
                        }  
[0-9]+                  {
                            //printf("INteger type match %s\n", yytext);
                            yylval.p.ival = atoi(yytext);
                            yylval.p.fval = 0;
                            yylval.p.type =1;
                            return num;
                        }
[ \t]*\+[ \t]* { return PLUS;}
[ \t]*\-[ \t]* { return MINUS;}
[ \t]*\*[ \t]* { return MUL;}
[ \t]*\|[ \t]* { return OR;}
[ \t]*\&[ \t]* { return AND;}
[\t] ;
\n return 0;
. return yytext[0];
%%

int yywrap(){
    return 0;
}
