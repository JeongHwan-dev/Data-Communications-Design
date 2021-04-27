#include <stdio.h>     // stdio.h 헤더파일(header file) 삽입
#include <string.h>    // strlen 을 사용하기 위해 string.h 헤더파일을 삽입 하였습니다.
#define MAXLENGTH 100  // 전처리 지시자를 이용하여 최대 이름의 길이를 정의합니다.

int main(void) {
	char name[MAXLENGTH];	// 이름 변수를 char형 배열로 선언 하였다 배열의 크기는 전처기지시자로 이미 할당한 100입니다.
	int length;				// 이름 길이를 받는 정수형 변수를 선언

	printf("이름을 입력하시오 : ");		// 출력 
	scanf("%s", name);					// 이름을 입력받습니다.

	length = strlen(name);				// 문자열 함수중 하나로 문자열의 길이를 알려줍니다.

	printf("입력 받은 이름: ");			  // 출력
	for (int i = 0; i < length; i++) {    // 반복문 for문을 이용해 배열에 차례대로 저장했던 변수를 꺼내면서 출력합니다.
		printf("%c", name[i]);		      // name배열에 저장해둔 문자를 순서대로 출력
	}

	// C언어에서 'a'는 문자가 아닌 a에 해당하는 '아스크 코드'입니다.
	// C언어에서는 아스키 코드 값을 외우고 있지 않아도 'a'를 통해 코드를 알 수 있습니다.
	// 이를 통해 A와 a또는 a와 A의 아스크 코드 값의 차를 더해서 변환 할 수 있습니다.
	if (name >= 'A' && name <= 'Z')		// 문자가 대문자일 경우
		name + ('a' - 'A');				// a와 A의 아스크 코드 값의 차를 더해서 소문자로 변환

	if (name >= 'a' && name <= 'z')		// 문자가 소문자일 경우
		name + ('A' - 'a');				// A와 a의 아스크 코드 값의 차를 더해서 소문자로 변환

	printf("\n입력 받은 이름(역순): ");  // 출력

	for (int i = 0; i < length; i++) {			// 이름을 역순으로 불러오기 위해 배열의 끝 부터 불러 옵니다.
		printf("%c", name[length - i - 1]);		// -1을 해준 이유는 보통 배열이 char array[10] 이라고 선언되면 실제로는 array[0]부터 array[9]까지 존재하기 때문입니다.
	}

	printf("\n");		// 줄 바꿈 출력

	return 0;
}