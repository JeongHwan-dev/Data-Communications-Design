#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <WS2tcpip.h>
#include <string.h>		// strncpy() �Լ� ����ϱ� ���� �������
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024
#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main(int argc, char** argv) {

	SOCKET clntSock;
	WSADATA wsaData;
	SOCKADDR_IN servAddr;

	char sAddr[15];
	int sPort;
	int nRcv;
	unsigned int Addr;
	char message[BUFSIZE];
	struct hostent* host;
	printf("Server Address : ");       gets(sAddr);
	printf("Port Number : ");       gets(message);
	sPort = atoi(message);

	// ������ ���� ���̺귯���� ws2_32.lib�� �ʱ�ȭ ���ִ� ���� 
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ���� ����, ��κ� AF_INET ��� / TCP- SOCK_STREAM , UDP- SOCK_DGRAM / 0 : PROTOCOL �� AUTO�� ���� 
	clntSock = socket(AF_INET, SOCK_STREAM, 0);

	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	auto ret = inet_pton(AF_INET, sAddr, (void*)&servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(sPort);	// servAddr ����ü�� ip�ּҿ� port��ȣ ����.
	

	// ������ ������ ����ü�� �̿�, server�� ���� ��û
	connect(clntSock, (void*)&servAddr, sizeof(servAddr));

	while (1) {
		printf("\nSend Message : ");
		gets(message);

		send(clntSock, message, (int)strlen(message), 0);

		printf("Message Receives ...\n");

		/* 
			strncmp �Լ�
			�Լ� ���� : char* strncpy(char* dest, const char* origin, size_t_n);
			origin�� �ִ� ���ڿ��� dest�� ���縦 �ϴµ�, n��ŭ�� �����ϴ� �Լ��̴�.
			( ���⼭ �����ؾ� �� ���� ���ڿ� ��('\0')���� �����ϹǷ� n���� ���Ϸ��� �ܾ��� ũ�⿡ +1�� ������ ���� �ִ´�. )
			dest�� origin�� ��ġ�ϸ� 0�� �����Ѵ�.
			�׷��Ƿ� if�� ���ǿ� !strncmp�� �־��־� ���� message�� "end" ���� ������
			0�� ��ȯ�ϰ� '!'�� 0�� 1(True)�� ������־� if���� �����Ű�� �ڵ带 ����� �ش�.
		*/
		if (!strncmp(message, "end", 4)) {
			break;	// �ݺ����� �����.
		}

		nRcv = recv(clntSock, message, sizeof(message), 0);
		message[nRcv] = '\0';	// ���� ������ �� ����.

		printf("Receive Message : %s", message);

	}	//READ & Write

	closesocket(clntSock);	// Ŭ���̾�Ʈ ����
	WSACleanup();
	printf("Close Connection..\n");
	_getch();

	return 0;
}