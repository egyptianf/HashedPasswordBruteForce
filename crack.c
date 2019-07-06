#include<stdio.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>
#include<math.h>
#include <stdlib.h>
int error(){
    printf("Usage: ./crack hash\n");
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
char *brute_force(int digits, int base, char *salt, char *hashed)
{
    int *ascii_chars = malloc(sizeof(int) * digits);
    char *hashed_plaintext, *plaintext= (char *)malloc(sizeof(char) * digits);
    //Inititialization
    int i, index;
    for(i=0; i<digits; i++){
        ascii_chars[i] = 65;//A=65 in ASCII
        plaintext[i] = 65;
    }
    int permutations =(int) pow(base, digits);
    for(i=2; i<= permutations; i++)
    {
        //If conditions for each digit starting from the least significant digit
        for(index= digits-1; index>=0; index--)
        {
            if( (i % ((int) pow(base,(digits-1-index)))) == 0)
                ascii_chars[index] = get_next_char(ascii_chars[index]);
            plaintext[index] = ascii_chars[index];
        }
        hashed_plaintext = crypt(plaintext, salt);
        //puts(plaintext);
        if(match(plaintext, hashed_plaintext, hashed))
        {
            free(ascii_chars);      
            return plaintext;
        }
    }
    free(ascii_chars);
    free(plaintext);
    return NULL;
}
int main(int argc, char** argv)
{
    if(argc != 2)
        return error();
    char *hashed = argv[1], salt[2];
    salt[0]= hashed[0];
    salt[1]=hashed[1];
    //If we're using a password of 5 digits
    int max_digits=5, base=52;//(26+26)for capital and small english letters.
    char *password;
    //This will start by a gussing a password of 1 digit, then 2, then 3, etc..
    int k;
    for(k=1; k<=max_digits; k++)
    {
        password = brute_force(k, base, salt, hashed);
        if(password != NULL)
            break;
    }
    if(password == NULL){
        puts("Sorry, nothing found!");
        return 1;
    }
    printf("The password is: ");
    puts(password);
    return 0;
}