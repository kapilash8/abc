/************* UDP SERVER CODE *******************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(){
  int udpSocket, nBytes;
  char buffer[1024];
  struct sockaddr_in serverAddr, clientAddr;
  struct sockaddr_storage serverStorage;
  socklen_t addr_size, client_addr_size;
  int i;

  /*Create UDP socket*/
  udpSocket = socket(PF_INET, SOCK_DGRAM, 0);

  /*Configure settings in address struct*/
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(7891);
  serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
  memset(serverAddr.sin_zero, '\0', sizeof serverAddr.sin_zero);  

  /*Bind socket with address struct*/
  bind(udpSocket, (struct sockaddr *) &serverAddr, sizeof(serverAddr));

  /*Initialize size variable to be used later on*/
  addr_size = sizeof serverStorage;
  FILE *dns;

  char name[1024],add[10000];

  while(1){
    /* Try to receive any incoming UDP datagram. Address and port of 
      requesting client will be stored on serverStorage variable */int flag=0;
    nBytes = recvfrom(udpSocket,buffer,1024,0,(struct sockaddr *)&serverStorage, &addr_size);
printf("Recv:%s:",buffer);

    dns=fopen("dnsfile.dat","r");
    while(fscanf(dns,"%s %s\n",name,add)!= EOF){
		
		        if(strncmp(name,buffer,strlen(name))==0){
                                     flag=1;
                                     sendto(udpSocket,add,nBytes,0,(struct sockaddr *)&serverStorage,addr_size);
		        	

		
	       }}
      if(flag==0){
        sendto(udpSocket,"does not match",14,0,(struct sockaddr *)&serverStorage,addr_size);

     }
    
  }
  fclose(dns);

  return 0;
}
