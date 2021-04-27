#include <stdio.h>
#include <stdlib.h>     // rand() 함수를 사용하기 위해 필요
#include <time.h>       // time() 함수를 사용하기 위해 필요

#define SIZE 5			// 윷놀이 경우의 수 ( 도, 개, 걸, 윷, 모 ) 5가지
#define RAND_MAX 100

/*
	count[0]은 '도'가 나온 횟수
	count[1]은 '개'가 나온 횟수
	count[2]은 '걸'가 나온 횟수
	count[3]은 '윷'가 나온 횟수
	count[4]은 '모'가 나온 횟수
*/

int main(void) {

	int count[SIZE] = { 0, 0, 0, 0, 0 };  // 나온 횟수를 카운트 하는 크기가 SIZE(5)인 배열 선언 후 0으로 모두 초기화
	int yunnori;
	int repetition;						  // 반복 횟수 를 입력받을 변수 선언 
	int i;

	printf("반복 횟수 입력: ");
	scanf("%d", &repetition);  // 반복 횟수 입력 받기
	printf("\n\n");

	srand(time(NULL));		   // srand() 는 난수 발생기의 시드(seed)를 설정한다.

	for (i = 0; i < repetition; i++)			// for 반복문을 이용해 사전에 입력받은 반복 횟수(repetition)만큼 반복해 준다.
	{
		yunnori = 1 + (rand() % RAND_MAX);		// rand() 함수 이용하여 1부터 최대 100까지 중에 하나의 수를 얻어 yunnori 변수에 입력

		if ((yunnori >= 1) && (yunnori <= 20))  // 1부터 100까지 중에 1에서 20 사이의 수가 나왔을 때는 '도'로 취급한다. 그리고 그 확률은 20% 이다.
		{
			printf("도");
			count[0]++;							// '도'가 나온 횟수를 +1 해준다. 	
		}

		if ((yunnori >= 21) && (yunnori <= 45))  // 1부터 100까지 중에 21에서 45 사이의 수가 나왔을 때는 '개'로 취급한다. 그리고 그 확률은 25% 이다.
		{
			printf("개");
			count[1]++;							 // '개'가 나온 횟수를 +1 해준다. 
		}

		if ((yunnori >= 46) && (yunnori <= 75))  // 1부터 100까지 중에 46에서 75 사이의 수가 나왔을 때는 '걸'로 취급한다. 그리고 그 확률은 30% 이다.
		{
			printf("걸");
			count[2]++;							 // '걸'이 나온 횟수를 +1 해준다. 
		}

		if ((yunnori >= 76) && (yunnori <= 90))  // 1부터 100까지 중에 76에서 90 사이의 수가 나왔을 때는 '윷'으로 취급한다. 그리고 그 확률은 15% 이다.
		{
			printf("윷");
			count[3]++;							 // '윷'이 나온 횟수를 +1 해준다. 
		}

		if ((yunnori >= 91) && (yunnori <= 100)) // 1부터 100까지 중에 91에서 100 사이의 수가 나왔을 때는 '모'로 취급한다. 그리고 그 확률은 10% 이다.
		{
			printf("모");
			count[4]++;							 // '모'가 나온 횟수를 +1 해준다. 
		}
	}

	printf("\n\n");
	printf("====================\n");
	printf("   입력 받은 횟수\n");
	printf("====================\n");
	printf("도 - %d\n", count[0]);   // '도'가 나온 횟수 출력
	printf("개 - %d\n", count[1]);   // '개'가 나온 횟수 출력
	printf("걸 - %d\n", count[2]);   // '걸'이 나온 횟수 출력
	printf("윷 - %d\n", count[3]);   // '윷'이 나온 횟수 출력
	printf("모 - %d\n", count[4]);   // '모'가 나온 횟수 출력
	printf("\n");

	return 0;
}