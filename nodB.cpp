#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#define PORT 8080
char operationMode[256];
char *decryptECB(char cipher[], unsigned char key[])
{char out[256];
unsigned char cipher1[256], dec_out[256];
out[0]='\0';
cipher1[0]='\0';
int v=15;
for (int i=0;i<=(strlen(cipher)-1)/16;++i)
  {cipher1[0]='\0';
   v=16;
   for (int j=0;j<16;++j)
      {if (16*i+j<strlen(cipher))
         cipher1[j]=cipher[16*i+j];
       else
         {cipher1[j]=' ';
         //cipher1[j]='\0';
         //v=j;
        // break;
}
      // else
           // cipher1[j]=' ';
}

//cipher1[16]='\0';


//for (int i=v;i<=16;++i)
//cipher1[i]='\0';
AES_KEY dec_key;
AES_set_decrypt_key(key,128,&dec_key);
AES_decrypt(cipher1, dec_out,&dec_key);
strcat(out,reinterpret_cast<char *>(dec_out));
//strcat(out,"\n");
dec_out[0]='\0';
   }
char *p=out;
return p;
}

void xorCalc (int lung,unsigned char *a, unsigned char *b, unsigned char *c)
{for (int i=0;i<lung;++i)
     c[i]=a[i]^b[i];}


char *decryptOFB(char cipher[], unsigned char key[], unsigned char vector[])
{//unsigned char bloc[256];
unsigned char *bloc=new unsigned char[256];
unsigned char blocCurent[256];
unsigned char cipher1[256];
char textfinal[256];
textfinal[0]='\0';
int val=16;
AES_KEY dec_key;
//AES_set_decrypt_key(key,128,&dec_key);
AES_set_encrypt_key(key,128,&dec_key);
//AES_decrypt(vector, bloc,&dec_key);
AES_encrypt(vector, bloc,&dec_key);
for (int i=0;i<=(strlen (cipher)-1)/16;++i)
 {unsigned char text1[256];
  val=16;
  text1[0]='\0';
  cipher1[0]='\0';
  for (int j=0;j<16;++j)
    {if (16*i+j<strlen(cipher))
        cipher1[j]=cipher[16*i+j];
       else
                  {val=j;
           break;}
       // cipher1[j]=' ';   
}

  //cipher1[16]='\0'; 
int min;
if ( strlen((char*)(bloc))>val)
    min=val;
else
   min=strlen((char*)(bloc));
xorCalc(min,bloc,cipher1,text1);
//xorCalc(16,bloc,cipher1,text1);
strcat(textfinal,reinterpret_cast<char *>(text1));
//printf("%s ",text1);
//strcat(textfinal,"\n");
if (i!=(strlen (cipher)-1)/16 )
{AES_KEY dec_key1;
//AES_set_decrypt_key(key,128,&dec_key);
AES_set_encrypt_key(key,128,&dec_key);
for (int i=0;i<=strlen ((char*)(bloc));++i)
 blocCurent[i]=bloc[i];
bloc[0]='\0';
delete bloc;
bloc =new unsigned char[256];
AES_encrypt(blocCurent, bloc,&dec_key);
//AES_decrypt(blocCurent, bloc,&dec_key);
}
else
{delete bloc;
bloc =new unsigned char[256];}
}
char *point=textfinal;
return point;
}

using namespace std;
int main(int argc, char const *argv[])
{
    int sock = 0, valread, sock0=0;
    struct sockaddr_in serv_addr;
    char buffer[256] ;
	char vector[256];
//char plaintext[256];
char keyPrime1[256]="bPeSgVkYp3s6v9y$";
cout<<"Scrieti vectorul de initializare: \n";
long lungimePlaintext;
cin.getline(vector,256);
//cin.getline(plaintext,256);

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
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
    valread = read( sock , buffer, 256);
    
    printf("Modul de operare receptionat de nodul B este %s \n",buffer );
strcpy(operationMode,buffer);
close(sock);
sock=0;


cout<<"Scrieti un mesaj cand urmeaza ca A sa trimita rezultatul spre B \n";
char sir[256];
cin.getline(sir,256);
 if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT-3);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
//cout<<"a ajuns aici";
    int okay=1;
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
//cout<<"a ajuns aici";
okay=1;
   buffer[0]='\0';
    valread = read( sock , buffer, 256);
//cout<<"KK\n";    
/*for (int i=0;i<strlen(buffer);++i)
   cout<<buffer[i];*/
    char encodedKey[256];
    strcpy(encodedKey,buffer);
    int k=0;
    /*while (buffer[k]!='\n')
       {encodedKey[k]=buffer[k];
        k++;}
    encodedKey[k]='\0';
    char *p0=strchr(buffer,'\n');
    char p3[256];
    strcpy(p3,p0+1);*/
    char *p4=keyPrime1;
    //cout<<"a ajuns aici";
    AES_KEY dec_key1;
    unsigned char dec_out1[256];
    unsigned char *encodedKey1=reinterpret_cast<unsigned char *>(encodedKey);
   unsigned char *primeKey1=reinterpret_cast<unsigned char *>(p4);
   AES_set_decrypt_key(primeKey1,128,&dec_key1);
   AES_decrypt(encodedKey1,dec_out1,&dec_key1);

    char message[65]="A a primit mesajul trimis de B pentru a incepe comunicarea!";
    send(sock , message , strlen(message) , 0 );
    close(sock);
    sock=0;

cout<<"Scrieti un mesaj pentru a confirma ca B poate primi continutul fisierului criptat pe blocuri! \n";
char h[256];
cin.getline(h,256);
    if ((sock0 = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT-5);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock0, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
   char bufferprime[256];
   char a[256];
    valread = read( sock0 , buffer, 256);
   /* for (int i=0;i<strlen(buffer);++i)
        if (buffer[i]=='\n')
            {strcpy(bufferprime,buffer);
             char *p=bufferprime;
             
             strcpy (p+i,p+i+1);
           
             strcpy(a,p);
             strcpy(buffer,a);
             i--;}*/
int p=0;
for (int i=0;i<strlen(buffer);++i)
       {bufferprime[p++]=buffer[i];
       // cout<<bufferprime[p-1];
}
   bufferprime[p]='\0';
char *primepointer=bufferprime;
close(sock0);
sock0=0;


char rezultatfinal[256];
if (strcmp(operationMode,"ECB")==0)
   strcpy(rezultatfinal,decryptECB(primepointer,dec_out1));
else
   strcpy(rezultatfinal,decryptOFB(primepointer,dec_out1,reinterpret_cast<unsigned char *>(vector)));
ifstream myfile("length.txt");
myfile>>lungimePlaintext;
myfile.close();
if (strcmp(operationMode,"ECB")==0)
for (int i=0;i<lungimePlaintext;++i)
   {cout<<rezultatfinal[i];
    if (i%16==0 && i!=0)
        cout<<" ";
}
//if (strcmp(operationMode,"ECB")!=0)
//{
else
for (int i=0;i<lungimePlaintext;++i)
   {cout<<rezultatfinal[i];
    if (i%16==0 && i!=0)
        cout<<" ";
}
unsigned char rezultatdecodat[256];
AES_KEY enc_keyf;
AES_set_decrypt_key(dec_out1,128,&enc_keyf);
AES_decrypt(reinterpret_cast<unsigned char *>(rezultatfinal), rezultatdecodat,&enc_keyf);
//for (int i=0;i<strlen((char*)rezultatdecodat);++i)
  // cout<<rezultatdecodat[i];
//}
    return 0;
}
