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
	
	listen(servSock, 2); // listen ����. ���� ���ڴ� ������ �� �ǹ�
	
	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);

	closesocket(servSock);
	while (1) {
		printf("Message Receives ...\n");

		//	clntSock: �����͸� ������ ����.
		//	message : ���ŵ� �����͸� ���� char*�� ����.
		//	sizeof(message) : �����ϱ� ���ϴ� ũ��, Ȥ�� ������ ũ��
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);
		message[nRcv] = '\0';	// ���� ������ �� ����.
		
		printf("Receive Message : %s", message);
		printf("\nSend Message : ");

		/*
		  ���� ������ ����� ���ؼ� �޽����� ���� �Է� ���� �ʰ� ���� �޽����� �״�� �ٽ� Ŭ���̾�Ʈ��
		  �����ֱ� ���ؼ��� �ٽ� �޽����� �Է¹޴� �Լ� gets()��  ȣ������ �ʰ� �״�� ���� �޽����� �����ؾ��Ѵ�.
		  �׷��� ó���ϱ� ���ؼ� �Ʒ��� �Լ� ȣ�� �ڵ带 �ּ�ó�� ���ָ� �ȴ�. 
		*/

		/* 
			strncmp �Լ�
			�Լ� ���� : char* strncpy(char* dest, const char* origin, size_t_n);
			origin�� �ִ� ���ڿ��� dest�� ���縦 �ϴµ�, n��ŭ�� �����ϴ� �Լ��̴�.
			( ���⼭ �����ؾ� �� ���� ���ڿ� ��('\0')���� �����ϹǷ� n���� ���Ϸ��� �ܾ��� ũ�⿡ +1�� ������ ���� �ִ´�. )
			dest�� origin�� ��ġ�ϸ� 0�� �����Ѵ�.
			�׷��Ƿ� if�� ���ǿ� !strncmp�� �־��־� ���� message�� "end" ���� ������
			0�� ��ȯ�ϰ� '!'�� 0�� 1(True)�� ������־� if���� �����Ű�� �ڵ带 ����� �ش�.
		*/
		if (!strncmp(message, "end", 4))
			break;	// �ݺ����� �����.

		// clntSock: �����͸� �����ϱ� ���ϴ� ����� ����.
		// message: ������ �����Ͱ� ��� char*�� ����.
		// strlen(message) : ������ �������� ũ��.
		send(clntSock, message, (int)strlen(message), 0);

	}	// READ & Write
	closesocket(clntSock);	// ���� ����
	WSACleanup();
	printf("Close Connection..\n");
	_getch();

	return 0;
}