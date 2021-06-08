%{
    #include <stdio.h>
    #include <math.h>
    int yylex();
    void yyerror(char *);
    #include "number.h"
    extern char FLOAT_TYPE;
    extern char INT_TYPE;
    extern int error_flag;
%}

%union { 
    struct number p;    
}
%token<p> num
%token PLUS MINUS
%token MUL AND OR
%token ERROR
%left OR AND
%left PLUS MINUS
%left MUL '/'
%nonassoc uminu
%type<p>exp

%%


ss: exp  { 
                if ( $1.type == INT_TYPE ){
                    if(!error_flag) printf("Answer is %d\n" , $1.ival );
                }
                else{
                    if(!error_flag) printf("Answer is %.2f\n", $1.fval );
                    
                }
         }


exp: exp PLUS exp      { 
                        
                        if ( $1.type == FLOAT_TYPE || $3.type == FLOAT_TYPE ) $$.type = FLOAT_TYPE;
                        else $$.type = INT_TYPE;

                        if ($$.type == FLOAT_TYPE){
                            $$.fval = $1.fval + $3.fval + $1.ival + $3.ival; 
                            $$.ival = 0; 
                        }
                        else {
                            $$.ival = $1.ival + $3.ival; 
                            $$.fval = 0;
                        }
                    }
    | exp MINUS exp     {
                         if ( $1.type == FLOAT_TYPE || $3.type == FLOAT_TYPE ) $$.type = FLOAT_TYPE;
                         else $$.type = INT_TYPE;

                         if ($$.type == FLOAT_TYPE) $$.fval = $1.ival + $1.fval - ( $3.ival + $3.fval ), $$.ival = 0;
                         else $$.ival = $1.ival - $3.ival, $$.fval = 0;
                    }
    | exp MUL exp     {
                         if ( $1.type == FLOAT_TYPE || $3.type == FLOAT_TYPE ) $$.type = FLOAT_TYPE;
                         else $$.type = INT_TYPE;

                         if ($$.type == FLOAT_TYPE) $$.fval = ($1.ival + $1.fval) * ($3.ival + $3.fval), $$.ival = 0;
                         else $$.ival = $1.ival * $3.ival, $$.fval = 0;
                    }
    | exp OR exp     {
                         if ( ($1.type != INT_TYPE) || ($3.type != INT_TYPE )){
                             printf("Boolean operator | supports only int data types but float    given");
                         }
                         else{
                             $$.type = INT_TYPE;
                             $$.fval = 0; $$.ival = $1.ival |  $3.ival;
                         }
                    }
    | exp AND exp     {
                          if ( ($1.type != INT_TYPE) || ($3.type != INT_TYPE )){
                              printf("Boolean operator & supports only int data types but    float given");
                          }
                          else{
                              $$.type = INT_TYPE;
                              $$.fval = 0; $$.ival = $1.ival &  $3.ival;
                          }
                    }
    | MINUS exp        {
                         $$.type = $2.type;
                         if ( $$.type == FLOAT_TYPE ) $$.fval = -$2.fval, $$.ival = 0;
                         else $$.ival = -$2.ival, $$.fval = 0;

                    }
    | num           ;
    | '(' exp')'    {
                         $$.type = $2.type;
                         if ( $$.type == FLOAT_TYPE ) $$.fval = $2.fval, $$.ival = 0;
                         else $$.ival = $2.ival, $$.fval = 0;
                    }

%%

int main(){
    do{
        error_flag = 0;
        printf("Enter expression : ");
        yyparse();
    }while(1);
}


void yyerror(char * s){
    error_flag=1;
    printf("SYNTAX ERROR\n");
}
