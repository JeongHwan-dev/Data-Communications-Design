#include <stdio.h>
#include <stdlib.h>
#include <time.h>	// time() 함수를 위하여 필요하다.
#define MAX 100		// 난수 최대치 정의

int main(void) {
	int com_num;    // 컴퓨터가 생성하는 넘버 변수
	int user_num;   // 사용자가 입력하는 넘버 변수

	/* 
		srand()는 난수 발생기의 시드를 설정한다.
		시드는 난수 발생기에서 다음 난수를 계산하기 위하여 사용하는 변수이다.
		시드가 달라지면 전체 난수 수열이 변경된다. 
	*/
	srand(time(NULL));

	/* 
		rand()는 0부터 32767사이의 난수를 우리에게 반환한다.
		이것을 나머지 연산자 %를 사용해 0~(MAX-1)사이의 값의 난수를 반환하도록 만들 수 있다. 
	*/
	com_num = rand() % MAX;		// MAX가 100 이므로 0 ~ 99 사이의 난수 발생
	printf("숫자를 맞춰보세요\n\n");

	// while(1)은 계속 참 값을 의미하므로 break문이 나오기 전까지 계속 무한 반복을 해준다.
	while (1)
	{
		printf("숫자를 입력하세요\n");
		scanf("%d", &user_num);   // 사용자 넘버를 입력받는다

		if (user_num < 100 && user_num >= 0) {				 // 만약 입력된 사용자 넘버가 0~99 사이의 숫자일 경우
			if (user_num < com_num)							 // 만약 입력된 사용자 넘버가 컴퓨터 넘버보다 작을 경우
				printf("정답은 입력한 값보다 큽니다\n\n");
			else if (user_num > com_num)					 // 만약 입력된 사용자 넘버가 컴퓨터 넘버보다 클 경우
				printf("정답은 입력한 값보다 작습니다\n\n");
			else                                             // 남은 한 가지 경우의 수인 사용자 넘버와 컴퓨터 넘버가 일치할 경우
				break;                                       // break 문은 반복 루프를 벗어나기 위하여 사용한다. 
		}
		else {   // 입력된 사용자 넘버가 0~99 사이의 숫자가 아닐 경우
			printf("오류 : 0~99 사이의 숫자를 입력해주세요\n\n");
		}
	}
	printf("정답입니다.\n");   // 위에 있는 반복문이 종료되면 출력
	return 0;
}