#include <stdio.h>
#include <math.h>             // �ﰢ�Լ�(sin, cos)�� ����ϱ� ���� ����
#define PI 3.1415926535897    // ��ũ�ην� ���̰��� 3.14...���� ����

// getRadian() �Լ��� �Է¹��� ������ �������� ��ȯ�����ִ� �Լ�
double getRadian(int degree) {
	return degree * (PI / 180);
}

int main(void) {
	double x1, y1;   // �Է��� x, y ��ǥ�� ���� ����
	double x2, y2;   // �Է¹��� ��ǥ�� ȸ���� ���� ���� x, y ��ǥ�� ���� ����
	double degree;   // �Է¹��� ������ ���� ����
	double radian;   // ������ �������� ��ȯ �� ���� ����

	printf("x ��ǥ : ");
	scanf("%lf", &x1);  // x ��ǥ �Է� �ޱ�

	printf("y ��ǥ : ");
	scanf("%lf", &y1);  // y ��ǥ �Է� �ޱ�

	printf("Degree : ");
	scanf("%lf", &degree);  // ȸ�� �� ���� �ޱ�

	radian = getRadian(degree);  // getRadian()�Լ��� ȣ���Ͽ� �Է¹��� ������ �������� ��ȯ

	/* 
		ȸ����ȯ ����
		x' = x cos(��Ÿ) - ysin(��Ÿ)
		y' = x sin(��Ÿ) +ycos(��Ÿ)
		�� P(x, y)�� ���� '��Ÿ'��ŭ ȸ������ P'(x', y')���� �ű�� ��ȯ�� ȸ����ȯ�̶�� �Ѵ�.
	*/
	x2 = x1 * cos(radian) - y1 * sin(radian);
	y2 = x1 * sin(radian) + y1 * cos(radian);

	printf("ȸ�� �� x ��ǥ : %lf\n", x2);  // ȸ�� �� x'��ǥ ���
	printf("ȸ�� �� y ��ǥ : %lf\n", y2);  // ȸ�� �� y'��ǥ ���

	return 0;
}