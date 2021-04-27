#include <stdio.h>
#include <stdlib.h>   // random() �Լ��� ����ϱ� ���Ͽ� �ʿ��ϴ�.
#include <string.h>   // strcpy() �Լ��� ����ϱ� ���Ͽ� �ʿ��ϴ�.
#include <time.h>     // time() �Լ��� ����ϱ� ���Ͽ� �ʿ��ϴ�.

// trump ����ü ����
typedef struct {
	int order;
	char shape[3];   // ī�� ���
	int number;      // ī�� ���� ����
}trump;

// �Լ� ����
void createCards(trump m_card[]);
void showCards(trump m_card[]);
void shuffle(trump m_card[]);

int main(void) {
	// player�� �� 3���̹Ƿ� ����ü�� 3�� ���� �ϰ� �޴� ī�� ���� 5�� �̹Ƿ� ũ�Ⱑ 5�� ����ü �迭�� �����Ѵ�.
	trump player1[5], player2[5], player3[5];   //4���� ���
	/*  
		Ʈ���� ī��� �� 4������ ����� �ְ� �� ��縶�� 1���� K������ �� 13���� ���ڰ� �ִ�.
		�׷��� ���� �ٸ� Ʈ���� ī��� �� 4*13 = 52 ���� ���� ���´�. 
	*/
	trump card[52];		// ũ�Ⱑ 52�� ī�� ����ü �迭 ����

	createCards(card);  // Ʈ���� ī�� ���� �Լ� ȣ��
	shuffle(card);      // Ʈ���� ī�� ���� �Լ� ȣ��

	for (int i = 0; i < 5; i++) {
		player1[i] = card[4 * i];
		player2[i] = card[4 * i + 1];
		player3[i] = card[4 * i + 2];
	}

	// 3���� player �� Ʈ���� ī�� ��� �Լ� ȣ��
	showCards(player1, 1);
	showCards(player2, 2);
	showCards(player3, 3);

	return 0;
}

// 52���� ������ Ʈ���� ī�� ����
void createCards(trump m_card[]) {
	int i, j;
	char shape[4][3] = { "S", "D", "H", "C" };

	// 4���� ����� ī�� 'A'���� 'K' ������  (0 ~12), (13 ~ 25), (26 ~ 38), (39 ~ 51) �� ǥ��  
	for (i = 0; i < 4; i++) {
		for (j = i * 13; j < i * 13 + 13; j++) {
			m_card[j].order = i;
			strcpy(m_card[j].shape, shape[i]);
			m_card[j].number = j % 13 + 1;

			// ī�� ���ڰ� Ư���� ���̽� �϶�
			switch (m_card[j].number) {
			case 1:                      // ī�� ���ڰ� 1�� ���
				m_card[j].number = 'A';  // ������ ���� 1 ��� 'A' ����
				break;
			case 11:                     // ī�� ���ڰ� 11�� ���
				m_card[j].number = 'J';  // ������ ���� 11 ��� 'J' ����
				break;
			case 12:                     // ī�� ���ڰ� 12�� ���
				m_card[j].number = 'Q';  // ������ ���� 12 ��� 'Q' ����
				break;
			case 13:                     // ī�� ���ڰ� 13�� ���
				m_card[j].number = 'K';  // ������ ���� 13 ��� 'K' ����
				break;
			}
		}
	}
}

// Ʈ���� ī�� ��� 
void showCards(trump m_card[], int num) {
	int i, count = 0;

	// ī�� �ټ��� ���
	for (i = 0; i < 5; i++) {
		printf("��� %d�� ", num);
		printf("shape : %s ", m_card[i].shape);  // ī�� ��� ���

		// ī�� ���� ���
		if (10 < m_card[i].number)
			printf("num : %c ", m_card[i].number);
		else
			printf("num : %d ", m_card[i].number);

		printf("\n");
	}
}

// ī�� ���� ����
void shuffle(trump m_card[]) {
	int i, randumNum;

	trump temp;  // ī�带 swap �ϱ� ���� �� ����ü �Ѱ� ����

	/* 
		srand()�� ���� �߻����� �õ带 �����Ѵ�.
		�õ�� ���� �߻��⿡�� ���� ������ ����ϱ� ���Ͽ� ����ϴ� �����̴�.
		�õ尡 �޶����� ��ü ���� ������ ����ȴ�. 
	*/
	srand(time(NULL));

	for (i = 0; i < 52; i++) {

		/* 
		   rand()�� 0���� 32767������ ������ �츮���� ��ȯ�Ѵ�.
		   �̰��� ������ ������ '%'�� ����� 0 ~ (52-1) ������ ���� ������ ��ȯ�ϵ��� ���� �� �ִ�.
		   ��, randumNum ������ 0 ~ 51 ������ ���� �߿� �ϳ��� �������� ����� ���̴�.
		*/
		randumNum = rand() % 52;

		// swap ���� 
		temp = m_card[randumNum];       // �� temp������ m_card[randomNum] ������ ����Ǿ� �ִ� ���ڸ� ����
		m_card[randumNum] = m_card[i];  // m_card[randomNum] ���� m_card[i] ������ ����Ǿ� �ִ� ���ڸ� ����
		m_card[i] = temp;               // m_card[i] ������ temo
	}
}
