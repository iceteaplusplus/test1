#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write
#define jumlahmac 3
#define semuapin 12
#define mymac 1122334455
char data[1024];
//char data[1024] = "B3223A52F3.rizaldi.rizaldikeren.r,1,2,7,11,10,.";
//char data[1024] = "B3223A52F3.rizaldi.rizaldikeren.rpa.";
char databalik[1024];
char datamacread[10];
char user[30] = "rizaldi", password[30] = "rizaldikeren";
char userinput[30], passwordinput[30];
char readdata[99];
char rpa[4] = "rpa";
char buffer[10];
int bos, direktur[20];
char mama[5];
char halu[12];
char coma[2]=",";
char bracket[2]=".";
char zero[2]="0";
int pinposition[semuapin] = {
   1,
   0,
   1,
   0,
   1, //digital
   429,
   500,
   700,
   12,
   5323, //analog
   1,
   0 //digital
};
int positionsplit[5];
int positioncoma[10];

char macclient[jumlahmac][11] = {
   "B3223A52F3",
   "AAAAAAAAAA",
   "FFFFFFFFFF"
};

int checkmacread(char * mac, int jumlah);
int positioncomaku(char * macd, int * sum);
void positionsplitku(char * mac, int * jumlahnya);
void clearbuffer(char * bufferdata);
void tostring(char str[], int num);

int main(int argc , char *argv[])
{
	int socket_desc , client_sock , c , read_size;
	struct sockaddr_in server , client;
	char client_message[2007];
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		puts("Could not create socket");
	}
	puts("Socket created");
	
	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(2007);
	
	//Bind
	if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
	{
		//print the error message
		perror("bind failed. Error");
		return 1;
	}
	puts("bind done");
	
	//Listen
	listen(socket_desc , 3);
	
	//Accept and incoming connection
	puts("Waiting for incoming connections...");
	c = sizeof(struct sockaddr_in);
	
	//accept connection from an incoming client
	client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
	if (client_sock < 0)
	{
		perror("accept failed");
		return 1;
	}
	puts("Connection accepted");
	
	//Receive a message from client
	while( (read_size = recv(client_sock , data , 2000 , 0)) > 0 )
	{
//puts("\nproses tahap 0");
 clearbuffer((char * ) & databalik);
 for (int i = 0; i <= 9; i++) {
      datamacread[i] = data[i];
   }
puts("\nproses tahap 0");//ini kenapa
   for (int i = 0; i <= jumlahmac; i++) {}
   positionsplitku(data, (int * ) & positionsplit[0]);
   int f;
//puts("\nproses tahap 02");
   for (int i = positionsplit[0] + 1, j = 0; i < positionsplit[1]; i++, j++) {
      userinput[j] = data[i];
   }
//puts("\nproses tahap 03");
   bos = positioncomaku(data, (int * ) & positioncoma[0]);

 //  printf("bos = %d\n", bos);
// puts("proses tahap 1");  
for (int i = positionsplit[1] + 1, j = 0; i < positionsplit[2]; i++, j++) {
      passwordinput[j] = data[i];

   }
   for (int i = positionsplit[2] + 1, j = 0; i < positionsplit[3]; i++, j++) {
      readdata[j] = data[i];

   }
   /*	for(int i=0;i<bos-1;i++){
   		//printf("%d\n",positioncoma[i]);
   	}*/
   for (int i = 0; i <= bos - 2; i++) {
      for (int h = positioncoma[i] + 1, j = 0; h < positioncoma[i + 1]; h++, j++) {
         mama[j] = data[h];
      }
//      printf("%s", mama);
      sscanf(mama, "%d", & direktur[i]);
  //    printf("\t%d\n", direktur[i]);
      clearbuffer((char * ) & mama);
   }
//puts("proses tahap 2");
   if (checkmacread(datamacread, jumlahmac)) {
//printf("\nMAC %s diberikan akses" ,datamacread);
      if (strcmp(user, userinput) == 0 && strcmp(password, passwordinput) == 0) {
//printf("login berhasil");
//printf("\nUser %s diberikan akses",userinput);

         if (strcmp(readdata, rpa) == 0) {
            //printf("\nREAD ALL PIN\n");
            for (int i = 0; i < semuapin; i++) {
					//printf("%d,", pinposition[i]);
                     tostring(halu,pinposition[i]);
                     if(pinposition[i]==0){
                     	clearbuffer((char * ) & halu);
                     	halu[0]='0';
					 }
					 strcat(databalik,halu);
                     strcat(databalik,coma);
            } strcat(databalik,bracket);
           // printf("\n%s",databalik);
         } else {
            //printf("\nWrong Syntax\n");
            //
//printf("\n%s",readdata);
            for (int i = 0; i <= bos - 2; i++) {
               for (int j = 0; j < semuapin; j++) {
                  if (direktur[i] == j) {
                    // printf("%d,", pinposition[j]);
                     tostring(halu,pinposition[j]);
                     if(pinposition[j]==0){
                     	clearbuffer((char * ) & halu);
                     	halu[0]='0';
					 }
					 strcat(databalik,halu);
                     strcat(databalik,coma);
                     
                  }
               }
            }
            strcat(databalik,bracket);
         //   printf("\n%s",databalik);
         }
      } else {
         strcat(databalik,"login gagal");
      }
   } else {
      strcat(databalik,"Bukan mac yang dizinkan");

   }

//puts("\nproses tahap 3");

		//Send the message back to client
		write(client_sock , databalik , strlen(databalik));
 clearbuffer((char * ) & data);
	}
	
	if(read_size == 0)
	{
		puts("Client disconnected");
		fflush(stdout);
	}
	else if(read_size == -1)
	{
		perror("recv failed");
	}
	
	return 0;
}
int checkmacread(char * mac, int jumlah) {
   for (int i = 0; i < jumlah; i++) {
      int ret = strcmp(macclient[i], datamacread);
      if (ret == 0) {
         return 1;
      }
   }
   return 0;
}
int positioncomaku(char * macd, int * sum) {
   int h = 0;
   for (int i = 0; i <= strlen(macd); i++) {
      if (macd[i] == ',') {
         sum[h] = i;
         h++;
      }
   }
   return h;
}
void positionsplitku(char * mac, int * jumlahnya) {
   int h;
   for (int i = 0; i <= strlen(mac); i++) {
      if (mac[i] == '.') {
         jumlahnya[h] = i;
         h++;
      }
   }
}
void clearbuffer(char * bufferdata) {
   for (int i = 0; i < 10; i++) {
      bufferdata[i] = '\0';
   }
}
void tostring(char str[], int num)
{
    int i, rem, len = 0, n;
 
    n = num;
    while (n != 0)
    {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++)
    {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}
