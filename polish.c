#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <editline/readline.h>
#include <editline/history.h>

#include "mpc.h"

long eval_op(long x, char* op, long y){
    if((strcmp("+",op)&strcmp("add",op))==0){
        return x+y;
    } else if((strcmp("-",op)&strcmp("sub",op))==0){
        return x-y;
    } else if((strcmp("*",op)&strcmp("mul",op))==0){
        return x*y;
    } else if((strcmp("/",op)&strcmp("div",op))==0&&!(strcmp("^",op)==0)){
        return x/y;
    } else if((strcmp("^",op)&strcmp("xor",op))==0){
        return x^y;
    } else if((strcmp("&",op)&strcmp("and",op))==0){
        return x&y;
    } else if((strcmp("|",op)&strcmp("or",op))==0){
        return x|y;
    }
    fputs("Not implemented yet\n",stderr);
    return 0;
}

long eval(mpc_ast_t* t){

    // if it is a number
    if(strstr(t->tag, "number")){
        return atoi(t->contents);
    }
    // otherwise its an expression/original 
    
    // operator is 2nd child
    char* op = t->children[1]->contents;

    // store the third in x
    long x = eval(t->children[2]);

    //iterate through the rest and evaluate
    for(int i=3; strstr(t->children[i]-> tag, "expr");i++){
        x = eval_op(x, op, eval(t->children[i]));
    } 

    return x;
}

int main(int argc, char *argv[]){
    char* input;
    puts("Welcome to MinLisp 0.0.0.3");
    // create parsers
    mpc_parser_t* Number = mpc_new("number");
    mpc_parser_t* Operator = mpc_new("operator");
    mpc_parser_t* Expr = mpc_new("expr");
    mpc_parser_t* MinLisp = mpc_new("MinLisp");

    // define them
    mpca_lang(MPCA_LANG_DEFAULT,
        "                                                           \
            number : /-?[0-9]+/;                                    \
            operator : '+' | '-' | '*' | '/' | \"mul\"\"and\" | \"|\"\
            | '^' | \"&\" | \"div\" | \"add\" | \"sub\" | \"xor\" | \"or\" ; \
            expr : <number> | '(' <operator> <expr>+ ')';           \
            MinLisp : /^/ <operator> <expr>+ /$/ ;                   \
        ",
        Number, Operator, Expr, MinLisp);

    while((input = readline("MinLisp> "))!= NULL){
        add_history(input);
        mpc_result_t r;
        if(mpc_parse("<stdin>", input, MinLisp, &r)){
            // print the AST
            #ifdef INFO
            mpc_ast_print(r.output);
            #endif
            printf("  %li\n",eval(r.output));
        } else {
            // Print error
            mpc_err_print(r.error);
            mpc_err_delete(r.error);
        }
        free(input);
    }
    puts("\0");
    mpc_cleanup(4, Number, Operator, Expr, MinLisp);

    return 0;
}