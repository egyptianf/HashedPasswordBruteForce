#include<stdio.h>
#include<unistd.h>
#include<crypt.h>
int error(){
    printf("Usage: ./crack plaintext\n");
    return 1;
}
int main(int argc, char** argv)
{
    if(argc != 2)
        return error();

    char *plaintext = argv[1], *salt = "50";
    char *hashed = crypt(plaintext, salt);
    puts(hashed);

    return 0;
}