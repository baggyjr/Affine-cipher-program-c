//Created by Will Baggott
//Created for CTEC2915-28.03.2021-De Montfort University

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int InMod;//Initialises InMod as a global variable so it can be used outside of the ModInverse Function
int gcdExtended(int Key1, int b, int* x, int* y);//Makes the variables used in gcdExtended global variables as they are also used in the ModInverse function
int modInverse(int Key1, int modulo)
{
    int x, y;
    int g=gcdExtended(Key1, modulo, &x, &y);//g is the end value of the euclidean algorithm 
    if (g!=1)//if g is 1 then key1 has an inverse
    {
        return 0;//if the value of key1 doesn't have an inverse it returns nothing
    }
    else
    {
        InMod=(x%modulo+modulo)%modulo;//using the x value from gcdExtended it calculates the Inverse Mod of the alpha key
        return InMod;//returns InMod to be used in the decryption formula
    }
}
 
int gcdExtended(int Key1, int b, int* x, int* y)
{
    if (Key1==0)//if key1 then GCD(Key1,B)=B, since the GCD(0,B)=B
    {
        *x=0, *y=1;
        return b;
    }
    int x1, y1;
    int gcd=gcdExtended(b % Key1, Key1, &x1, &y1);//loops through until b%key1 = 0
    *x=y1-(b/Key1)*x1;
    *y=x1;
 	
    return gcd;
}

