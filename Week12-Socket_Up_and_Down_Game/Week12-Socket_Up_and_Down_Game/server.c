#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

int main(int argc, char** argv) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;

	char message[BUFSIZE];
	int strLen;
	int fromLen, nRcv;
	int answer = 30;  // ���� ���ڸ� 30���� ����

	// ������ ���� ���̺귯���� ws2_32.lib�� �ʱ�ȭ ���ִ� ���� 
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ���� ����, ��κ� AF_INET ��� / TCP- SOCK_STREAM , UDP- SOCK_DGRAM / 0 : PROTOCOL �� AUTO�� ���� 
	servSock = socket(PF_INET, SOCK_STREAM, 0);

	// servAddr ����ü�� ip�ּҿ� port��ȣ ����.
	memset(&servAddr, 0, sizeof(servSock));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[1]));
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// servSock ip�ּҿ� port��ȣ bind.
	bind(servSock, (void*)&servAddr, sizeof(servAddr));

	listen(servSock, 2);	//	listen ����. ���� ���ڴ� ������ �� �ǹ�

	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);

	closesocket(servSock);

	while (1) {
		printf("Message Receives ...\n");

		// clntSock: �����͸� ������ ����.
		// message : ���ŵ� �����͸� ���� char*�� ����.
		// sizeof(message) : �����ϱ� ���ϴ� ũ��, Ȥ�� ������ ũ��	
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);

		message[nRcv] = '\0';	//���� ������ �� ����.
		
		/* 
			atoi() �Լ��� ���ڿ��� ������ ��ȯ�����ִ� �Լ��̴�.
			client �Լ����� ���� ���� message�� ��� ���ڿ��� ������ ��ȯ�Ͽ�
			answer �� ���� 30�� ���� �ش�. 
		*/
		if (answer < atoi(message)) {       // ���� ������ �޽��� ���ڰ� 30���� ũ��
			send(clntSock, "down", 4, 0);   // "down"�� ����
		}
		else if (answer > atoi(message)) {  // ���� ������ �޽��� ���ڰ� 30���� ������
			send(clntSock, "up", 2, 0);     // "up"�� ����
		}
		else {                              // ���� ������ �޽��� ���ڰ� 30�̶��
			send(clntSock, "Congratulation", 14, 0);  // "Congratulatuon"�� ����
		}

		// send(clntSock, message, (int)strlen(message), 0);
		// clntSock: �����͸� �����ϱ� ���ϴ� ����� ����.
		// message: ������ �����Ͱ� ��� char*�� ����.
		// strlen(message) : ������ �������� ũ��.

	}	// READ & Write
	closesocket(clntSock);
	WSACleanup();
	_getch();

	return 0;
}