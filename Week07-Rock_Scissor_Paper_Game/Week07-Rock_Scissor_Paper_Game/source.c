#include<stdio.h>
#include<stdlib.h> // random 함수를 사용하기 위하여 필요하다.
#include<time.h>   // time() 함수를 사용하기 위하여 필요하다.

/* 
	승 무 패를 카운트 할 배열을 선언
	result[0]-> 이긴 횟수
	result[1]-> 진 횟수
	result[3]-> 비긴 횟수
	를 저장한다. 
*/

int result[3] = { 0 };  // 배열 선언과 동시에 각 배열의 값을 0으로 초기화

// 이겼을 경우
void winCase() {
	result[0]++;   // 이긴 횟수 카운트 +1
	printf("이겼습니다.\n");
}

// 졌을 경우
void loseCase() {
	result[1]++;   // 진 횟수 카운트 +1
	printf("졌습니다.\n");
}

// 비겼을 경우
void drawCase() {
	result[2]++;   // 비긴 횟수 카운트 +1
	printf("비겼습니다.\n");
}

int main(void) {

	int repeat;       // 반복 횟수
	int playerNum;    // 사용자 숫자
	int computerNum;  // 컴퓨터 숫자

	/* 
		srand()는 난수 발생기의 시드를 생성한다.
		시드는 난수 발생기에서 다음 난수를 계산하기 위하여 사용하는 변수이다.
		시드가 달라지면 전체 난수 수열이 변경된다. 
	*/
	srand(time(NULL));

	printf("가위는 0 바위는 1 보 2 입니다.\n");
	printf("\n가위바위보 할 횟수를 입력하세요\n");
	scanf("%d", &repeat);   // 가위 바위 보 시행 횟수 입력받기

	for (int i = 0; i < repeat; i++) {

		/* 
		    rand()는 0부터 32767사이의 난수를 우리에게 반환한다.
			이것을 나머지 연산자 %를 사용해 0 ~ (3-1) 사이의 값의 난수를 반환하도록 만들 수 있다.
			즉, computerNum 변수에 0, 1, 2 중에 하나의 숫자가 랜덤으로 저장될 것이다.
		*/
		computerNum = rand() % 3;

		printf("\n가위 바위 보 중 하나를 선택하세요.\n");
		scanf("%d", &playerNum);   // 사용자 숫자 입력받기

		if (playerNum >= 0 && playerNum <= 2) {  // 사용자 숫자가 0 ~ 2 사이가 입력될 경우
			if (playerNum == 0) {                // 사용자가 가위(0)를 입력했을 경우
				if (computerNum == 0)            // 컴퓨터가 숫자가 가위(0)일 경우
					drawCase();
				else if (computerNum == 1)	     // 컴퓨터가 숫자가 바위(1)일 경우
					loseCase();
				else if (computerNum == 2)       // 컴퓨터가 숫자가 보(2)일 경우
					winCase();
			}
			else if (playerNum == 1) {           // 사용자가 바위(1)를 입력했을 경우
				if (computerNum == 0)			 // 컴퓨터가 숫자가 가위(0)일 경우
					winCase();
				else if (computerNum == 1)		 // 컴퓨터가 숫자가 바위(1)일 경우
					drawCase();
				else if (computerNum == 2)		 // 컴퓨터가 숫자가 보(2)일 경우
					loseCase();
			}
			else if (playerNum == 2) {			 // 사용자가 보(2)를 입력했을 경우
				if (computerNum == 0)			 // 컴퓨터가 숫자가 가위(0)일 경우
					loseCase();
				else if (computerNum == 1)		 // 컴퓨터가 숫자가 바위(1)일 경우
					winCase();
				else if (computerNum == 2)		 // 컴퓨터가 숫자가 보(2)일 경우
					drawCase();
			}
		}
		else {		// 사용자 숫자가 0 ~ 2 사이의 숫자가 아닌 숫자를 입력할 경우
			i--;	// 횟수를 무효 처리 
			printf("다시 입력하세요.\n");   // 오류 알림 출력
		}
	}

	printf("\n\n\n이긴 횟수 %d 진 횟수 %d 비긴 횟수 %d\n", result[0], result[1], result[2]);

	return 0;
}