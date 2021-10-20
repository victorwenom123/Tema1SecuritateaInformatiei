#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
//#include "cryptlib.h"
#include <cryptopp/rijndael.h>
//#include <cryptopp/osrng.h>
//#include <cryptopp/validate.h>
#include <cryptopp/osrng.h>
#include <cryptopp/aes.h>
#include <cryptopp/cryptlib.h>
//#include <cryptopp/filter.h>
#include <cryptopp/modes.h>
#include <cryptopp/hex.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#define PORT 8080
using namespace std;
using namespace CryptoPP;
int main(int argc, char const *argv[])
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[256] = {0};
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT-1);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
   // send(sock , hello , strlen(hello) , 0 );
   // printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);
    if (buffer[0]=='1')
      printf("Nodului KM i s-a solicitat de catre A cheia de criptare!" );
    else
       printf("Solicitarea nu a fost primita!");

/*
AutoSeededRandomPool rnd;
byte key[16];
rnd.GenerateBlock(key,16);
byte keyPrime[16];
rnd.GenerateBlock(keyPrime,16);
ECB_Mode<AES>::Encryption enc;
string encoded,cipher;
encoded.clear();
StringSource(keyPrime,sizeof(keyPrime),true,new HexEncoder(new StringSink(encoded)));
ECB_Mode<AES>::Encryption e;
e.SetKey(keyPrime,sizeof(keyPrime));
StringSource(key,true,new StreamTransformationFilter(e,new StringSink(cipher)));
encoded.clear();
StringSource(cipher,true, new HexEncoder(new StringSink(encoded)));
//cout<<encoded;
unsigned char encoded1[256];
for (int i=0;i<encoded.length();++i)
   encoded1[i]=encoded[i];
//strcpy(encoded1,encoded); DE AICI: */
unsigned char enc_out[256];
unsigned char key1[256], keyPrime1[256]="bPeSgVkYp3s6v9y$";
if (!RAND_bytes(key1,16))
   cout<<"Failure";
/*for (int i=0;i<strlen((char*)key1);++i)
   if (key1[i]=='\n')
      key1[i]='a';*/

/*if (!RAND_bytes(keyPrime1,128))
   cout<<"Failure";
for (int i=0;i<strlen((char*)keyPrime1);++i)
   if (keyPrime1[i]=='\n')
      keyPrime1[i]='a';
for (int i=0;i<strlen((char*)keyPrime1);++i)
    cout<<+keyPrime1[i];*/

cout<<endl;
AES_KEY enc_key1,dec_key;
AES_set_encrypt_key(keyPrime1,128, &enc_key1);
AES_encrypt(key1,enc_out,&enc_key1);
char *finale=reinterpret_cast<char *>(enc_out);
char keyPrime2[256];
for (int i=0;i<=strlen((char*)keyPrime1);++i)
{    //if (i!=strlen((char*)keyPrime1))
         //cout<<keyPrime1[i];
     keyPrime2[i]=keyPrime1[i];
}
//strcat(finale,"\n");
//strcat(finale,keyPrime2);
 send(sock , finale , strlen(finale) , 0 );
close(sock);
sock=0;
/*ECB_Mode<AES>::Encryption enc;
const byte* keydata=(const byte*)&keyPrime[0];
const byte* ivdata=(const byte*)&key.iv[0];
enc.setKeyWithIV(keydata, keyPrime.size(),ivdata);
string cipher;
StringSource(pl*/

    return 0;
}
