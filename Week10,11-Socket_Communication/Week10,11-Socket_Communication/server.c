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
	
	listen(servSock, 2); // listen 과정. 뒤의 숫자는 접속자 수 의미
	
	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);

	closesocket(servSock);
	while (1) {
		printf("Message Receives ...\n");

		//	clntSock: 데이터를 수신할 소켓.
		//	message : 수신된 데이터를 담을 char*형 버퍼.
		//	sizeof(message) : 수신하길 원하는 크기, 혹은 버퍼의 크기
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);
		message[nRcv] = '\0';	// 받은 문자의 끝 정의.
		
		printf("Receive Message : %s", message);
		printf("\nSend Message : ");

		/*
		  에코 서버를 만들기 위해서 메시지를 새로 입력 받지 않고 들어온 메시지를 그대로 다시 클라이언트로
		  보내주기 위해서는 다시 메시지를 입력받는 함수 gets()을  호출하지 않고 그대로 들어온 메시지를 전달해야한다.
		  그렇게 처리하기 위해서 아래의 함수 호출 코드를 주석처리 해주면 된다. 
		*/

		/* 
			strncmp 함수
			함수 원형 : char* strncpy(char* dest, const char* origin, size_t_n);
			origin에 있는 문자열을 dest로 복사를 하는데, n만큼만 복사하는 함수이다.
			( 여기서 주의해야 할 점은 문자열 끝('\0')까지 복사하므로 n에는 비교하려는 단어의 크기에 +1을 더해준 값을 넣는다. )
			dest와 origin이 일치하면 0을 리턴한다.
			그러므로 if문 조건에 !strncmp로 넣어주어 만약 message에 "end" 값이 들어오면
			0을 반환하고 '!'가 0을 1(True)로 만들어주어 if문을 실행시키는 코드를 만들어 준다.
		*/
		if (!strncmp(message, "end", 4))
			break;	// 반복문을 벗어난다.

		// clntSock: 데이터를 전송하길 원하는 연결된 소켓.
		// message: 전송할 데이터가 담긴 char*형 버퍼.
		// strlen(message) : 전송할 데이터의 크기.
		send(clntSock, message, (int)strlen(message), 0);

	}	// READ & Write
	closesocket(clntSock);	// 서버 종료
	WSACleanup();
	printf("Close Connection..\n");
	_getch();

	return 0;
}