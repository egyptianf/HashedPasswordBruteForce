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
    {
        puts(plaintext);
        return 1;
    }
    return 0;
}
int main(int argc, char** argv)
{
    if(argc != 2)
        return error();

    char *hashed = argv[1], *salt = "00";
    char plaintext[5]= "AAAAA";//A:65 in ASCII and Z:90, a:97 and z:122
    char *hashed_plaintext = crypt(plaintext, salt);

    if(strcmp(hashed_plaintext, hashed) == 0)
    {
        puts(plaintext);
        return 0;
    }

    //If we're using a password of 5 digits
    int digits;
    digits = strlen(plaintext)+0.0;
    
    int digit1=0, digit2=0, digit3=0, digit4=0, digit5=0;
    int *ascii_chars = malloc(sizeof(int) * digits);
    //Inititialization
    int i;
    for(i=0; i<digits; i++)
        ascii_chars[i] = 0;


    int permutations =(int) pow(10.0, digits);
    for(i=1; i<= permutations; i++)
    {
        //If conditions for each digit except the least significant digit

        int index;
        for(index= digits-1; index>=0; index--)
        {
            plaintext[index] = ascii_chars[index] + '0';
            if( (i % ((int) pow(10.0,(digits-1-index)))) == 0)
                ascii_chars[index] = (ascii_chars[index] + 1)%10;
        }






        // //Leaset significant bit digit
        // plaintext[4] = digit1 + '0';
        // digit1 = (digit1+1)%10;

        // plaintext[3] = digit2 + '0';
        // if((i%10) == 0)
        //     digit2 = (digit2+1)%10;
        
        // plaintext[2] = digit3 + '0';
        // if((i%100)==0)
        //     digit3 = (digit3+1)%10;
    
        // plaintext[1] = digit4 + '0';
        // if((i%1000)==0)
        //     digit4 = (digit4+1)%10;
        // plaintext[0] = digit5 + '0';
        // if((i%10000)==0)
        //     digit5 = (digit5+1)%10;


        //puts(plaintext);
    }
    free(ascii_chars);
    return 0;
}