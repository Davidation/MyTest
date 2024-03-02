%option noyywrap yylineno
%{
    #include <stdio.h>
    #include "set_calc_v3.tab.h"
    int fileno(FILE *stream);
%}

%%

PRINT       { return PRINT; }
[A-Z]       { yylval.name = yytext[0]; return IDENTIFIER; }
[a-z]       { yylval.element = yytext[0]; return CHAR; }
","         { return COMMA; }
"["         { return LEFT_BRACKET; }
"]"         { return RIGHT_BRACKET; }
"="         { return ASSIGN; }
"¡È"         { return UNION; }
"¡É"         { return INTERSECT; }
"-"         { return SUBSTRACT; }
\n          { return NEWLINE; }
"//".*      { /* omit comment*/ }
[ \t]       { /*ignore white space*/ }
.           { printf("unexpected token: (%s)\n", yytext); }

%%
