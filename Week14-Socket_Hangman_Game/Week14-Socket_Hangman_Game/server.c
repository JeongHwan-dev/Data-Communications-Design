#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

// �Լ� ����
int check(int length); // ���� üũ �Լ� 

char word[20];	 // ���� �ܾ ������ �迭		
char blank[20];	 // ��ĭ �迭
int i;			 // �ݺ����� �̿��� ����					

int main(int argc, char** argv) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;

	char message[BUFSIZE];
	int strLen;
	int fromLen, nRcv;

	int length; // �ܾ� ���̸� ������ ����

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

	listen(servSock, 2);	// listen ����. ���� ���ڴ� ������ �� �ǹ�

	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);
	closesocket(servSock);

	printf("��� �ܾ �Է��ϼ��� : ");
	gets(word);		// ��� �ܾ� �Է¹ޱ�

	// strlen(���ڿ�) �Լ��� �̿��Ͽ� ���ڿ� ���̸� �����ش�.
	length = strlen(word); // �Է¹��� word �ܾ��� ���̸� length ������ ����

	// �ݺ����� �̿��� �ܾ� ���̸�ŭ blank �迭�� '_'�� �ʱ�ȭ �����ش�.
	for (i = 0; i < length; i++) {
		blank[i] = '_';
	}

	// _itoa_s �Լ��� ����Ͽ� ������(length)�� ������(message)���� ���������ش�.
	_itoa_s(length, message, 10, 10);
	send(clntSock, message, 10, 0);		// �ܾ� ���� ����
	while (1) {
		printf("Message Receives ...\n");

		// clntSock: �����͸� ������ ����.
		// message : ���ŵ� �����͸� ���� char*�� ����.
		// sizeof(message) : �����ϱ� ���ϴ� ũ��, Ȥ�� ������ ũ��
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);


		for (i = 0; i < length; i++)      // �ݺ����� �̿��Ͽ� ���޹��� ���ڿ� ������ ��
		{
			if (word[i] == message[0]) {  // ���� ���޹��� ���ڰ� ����ȿ� ������ �� ��ġ(i)�� Ȯ���ϰ� �ȴ�.
				blank[i] = message[0];    // Ȯ���� ��ġ(i)�� Ȱ���Ͽ� ��ĭ �迭[i]�� ���޹��� ���� ����
			}
		}

		if (check(length) == 1) {		   // üũ �Լ��� ȣ���Ͽ� ������ Ȯ�� �� ���		
			send(clntSock, "����", 10, 0); // "����" �޽����� �����ϰ�
			break;                         // break�� �ɾ� �ݺ��� ���� 
		}
		else {                                            // ���� ������ ������ ������ ��������
			send(clntSock, blank, (int)strlen(blank), 0); // blank �迭�� ����
		}

		// clntSock: �����͸� �����ϱ� ���ϴ� ����� ����.
		// message: ������ �����Ͱ� ��� char*�� ����.
		// strlen(message) : ������ �������� ũ��.
	}	// READ & Write
	closesocket(clntSock);
	WSACleanup();
	printf("Close Connection..\n");
	_getch();

	return 0;
}

// ���� üũ �Լ� ����
int check(int length) // �ܾ� ���̸� �Ű������� �޾ƿ´�
{
	int result;       // ������� ���� ����, �����̸� 1, ���� ������ �ƴϸ� 0

	// �ݺ����� �̿��Ͽ� word �迭�� ����ִ� ���� blank �迭�� ����ִ� �� ��
	for (i = 0; i < length; i++) {
		if (word[i] != blank[i]) { // ���� ���� �ٸ� ���� �ִٸ�
			result = 0;            // result�� 0�� �����ϰ�
			break;                 // �ݺ��� ���� (�ϳ��� Ʋ���� �� �̻� �񱳰� ���ǹ� �ϹǷ�)
		}
		else {
			result = 1; // ��� ���ٸ� result�� ��� 1�� ����
		}
	}

	return result; // üũ ����� Ȯ���� �� �ִ� result�� ��ȯ
}