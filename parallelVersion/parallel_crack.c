#include<stdio.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>
#include<math.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif
#include "error.h"



void Hello(void);
char *brute_force(int, int, char *, char *, int);
_Bool match(char *, char *, char *);
int get_next_char(int);

int main(int argc, char** argv)
{
    if(argc != 3)
        return error();
    char *hashed = argv[1], salt[2];
    salt[0]= hashed[0];
    salt[1]=hashed[1];
    int thread_count = strtol(argv[2], NULL, 10);
    



    int max_digits=5, base=52;//(26+26)for capital and small english letters.
    
    int k;
    for(k=1; k<=max_digits; k++)
    {
        
        char *password;
        printf("getting into bruteforce function at k = %d\n", k);
        password = brute_force(k, base, salt, hashed, thread_count);
        printf("finished function brute_force.\n");
        //This is not gonna work if using parallel for directive
        if(password != NULL)
           puts(password);
    }

    /*Testing Suite */
    // #pragma omp parallel num_threads(thread_count)
    // Hello();
    /*End testing suite */



    // if(password == NULL){
    //     puts("Sorry, nothing found!");
    //     return 1;
    // }
    // printf("The password is: ");
    // puts(password);
    return 0;
}

// //Returns 1 when found
char *brute_force(int digits, int base, char *salt, char *hashed, int num_threads)
{
    omp_set_num_threads(num_threads);
    
    int i, index;

        
    
    _Bool password_found=0;
    int permutations =(int) pow(base, digits);
    char *global_paliantext;
    #pragma omp parallel private(i,index)
    {
        char *local_hashed_plaintext, *local_plaintext= (char *)malloc(sizeof(char) * digits);
        int *local_ascii_chars = malloc(sizeof(int) * digits);
        int id = omp_get_thread_num();
        //Inititialization
        for(i=0; i<digits; i++){
            local_plaintext[i] = 65;
            local_ascii_chars[i] = 65;//A=65 in ASCII
        }
        //End initialization
        /*We need just to parallelize this loop!*/
        for(i=id+2; i<= permutations; i+=num_threads)
        {
            //printf("thread(%d) reached i=%d\n", id, i);
            if(password_found)
                break;
            //If conditions for each digit starting from the least significant digit
            for(index= digits-1; index>=0; index--)
            {
                if( (i % ((int) pow(base,(digits-1-index)))) == 0)
                    local_ascii_chars[index] = get_next_char(local_ascii_chars[index]);
                local_plaintext[index] = local_ascii_chars[index];
            }
            local_hashed_plaintext = crypt(local_plaintext, salt);
            //puts(plaintext);
            if(match(local_plaintext, local_hashed_plaintext, hashed))
            {

                #pragma omp critical
                {
                    password_found = 1;     
                    global_paliantext = local_plaintext;
                }
            }
            
        }
        free(local_ascii_chars);

    }

    return global_paliantext;
}
_Bool match(char *plaintext, char *hashed_plaintext, char *hashed)
{
    if(strcmp(hashed_plaintext, hashed)==0)
        return 1;
    return 0;
}
int get_next_char(int current_char)
{
    int next_char = (current_char + 1);
    if(next_char == 91)
        return 97;
    if(next_char == 123)
        return 65;
    return next_char;
}
