%{
  
  #include "y.tab.h"
%}
  
%%
[ \t]*Morning,[ \t]* {return morn;}
[ \t]*Afternoon,[ \t]* {return after;}
[ \t]*I[ \t]* {return itok;}
[ \t]*am[ \t]* {return am;}
[ \t]*[a-zA-Z]*[ \t]* { strcpy( yylval.string, yytext); return name;}

\n {return NL;}
.  ;
%%
  
int yywrap() 
{ 
  return 1; 
} 
