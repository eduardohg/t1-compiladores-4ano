%option noyywrap
%x COMMENT
%option header-file="lexico.yy.h"
%option outfile="lexico.yy.c"

%{
#include <stdio.h>
#include <string.h>
#include "sintatico.tab.h"

%}


%%


"Grafo" {return(GRAPH);}
"K"     {return(K);}
":"     {return(COLON);}
"="     {return(ASSIGN);}
"-->"   {return(EDGE);}
"<->"   {return(MOVE);}
" "     {}
[\t]    {}
[\n]    {return(END_LINE);}
[0-9]+  {yylval.int_t = strtod(yytext, NULL); return(NUM);}
.       {printf("Erro lexico"); exit(0);}
<<EOF>> {return(END_FILE);}


%%
