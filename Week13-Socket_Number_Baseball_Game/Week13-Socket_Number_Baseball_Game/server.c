#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

// �Լ� ����
int checkStrike(int*, int*);		// Strike ī��Ʈ �Լ� ���� 
int checkBall(int*, int*);			// Ball ī��Ʈ �Լ� ����
int checkOut(int strike, int ball); // Out ī��Ʈ �Լ� ����

int main(int argc, char** argv) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;

	char message[BUFSIZE];
	int strLen;
	int fromLen, nRcv;

	int computer[3] = { 3, 6, 5 };		// ���� ���ڸ� 365�� ����
	int user[3];					    // ����ڰ� ������ ���ڸ� ���� �迭
	int strike = 0, ball = 0, out = 0;  // Strike, Ball, Out ���� ī��Ʈ 0���� �ʱ�ȭ
	int result;							// ����� (Strike_cout Ball_cout Out_cout) ���� ����

	// ������ ���� ���̺귯���� ws2_32.lib�� �ʱ�ȭ ���ִ� ���� 
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// ���� ����, ��κ� AF_INET ��� / TCP- SOCK_STREAM , UDP- SOCK_DGRAM / 0 : PROTOCOL �� AUTO�� ���� 
	servSock = socket(PF_INET, SOCK_STREAM, 0);

	// servAddr ����ü�� ip�ּҿ� port��ȣ ����.
	memset(&servAddr, 0, sizeof(servSock));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[1]));
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(servSock, (void*)&servAddr, sizeof(servAddr)); // servSock ip�ּҿ� port��ȣ bind.
	listen(servSock, 2); // listen ����. ���� ���ڴ� ������ �� �ǹ�
	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);

	closesocket(servSock);
	while (1) {
		printf("Message Receives ...\n");

		// clntSock: �����͸� ������ ����.
		// message : ���ŵ� �����͸� ���� char*�� ����.
		// sizeof(message) : �����ϱ� ���ϴ� ũ��, Ȥ�� ������ ũ��
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);

		// message[nRcv] = '\0';
		// ���� ������ �� ����.

		/* 
		   atoi() �Լ��� ���ڿ��� ������ ��ȯ�����ִ� �Լ��̴�.
		   ���� �Լ��� �̿��Ͽ� 100�� �ڸ�, 10�� �ڸ�, 1�� �ڸ���
		   �и��� �� ���̴�.

		   ��, 100�� �ڸ� ���ڴ� ����ڰ� ù��° �Է��� ����,
		   10�� �ڸ� ���ڴ� ����ڰ� �ι�° �Է��� ����,
		   1�� �ڸ� ���ڴ� ����ڰ� ����° �Է��� �����̴�.
		*/
		user[0] = atoi(message) / 100;         // 100�� �ڸ� ���ڸ� ����       
		user[1] = (atoi(message) % 100) / 10;  // 10�� �ڸ� ���ڸ� ����
		user[2] = (atoi(message) % 100) % 10;  // 1�� �ڸ� ���ڸ� ���� 

		strike = checkStrike(computer, user);  // Strike ī��Ʈ �Լ� ȣ��
		ball = checkBall(computer, user);      // Ball ī��Ʈ �Լ� ȣ��
		out = checkOut(strike, ball);          // Out ī��Ʈ �Լ� ȣ��

		if (strike == 3) {                       // ���� Strike ī��Ʈ�� 3�̸�,
			send(clntSock, "�����Դϴ�", 11, 0);  // '�����Դϴ�'�� �����Ѵ�. 
		}
		else {
			result = (100 * strike + 10 * ball + out);  // strike, out, ball ī��Ʈ�� ���ڸ� ���ڷ� ǥ���Ͽ� ����

			// _itoa_s �Լ��� ����Ͽ� ������(result)�� ������(message)���� ���������ش�.)
			_itoa_s(result, message, 10, 10);
			send(clntSock, message, (int)strlen(message), 0);
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

// �Լ� ������
// Strike ī��Ʈ �Լ�
int checkStrike(int* computer, int* user) {
	int strike = 0;
	int i;

	/* 
	   user�� computer �迭���� �ε����� ���� ���� ���� ���� ���
	   strike�� 1�� ī��Ʈ 
	*/
	for (i = 0; i < 3; i++) {
		if (user[i] == computer[i]) {
			strike++;
		}
	}
	return strike;
}

// Ball ī��Ʈ �Լ�
int checkBall(int* computer, int* user) {
	int ball = 0;
	int i, j;

	/* 
	   user�� computer �迭���� �ε����� �ٸ��� ���� ���� ���� ���
	   ball�� 1�� ī��Ʈ 
	*/
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (i == j) {
				continue;	// �ε����� ���� ��� �������� ���� ��Ų��.
			}
			else {
				if (user[i] == computer[j]) {
					ball++;
				}
			}
		}
	}
	return ball;
}

// Out ī��Ʈ �Լ�
int checkOut(int strike, int ball) {
	int out = 0;

	/* 
	   strike + ball + out �� ���� �׻� 3���� ���;� �Ѵ�.
	   �׷��Ƿ� strike ���� ball ���� �˰� ���� ��
	   ���� ���� ���� out���� ���� �� �ִ�.
	*/
	out = 3 - (strike + ball);
	
	return out;
}