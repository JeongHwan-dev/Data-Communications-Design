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

	// 윈도우 소켓 라이브러리인 ws2_32.lib를 초기화 해주는 역할 
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	// 소켓 생성, 대부분 AF_INET 사용 / TCP- SOCK_STREAM , UDP- SOCK_DGRAM / 0 : PROTOCOL 을 AUTO로 설정 
	clntSock = socket(AF_INET, SOCK_STREAM, 0);

	// servAddr 구조체의 ip주소와 port번호 정의.
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	auto ret = inet_pton(AF_INET, sAddr, (void*)&servAddr.sin_addr.s_addr);
	servAddr.sin_port = htons(sPort);

	// 위에서 정의한 구조체를 이용, server에 연결 요청
	connect(clntSock, (void*)&servAddr, sizeof(servAddr));

	nRcv = recv(clntSock, message, sizeof(message), 0); // 단어 길이 메시지 전달 받기

	// atoi()함수는 문자열을 정수로 변환시켜주는 함수
	printf("맞춰야할 단어 길이 : %d", atoi(message));    // 맞춰야할 단어 길이 출력

	while (1) {
		printf("\n알파벳 입력 : ");
		gets(message);                                     // 메시지 입력 받기
		send(clntSock, message, (int)strlen(message), 0);  // 입력받은 메시지 전송

		nRcv = recv(clntSock, message, sizeof(message), 0); // 메시지 전달 받기
		message[nRcv] = '\0';  // 받은 문자의 끝 정의.

		printf("결과 : %s", message); // 전달 받은 결과 메시지 출력                    

		// strcmp() 함수를 이용하여 message에 담긴 값이 "정답"인지 확인
		if (!strcmp(message, "정답", 5)) { // 만약 메시지에 "정답"이 담겨 오면
			break;                         // 반복문 종료
		}
	}	// READ & Write

	closesocket(clntSock);
	WSACleanup();
	printf("\n");
	printf("Close Connection..\n");
	_getch();

	return 0;
}