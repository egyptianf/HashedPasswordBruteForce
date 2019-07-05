#include<stdio.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>
#include<math.h>
#include <stdlib.h>
#ifdef _OPENMP
#include <omp.h>
#endif
int error(){
    printf("Usage: ./crack hash threads_number\n");
    return 1;
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
//Returns 1 when found
char *brute_force(int digits, int base, char* plaintext, char *salt, char *hashed, char *hashed_plaintext)
{  
    int *ascii_chars = malloc(sizeof(int) * digits);
    //Inititialization
    int i, index;
    for(i=0; i<digits; i++)
        ascii_chars[i] = 65;//A=65 in ASCII
    int permutations =(int) pow(base, digits);
    for(i=1; i<= permutations; i++)
    {
        //If conditions for each digit starting from the least significant digit
        for(index= digits-1; index>=0; index--)
        {
            plaintext[index] = ascii_chars[index];
            if( (i % ((int) pow(base,(digits-1-index)))) == 0)
                ascii_chars[index] = get_next_char(ascii_chars[index]);//need to be changed
        }
        hashed_plaintext = crypt(plaintext, salt);
        if(match(plaintext, hashed_plaintext, hashed))
            return plaintext;
        //puts(plaintext);
    }
    free(ascii_chars);
    return NULL;
}
void Hello(void){
    #ifdef _OPENMP
    int my_rank = omp_get_thread_num();
    int thread_count = omp_get_num_threads();
    #else
    int my_rank = 0;
    int thread_count = 1;
    #endif
    printf("Hello from thread %d form %d\n", my_rank, thread_count);
}
int main(int argc, char** argv)
{
    if(argc != 3)
        return error();
    char *hashed = argv[1], salt[2],  thread_count = strtol(argv[2], NULL, 10);;
    salt[0]= hashed[0]; salt[1]=hashed[1];
    char plaintext[5]= "AAAAA";//A:65 in ASCII and Z:90, a:97 and z:122
    char *hashed_plaintext = crypt(plaintext, salt);
    if(strcmp(hashed_plaintext, hashed) == 0)
    {
        puts(plaintext);
        return 0;
    }
    //If we're using a password of 5 digits
    int digits, base=52;//(26+26)for capital and small english letters.
    digits = strlen(plaintext);
    char *password;


    /*Testing Suite */
    #pragma omp parallel num_threads(thread_count)
    Hello();

    /*End testing suite */

    //This will start by a gussing a password of 1 digit, then 2, then 3, etc..
    // int i;
    // for(i=1; i<=digits; i++)
    // {
    //     password = brute_force(i, base, plaintext, salt, hashed, hashed_plaintext);
    //     if(password != NULL)
    //         break;
    // }



    // if(password == NULL){
    //     puts("Sorry, nothing found!");
    //     return 1;
    // }
    // puts(password);
    return 0;
}