/*
	C ECHO client example using sockets
*/
#include<stdio.h>	//printf
#include<string.h>	//strlen
#include<sys/socket.h>	//socket
#include<arpa/inet.h>	//inet_addr
//struct hostent he;
//const char hostname[] "180.249.220.110";
void clearbuffer(char * bufferdata);
int main(int argc , char *argv[])
{
	int sock;
	struct sockaddr_in server;
	char c[1000];
	char message[1000] , server_reply[2000];
/*if((he= gethostbyname(hostname))==null){
return 0;
}*/

	//Create socket
	sock = socket(AF_INET , SOCK_STREAM , 0);
	if (sock == -1)
	{
		printf("Could not create socket");
	}
	puts("Socket created");
	
	server.sin_addr.s_addr = inet_addr("125.162.247.2");
	server.sin_family = AF_INET;
	server.sin_port = htons( 2007 );

	//Connect to remote server
	if (connect(sock , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		perror("connect failed. Error");
		return 1;
	}
	
	puts("Connected\n");
	
	//keep communicating with server
	while(1)
	{
clearbuffer((char * ) & message);		
	printf("Enter message : ");
		scanf("%s",&message);
//		 message[1000]="B3223A52F3#rizaldi#rizaldikeren#rpa#";
		
		//Send some data
		if( send(sock , message , strlen(message) , 0) < 0)
		{
			puts("Send failed");
			return 1;
		}
		
		//Receive a reply from the server
		if( recv(sock , server_reply , 2000 , 0) < 0)
		{
			puts("recv failed");
			break;
		}
		puts("Server reply :");
		puts(server_reply);
		clearbuffer((char * ) & server_reply);
	}
	
	close(sock);
	return 0;
}
void clearbuffer(char * bufferdata) {
   for (int i = 0; i < 10; i++) {
      bufferdata[i] = '\0';
   }
}
