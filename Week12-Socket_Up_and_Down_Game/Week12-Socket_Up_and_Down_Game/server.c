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
	int answer = 30;  // 맞힐 숫자를 30으로 설정

	// 윈도우 소켓 라이브러리인 ws2_32.lib를 초기화 해주는 역할 
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 소켓 생성, 대부분 AF_INET 사용 / TCP- SOCK_STREAM , UDP- SOCK_DGRAM / 0 : PROTOCOL 을 AUTO로 설정 
	servSock = socket(PF_INET, SOCK_STREAM, 0);

	// servAddr 구조체의 ip주소와 port번호 정의.
	memset(&servAddr, 0, sizeof(servSock));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[1]));
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	// servSock ip주소와 port번호 bind.
	bind(servSock, (void*)&servAddr, sizeof(servAddr));

	listen(servSock, 2);	//	listen 과정. 뒤의 숫자는 접속자 수 의미

	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);

	closesocket(servSock);

	while (1) {
		printf("Message Receives ...\n");

		// clntSock: 데이터를 수신할 소켓.
		// message : 수신된 데이터를 담을 char*형 버퍼.
		// sizeof(message) : 수신하길 원하는 크기, 혹은 버퍼의 크기	
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);

		message[nRcv] = '\0';	//받은 문자의 끝 정의.
		
		/* 
			atoi() 함수는 문자열을 정수로 변환시켜주는 함수이다.
			client 함수에서 전송 받은 message에 담긴 문자열을 정수로 변환하여
			answer 즉 숫자 30과 비교해 준다. 
		*/
		if (answer < atoi(message)) {       // 만약 보내온 메시지 숫자가 30보다 크면
			send(clntSock, "down", 4, 0);   // "down"을 전송
		}
		else if (answer > atoi(message)) {  // 만약 보내온 메시지 숫자가 30보다 작으면
			send(clntSock, "up", 2, 0);     // "up"을 전송
		}
		else {                              // 만약 보내온 메시지 숫자가 30이라면
			send(clntSock, "Congratulation", 14, 0);  // "Congratulatuon"을 전송
		}

		// send(clntSock, message, (int)strlen(message), 0);
		// clntSock: 데이터를 전송하길 원하는 연결된 소켓.
		// message: 전송할 데이터가 담긴 char*형 버퍼.
		// strlen(message) : 전송할 데이터의 크기.

	}	// READ & Write
	closesocket(clntSock);
	WSACleanup();
	_getch();

	return 0;
}