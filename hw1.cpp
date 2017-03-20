#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <sys/uio.h>
#include <iostream>
#include <dirent.h>
#include "Connection.h"

using namespace std;
int MAXLINE = 1000;
char *protocal[4]={"tcp","tcp6","udp","udp6"};
void showConnInfo(Connection*,int);
int main(int argc, char* argv[])
{
	//Connection Conn[1000];
	Connection *Conn;
	Conn = new Connection[MAXLINE];
	for (int i=0;i<MAXLINE;i++)
	{
		Conn[i] = Connection();
	}
	FILE *fp[4];//tcp_fp, tcp6_fp, udp_fp, udp6_fp;
	fp[0] = fopen("/proc/net/tcp","r");
	fp[1] = fopen("/proc/net/tcp6","r");
	fp[2] = fopen("/proc/net/udp","r");
	fp[3] = fopen("/proc/net/udp6","r");
	char line[MAXLINE];

	//start parsing /proc/net/xxx
	int conncount=0;//connection entry count
	char *proto,*local_addr,*local_port,*dst_addr,*dst_port,*sockfd, *noneed;
/*	
	Conn[0].sockfd = "1111";
	Conn[1].sockfd = "2222";
	showConnInfo(Conn,2);
	exit(1);
*/
#ifdef debug
	for(int i=0;i<1;i++)
	{
		fgets(line,MAXLINE,fp[i]);
		while(fgets(line,MAXLINE,fp[i]))
		{
			cout << "readline:" << line << endl;
			//char *proto,*local_addr,*local_port,*dst_addr,*dst_port,*sockfd, *noneed;
			proto=new char[4];
			local_addr= new char[30];
		    local_port=new char[20];
    		dst_addr=new char[30];
    		dst_port=new char[20];
			sockfd=new char[10];
	/*		
			char* noneed;
			char *proto=new char[4];
			char *local_addr= new char[30];
		    char *local_port=new char[20];
    		char *dst_addr=new char[30];
    		char *dst_port=new char[20];
			char *sockfd=new char[10];
			char* noneed;*/


			proto=protocal[i];
			noneed=strtok(line," ");
			local_addr=strtok(NULL," :");
			local_port=strtok(NULL," :");
			
			dst_addr=strtok(NULL," :");
			dst_port=strtok(NULL," :");
			for(int t=0;t<6;t++)
				noneed=strtok(NULL," ");
			sockfd=strtok(NULL," ");
			cout<<"mychk "
				<<proto<<" "
				<<local_addr<<" "
				<<local_port<<" "
				<<dst_addr<<" "
				<<dst_port<<" "
				<<sockfd
				<<endl;
/*			cout<<"address chk "
				<<&proto<<" "
				<<&local_addr<<" "
				<<&local_port<<" "
				<<&dst_addr<<" "
				<<&dst_port<<" "
				<<&sockfd
				<<endl;
			*/
			Conn[conncount]=Connection(proto,local_addr,local_port,dst_addr,dst_port,sockfd);
			cout<<"after construct"<<endl;
			conncount++;
		
		/*	for(int i=0;i<conncount;i++)
			{
				cout<<Conn[i].proto<<"\t"
				<<Conn[i].local_addr<<":"<<Conn[i].local_port<<"\t"
				<<Conn[i].dst_addr<<":"<<Conn[i].dst_port<<"\t"
				<<Conn[i].sockfd
				<<endl;


			}*/
		}
	}

	showConnInfo(Conn,conncount);
	exit(1);
#endif
	for(int i=0;i<4;i++)
	{
		fgets(line,MAXLINE,fp[i]);
		while(fgets(line,MAXLINE,fp[i]))
		{
			cout << "readline:" << line << endl;
			//char *proto,*local_addr,*local_port,*dst_addr,*dst_port,*sockfd, *noneed;
			/*proto=new char[4];
			local_addr= new char[30];
		    local_port=new char[20];
    		dst_addr=new char[30];
    		dst_port=new char[20];
			sockfd=new char[10];
			*/
			char* noneed;
		/*	char *proto=new char[4];
			char *local_addr= new char[30];
		    char *local_port=new char[20];
    		char *dst_addr=new char[30];
    		char *dst_port=new char[20];
			char *sockfd=new char[10];
			char* noneed;*/


			Conn[conncount].proto=protocal[i];
			noneed=strtok(line," ");
			strcpy(Conn[conncount].local_addr,strtok(NULL," :"));
			strcpy(Conn[conncount].local_port,strtok(NULL," :"));
			
			strcpy(Conn[conncount].dst_addr,strtok(NULL," :"));
			strcpy(Conn[conncount].dst_port,strtok(NULL," :"));
			for(int t=0;t<6;t++)
				noneed=strtok(NULL," ");
			//Conn[conncount].sockfd=strtok(NULL," ");
			strcpy(Conn[conncount].sockfd,strtok(NULL," "));
			cout<<"mychk "
				<<Conn[conncount].proto<<" "
				//<<local_addr<<" "
				//<<local_port<<" "
				//<<dst_addr<<" "
				//<<dst_port<<" "
				<<Conn[conncount].sockfd
				<<endl;
/*			cout<<"address chk "
				<<&proto<<" "
				<<&local_addr<<" "
				<<&local_port<<" "
				<<&dst_addr<<" "
				<<&dst_port<<" "
				<<&sockfd
				<<endl;
			*/
		//	Conn[conncount]=Connection(proto,local_addr,local_port,dst_addr,dst_port,sockfd);
			cout<<"after construct"<<endl;
			conncount++;
		


		}
	}
	//finding pid
	DIR* mydir;
	mydir=opendir("/proc/2106/fd");
	struct dirent *mydirent;
	mydirent=readdir(mydir);
	cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
	mydirent=readdir(mydir);
	cout<<"proc's dirent: "<<mydirent->d_ino<<" "<<mydirent->d_off<<" "<<mydirent->d_name<<endl;
}

void showConnInfo(Connection *Conn, int cnt)
{
	cout<<"List of connections:\nProto Local Address\tForeign Address\tPID/Program name and arguments"<<endl;
	for(int i=0;i<cnt;i++)
	{
		cout<<Conn[i].proto<<"\t"
		<<Conn[i].local_addr<<":"<<Conn[i].local_port<<"\t"
		<<Conn[i].dst_addr<<":"<<Conn[i].dst_port<<"\t"
		<<Conn[i].sockfd
		<<endl;


	}
}











