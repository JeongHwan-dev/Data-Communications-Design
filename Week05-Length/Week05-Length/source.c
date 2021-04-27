#include <stdio.h> 
#define SIZE 10        // 숫자 10개를 입력받을 배열의 크기
#define COUNTSIZE 3    // 카운트 값을 입력받을 배열의 크기

int findMax(int* c, int size);
int findMaxNum(int* c, int size, int longest);

int main(void)
{
	int num[SIZE];              // 숫자 10개를 입력받을 배열 선언
	int count[3] = { 0 };       // 연속되는 횟수를 카운트하는 값을 저장할 배열 선언 후 0으로 초기화, count[0]은 '1'이 연속되는 횟수, count[1]은 '2'가 연속되는 횟수, count[2]는 '3'이 연속되는 횟수를 저장
	int max_count[3] = { 0 };	// 각 숫자가 연속되는 최고치 카운트 기록을 저장할 배열 선언 후 0으로 초기화 
	int longest;                // 가장 긴 길이
	int max_num;                // 가장 긴 연속하는 길이를 갖는 숫자 
	int i;
	int error;

	// 숫자 10개 입력받기 
	for (i = 0; i < SIZE; i++)
	{
		printf("숫자를 입력하시오 : ");
		scanf("%d", &num[i]);	// 값을 입력받기 
	}

	// 입력받은 숫자들의 연속되는 횟수를 파악하기
	for (i = 1; i < SIZE; i++)
	{
		if (num[i] == num[i - 1] && num[i] == 1)  // num[i] 값이 뒤에 있는 숫자 num[i-1] 값과 같고 그 숫자가 1일 경우
		{
			count[0] ++;	// 숫자'1'의 연속 횟수를 +1 해준다.
			count[1] = 0;	// 숫자'2'의 연속 횟수는 0 으로 초기화 해준다.
			count[2] = 0;   // 숫자'3'의 연속 횟수는 0 으로 초기화 해준다.

			if (max_count[0] < count[0])  // 기존 최고치 연속 횟수가 현재 연속 횟수 보다 작을 때
			{
				max_count[0] = count[0];  // 현재 연속 횟수를 최고지 연속 횟수로 바꿔준다.
			}
		}

		else if (num[i] == num[i - 1] && num[i] == 2)  // num[i] 값이 뒤에 있는 숫자 num[i-1] 값과 같고 그 숫자가 2일 경우
		{
			count[0] = 0;	// 숫자'1'의 연속 횟수는 0 으로 초기화 해준다.
			count[1] ++;	// 숫자'2'의 연속 횟수를 +1 해준다.
			count[2] = 0;	// 숫자'3'의 연속 횟수는 0 으로 초기화 해준다.

			if (max_count[1] < count[1])  // 기존 최고치 연속 횟수가 현재 연속 횟수 보다 작을 때
			{
				max_count[1] = count[1];  // 현재 연속 횟수를 최고지 연속 횟수로 바꿔준다.
			}
		}

		else if (num[i] == num[i - 1] && num[i] == 3)  // num[i] 값이 뒤에 있는 숫자 num[i-1] 값과 같고 그 숫자가 그 숫자가 3일 경우
		{
			count[0] = 0;   // 숫자'1'의 연속 횟수는 0 으로 초기화 해준다.
			count[0] = 0;   // 숫자'2'의 연속 횟수는 0 으로 초기화 해준다.
			count[2] ++;    // 숫자'3'의 연속 횟수를 +1 해준다.

			if (max_count[2] < count[2])  // 기존 최고치 연속 횟수가 현재 연속 횟수 보다 작을 때
			{
				max_count[2] = count[2];  // 현재 연속 횟수를 최고지 연속 횟수로 바꿔준다.
			}
		}

		else if (num[i] < 0 || num[i] >3)  // ( 1, 2, 3 )이 아닌 부적절한 숫자가 num[i]에 입력되었을 때 오류 메시지를 출력한다.
		{
			printf("오류: %d번째에 ( 1, 2, 3 ) 이 아닌 부적절한 숫자 %d가 포함되어 있습니다.\n", i + 1, num[i]);
		}
	}

	// max_count[]배열에서 가장 큰 값을 찾아주는 함수 호출
	longest = findMax(max_count, COUNTSIZE) + 1; // 연속되는 횟수 최고치 값을 찾아주고 1을 더해준다 그 이유는 저 카운트 값은 그전 값과 현재 값이 같을 때 하나씩 카운트 했으므로
												 // 기존 처음 시작된 값의 횟수 카운트가 안 되어 있기 때문이다.

	// 앞서 구한 최대 연속되는 길이 max 값이 어느 숫자인지 찾는 함수 호출
	max_num = findMaxNum(max_count, COUNTSIZE, longest);

	printf("가장 긴 길이는 %d이며 그 숫자는 %d이다.\n", longest, max_num);  // 가장 긴 길이와 그 숫자 출력

	return 0;
}

// max_count[] 배열에서 가장 큰 값을 찾아주는 함수
int findMax(int* c, int size) {
	int max = c[0];        // 우선 배열의 첫번째 값을 max로 할당

	for (int i = 1; i < size; i++)
		if (c[i] > max)  // 기존 max 값보다 더 큰 값인 c[i]이 나오면 
		{
			max = c[i];  // max값 교체
		}

	return max; // max 값을 돌려준다.
}

// 앞서 구한 최대 연속되는 길이 max 값이 어느 숫자인지 찾는 함수
int findMaxNum(int* c, int size, int longest) {
	int maxIndex = 0;

	for (int i = 0; i < size; i++)
	{
		if (c[i] == longest - 1) //  max 값과 같은 값을 같는 배열 값을 찾는다.
		{
			maxIndex = i;  // 그 배열을 가르키는 인덱스 값을 maxIndex 에 넣어준다.
		}
	}
	return maxIndex + 1; // 사전에 count[0]은 1을 count[1]은 2를 count[2]는 3의 카운트를 가르킨다고 했다. 
						 // 그러므로 실제 숫자와 인덱스 값이 1 이 차이가 발생하므로 실제 그 숫자를 구하기 위해서는 1을 더해준다.
}