#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <editline/readline.h>
#include <editline/history.h>

int main(int argc, char* argv[]){
    puts("MyLisp Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    char* input;

    while((input = readline("MyLisp> "))!= NULL){

        // store input
        add_history(input);
        printf("No you're a %s\n", input);
    
        free(input);
    }
    puts("\nUnexpected end of file.");
    
    return 0;
}