#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define BUFSIZE 1024

// 함수 선언
int checkStrike(int*, int*);		// Strike 카운트 함수 선언 
int checkBall(int*, int*);			// Ball 카운트 함수 선언
int checkOut(int strike, int ball); // Out 카운트 함수 선언

int main(int argc, char** argv) {
	WSADATA wsaData;
	SOCKET servSock, clntSock;
	SOCKADDR_IN servAddr, clntAddr;

	char message[BUFSIZE];
	int strLen;
	int fromLen, nRcv;

	int computer[3] = { 3, 6, 5 };		// 맞힐 숫자를 365로 설정
	int user[3];					    // 사용자가 예측한 숫자를 담을 배열
	int strike = 0, ball = 0, out = 0;  // Strike, Ball, Out 들의 카운트 0으로 초기화
	int result;							// 결과값 (Strike_cout Ball_cout Out_cout) 담을 변수

	// 윈도우 소켓 라이브러리인 ws2_32.lib를 초기화 해주는 역할 
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	// 소켓 생성, 대부분 AF_INET 사용 / TCP- SOCK_STREAM , UDP- SOCK_DGRAM / 0 : PROTOCOL 을 AUTO로 설정 
	servSock = socket(PF_INET, SOCK_STREAM, 0);

	// servAddr 구조체의 ip주소와 port번호 정의.
	memset(&servAddr, 0, sizeof(servSock));
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(atoi(argv[1]));
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(servSock, (void*)&servAddr, sizeof(servAddr)); // servSock ip주소와 port번호 bind.
	listen(servSock, 2); // listen 과정. 뒤의 숫자는 접속자 수 의미
	fromLen = sizeof(clntAddr);
	clntSock = accept(servSock, (void*)&clntAddr, &fromLen);

	closesocket(servSock);
	while (1) {
		printf("Message Receives ...\n");

		// clntSock: 데이터를 수신할 소켓.
		// message : 수신된 데이터를 담을 char*형 버퍼.
		// sizeof(message) : 수신하길 원하는 크기, 혹은 버퍼의 크기
		nRcv = recv(clntSock, message, sizeof(message) - 1, 0);

		// message[nRcv] = '\0';
		// 받은 문자의 끝 정의.

		/* 
		   atoi() 함수는 문자열을 정수로 변환시켜주는 함수이다.
		   다음 함수를 이용하여 100의 자리, 10의 자리, 1의 자리로
		   분리해 줄 것이다.

		   즉, 100의 자리 숫자는 사용자가 첫번째 입력한 숫자,
		   10의 자리 숫자는 사용자가 두번째 입력한 숫자,
		   1의 자리 숫자는 사용자가 세번째 입력한 숫자이다.
		*/
		user[0] = atoi(message) / 100;         // 100의 자리 숫자를 저장       
		user[1] = (atoi(message) % 100) / 10;  // 10의 자리 숫자를 저장
		user[2] = (atoi(message) % 100) % 10;  // 1의 자리 숫자를 저장 

		strike = checkStrike(computer, user);  // Strike 카운트 함수 호출
		ball = checkBall(computer, user);      // Ball 카운트 함수 호출
		out = checkOut(strike, ball);          // Out 카운트 함수 호출

		if (strike == 3) {                       // 만약 Strike 카운트가 3이면,
			send(clntSock, "정답입니다", 11, 0);  // '정답입니다'를 전송한다. 
		}
		else {
			result = (100 * strike + 10 * ball + out);  // strike, out, ball 카운트를 세자리 숫자로 표현하여 저장

			// _itoa_s 함수를 사용하여 정수형(result)를 문자형(message)으로 변형시켜준다.)
			_itoa_s(result, message, 10, 10);
			send(clntSock, message, (int)strlen(message), 0);
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

// 함수 구현부
// Strike 카운트 함수
int checkStrike(int* computer, int* user) {
	int strike = 0;
	int i;

	/* 
	   user와 computer 배열에서 인덱스도 같고 숫자 값도 같은 경우
	   strike를 1씩 카운트 
	*/
	for (i = 0; i < 3; i++) {
		if (user[i] == computer[i]) {
			strike++;
		}
	}
	return strike;
}

// Ball 카운트 함수
int checkBall(int* computer, int* user) {
	int ball = 0;
	int i, j;

	/* 
	   user와 computer 배열에서 인덱스는 다르고 숫자 값이 같은 경우
	   ball을 1씩 카운트 
	*/
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 3; j++) {
			if (i == j) {
				continue;	// 인덱스가 같은 경우 다음으로 진행 시킨다.
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

// Out 카운트 함수
int checkOut(int strike, int ball) {
	int out = 0;

	/* 
	   strike + ball + out 의 합은 항상 3으로 나와야 한다.
	   그러므로 strike 값과 ball 값을 알고 있을 때
	   다음 식을 통해 out값을 구할 수 있다.
	*/
	out = 3 - (strike + ball);
	
	return out;
}