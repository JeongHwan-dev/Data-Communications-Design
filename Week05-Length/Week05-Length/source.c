#include <stdio.h> 
#define SIZE 10        // ���� 10���� �Է¹��� �迭�� ũ��
#define COUNTSIZE 3    // ī��Ʈ ���� �Է¹��� �迭�� ũ��

int findMax(int* c, int size);
int findMaxNum(int* c, int size, int longest);

int main(void)
{
	int num[SIZE];              // ���� 10���� �Է¹��� �迭 ����
	int count[3] = { 0 };       // ���ӵǴ� Ƚ���� ī��Ʈ�ϴ� ���� ������ �迭 ���� �� 0���� �ʱ�ȭ, count[0]�� '1'�� ���ӵǴ� Ƚ��, count[1]�� '2'�� ���ӵǴ� Ƚ��, count[2]�� '3'�� ���ӵǴ� Ƚ���� ����
	int max_count[3] = { 0 };	// �� ���ڰ� ���ӵǴ� �ְ�ġ ī��Ʈ ����� ������ �迭 ���� �� 0���� �ʱ�ȭ 
	int longest;                // ���� �� ����
	int max_num;                // ���� �� �����ϴ� ���̸� ���� ���� 
	int i;
	int error;

	// ���� 10�� �Է¹ޱ� 
	for (i = 0; i < SIZE; i++)
	{
		printf("���ڸ� �Է��Ͻÿ� : ");
		scanf("%d", &num[i]);	// ���� �Է¹ޱ� 
	}

	// �Է¹��� ���ڵ��� ���ӵǴ� Ƚ���� �ľ��ϱ�
	for (i = 1; i < SIZE; i++)
	{
		if (num[i] == num[i - 1] && num[i] == 1)  // num[i] ���� �ڿ� �ִ� ���� num[i-1] ���� ���� �� ���ڰ� 1�� ���
		{
			count[0] ++;	// ����'1'�� ���� Ƚ���� +1 ���ش�.
			count[1] = 0;	// ����'2'�� ���� Ƚ���� 0 ���� �ʱ�ȭ ���ش�.
			count[2] = 0;   // ����'3'�� ���� Ƚ���� 0 ���� �ʱ�ȭ ���ش�.

			if (max_count[0] < count[0])  // ���� �ְ�ġ ���� Ƚ���� ���� ���� Ƚ�� ���� ���� ��
			{
				max_count[0] = count[0];  // ���� ���� Ƚ���� �ְ��� ���� Ƚ���� �ٲ��ش�.
			}
		}

		else if (num[i] == num[i - 1] && num[i] == 2)  // num[i] ���� �ڿ� �ִ� ���� num[i-1] ���� ���� �� ���ڰ� 2�� ���
		{
			count[0] = 0;	// ����'1'�� ���� Ƚ���� 0 ���� �ʱ�ȭ ���ش�.
			count[1] ++;	// ����'2'�� ���� Ƚ���� +1 ���ش�.
			count[2] = 0;	// ����'3'�� ���� Ƚ���� 0 ���� �ʱ�ȭ ���ش�.

			if (max_count[1] < count[1])  // ���� �ְ�ġ ���� Ƚ���� ���� ���� Ƚ�� ���� ���� ��
			{
				max_count[1] = count[1];  // ���� ���� Ƚ���� �ְ��� ���� Ƚ���� �ٲ��ش�.
			}
		}

		else if (num[i] == num[i - 1] && num[i] == 3)  // num[i] ���� �ڿ� �ִ� ���� num[i-1] ���� ���� �� ���ڰ� �� ���ڰ� 3�� ���
		{
			count[0] = 0;   // ����'1'�� ���� Ƚ���� 0 ���� �ʱ�ȭ ���ش�.
			count[0] = 0;   // ����'2'�� ���� Ƚ���� 0 ���� �ʱ�ȭ ���ش�.
			count[2] ++;    // ����'3'�� ���� Ƚ���� +1 ���ش�.

			if (max_count[2] < count[2])  // ���� �ְ�ġ ���� Ƚ���� ���� ���� Ƚ�� ���� ���� ��
			{
				max_count[2] = count[2];  // ���� ���� Ƚ���� �ְ��� ���� Ƚ���� �ٲ��ش�.
			}
		}

		else if (num[i] < 0 || num[i] >3)  // ( 1, 2, 3 )�� �ƴ� �������� ���ڰ� num[i]�� �ԷµǾ��� �� ���� �޽����� ����Ѵ�.
		{
			printf("����: %d��°�� ( 1, 2, 3 ) �� �ƴ� �������� ���� %d�� ���ԵǾ� �ֽ��ϴ�.\n", i + 1, num[i]);
		}
	}

	// max_count[]�迭���� ���� ū ���� ã���ִ� �Լ� ȣ��
	longest = findMax(max_count, COUNTSIZE) + 1; // ���ӵǴ� Ƚ�� �ְ�ġ ���� ã���ְ� 1�� �����ش� �� ������ �� ī��Ʈ ���� ���� ���� ���� ���� ���� �� �ϳ��� ī��Ʈ �����Ƿ�
												 // ���� ó�� ���۵� ���� Ƚ�� ī��Ʈ�� �� �Ǿ� �ֱ� �����̴�.

	// �ռ� ���� �ִ� ���ӵǴ� ���� max ���� ��� �������� ã�� �Լ� ȣ��
	max_num = findMaxNum(max_count, COUNTSIZE, longest);

	printf("���� �� ���̴� %d�̸� �� ���ڴ� %d�̴�.\n", longest, max_num);  // ���� �� ���̿� �� ���� ���

	return 0;
}

// max_count[] �迭���� ���� ū ���� ã���ִ� �Լ�
int findMax(int* c, int size) {
	int max = c[0];        // �켱 �迭�� ù��° ���� max�� �Ҵ�

	for (int i = 1; i < size; i++)
		if (c[i] > max)  // ���� max ������ �� ū ���� c[i]�� ������ 
		{
			max = c[i];  // max�� ��ü
		}

	return max; // max ���� �����ش�.
}

// �ռ� ���� �ִ� ���ӵǴ� ���� max ���� ��� �������� ã�� �Լ�
int findMaxNum(int* c, int size, int longest) {
	int maxIndex = 0;

	for (int i = 0; i < size; i++)
	{
		if (c[i] == longest - 1) //  max ���� ���� ���� ���� �迭 ���� ã�´�.
		{
			maxIndex = i;  // �� �迭�� ����Ű�� �ε��� ���� maxIndex �� �־��ش�.
		}
	}
	return maxIndex + 1; // ������ count[0]�� 1�� count[1]�� 2�� count[2]�� 3�� ī��Ʈ�� ����Ų�ٰ� �ߴ�. 
						 // �׷��Ƿ� ���� ���ڿ� �ε��� ���� 1 �� ���̰� �߻��ϹǷ� ���� �� ���ڸ� ���ϱ� ���ؼ��� 1�� �����ش�.
}