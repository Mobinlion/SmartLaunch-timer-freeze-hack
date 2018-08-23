// SmartLaunch.cpp : Defines the entry point for the console application.
//
#define _CRT_SECURE_NO_WARNINGS

#include "winsock2.h"
#include "Mswsock.h"
#include "stdafx.h"
#include <fstream>
#include "iostream"
#include <string>
using namespace std;
#include <cstdio>
#include <stdio.h>



int _tmain(int argc, _TCHAR* argv[])
{
	char ipaddr[30];
	unsigned short portnum=0;
	SOCKET s1;
	SOCKADDR_IN add1;
	WSADATA wsadata;
	int ret;
	in_addr addr;

	if((ret=WSAStartup(MAKEWORD(2,2),&wsadata))!=0)
	{
		cout<<"error is this: "<<ret;
			return 0;

	}
	cout<<"ip and then port: ";
	cin>>ipaddr;
	cin>>portnum;

	s1=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	add1.sin_family=AF_INET;
	add1.sin_addr.S_un.S_addr=inet_addr(ipaddr);
	add1.sin_port=htons(portnum);
		
	addr.S_un.S_addr=add1.sin_addr.S_un.S_addr;
	//cout<<"192.168.1.2 to integer to ascii is: "<<add1.sin_addr.S_un.S_addr<<" LOL "<<inet_ntoa(addr)<<endl;
	
	int size=sizeof(add1);

	connect(s1,(SOCKADDR *)&add1,size);

	if(WSAGetLastError()==WSAECONNREFUSED)
		cout<<"error no connection is active\n";

	//char a[]="hello world!!!! SENT DATA TO IT!";
	//cout<<"this is client, data is sent!\n";

	//char a[35]={"AdminID=1{end}CheckForUpdates{end}"};
	//char a[34]={'A','d','m' ,'i' ,'n' ,'I' ,'D' ,'=','1' ,'{' ,'e' ,'n'
	//	,'d' ,'}' ,'C', 'h','e' ,'c' ,'k'  ,'F','o' ,'r' ,'U'  ,'p',
		//'d','a','t' ,'e' ,'s' ,'{' ,'e' ,'n','d','}'};

	
	//if(send(s1,a,sizeof(a),0)==SOCKET_ERROR)
	//	cout<<"socket error on send\n";

	//cout<<"this is line one sent.\n";

	
	//Sleep(600); 
	//try sizeof(b)-1 and reduce nul character from string
	// and is Nul character 00 in hexadecimal?
	char b[]="ClientID=1{end}";
	if(send(s1,b,(sizeof(b)-1),0)==SOCKET_ERROR)
		cout<<"Socket error on send\n";

	Sleep(200);
	char b2[]="CheckForUpdatesAndLanguageFiles{end}";
	send(s1,b2,sizeof(b2)-1,0);

	Sleep(200);

	char b3[]="GetSettings{end}";
	send(s1,b3,sizeof(b3)-1,0);
	Sleep(400);
	char b4[]="GetInitialData{end}";
	send(s1,b4,sizeof(b4)-1,0);
	Sleep(200);

	char b5[]="SetClientInformation=ComputerDetails^4.7.65.0^192.168.1.5^08:00:27:20:7D:11^mcdonald-PC{end}SetClientInformation=IPAddress^192.168.1.5^fe80::38a7:e07:3f57:fefa%14{end}UserNotifyLogin=miochen^5VlQjbCa4zC+tj57hp6EV8Dv2pE={end}Ready{end}";
	send(s1,b5,sizeof(b5)-1,0);
	Sleep(300);
	char b6[]="Ping{end}";
	send(s1,b6,sizeof(b6)-1,0);
	Sleep(300);

	while(true){

	send(s1,b6,sizeof(b6)-1,0);
	Sleep(300);
	}


	closesocket(s1);


	//cout<<endl<<"********"<<inet_addr("192.168.1.2")<<"*****"<<endl;
	return 0;
}
