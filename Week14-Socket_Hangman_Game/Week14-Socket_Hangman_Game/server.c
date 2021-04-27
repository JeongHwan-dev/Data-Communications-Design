#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

// 함수 선언
int check(int length); // 정답 체크 함수 

char word[20];	 // 문제 단어를 저장할 배열		
char blank[20];	 // 빈칸 배열
int i;			 // 반복문에 이용할 변수					

int main(int argc, char** argv) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;

	char message[BUFSIZE];
	int strLen;
	int fromLen, nRcv;

	int length; // 단어 길이를 저장할 변수

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

	listen(servSock, 2);	// listen 과정. 뒤의 숫자는 접속자 수 의미

	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);
	closesocket(servSock);

	printf("행맨 단어를 입력하세요 : ");
	gets(word);		// 행맨 단어 입력받기

	// strlen(문자열) 함수를 이용하여 문자열 길이를 구해준다.
	length = strlen(word); // 입력받은 word 단어의 길이를 length 변수에 저장

	// 반복문을 이용해 단어 길이만큼 blank 배열을 '_'로 초기화 시켜준다.
	for (i = 0; i < length; i++) {
		blank[i] = '_';
	}

	// _itoa_s 함수를 사용하여 정수형(length)를 문자형(message)으로 변형시켜준다.
	_itoa_s(length, message, 10, 10);
	send(clntSock, message, 10, 0);		// 단어 길이 전송
	while (1) {
		printf("Message Receives ...\n");

		// clntSock: 데이터를 수신할 소켓.
		// message : 수신된 데이터를 담을 char*형 버퍼.
		// sizeof(message) : 수신하길 원하는 크기, 혹은 버퍼의 크기
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);


		for (i = 0; i < length; i++)      // 반복문을 이용하여 전달받은 문자와 정답을 비교
		{
			if (word[i] == message[0]) {  // 만약 전달받은 문자가 정답안에 있으면 그 위치(i)를 확보하게 된다.
				blank[i] = message[0];    // 확보한 위치(i)를 활용하여 빈칸 배열[i]에 전달받은 문자 저장
			}
		}

		if (check(length) == 1) {		   // 체크 함수를 호출하여 성공을 확인 할 경우		
			send(clntSock, "정답", 10, 0); // "정답" 메시지를 전송하고
			break;                         // break를 걸어 반복문 종료 
		}
		else {                                            // 아직 완전히 정답을 맞추지 못했으면
			send(clntSock, blank, (int)strlen(blank), 0); // blank 배열값 전송
		}

		// clntSock: 데이터를 전송하길 원하는 연결된 소켓.
		// message: 전송할 데이터가 담긴 char*형 버퍼.
		// strlen(message) : 전송할 데이터의 크기.
	}	// READ & Write
	closesocket(clntSock);
	WSACleanup();
	printf("Close Connection..\n");
	_getch();

	return 0;
}

// 정답 체크 함수 정의
int check(int length) // 단어 길이를 매개변수로 받아온다
{
	int result;       // 결과값을 담을 변수, 정답이면 1, 아직 정답이 아니면 0

	// 반복문을 이용하여 word 배열에 들어있는 값과 blank 배열에 들어있는 값 비교
	for (i = 0; i < length; i++) {
		if (word[i] != blank[i]) { // 만약 서로 다른 값이 있다면
			result = 0;            // result에 0을 대입하고
			break;                 // 반복문 종료 (하나라도 틀리면 더 이상 비교가 무의미 하므로)
		}
		else {
			result = 1; // 모두 같다면 result에 계속 1을 대입
		}
	}

	return result; // 체크 결과를 확인할 수 있는 result값 반환
}