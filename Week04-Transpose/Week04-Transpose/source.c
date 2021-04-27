#include <stdio.h>

// 함수 원형 정의
void transpose(int matrix[3][3]);
void print_matrix(int matrix[3][3]);

int main(void)
{
	int i, j;           // 행과 열의 인덱스 값
	int matrix[3][3];   // 정수형 크기가 3 x 3인 matrix(행렬) 배열 선언

	printf("3x3 행렬을 입력하시오.\n");

	for (i = 0; i < 3; i++)				// 행 인덱스 값을 바꿔준다.
	{
		for (j = 0; j < 3; j++)			// 열 인덱스 값을 바꿔준다
		{
			scanf("%d", &matrix[i][j]); // 행렬의 값을 입력받기
		}
	}

	printf("======입력한 행렬======\n");
	print_matrix(matrix);   // 입력받은 행렬을 출력시키는 함수 print_matrix() 를 호출

	printf("======해당 행렬의 Transpose======\n");
	transpose(matrix);      // 입력받은 행렬의 transpose를 출력 해주는 함수 transpose() 를 호출

	return 0;
}

void print_matrix(int matrix[3][3])  // 입력 받은 행렬 3x3 형식으로 출력해주는 함수 정의
{
	int i, j;                        // 행과 열의 인덱스 변수 선언

	for (i = 0; i < 3; i++)          // 행 인덱스 값을 바꿔준다.
	{
		for (j = 0; j < 3; j++)      // 열 인덱스 값을 바꿔준다
		{
			printf("%2d ", matrix[i][j]);    // 한 행에 있는 열의 값을 간격을 두면서 출력
		}
		printf("\n");               // 한 행에 있는 열 값들의 출력이 끝나면 한줄을 띄워준다 
	}                               // 그리고 다음 행으로 가서 다시 반복
}
/*
 행렬의 transpose 는 행의 인덱스와 열의 인덱스를 바꿔주는 것이다.
즉, array[0][1] 은 t_array[1][0] 으로 바꿔 주는 것이다.
만약 array[1][1] 처럼 행과 열의 인덱스가 같은 경우, 내부적으로는 인덱스를 바꿔줬지만 행과 열의 인덱스 값이 같으므로 그대로 t_array[1][1]과 같다.
밑에 있는 transpose() 함수는 행렬의 transpose를 구하기 위해 행렬의 각각의 값의 행과 열의 인덱스 값을 바꿔주는 함수이다.
*/

void transpose(int matrix[3][3])    // 입력받은 행렬의 transpose 를 출력해주는 함수 정의
{
	int trans_matrix[3][3];         // 행과 열의 인덱스를 바꿔주고난 후의 값을 잠시 보관할 trans_matrix 배열 선언

	for (int i = 0; i < 3; i++)     // 행 인덱스 값을 바꿔준다.
	{
		for (int j = 0; j < 3; j++) // 열 인덱스 값을 바꿔준다
		{
			trans_matrix[j][i] = matrix[i][j];  // matrix[i][j] 값을 행과 열의 인덱스를 바꾼 trans_matrix[j][i]에 할당, 즉, matrix[0][1] 값을 trans_matrix[1][0]에 할당
		}
	}

	print_matrix(trans_matrix);     // 입력받은 행렬을 출력시키는 함수 print_matrix() 를 호출시켜 행렬의 tramspose 를 출력
}