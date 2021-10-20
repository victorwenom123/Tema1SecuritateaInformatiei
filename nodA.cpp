

// Server side C/C++ program to demonstrate Socket programming
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <fstream>
#define PORT 8080
char *encryptECB(char text[], unsigned char key[])
{char out[256];
unsigned char text1[256], enc_out[256];
out[0]='\0';
text1[0]='\0';
int v=16;
for (int i=0;i<=(strlen(text)-1)/16;++i)
  {text1[0]='\0';
   v=16;
   for (int j=0;j<16;++j)
      {if (16*i+j<strlen(text))
        text1[j]=text[16*i+j];
       else
        {text1[j]=' ';
//text1[j]='\0';
       // v=j;
       // break;
}
      // else
        //text1[j]=' ';   
}
//text1[16]='\0';
//for (int i=v;i<=16;++i)
//text1[i]='\0';
AES_KEY enc_key;
AES_set_encrypt_key(key,128,&enc_key);
AES_encrypt(text1, enc_out,&enc_key);
strcat(out,reinterpret_cast<char *>(enc_out));
//strcat(out,"\n");
enc_out[0]='\0';
   }
char *p=out;
return p;
}
void xorCalc (int lung,unsigned char *a, unsigned char *b, unsigned char *c)
{for (int i=0;i<lung;++i)
     c[i]=a[i]^b[i];}
char *encryptOFB(char text[], unsigned char key[], unsigned char vector[])
{//unsigned char bloc[256];
unsigned char *bloc=new unsigned char[256];
unsigned char blocCurent[256];
unsigned char text1[256];
char* cipherfinal=new char[256];
AES_KEY enc_key;
AES_set_encrypt_key(key,128,&enc_key);
AES_encrypt(vector, bloc,&enc_key);
for (int i=0;i<=(strlen (text)-1)/16;++i)
 {unsigned char * ciphertext1=new unsigned char [256];
  int val=16;
  ciphertext1[0]='\0';
  text1[0]='\0';
  for (int j=0;j<16;++j)
    {if (16*i+j<strlen(text))
        text1[j]=text[16*i+j];
       else
          {val=j;
           break;}
       // text1[j]=' ';   
}

  //text1[16]='\0'; 
//int min=100000;
int min;
if ( strlen((char*)(bloc))>val)
    min=val;
else
   min=strlen((char*)(bloc));
xorCalc(min,bloc,text1,ciphertext1); // ??
//xorCalc(16,bloc,text1,ciphertext1);
strcat(cipherfinal,reinterpret_cast<char *>(ciphertext1));
delete ciphertext1;
//strcat(cipherfinal,"\n");
if (i!=(strlen (text)-1)/16 )
{AES_KEY enc_key1;
AES_set_encrypt_key(key,128,&enc_key);
for (int i=0;i<=strlen ((char*)(bloc));++i)
 blocCurent[i]=bloc[i];
bloc[0]='\0';
delete bloc;
bloc =new unsigned char[256];
AES_encrypt(blocCurent, bloc,&enc_key);}
else
{delete bloc;
bloc =new unsigned char[256];}
}
return cipherfinal;
}
        //out[16*i+j])
using namespace std;
//int main(int argc, char const *argv[])
int main ()
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[256] = {0};
    char operationMode[256] = "";
    char vector[256];
    char plaintext[256];
    char ok[256];
    ok[0]='1';
    ok[1]='\0';
    cout<<"Scrieti vectorul de initializare, textul in clar si modul de operare - ECB sau OFB \n";
char keyPrime1[256]="bPeSgVkYp3s6v9y$";
    cin.getline(vector,256);   
    cin.getline(plaintext,256);
    std::ofstream clearer1;
clearer1.open("length.txt",std::ofstream::out | std::ofstream::trunc);
clearer1.close();
std::ofstream ofs1;
ofs1.open("length.txt");
ofs1<<strlen(plaintext);
ofs1.close();

    cin.getline(operationMode,256);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    //valread = read( new_socket , buffer, 1024);
    //printf("%s\n",buffer );
    send(new_socket , operationMode , strlen(operationMode) , 0 );
    printf("A fost trimis modul de operare %s de la A spre B\n", operationMode);
	close(new_socket);
new_socket=0;
cout<<"Nodul A cere de la nodul KM cheia de criptare...";
ok[0]='1';

if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT-1 );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    } 
    buffer[0]='\0';
    //valread = read( new_socket , buffer, 1024);
    //printf("%s\n",buffer );
    send(new_socket , ok , strlen(ok) , 0 );
    valread = read( new_socket , buffer, 256);
    cout<<"A a primit cheia criptata de la KM";
    cout<<'\n';
    //printf("%s",buffer);
    close(new_socket);
    new_socket=0;
    char encodedKey[256];
    int k=0;
    char buffer0[256];
    strcpy(buffer0,buffer);
    strcpy(encodedKey,buffer0);
    /*while (buffer[k]!='\n')
       {encodedKey[k]=buffer[k];
        k++;}
    encodedKey[k]='\0';
    char *p=strchr(buffer,'\n');
    char p1[256];
    strcpy(p1,p+1);*/
    AES_KEY dec_key1;
    char *p3=keyPrime1;
    unsigned char dec_out1[256];
    unsigned char *encodedKey1=reinterpret_cast<unsigned char *>(encodedKey);
   unsigned char *primeKey1=reinterpret_cast<unsigned char *>(p3);

//cout<<"S-A AJUNS AICI!!!!!!";
   AES_set_decrypt_key(primeKey1,128,&dec_key1);
   AES_decrypt(encodedKey1,dec_out1,&dec_key1);
if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT-3 );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    } 
    //valread = read( new_socket , buffer, 1024);
    //printf("%s\n",buffer );
    //cout<<"SOCKETUL CU BINE";
    send(new_socket , buffer0 , strlen(buffer0) , 0 );
    char messageRead[65];
    messageRead[0]='\0';
    int okay=1;
    while ( (valread = read( new_socket , messageRead, 65))==-1);
{okay=0;}
okay=1;
    close(new_socket);
printf("\n");
printf("%s",messageRead);
    new_socket=0;
    //cout<<"S A CITIT";
    cout<<'\n';
    /*for (int i=0;i<strlen(messageRead);++i)
       cout<<messageRead[i];*/
    //cout<<"YES";


if (strcmp(operationMode,"ECB")==0)
   strcpy(buffer,encryptECB(plaintext,dec_out1));
else
   strcpy(buffer,encryptOFB(plaintext,dec_out1,reinterpret_cast<unsigned char *>(vector)));



if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT-5 );
       
    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    } 
    //valread = read( new_socket , buffer, 1024);
    //printf("%s\n",buffer );
std::ofstream clearer;
clearer.open("outfile.txt",std::ofstream::out | std::ofstream::trunc);
clearer.close();
std::ofstream ofs;
ofs.open("outfile.txt");
for (int i=0;i<strlen(plaintext);++i)
    {if (i%16==0 && i!=0)
         ofs<<" ";
     ofs<<buffer[i];
     }
ofs.close();

    send(new_socket , buffer , strlen(buffer) , 0 );
    close(new_socket);
    new_socket=0;
    return 0;
}
