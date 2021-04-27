#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <WS2tcpip.h>
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
	printf("Server Address : ");       
	gets(sAddr);
	printf("Port Number : ");       
	gets(message);
	sPort = atoi(message);

	// ������ ���� ���̺귯���� ws2_32.lib�� �ʱ�ȭ ���ִ� ���� 
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	// ���� ����, ��κ� AF_INET ��� / TCP- SOCK_STREAM , UDP- SOCK_DGRAM / 0 : PROTOCOL �� AUTO�� ���� 
	clntSock = socket(AF_INET, SOCK_STREAM, 0);

	// servAddr ����ü�� ip�ּҿ� port��ȣ ����.
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	auto ret = inet_pton(AF_INET, sAddr, (void*)&servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(sPort);

	// ������ ������ ����ü�� �̿�, server�� ���� ��û
	connect(clntSock, (void*)&servAddr, sizeof(servAddr));

	nRcv = recv(clntSock, message, sizeof(message), 0); // �ܾ� ���� �޽��� ���� �ޱ�

	// atoi()�Լ��� ���ڿ��� ������ ��ȯ�����ִ� �Լ�
	printf("������� �ܾ� ���� : %d", atoi(message));    // ������� �ܾ� ���� ���

	while (1) {
		printf("\n���ĺ� �Է� : ");
		gets(message);                                     // �޽��� �Է� �ޱ�
		send(clntSock, message, (int)strlen(message), 0);  // �Է¹��� �޽��� ����

		nRcv = recv(clntSock, message, sizeof(message), 0); // �޽��� ���� �ޱ�
		message[nRcv] = '\0';  // ���� ������ �� ����.

		printf("��� : %s", message); // ���� ���� ��� �޽��� ���                    

		// strcmp() �Լ��� �̿��Ͽ� message�� ��� ���� "����"���� Ȯ��
		if (!strcmp(message, "����", 5)) { // ���� �޽����� "����"�� ��� ����
			break;                         // �ݺ��� ����
		}
	}	// READ & Write

	closesocket(clntSock);
	WSACleanup();
	printf("\n");
	printf("Close Connection..\n");
	_getch();

	return 0;
}