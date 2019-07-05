#include<stdio.h>
#include<unistd.h>
#include<crypt.h>
#include<string.h>
#include<math.h>
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

    // char *hashed = argv[1], *salt = "00";
    // char plaintext[5]= "AAAAA";//A:65 in ASCII and Z:90, a:97 and z:122
    // char *hashed_plaintext = crypt(plaintext, salt);

    // if(strcmp(hashed_plaintext, hashed) == 0)
    // {
    //     puts(plaintext);
    //     return 0;
    // }

    //If we're using a password of 5 digits
    int digits =5;
    int digit;
    //Start from right to left by changing the digit by to all its possible values
    // for(digit=4; digit>=0; digit--)
    // {
    //     //2 for loops; one for uppercase and the other for lowercase letters
    //     int upper;
    //     for(upper=65; upper<91; upper++)
    //     {
    //         plaintext[digit] = upper;
    //         //puts(plaintext);
    //         hashed_plaintext = crypt(plaintext, salt);
    //         if(match(plaintext, hashed_plaintext, hashed))
    //             return 0;
    //     }
    //     int lower;
    //     for(lower=97; lower<123; lower++)
    //     {
    //         plaintext[digit] = lower;
    //         //puts(plaintext);
    //         hashed_plaintext = crypt(plaintext, salt);
    //         if(match(plaintext, hashed_plaintext, hashed))
    //             return 0;
    //     }
    // }

    //Testing
    char txt[3] = "000";
    int i;
    int digit1=0, digit2=0, digit3=0;
    int permutations = pow(10.0, 3);
    int counter =0;
    for(i=1; i<= permutations; i++)
    {
        //If Else for each digit.
        //Leaset significant bit digit
        txt[2] = digit1 + '0';
        digit1 = (digit1+1)%10;

        txt[1] = digit2 + '0';
        if((i%10) == 0)
            digit2 = (digit2+1)%10;
        
        txt[0] = digit3 + '0';
        if((i%100)==0)
            digit3 = (digit3+1)%10;
    
        puts(txt);
    }

    return 0;
}