#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <iostream>
#include <stdio.h>
#include <WinSock2.h>

using namespace std;

#pragma comment(lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	
	SOCKADDR_IN ServerSockAddr;
	memset(&ServerSockAddr, 0, sizeof(ServerSockAddr));
	ServerSockAddr.sin_family = PF_INET;
	ServerSockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	ServerSockAddr.sin_port = htons(3001);

	connect(ServerSocket, (SOCKADDR*)&ServerSockAddr, sizeof(ServerSockAddr));



	while (1)
	{
		char* Buffer = new char[512];
		char recvBuf[512] = { 0, };

		cin >> Buffer;

		int RecvByte = 0;
		int SendByte = 0;
		SendByte = send(ServerSocket, Buffer, strlen(Buffer) + 1, 0);

		RecvByte = recv(ServerSocket, recvBuf, 512, 0);
		
		cout << "recvBuf[0]은 " << recvBuf[0] << "입니다." << endl;

		if (recvBuf[0] == '1' && strlen(recvBuf) == 1)
		{
			//cout << recvBuf << endl;

			int checkByte = 0;
			checkByte = recv(ServerSocket, recvBuf, 512, 0);

			cout << recvBuf << endl;

			char* ID = new char[512];
			char* PW = new char[512];

			cin >> ID >> PW;

			SendByte = send(ServerSocket, ID, strlen(ID) + 1, 0);
			SendByte = send(ServerSocket, PW, strlen(PW) + 1, 0);

			char result[512] = { 0, };

			checkByte = recv(ServerSocket, result, 512, 0);

			cout << result << endl;

		}
		else if (recvBuf[0] == '2' && strlen(recvBuf) == 1)
		{
			int checkByte = 0;
			checkByte = recv(ServerSocket, recvBuf, 512, 0);

			cout << recvBuf << endl;

			char* ID = new char[512];
			char* PW = new char[512];

			cin >> ID >> PW;

			SendByte = send(ServerSocket, ID, strlen(ID) + 1, 0);
			SendByte = send(ServerSocket, PW, strlen(PW) + 1, 0);

			char result[512] = { 0, };

			checkByte = recv(ServerSocket, result, 512, 0);

			cout << result << endl;
		}

		delete[] Buffer;
	}



	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}