int main(){

int key1, key2, inv, i, j, n, option, option2, final;
int div=26;
int intText[200];
char *plainText, *cipherText;

printf(ANSI_COLOR_GREEN"Welcome to Group 33 Affine program!\n\n"ANSI_COLOR_RESET);//Main page function to help guide users.
jump://Used to restart the program if the user wants to. Ease of use.
printf(ANSI_COLOR_GREEN"Please enter the number for your desired function. \n"ANSI_COLOR_RESET);//Allows user to decide what function they want to use. Ease of use. 
printf("Function 1: Encryption \nFunction 2: Decryption \nFunction 3: Brute force \n\n");//Each funciton is numbered so it is easy to understand.
scanf("%d", &option);
getchar();

if(option==1)//This starts the encryption function if number 1 is chosen at the main page. Ease of use.
{
plainText=(char*)malloc(200);//Allocates 200 bytes for plaintext so the program can run more efficient.
cipherText=(char*)malloc(200);//Allocates 200 bytes for ciphertext so the program can run more efficient.
printf(ANSI_COLOR_GREEN"Welcome to the encryption function! 2 random keys will be provided to you. \n"ANSI_COLOR_RESET );//Prints a title so the user knows what function they entered.
    
jump1://Jump1 is used to re-gain a new key incase it is illegal. Helps the user so the do not have to restart the program.
srand(time(NULL));//Uses internal clock to get a random key since time is always changing.
key1=rand()%26;//Makes the range 0-25 which is the requirement for an alpha key. This will make the program run more efficient.

if(key1==0)//The key cannot be 0 since it will make the program much less secure.
    {
        sleep(1);//Program waits for 1 second to make the program gain a new key from internal clock. Otherwise it wil be the same key as before.
        printf(ANSI_COLOR_RED"Key 1 (%i) is illegal!"ANSI_COLOR_RESET" \nGaining new key...\n\n", key1);//Tells the user that they key is invalid. Information for the user.
        goto jump1;//Goes to re-gain new key if invalid. Ease of use for the user since they will not have to do it manually.
    }

if(key1==14)//The key cannot be 14 since it will make the program much less secure.
    {
        sleep(1);//Program waits for 1 second to make the program gain a new key from internal clock. Otherwise it wil be the same key as before.
        printf(ANSI_COLOR_RED"Key 1 (%i) is illegal!"ANSI_COLOR_RESET" \nGaining new key...\n\n", key1);//Tells the user that they key is invalid. Information for the user.
        goto jump1;//Goes to re-gain new key if invalid. Ease of use for the user since they will not have to do it manually.
    }

int gcd1=key1;//Checks if the greatest common denominator of the key is 1. The GCD will need to be 1 in order for the encryption to work.
while(gcd1!=div)//while these values are not equal it loops through to find the gcd of both values.
    {
    if(gcd1>div)
        gcd1-=div;//if gcdKey1 is bigger then minus div from gcdKey1
    else
        div-=gcd1;//if div is bigger the minus gcdKey1 from div
    }
    
if(gcd1!=1)//If the GCD is not 1, the program will gain a new key.
    {
    sleep(1);//Program waits for 1 second to make the program gain a new key from internal clock. Otherwise it wil be the same key as before.
    printf(ANSI_COLOR_RED"Key 1 (%i) is illegal, GCD is: %i!"ANSI_COLOR_RESET" \nGaining new key...\n\n", key1, gcd1);//Tells the user that they key is invalid. Information for the user.
    goto jump1;//Goes to re-gain new key if invalid. Ease of use for the user since they will not have to do it manually.
    }
    
if(gcd1==1)//This is the successful route. Once the key is certainly correct, the program will move on.
    {
    printf("Key 1 is %i\n", key1);//Prints the first key to show the user. This will help the user to decrypt if they ever want to.
    }
    
sleep(1);//Program waits for 1 second to make the program gain a new key from internal clock. Otherwise it wil be the same key as before.
srand(time(NULL));//Uses internal clock to get a random key since time is always changing.
jump7:
key2=rand()%26;//Makes the range 1-25 which is the requirement for an beta key. This will make the program run more efficient.
printf("Key 2 is %i\n\n", key2);//This will show the second key to the user so they can use to decrypt.
printf("Please enter your plaintext message. Maximum string size is 200 characters!\n");//This will inform the user that the maximum string is 200 characters to protect memory.
fgets(plainText, 200, stdin);//This will stop the user from overflowing the memory allocated so it won't crash the program.

if(plainText==NULL)
    {
    printf(ANSI_COLOR_RED"Plaintext was not saved! \n"ANSI_COLOR_RESET);
    goto jump1;
    }
    
if(*plainText&&plainText[strlen(plainText)-1]=='\n')
    plainText[strlen(plainText)-1]=0;
    
for(i=0;i<=strlen(plainText);i++)//This will loop through all of the characters in "plainText". This will make sure all characters are converted.
    {
    if(plainText[i]!=32)//This will maintain whitespace within the user input. This will be needed otherwise the maths will not work.
        {
        if(plainText[i]>=97&&plainText[i]<=122)//This will detect if the character is lowercase. Lowercase cannot be used.
            plainText[i]=plainText[i]-32;//If the text is lowercase then it is converted to uppercase to allow the program to work properly.
        }
    else(plainText[i]=32);//This will maintain whitespace within the user input. This will be needed otherwise the maths will not work.
    }
    printf("Your uppercase plaintext is: %s\n", plainText); 
    while(plainText[i])
    plainText[i++];

for(i=0;i<=strlen(plainText);i++)
    {
    if(plainText[i]!=32)
        {
        intText[i]=plainText[i]-65;
        }
    else(plainText[i]=32);
    }
    
for(i=0;i<strlen(plainText);i++)//This will loop through all of the characters in "plainText". This will make sure all characters are encrypted.
        {
        if(plainText[i]!=32)
            cipherText[i]=((key1*intText[i])+(key2))%26+65;//if plainText[i] isn't whitespace it applies the encryption algorithm
        else if(plainText[i]=32)
            cipherText[i]=32;//if plainText[i] is whitespace it gets left as whitespace
        }
    printf("Your ciphertext is: "ANSI_COLOR_GREEN"%s\n\n"ANSI_COLOR_RESET, cipherText);
    while(cipherText[i])
    cipherText[i++];

plainText="";
cipherText="";

    jump4:
    printf("Please enter 1 to exit or 2 to restart... \n\n");//gives user the option to leave or restart the program. ease of use
    scanf("%i", &final);
if(final==1)
    {
    return 0;//option 1 ends the program
    }
else if(final==2)
    {
    goto jump;//option 2 goes to the start of the program
    }
else;
    printf(ANSI_COLOR_RED"Incorrect input! \n\n"ANSI_COLOR_RESET);
    goto jump4;//if a user inputs an incorrect value it asks again
}
else if(option==2)//This starts the encryption function if number 2 is chosen at the main page. Ease of use.
{

printf(ANSI_COLOR_GREEN"Welcome to the decryption function! \n"ANSI_COLOR_RESET);
int incText[200];
char *decodedText, *inputText;
decodedText=(char*)malloc(200);
inputText=(char*)malloc(200);    

jump2:
printf("Please enter your first key! Between 1-26 and must have a GCD of 1... \n");
scanf("%i", &key1);
getchar();
    
int gcdKey1=key1;
while(gcdKey1!=div)//while these values are not equal it loops through to find the gcd of both values. Checking to ensure key 1 is valid.
    {
if(gcdKey1>div)
    gcdKey1-=div;//if gcdKey1 is bigger then minus div from gcdKey1
else
    div-=gcdKey1;//if div is bigger the minus gcdKey1 from div
    }
    
if(gcdKey1!=1)
    {
    printf(ANSI_COLOR_RED"Illegal key!"ANSI_COLOR_RESET" \nDoes not have a GCD of 1 or doesn't meet the min/max requirements... \n\n\n");
    goto jump2;//if a user inputs a wrong key, it asks for the key again. ease of use
    }
    else;
    
    jump3:
    printf("Please enter your second key! Between 1-26... \n");
    scanf("%d", &key2);
    
    if(key2>26||key2<1)//checks to see if key2 is between 1 and 26. Ensuring valid key values.
    {
    printf(ANSI_COLOR_RED"Illegal key! "ANSI_COLOR_RESET"\nDoes not meet max/min requirements... \n\n\n");
    goto jump3;//if key2 isn't between 1 and 26 user is asked to input key2 again. ease of use
    }
    
    printf("Please enter your ciphertext! \n");
    scanf("%s", inputText);
    
if(inputText==NULL)//if the user doesn't input anything they are brought back to the start of the function. ease of use
    {
    printf(ANSI_COLOR_RED"Plaintext was not saved! \n\n"ANSI_COLOR_RESET);
    goto jump2;
    }
    
for(i=0;i<=strlen(inputText);i++)//Cycles through all of the letters in the cipherText. Applying the decryption algorithm to each character.
    {
    if(inputText[i]>=97&&inputText[i]<=122)
        inputText[i]=inputText[i]-32;//if the ascii value of is a letter corresponds to it's lowercase value we minus 32 to get the uppercase. Ensuring the calculation is correct.
    }
    
for(i=0;i<=strlen(inputText);i++)
    {
    incText[i]=inputText[i]+65;
    }

modInverse(key1, 26);//Calls the modInverse function using the values key1 and 26. For later use of the algortihm - calculating it before the fact.    
for(i=0;i<=(strlen(inputText)-1);i++)//goes through each letter of the cipherText
    {
    decodedText[i]=(InMod*(incText[i]-key2))%26+65;//applies the decryption formula to the cipherText
    }
    printf("Your plaintext is: "ANSI_COLOR_GREEN"%s \n\n"ANSI_COLOR_RESET, decodedText);
    while(decodedText[i])
    decodedText[i++];

jump5:
    printf("Please enter 1 to exit or 2 to restart... \n\n");
    scanf("%i", &final);
if(final==1)
    {
    return 0;
    }
else if(final==2)
    {
    goto jump;
    }
else;
    printf(ANSI_COLOR_RED"Incorrect input! \n\n"ANSI_COLOR_RESET);
    goto jump5;
}
else if(option==3)//this starts the brute force option if user picked 3. ease of use
{
plainText=(char*)malloc(200);
cipherText=(char*)malloc(200);
int result=0;
int inverse[12]={1, 9, 21, 15, 3, 19, 7, 23, 11, 5, 17, 25}; //These are all multiplicative inverse of all availble key1 values eg. inverse[0]=key1[0] multiplicative inverse. Used for later use on the decrytion algorithm.
int key1[12]={1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25}; //these are all the coprimes of 26 possible. Having this array ensures that kays are coprime, instead of calculating during the brute force method.
int key2[26]={0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};//all values that key2 can become. Reducing resources for constant calulation.
    printf(ANSI_COLOR_GREEN"Welcome to the brute force function! \n"ANSI_COLOR_RESET);
    printf("Please enter your ciphertext! \n");
    scanf("%s", cipherText);
    
if(cipherText==NULL)
    {
    printf(ANSI_COLOR_RED"Plaintext was not saved!\n\n"ANSI_COLOR_RESET);
    goto jump2;
    }
    
for(i=0;i<=strlen(cipherText);i++)//converts any lowercase letters in the plaintext to uppercase. Creating a constant group set for the algorithm.
    {
    if(cipherText[i]>=97&&cipherText[i]<=122)
        cipherText[i]=cipherText[i]-32;
    }
    
for(i=0;i<=strlen(cipherText);i++)
    {
    intText[i]=cipherText[i]+65;
    }
    
for(j=0;j<26;j++)//goes through each value of key2. Making sure every possbile value of the key is used.
{
    for(n=0;n<12;n++)//goes through each value of key1(co-primes). Making sure every possbile value of the key is used.
    {
        for(i=0;i<=(strlen(cipherText)-1);i++)//for the length on the string, it applies the decryption algorithm. The -1 ensures that the calculation is only on letters and not using the white space at the end of th array.
        {
        plainText[i]=(inverse[n]*(intText[i]-key2[j]))%26+65;
        }
        printf("Your plaintext is: "ANSI_COLOR_GREEN"%s "ANSI_COLOR_RESET"using (key 1= %i) and (key 2= %i) \n", plainText, key1[n], key2[j]);//prints out the plaintext with what keys were used. Allowing the user to know the keys used to encrypt.
        while(plainText[i])
        plainText[i++];
        result++;
    }
}
printf("Your search returned: "ANSI_COLOR_GREEN"%i "ANSI_COLOR_RESET"results. \n\n", result);
plainText="";
cipherText="";
jump6:
    printf("Please enter '1' to exit or '2' to restart... \n\n");
    scanf("%i", &final);
if(final==1)
    {
    return 0;
    }
else if(final==2)
    {
    goto jump;
    }
else;
    printf(ANSI_COLOR_RED"Incorrect input! \n\n"ANSI_COLOR_RESET);
    goto jump6;
}
else{
    printf("Please enter a number from 1-3! Restarting program...\n\n");
    goto jump;
}

return 0;
}


