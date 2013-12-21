 #include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <unistd.h>

#define PORT 8080 
#define INADDR "192.168.0.102"
int main(int argc, char**argv){
	struct sockaddr_in serv_addr, clnt_addr[8];
	struct timeval timeout={0,0};
	char rmsg[8][255], smsg[255];
	fd_set fda, fds, fdm;
	socklen_t len = sizeof(serv_addr);
	
	int socketfd = socket(AF_INET,SOCK_STREAM,0);
	if(socketfd==-1){
		return -1;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	bzero(&(serv_addr.sin_zero), 8);

	int bl = bind(socketfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr));
	if(bl<0){
		return -1;
	}

	int ret = listen(socketfd,8);
	if(ret <0){
		return -1;
	}
	bool ready=false;
	int count=0;
	int peer[8];
	while(true){
		
		FD_ZERO(&fda);
		FD_SET(socketfd, &fda);
		switch(select(socketfd+1, &fda, NULL, NULL, &timeout)){
			case -1:
				exit(-1);
				break;
			case 0:
				break;
			default:
				if(FD_ISSET(socketfd, &fda)){
					peer[count] = accept(socketfd, (struct sockaddr *)&clnt_addr[count], &len);
					if (peer < 0) {
						return -1;
					}
					printf("accept%d\n",count);
					count++;
					break;
				}
		}
		FD_ZERO(&fdm);
		int max=-1;
		bool flag=false;
		for(int i=0; i<count; i++){
			FD_SET(peer[i], &fdm);
			if(peer[i]>max)
				max=peer[i];
		}
		switch(select(max+1, &fdm, NULL, NULL, &timeout)){
			case -1:
				exit(-1);
				break;
			case 0:
				break;
			default:
				for(int i=0; i<count; i++){
					if(FD_ISSET(peer[i], &fdm)){
						recv(peer[i],rmsg[0],sizeof(rmsg[0]), 0);
						if(strcmp(rmsg[0], "ok")==0){
							flag=true;
							break;
						}
					}
				}
				break;
		}
		if(flag){
			for(int i=0; i<count; i++){
				send(peer[i], rmsg[0],sizeof(rmsg[0]),0);
			}
			break;
		}
		
	}
	int max=-1;
	for(int i=0; i<count; i++){
		printf("%d\n", peer[i]);
		if(peer[i]>max)
			max=peer[i];
	}
	bool sendEnable[8];
	memset(rmsg, 0,sizeof(rmsg));
	
	while(1){
		
		FD_ZERO(&fds);
		for(int i=0; i<count; i++)
				FD_SET(peer[i],&fds);
			
		switch(select(max+1, &fds, NULL, NULL, &timeout)){
			case -1:
				printf("-1\n");
				break;
			case 0:
				break;
			default:
				for(int i=0; i<count; i++){
					if(FD_ISSET(peer[i], &fds)){
						int r=recv(peer[i],rmsg[i],sizeof(rmsg[i]), 0);
						if(r<0){
							break;
						}
						else{
							for(int j=0; j<count; j++){
								send(peer[j], rmsg[i],sizeof(rmsg[i]),0);
							}
						}
					}
				}
				break;
		}
	}
	return 0;
}

 
 
