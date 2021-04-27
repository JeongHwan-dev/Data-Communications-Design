#include <stdio.h>
#include <math.h>             // 삼각함수(sin, cos)을 사용하기 위해 선언
#define PI 3.1415926535897    // 매크로로써 파이값을 3.14...으로 정의

// getRadian() 함수는 입력받은 각도를 라디안으로 변환시켜주는 함수
double getRadian(int degree) {
	return degree * (PI / 180);
}

int main(void) {
	double x1, y1;   // 입력한 x, y 좌표를 담을 변수
	double x2, y2;   // 입력받은 좌표가 회전한 후의 점의 x, y 좌표를 담을 변수
	double degree;   // 입력받은 각도를 담을 변수
	double radian;   // 각도를 라디안으로 변환 후 담을 변수

	printf("x 좌표 : ");
	scanf("%lf", &x1);  // x 좌표 입력 받기

	printf("y 좌표 : ");
	scanf("%lf", &y1);  // y 좌표 입력 받기

	printf("Degree : ");
	scanf("%lf", &degree);  // 회전 할 각도 받기

	radian = getRadian(degree);  // getRadian()함수를 호출하여 입력받은 각도를 라디안으로 변환

	/* 
		회전변환 공식
		x' = x cos(세타) - ysin(세타)
		y' = x sin(세타) +ycos(세타)
		점 P(x, y)를 각도 '세타'만큼 회전시켜 P'(x', y')으로 옮기는 변환을 회전변환이라고 한다.
	*/
	x2 = x1 * cos(radian) - y1 * sin(radian);
	y2 = x1 * sin(radian) + y1 * cos(radian);

	printf("회전 후 x 좌표 : %lf\n", x2);  // 회전 후 x'좌표 출력
	printf("회전 후 y 좌표 : %lf\n", y2);  // 회전 후 y'좌표 출력

	return 0;
}