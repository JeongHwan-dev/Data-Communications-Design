#include <stdio.h>

// �Լ� ���� ����
void transpose(int matrix[3][3]);
void print_matrix(int matrix[3][3]);

int main(void)
{
	int i, j;           // ��� ���� �ε��� ��
	int matrix[3][3];   // ������ ũ�Ⱑ 3 x 3�� matrix(���) �迭 ����

	printf("3x3 ����� �Է��Ͻÿ�.\n");

	for (i = 0; i < 3; i++)				// �� �ε��� ���� �ٲ��ش�.
	{
		for (j = 0; j < 3; j++)			// �� �ε��� ���� �ٲ��ش�
		{
			scanf("%d", &matrix[i][j]); // ����� ���� �Է¹ޱ�
		}
	}

	printf("======�Է��� ���======\n");
	print_matrix(matrix);   // �Է¹��� ����� ��½�Ű�� �Լ� print_matrix() �� ȣ��

	printf("======�ش� ����� Transpose======\n");
	transpose(matrix);      // �Է¹��� ����� transpose�� ��� ���ִ� �Լ� transpose() �� ȣ��

	return 0;
}

void print_matrix(int matrix[3][3])  // �Է� ���� ��� 3x3 �������� ������ִ� �Լ� ����
{
	int i, j;                        // ��� ���� �ε��� ���� ����

	for (i = 0; i < 3; i++)          // �� �ε��� ���� �ٲ��ش�.
	{
		for (j = 0; j < 3; j++)      // �� �ε��� ���� �ٲ��ش�
		{
			printf("%2d ", matrix[i][j]);    // �� �࿡ �ִ� ���� ���� ������ �θ鼭 ���
		}
		printf("\n");               // �� �࿡ �ִ� �� ������ ����� ������ ������ ����ش� 
	}                               // �׸��� ���� ������ ���� �ٽ� �ݺ�
}
/*
 ����� transpose �� ���� �ε����� ���� �ε����� �ٲ��ִ� ���̴�.
��, array[0][1] �� t_array[1][0] ���� �ٲ� �ִ� ���̴�.
���� array[1][1] ó�� ��� ���� �ε����� ���� ���, ���������δ� �ε����� �ٲ������� ��� ���� �ε��� ���� �����Ƿ� �״�� t_array[1][1]�� ����.
�ؿ� �ִ� transpose() �Լ��� ����� transpose�� ���ϱ� ���� ����� ������ ���� ��� ���� �ε��� ���� �ٲ��ִ� �Լ��̴�.
*/

void transpose(int matrix[3][3])    // �Է¹��� ����� transpose �� ������ִ� �Լ� ����
{
	int trans_matrix[3][3];         // ��� ���� �ε����� �ٲ��ְ� ���� ���� ��� ������ trans_matrix �迭 ����

	for (int i = 0; i < 3; i++)     // �� �ε��� ���� �ٲ��ش�.
	{
		for (int j = 0; j < 3; j++) // �� �ε��� ���� �ٲ��ش�
		{
			trans_matrix[j][i] = matrix[i][j];  // matrix[i][j] ���� ��� ���� �ε����� �ٲ� trans_matrix[j][i]�� �Ҵ�, ��, matrix[0][1] ���� trans_matrix[1][0]�� �Ҵ�
		}
	}

	print_matrix(trans_matrix);     // �Է¹��� ����� ��½�Ű�� �Լ� print_matrix() �� ȣ����� ����� tramspose �� ���
}