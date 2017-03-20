#include <iostream>
#include <string.h>
#include "Connection.h"

using namespace std;

Connection::Connection()
{
	proto=new char[4];
	local_addr=new char[30];
	local_port=new char[20];
	dst_addr=new char[30];
	dst_port=new char[20];
	sockfd=new char[10];
	pid=new char[10];
	pro_name=new char[30];
}
Connection::Connection(char* p, char* la, char* lp,  char* da, char* dp, char* s)
{
	proto=new char[4];
	local_addr=new char[30];
	local_port=new char[20];
	dst_addr=new char[30];
	dst_port=new char[20];
	sockfd=new char[10];
	pid=new char[10];
	pro_name=new char[30];
	/*proto=p;
	local_addr=la;
	local_port=lp;
	dst_addr=da;
	dst_port=dp;
	sockfd=s;
	pid="";
	pro_name="";*/
	/*strcpy(proto,p);
	strcpy(local_addr,la);
	strcpy(local_port,lp);
	strcpy(dst_addr,da);
	strcpy(dst_port,dp);
	strcpy(sockfd,s);*/
}
