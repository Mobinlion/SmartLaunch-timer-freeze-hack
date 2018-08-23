// SmartLaunch.cpp : Defines the entry point for the console application.
//

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
	char a[34]={'A','d','m' ,'i' ,'n' ,'I' ,'D' ,'=','1' ,'{' ,'e' ,'n'
		,'d' ,'}' ,'C', 'h','e' ,'c' ,'k'  ,'F','o' ,'r' ,'U'  ,'p',
		'd','a','t' ,'e' ,'s' ,'{' ,'e' ,'n','d','}'};

	if(send(s1,a,sizeof(a),0)==SOCKET_ERROR)
		cout<<"socket error on send\n";

	cout<<"this is line one sent.\n";

	
	Sleep(600); 
	//try sizeof(b)-1 and reduce nul character from string
	// and is Nul character 00 in hexadecimal?
	char b[]="GetCurrentCashier{end}";
	if(send(s1,b,(sizeof(b)-1),0)==SOCKET_ERROR)
		cout<<"Socket error on send\n";

	Sleep(200);
	char login[40];
	char pass[40];
	cout<<"type in username and pass:";
	cin>>login;
	cin>>pass;
	
	//char c[]="Logon=Admin^admin{end}";
	char c[90];
	int fandom=sprintf(c,"Logon=%s^%s{end}",login,pass);
	send(s1,c,fandom-1,0);

	Sleep(600);
	
	char d[]="FirstConnection{end}";
	send (s1,d,(sizeof(d)-1),0);
	Sleep(1000);

	//char e[]="ReceiptBeginTransaction{end}UserAddTime=miochen^290.5^1^True{end}ReceiptEndTransaction{end}";  //adds money
	//char e[]="ReceiptBeginTransaction{end}UserAddSpecialTime=miochen^600^0^1^True{end}UserOpenAccount=miochen{end}ReceiptEndTransaction{end}";  //adds time
	char e[256];
	memset(e,'\0',sizeof(e));
	char name[20];
	cout<<"name1: ";
	cin>>name;
	int rtn=sprintf(e,"ReceiptBeginTransaction{end}UserAddSpecialTime=%s^600^0^1^True{end}UserOpenAccount=miochen{end}ReceiptEndTransaction{end}",name);
	cout<<e<<endl;
	//char kalam;
	//cin>>kalam;
	send(s1,e,rtn-1,0);
	Sleep(500);
	//char ff[]="Connection Idle{end}";
	//send(s1,ff,sizeof(ff)-1,0);
	char ff1[]="Error{end}";
	send(s1,ff1,sizeof(ff1)-1,0);
	/*
	char e2[]="ReceiptBeginTransaction{end}UserAddSpecialTime=miochen^600^0^1^True{end}UserOpenAccount=miochen{end}ReceiptEndTransaction{end}";  //adds time
	send(s1,e2,sizeof(e2),0);
	Sleep(500);
	char e3[]="ReceiptBeginTransaction{end}UserAddSpecialTime=miochen^600^0^1^True{end}UserOpenAccount=miochen{end}ReceiptEndTransaction{end}";  //adds time
	send(s1,e3,sizeof(e3),0);
	Sleep(500);*/


	closesocket(s1);


	//cout<<endl<<"********"<<inet_addr("192.168.1.2")<<"*****"<<endl;
	return 0;
}
