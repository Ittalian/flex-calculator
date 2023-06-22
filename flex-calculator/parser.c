/*15820094 嘉松一汰*/

/* parser for simple expressions */
/* Grammar:
   Statement → Expression ';'
   Expression → Term '+' Term
                Expression-Term
              | Term
   Term → number
*/

#include <stdio.h>
#include <stdlib.h>
#include "scanner.h"

token nextToken;

int Statement();  // forward declarations
int Expression(); // (also needed for
int Term();       //  mutual recursion)


int main () {    
    initScanner();
    nextToken = getNextToken(); // get first token
    Statement();
    
    return 0;
}

int Statement() {
    int value = Expression();

    if (nextToken.type == semicolon) {    //
        printf ("Result is %d\n", value);
        // semicolon is last token, so we do not need a next one,
        // but this needs to be uncommented if we have multiple statements
        // nextToken = getNextToken();
    }
    else printf("Error: Missing semicolon!\n"), exit(1);
}

int Expression() {  /*演算子判別*/
    int r = Term();

    while(nextToken.type == plus || nextToken.type == hyphen||nextToken.type == pipe){

   if (nextToken.type == plus) {
         nextToken = getNextToken();
         r += Term();
        }
        else if (nextToken.type == hyphen) {
          nextToken = getNextToken();
          r -=Term();
        }
    }
    return r;
}

int Term() {
    int r;

    while(nextToken.type == number||nextToken.type == asterisk||nextToken.type == slash||nextToken.type == tilde||nextToken.type == ampersand){

        if (nextToken.type == number) {
        r = nextToken.val.iv;
        nextToken = getNextToken();
        
        }
        else if(nextToken.type == asterisk){
            nextToken = getNextToken();
            
             r  =r*nextToken.val.iv;
            
             nextToken = getNextToken();
        }
        else if(nextToken.type == slash){
            nextToken = getNextToken();
             r  /=nextToken.val.iv;
             nextToken = getNextToken();
        }
        else if(nextToken.type == ampersand){
            nextToken = getNextToken();
            
             r  =r*nextToken.val.iv;
            
             nextToken = getNextToken();
        }
        
        else printf("Error: Number expected but not found!\n"), exit(1);
    }

    return r;
}
