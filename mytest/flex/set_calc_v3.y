%{
    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>
    #include <stdarg.h>

    #define NAME_SIZE 100
    #define CHAR_SET_SIZE 26

    extern int yylineno; /* from lexer */
    int yylex();
    void yyerror(char *s, ...)
    {
        va_list ap;
        va_start(ap, s);

        fprintf(stderr, "%d: error: ", yylineno);
        vfprintf(stderr, s, ap);
        fprintf(stderr, "\n");
    }

    struct Symbol
    {
        char name;
        char value[CHAR_SET_SIZE];
    };

    struct Symbol symbol_table[26];
    char temp_char_set[CHAR_SET_SIZE];
    char factor_char_set[CHAR_SET_SIZE];
    char expr_char_set[CHAR_SET_SIZE];

    struct Symbol* NewSymbol()
    {
        struct Symbol* symbol =  (struct Symbol*)malloc(sizeof(struct Symbol));
        symbol->name = 0;
        memset(symbol->value, 0, sizeof(symbol->value));
    }

    void PrintCharSet(char name, const char* char_set)
    {
        printf("%c: [", name);
        int need_comma = 0;
        for(int i=0; i< CHAR_SET_SIZE; i++)
        {
            if(char_set[i] != 0)
            {
                if(need_comma == 1)
                {
                    printf(",");
                }
                printf("%c", char_set[i]);
                need_comma = 1;
            }
        }
        printf("]\n");
    }

    void PrintSymbol(const struct Symbol* symbol)
    {
        PrintCharSet(symbol->name, symbol->value);
    }

    void Union(char* result_char_set, const char* char_set_1, const char* char_set_2)
    {
        memcpy(result_char_set, char_set_1, CHAR_SET_SIZE);
        for(int i=0; i<CHAR_SET_SIZE; i++)
        {
            if(char_set_2[i] != 0)
            {
                result_char_set[i] = char_set_2[i];
            }
        }
    }

    void Intersect(char* result_char_set, const char* char_set_1, const char* char_set_2)
    {
        for(int i=0;i <CHAR_SET_SIZE; i++)
        {
            if(char_set_1[i] != char_set_2[i] || char_set_1[i] == 0)
            {
                result_char_set[i] = 0;
            }else
            {
                result_char_set[i] = char_set_1[i];
            }
        }
    }

    void Substract(char* result_char_set, const char* char_set_1, const char* char_set_2)
    {
        for(int i=0;i <CHAR_SET_SIZE; i++)
        {

            if(char_set_1[i] == 0 || char_set_1[i] == char_set_2[i])
            {
                result_char_set[i] = 0;
            }else
            {
                result_char_set[i] = char_set_1[i];
            }
        }
    }
%}

%union
{
    char name;
    char element;
    char* char_set;
}

%token PRINT
%token <name> IDENTIFIER
%token <element> CHAR
%token COMMA
%token LEFT_BRACKET
%token RIGHT_BRACKET
%token ASSIGN
%token UNION
%token INTERSECT
%token SUBSTRACT
%token NEWLINE

%type <char_set> char_list init_list factor expr

%%

language: /* nothing */
    | language statement NEWLINE
    | language NEWLINE  /*允许空行出现*/

statement: PRINT IDENTIFIER { PrintSymbol(&symbol_table[$2 - 'A']); }
    | IDENTIFIER ASSIGN init_list { symbol_table[$1-'A'].name = $1; memcpy(symbol_table[$1-'A'].value, $3, CHAR_SET_SIZE); }
    | IDENTIFIER ASSIGN expr      { symbol_table[$1-'A'].name = $1; memcpy(symbol_table[$1-'A'].value, $3, CHAR_SET_SIZE); }

expr: factor { $$ = expr_char_set; memcpy($$, $1, CHAR_SET_SIZE); }
    | expr SUBSTRACT factor { Substract($$, $1, $3); }

factor: IDENTIFIER { $$ = factor_char_set; memcpy($$, symbol_table[$1-'A'].value, CHAR_SET_SIZE); }
    | factor UNION IDENTIFIER { Union($$, $1, symbol_table[$3-'A'].value); }
    | factor INTERSECT IDENTIFIER  { Intersect($$, $1, symbol_table[$3-'A'].value); }

init_list: LEFT_BRACKET char_list RIGHT_BRACKET  { $$ = $2; }

char_list: CHAR { $$ = temp_char_set; memset($$, 0, 26); $$[$1-'a'] = $1; }
    | char_list COMMA CHAR  { $$[$3-'a'] = $3; }

%%

int main(int argc, char ** argv)
{
    yyparse();
}
