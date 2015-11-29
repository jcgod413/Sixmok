#include "MySocket.h"
/*============================================================================================*/
/*===============================  socket basic fuction   ====================================*/
/*============================================================================================*/
MySocket::MySocket(int dataLength)
	:DATA_LENGTH(dataLength)
{
}
MySocket::~MySocket(void)
{
}
void MySocket::ErrorHandle(char *message)
{
	fputs(message,stderr);
	fputc('\n',stderr);
	system("pause");
	exit(1);
}
void MySocket::SocketInit()
{
	if(WSAStartup(MAKEWORD(2,2),&wsaData)!=0)
	{// Initialize the Version of Socket (v2.2)
		ErrorHandle("WSAStartup() error!");
	}
}
/*============================================================================================*/
/*=============================   Server socket fuction   ====================================*/
/*============================================================================================*/
void MySocket::ServerSetting()
{
	SocketInit();
	servSock=socket(AF_INET,SOCK_STREAM,0);
	if(servSock==INVALID_SOCKET)
	{
		ErrorHandle("servSock error!");
	}
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;//ipv4 setting
	servAddr.sin_addr.s_addr=htonl(INADDR_ANY);//server ip setting
	servAddr.sin_port=htons(SERVER_PORT);//port setting
}

void MySocket::ServerRun()
{
	if(bind(servSock,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR)
	{
		ErrorHandle("bind() error!");
	}
	
	if(listen(servSock,SOMAXCONN)==SOCKET_ERROR)
	{
		ErrorHandle("listen() error!");
	}

	clntAddrSize=sizeof(clntAddr);
	clntSock=accept(servSock,(SOCKADDR*)&clntAddr,&clntAddrSize);
	if(clntSock==INVALID_SOCKET)
	{
		ErrorHandle("accept() error!");
	}else{
		cout<<"¿¬°áµÈ »õÅ¬¶óÀÌ¾ðÆ®IP : "<<inet_ntoa(clntAddr.sin_addr)<<endl;
	}
}

void MySocket::ServerClose() // Closing the server function
{
	closesocket(servSock);
	closesocket(clntSock);
	WSACleanup(); 
}
/*============================================================================================*/
/*=============================   Client socket fuction   ====================================*/
/*============================================================================================*/
void MySocket::ClientSetting()
{
	SocketInit();
	clntSock=socket(AF_INET,SOCK_STREAM,0);
	if(clntSock==INVALID_SOCKET)
	{
		ErrorHandle("servSock error!");
	}
	memset(&servAddr,0,sizeof(servAddr));
	servAddr.sin_family=AF_INET;// ipv4 setting
	servAddr.sin_addr.s_addr=inet_addr(SERVER_IP);// server ip setting
	servAddr.sin_port=htons(SERVER_PORT);// port setting
}
void MySocket::ClientRun()
{
	if(connect(clntSock,(SOCKADDR*)&servAddr,sizeof(servAddr))==SOCKET_ERROR){
		ErrorHandle("connect() error!");
	}
}

void MySocket::ClientClose()  // Closing the Client function
{
	closesocket(clntSock);
	WSACleanup();
}

/*============================================================================================*/
/*================================   User usable function   ==================================*/
/*============================================================================================*/
UINT WINAPI MySocket::SendData(void *args)
{
	send(clntSock,(char*)args,DATA_LENGTH,0);
	return 0;
}

UINT WINAPI MySocket::RecvData(void *args)
{
	recv(clntSock,(char*)args,DATA_LENGTH,0);
	return 0;
}