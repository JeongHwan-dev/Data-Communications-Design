#include<stdio.h>
#include<stdlib.h> // random �Լ��� ����ϱ� ���Ͽ� �ʿ��ϴ�.
#include<time.h>   // time() �Լ��� ����ϱ� ���Ͽ� �ʿ��ϴ�.

/* 
	�� �� �и� ī��Ʈ �� �迭�� ����
	result[0]-> �̱� Ƚ��
	result[1]-> �� Ƚ��
	result[3]-> ��� Ƚ��
	�� �����Ѵ�. 
*/

int result[3] = { 0 };  // �迭 ����� ���ÿ� �� �迭�� ���� 0���� �ʱ�ȭ

// �̰��� ���
void winCase() {
	result[0]++;   // �̱� Ƚ�� ī��Ʈ +1
	printf("�̰���ϴ�.\n");
}

// ���� ���
void loseCase() {
	result[1]++;   // �� Ƚ�� ī��Ʈ +1
	printf("�����ϴ�.\n");
}

// ����� ���
void drawCase() {
	result[2]++;   // ��� Ƚ�� ī��Ʈ +1
	printf("�����ϴ�.\n");
}

int main(void) {

	int repeat;       // �ݺ� Ƚ��
	int playerNum;    // ����� ����
	int computerNum;  // ��ǻ�� ����

	/* 
		srand()�� ���� �߻����� �õ带 �����Ѵ�.
		�õ�� ���� �߻��⿡�� ���� ������ ����ϱ� ���Ͽ� ����ϴ� �����̴�.
		�õ尡 �޶����� ��ü ���� ������ ����ȴ�. 
	*/
	srand(time(NULL));

	printf("������ 0 ������ 1 �� 2 �Դϴ�.\n");
	printf("\n���������� �� Ƚ���� �Է��ϼ���\n");
	scanf("%d", &repeat);   // ���� ���� �� ���� Ƚ�� �Է¹ޱ�

	for (int i = 0; i < repeat; i++) {

		/* 
		    rand()�� 0���� 32767������ ������ �츮���� ��ȯ�Ѵ�.
			�̰��� ������ ������ %�� ����� 0 ~ (3-1) ������ ���� ������ ��ȯ�ϵ��� ���� �� �ִ�.
			��, computerNum ������ 0, 1, 2 �߿� �ϳ��� ���ڰ� �������� ����� ���̴�.
		*/
		computerNum = rand() % 3;

		printf("\n���� ���� �� �� �ϳ��� �����ϼ���.\n");
		scanf("%d", &playerNum);   // ����� ���� �Է¹ޱ�

		if (playerNum >= 0 && playerNum <= 2) {  // ����� ���ڰ� 0 ~ 2 ���̰� �Էµ� ���
			if (playerNum == 0) {                // ����ڰ� ����(0)�� �Է����� ���
				if (computerNum == 0)            // ��ǻ�Ͱ� ���ڰ� ����(0)�� ���
					drawCase();
				else if (computerNum == 1)	     // ��ǻ�Ͱ� ���ڰ� ����(1)�� ���
					loseCase();
				else if (computerNum == 2)       // ��ǻ�Ͱ� ���ڰ� ��(2)�� ���
					winCase();
			}
			else if (playerNum == 1) {           // ����ڰ� ����(1)�� �Է����� ���
				if (computerNum == 0)			 // ��ǻ�Ͱ� ���ڰ� ����(0)�� ���
					winCase();
				else if (computerNum == 1)		 // ��ǻ�Ͱ� ���ڰ� ����(1)�� ���
					drawCase();
				else if (computerNum == 2)		 // ��ǻ�Ͱ� ���ڰ� ��(2)�� ���
					loseCase();
			}
			else if (playerNum == 2) {			 // ����ڰ� ��(2)�� �Է����� ���
				if (computerNum == 0)			 // ��ǻ�Ͱ� ���ڰ� ����(0)�� ���
					loseCase();
				else if (computerNum == 1)		 // ��ǻ�Ͱ� ���ڰ� ����(1)�� ���
					winCase();
				else if (computerNum == 2)		 // ��ǻ�Ͱ� ���ڰ� ��(2)�� ���
					drawCase();
			}
		}
		else {		// ����� ���ڰ� 0 ~ 2 ������ ���ڰ� �ƴ� ���ڸ� �Է��� ���
			i--;	// Ƚ���� ��ȿ ó�� 
			printf("�ٽ� �Է��ϼ���.\n");   // ���� �˸� ���
		}
	}

	printf("\n\n\n�̱� Ƚ�� %d �� Ƚ�� %d ��� Ƚ�� %d\n", result[0], result[1], result[2]);

	return 0;
}