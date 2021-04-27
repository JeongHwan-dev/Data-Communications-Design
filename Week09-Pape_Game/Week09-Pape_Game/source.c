#include <stdio.h>
#include <stdlib.h>   // random() 함수를 사용하기 위하여 필요하다.
#include <string.h>   // strcpy() 함수를 사용하기 위하여 필요하다.
#include <time.h>     // time() 함수를 사용하기 위하여 필요하다.

// trump 구조체 정의
typedef struct {
	int order;
	char shape[3];   // 카드 모양
	int number;      // 카드 숫자 변수
}trump;

// 함수 선언
void createCards(trump m_card[]);
void showCards(trump m_card[]);
void shuffle(trump m_card[]);

int main(void) {
	// player가 총 3명이므로 구조체를 3개 선언 하고 받는 카드 수는 5장 이므로 크기가 5인 구조체 배열로 선언한다.
	trump player1[5], player2[5], player3[5];   //4명의 사람
	/*  
		트럼프 카드는 총 4가지의 모양이 있고 각 모양마다 1부터 K까지의 총 13개의 숫자가 있다.
		그러면 각기 다른 트럼프 카드는 총 4*13 = 52 가지 수가 나온다. 
	*/
	trump card[52];		// 크기가 52인 카드 구조체 배열 선언

	createCards(card);  // 트럼프 카드 생성 함수 호출
	shuffle(card);      // 트럼프 카드 셔플 함수 호출

	for (int i = 0; i < 5; i++) {
		player1[i] = card[4 * i];
		player2[i] = card[4 * i + 1];
		player3[i] = card[4 * i + 2];
	}

	// 3명의 player 별 트럼프 카드 배부 함수 호출
	showCards(player1, 1);
	showCards(player2, 2);
	showCards(player3, 3);

	return 0;
}

// 52가지 종류의 트럼프 카드 생성
void createCards(trump m_card[]) {
	int i, j;
	char shape[4][3] = { "S", "D", "H", "C" };

	// 4가지 모양의 카드 'A'부터 'K' 까지를  (0 ~12), (13 ~ 25), (26 ~ 38), (39 ~ 51) 로 표현  
	for (i = 0; i < 4; i++) {
		for (j = i * 13; j < i * 13 + 13; j++) {
			m_card[j].order = i;
			strcpy(m_card[j].shape, shape[i]);
			m_card[j].number = j % 13 + 1;

			// 카드 숫자가 특수한 케이스 일때
			switch (m_card[j].number) {
			case 1:                      // 카드 숫자가 1인 경우
				m_card[j].number = 'A';  // 변수에 숫자 1 대신 'A' 저장
				break;
			case 11:                     // 카드 숫자가 11인 경우
				m_card[j].number = 'J';  // 변수에 숫자 11 대신 'J' 저장
				break;
			case 12:                     // 카드 숫자가 12인 경우
				m_card[j].number = 'Q';  // 변수에 숫자 12 대신 'Q' 저장
				break;
			case 13:                     // 카드 숫자가 13인 경우
				m_card[j].number = 'K';  // 변수에 숫자 13 대신 'K' 저장
				break;
			}
		}
	}
}

// 트럼프 카드 배부 
void showCards(trump m_card[], int num) {
	int i, count = 0;

	// 카드 다섯장 배부
	for (i = 0; i < 5; i++) {
		printf("사람 %d는 ", num);
		printf("shape : %s ", m_card[i].shape);  // 카드 모양 출력

		// 카드 숫자 출력
		if (10 < m_card[i].number)
			printf("num : %c ", m_card[i].number);
		else
			printf("num : %d ", m_card[i].number);

		printf("\n");
	}
}

// 카드 순서 섞기
void shuffle(trump m_card[]) {
	int i, randumNum;

	trump temp;  // 카드를 swap 하기 위한 빈 구조체 한개 선언

	/* 
		srand()는 난수 발생기의 시드를 생성한다.
		시드는 난수 발생기에서 다음 난수를 계산하기 위하여 사용하는 변수이다.
		시드가 달라지면 전체 난수 수열이 변경된다. 
	*/
	srand(time(NULL));

	for (i = 0; i < 52; i++) {

		/* 
		   rand()는 0부터 32767사이의 난수를 우리에게 반환한다.
		   이것을 나머지 연산자 '%'를 사용해 0 ~ (52-1) 사이의 값의 난수를 반환하도록 만들 수 있다.
		   즉, randumNum 변수에 0 ~ 51 범위의 숫자 중에 하나가 랜덤으로 저장될 것이다.
		*/
		randumNum = rand() % 52;

		// swap 진행 
		temp = m_card[randumNum];       // 빈 temp변수에 m_card[randomNum] 변수에 저장되어 있던 숫자를 저장
		m_card[randumNum] = m_card[i];  // m_card[randomNum] 변수 m_card[i] 변수에 저장되어 있던 숫자를 저장
		m_card[i] = temp;               // m_card[i] 변수에 temo
	}
}
