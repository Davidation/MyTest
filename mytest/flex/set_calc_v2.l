%option noyywrap

%{
    #include <stdio.h>

    enum yytokentype
    {
        PRINT = 258,
        IDENTIFIER = 259,
        CHAR = 260,
        COMMA = 261,
        LEFT_BRACKET = 262,
        RIGHT_BRACKET = 263,
        ASSIGN = 264,
        UNION = 265,
        INTERSECT = 266,
        SUBSTRACT = 267,
        NEWLINE = 268
    };

    char yylval;
%}

%%

PRINT       { return PRINT; }
[A-Z]       { yylval = yytext[0]; return IDENTIFIER; }
[a-z]       { yylval = yytext[0]; return CHAR; }
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
.           { printf("unexpected token: (%s)\n", yytext); 
              return -1; }

%%


int main()
{
    int token_type;
    while(token_type = yylex())
    {
        printf("token_type: %d", token_type);
        if(token_type == IDENTIFIER || token_type == CHAR ) 
        {
            printf(", value = %c\n", yylval);
        }else
        {
            printf("\n");
        }
    }
}
