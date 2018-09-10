#include <stdio.h>
#include <stdlib.h>


static char input[2048];

int main(int argc, char* argv[]){
    puts("MyLisp Version 0.0.0.0.1");
    puts("Press Ctrl+c to Exit\n");

    for(;;){
        // prompt
        fputs("MyLisp> ", stdout);

        // get input
        fgets(input, 2048, stdin);

        // echo response
        printf("No you're a %s", input);
    }
    
    return 0;
}