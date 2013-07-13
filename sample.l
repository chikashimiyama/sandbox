%{
#include <stdio.h>
%}

%%
[\t ]+ { /***/ }
[0-9]+ { printf("digit=%s",yytext); }
[a-z]+ { printf("alphabet=%s",yytext); }
\n { /*  */ }
. { printf("Syntax error\n"); }
%%
