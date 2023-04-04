#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 행렬 X, Y를 표시하기 위한 매크로
#define X 0
#define Y 1

// 행렬의 개수, 기본적으로 X, Y임으로 두 개이다.
#define MAT_SIZE 2

// selectMenu에서 사용되는, 행렬이 존재하는 지 판별하고 존재하지 않을 경우 에러 메시지를 출력하고 리턴하는 매크로
#define MATRIX_EXIST(flag) if(flag == 0){ puts("Error: Random Square Matrix Not Ready"); return; }

// malloc 함수에서 NULL이 리턴되었을 때를 처리하기 위한 매크로
// 만약 동적 할당에 실패하여 malloc에서 NULL이 발생하였을 때, 에러 메시지를 출력한다.
#define _MALLOC(ptr, size) if((ptr = malloc(size)) == NULL) { puts("Error: Matrix Generation Failure");}

// 계산 옵션 목록 상수
enum { PLUS, MINUS, MULTIPLICATIOIN };

// 메뉴 목록 상수
enum { RandomSquareMatrixGeneration = 1, Transpose, Rotation, Inverse, Calculation, Exit };

void printMenu();
void selectMenu(int menuSeleciton, int** [], int*);
int getMenuSelection();
void printMatrix(const int** matrix, int);
void printDoubleMatrix(const double** matrix, int);
int randomSquareMatrixGeneration(int** []);
int** generateBlankedMatrix(int);
double** generateDoubleMatrix(int);
void fillMatrixWithZero(int** matrix, int);
void fillMatrixWithRandom(int** matrix, int);
void deleteMatrix(void** matrix, int);
void transpose(int** [], int);
void rotation(const int** [], int);
int getDegree();
void rotate90(int**, int);
void inverse(int** [], int);
double** getInverseMatrix(const int** matrix, int);
int getDeterminant(const int** matrix, int);
void calculation(int** [], int);
int getCalculationSelection();
void calc_plus(int** [], int);
void calc_minus(int** [], int);
void calc_multiplication(int** [], int);


int main(void)
{
	
	int** MATRIX[MAT_SIZE] = {NULL, NULL}; ///>MATRIX[X], [Y]를 담을 int**의 배열
	int SQUARE = 0; ///>정방 행렬의 열(행) 수

	int menuSelection = 0; ///>메뉴 선택지

	// menuSelection이 Exit이 아닐 동안 계속 반복해서 메뉴를 입력받는다.
	while (menuSelection != Exit) {
		printMenu();
		menuSelection = getMenuSelection();
		selectMenu(menuSelection, MATRIX, &SQUARE);
	}

	//프로그램이 종료될 때, 행렬을 모두 해제하고 종료한다.
	for (int i = 0; i < MAT_SIZE; i++) {
		if(MATRIX[i] != NULL) {
			deleteMatrix(MATRIX[i], SQUARE);
		}
	}

	return 0;
}

/*********
* function : printMenu
* purpose : 메뉴 선택지를 출력한다.
**********/
void printMenu()
{
	puts("-- Menu --");
	puts("1. Random Square Matrix Generation");
	puts("2. Transpose(T)");
	puts("3. Rotation(90, 180, 270, 360 degree)");
	puts("4. Inverse(^ -1)");
	puts("5. Calculation(+, -, *)");
	puts("6. Exit");
}

/********
* function : selectMenu
* purpose : menuSelection을 바탕으로 지정된 메뉴 함수를 호출한다.
* parameters
*	int menuSelection : 메뉴 선택지
*	int** matrix[] : 행렬 X, Y		///> 이후 생략
*	int* square : 행렬의 열(또는 행)
* descriptions
*	메뉴 목록은 printMenu() 또는 enum 참고
*	만약 menuSelection이 올바른 메뉴 선택지가 아닐 경우, 안내문을 출력하고 반환한다.
*	행렬이 존재하지 않는 상태에서 1번 이외 메뉴를 선택할 경우 안내문을 출력하고 반환한다. 이때 MATRIX_EXIST 매크로 사용
* note
*	square을 포인터로 받는다. 
*	RandomSquareMatrixGeneration 메뉴 실행 시 메인함수에서 선언된 square을 직접 수정한다.
*	EXIT이 선택되어도 행렬 MATRIX를 따로 해제하지는 않는다. 메인함수에서 따로 해제해줘야 한다.
*********/
void selectMenu(int menuSeleciton, int** MATRIX[], int* square)
{
	static int isMatrixGenerated = 0; ///> 행렬이 이미 있는 지 확인하는 bool값, 0이면 없고, 1이면 있다는 뜻이다.
	int SQUARE = *square; ///>포인터로 받은 square을 안전하게 사용하기 위해 SQUARE에 복사한다.

	switch (menuSeleciton) {
	case RandomSquareMatrixGeneration:
		//이미 생성된 행렬이 존재할 시, 기존 행렬을 삭제하고 다시 생성한다.
		if (isMatrixGenerated != 0) {
			for (int i = 0; i < MAT_SIZE; i++) {
				deleteMatrix(MATRIX[i], SQUARE);
			}
		}
		*square = randomSquareMatrixGeneration(MATRIX);
		isMatrixGenerated = 1;
		break;
	case Transpose:
		MATRIX_EXIST(isMatrixGenerated)
		transpose(MATRIX, SQUARE);
		break;
	case Rotation:
		MATRIX_EXIST(isMatrixGenerated)
		rotation(MATRIX, SQUARE);
		break;
	case Inverse:
		MATRIX_EXIST(isMatrixGenerated)
		inverse(MATRIX, SQUARE);
		break;
	case Calculation:
		MATRIX_EXIST(isMatrixGenerated)
		calculation(MATRIX, SQUARE);
		break;
	case Exit:
		puts("Exit, thank you");
		return;
	default:
		//메뉴 선택 목록에 없을 시, 안내문 출력
		puts("Thou selected wrong menu, try again");
	}
}

/********
* function : getMenuSelection
* purpose : 키보드로 메뉴 선택지를 입력받는다.
* description
*	안내문을 출력하고 메뉴 선택지를 정수로 입력받는다.
* note 
*	올바르지 않은 메뉴를 선택했을 시 이를 검사하는 기능은 없다. 오직 입력받은 integer만 반환한다.
*	입력 버퍼 자동적으로 비워주는 기능 포함되어 있다.
*********/
int getMenuSelection()
{
	int selection = 0;
	printf("Choose the item you want: ");
	scanf_s("%d", &selection);
	while (getchar() != '\n'); //입력 버퍼 비우기
	return selection;
}

/*******
* function : printMatrix
* purpose : 행렬을 출력한다.
* parameters
*	int** matrix : 출력할 행렬
*	int SQUARE : 행렬의 열(또는 행) ///> 이하 생략
* description
*	행렬을 출력한다. 이때 줄간격은 기본적으로
*	"X = " 다음에 출력하는 것을 전제로 정렬한다.
* note
*	int** []을 매개변수로 받지 않는다. 즉 MATRIX[X] 이런 식으로 전달한다.
********/
void printMatrix(const int** matrix, int SQUARE)
{
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			printf("%2d ", matrix[i][j]);
		}
		printf("\n");
		printf("    "); // 정렬 기능
	}
	printf("\n");
}

/********
* function : printDoubleMatrix
* purpose : double형 행렬을 출력한다.
* parameters
*	double** matrix : double형으로 이루어진 행렬
* description
*	printMatrix의 double형 출력 버전
*	출력 시 기본적으로 "X^(-1) = " 에 맞추는 것을 전제로 정렬한다.
*********/
void printDoubleMatrix(const double** matrix, int SQUARE)
{
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			printf("%9f ", matrix[i][j]);
		}
		printf("\n");
		printf("         "); //정렬 기능
	}
	printf("\n");
}

/********
* function : randomSquareMatrixGeneration
* purpose : menu 1_RandomSquareMatrixGeneration 기능 수행
* return : SQUARE, 행렬의 열(=행)
* description
*	안내문을 출력하고 SQUARE 값을 입력받는다.
*	generateBlandkedMatrix 함수로 행렬을 생성한다.
*	fillMatrixWithRandom 함수로 행렬을 무작위 숫자로 채운다.
*	행렬 X, Y를 출력한다.
*	입력받는 SQUARE을 반환한다.
*********/
int randomSquareMatrixGeneration(int** MATRIX[])
{
	int SQUARE = 0;
	printf("Input the number of rows (2 or 3): ");
	scanf_s("%d", &SQUARE);

	for (int i = 0; i < MAT_SIZE; i++) {
		MATRIX[i] = generateBlankedMatrix(SQUARE);
	}

	srand((unsigned int)time(NULL));
	for (int i = 0; i < MAT_SIZE; i++) {
		fillMatrixWithRandom(MATRIX[i], SQUARE);
	}

	printf("X = ");
	printMatrix(MATRIX[X], SQUARE);

	printf("Y = ");
	printMatrix(MATRIX[Y], SQUARE);

	return SQUARE;
}

/********
* function : generateBlankedMatrix
* purpose : SQUARE * SQUARE 의 정방 행렬을 생성한다.
* return : 생성된 int** 형 matrix
* description
*	동적할당으로 2차원 배열 생성
*	동적할당 실패를 대비해 _MALLOC 매크로 사용
* note
*	0으로 초기화 안 한다.
*********/
int** generateBlankedMatrix(int SQUARE)
{
	int** matrix = NULL;
	_MALLOC(matrix, sizeof(int*) * SQUARE);
	for (int i = 0; i < SQUARE; i++) {
		_MALLOC(matrix[i], sizeof(int) * SQUARE);
	}
	return matrix;
}

/********
* function : generateDoubleMatrix
* purpose : SQUARE * SQUARE의 double형 정방 행렬을 생성한다.
* return : 생성된 double** 형 matrix
* description
*	generateBlankedMatrix의 double형 버전
*	모든 요소들을 0.0으로 초기화한다.
*********/
double** generateDoubleMatrix(const int SQUARE)
{
	double** matrix = NULL;
	_MALLOC(matrix, sizeof(double*) * SQUARE);
	for (int i = 0; i < SQUARE; i++) {
		_MALLOC(matrix[i], sizeof(double) * SQUARE);
		for (int j = 0; j < SQUARE; j++) {
			matrix[i][j] = 0.0;
		}
	}
	return matrix;
}

/*******
* function : fillMatrixWithZero
* purpose : 행렬의 모든 요소를 0으로 초기화한다.
* parameters
	int** matrix : 0으로 초기화할 대상 행렬
********/
void fillMatrixWithZero(int** matrix, int SQUARE)
{
	for (int i = 0; i < SQUARE; i++) {
		memset(matrix[i], 0, sizeof(int) * SQUARE);
	}
}

/*******
* function : fillMatrixWithRandom
* purpose : 행렬의 모든 요소를 난수로 채운다.
* parameters
*	int** matrix : 0으로 초기화할 대상 행렬
* description
*	0부터 99까지의 임의의 정수로 행렬을 채운다.
* note
*	srand로 시드값 초기화하지 않음. 미리 srand로 시드값을 설정해야 함.
********/
void fillMatrixWithRandom(int** matrix, int SQUARE)
{
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			matrix[i][j] = rand() % 100;
		}
	}
}

/********
* function : deleteMatrix
* purpose : 2차원 행렬을 해제한다.
* paremeters
*	void** matrix : 해제하고자 하는 대상 행렬
*********/
void deleteMatrix(void** matrix,int SQUARE)
{
	if (matrix == NULL) return;
	for (int i = 0; i < SQUARE; i++) {
		if(matrix[i] != NULL)
			free(matrix[i]);
	}

	free(matrix);
}

/********
* function : transpose
* purpose : menu 2_Transpose 기능 수행
* description
*	X와 Y의 전치행렬을 출력한다.
* note
*	결과 행렬을 반환하지는 않는다.
*********/
void transpose(int** MATRIX[], int SQUARE)
{
	printf("Transpose X and Y\n");

	printf("X^T = ");
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			printf("%2d ", MATRIX[X][j][i]);
		}
		printf("\n");
		printf("      ");
	}
	printf("\n");

	printf("Y^T = ");
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			printf("%2d ", MATRIX[Y][j][i]);
		}
		printf("\n");
		printf("      ");
	}
	printf("\n");
}

/********
* function : rotation
* purpose : menu 3_Rotation 기능 수행
* description
*	getDegree() 함수로 각도를 입력받고, 이를 통해 회전수를 계산한다.
*	회전수만큼 rotation한 결과를 출력한다. (rotate90 함수 이용)
*********/
void rotation(const int** MATRIX[], int SQUARE)
{
	int degree = getDegree();
	int rotationCycle = degree / 90; ///> 회전 바퀴 수

	// 회전시킬 행렬 2개를 생성한다.
	int** rotatedMatrix[MAT_SIZE] = { generateBlankedMatrix(SQUARE), generateBlankedMatrix(SQUARE) };

	// 회전시킬 행렬에 원본 행렬을 복사한다.
	for (int i = 0; i < MAT_SIZE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			for (int k = 0; k < SQUARE; k++) {
				rotatedMatrix[i][j][k] = MATRIX[i][j][k];
			}
		}
	}
	
	// rotate Matrix for rotation Cycle
	// ex : if degree == 180, cycle is 2 and rotate for 2 times
	for (int k = 0; k < MAT_SIZE; k++) { // k는 X와 Y
		for (int i = 0; i < rotationCycle; i++) {
			rotate90(rotatedMatrix[k], SQUARE);
		}
	}
	
	printf("X = ");
	printMatrix(rotatedMatrix[X], SQUARE);

	printf("Y = ");
	printMatrix(rotatedMatrix[Y], SQUARE);

	for (int i = 0; i < MAT_SIZE; i++) {
		deleteMatrix(rotatedMatrix[i], SQUARE);
	}
}

/********
* function : getDegree
* purpose : 정수형 각도를 입력받고, 이를 반환한다.
* return : degree
* description
	90도, 180도, 270, 360도 중 하나를 입력받는다.
	만약 다른 각도가 입력되었을 시 안내문을 출력하고 다시 입력받는다.
*********/
int getDegree()
{
	int degree = -1;
	while (!(degree == 0 || degree == 90 || degree == 180 || degree == 270 || degree == 360)) {
		printf("Input the degree to rotate: ");
		scanf_s("%d", &degree);
		if (!(degree == 0 || degree == 90 || degree == 180 || degree == 270 || degree == 360)) {
			printf("Wrong degree, try again\n");
		}
	}
	return degree;
}

/*******
* function : rotate90
* purpose : 입력받은 행렬을 90도만큼 시계방향 회전시킨다.
* parameters
*	int** originalMatrix : 90도 회전시킬 행렬
********/
void rotate90(int** matrix, int SQUARE)
{
	int** rotatedMatrix = generateBlankedMatrix(SQUARE);
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			rotatedMatrix[j][SQUARE - i - 1] = matrix[i][j];
		}
	}

	// 원본 행렬 직접 수정
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			matrix[i][j] = rotatedMatrix[i][j];
		}
	}
	deleteMatrix(rotatedMatrix, SQUARE);
}

/********
* function : inverse
* purpose : menu 4_Inverse 기능 실행
* description
*	getInverseMatrix() 함수로 역행렬을 계산하고, 만약 역행렬이 존재하면 이를 출력한다.
* description
*	getInverseMatrix()를 통해 X, Y가 역행렬이 존재하는 지를 각각 판단한다(NULL일 경우 존재하지 않는 것임).
*	이를 printDoubleMatrix() 로 출력한다.
*********/
void inverse(int** MATRIX[], int SQUARE)
{
	double** inverseMatrix[MAT_SIZE];	///> 역행렬 X, Y를 저장할 double** [] 형 행렬
	inverseMatrix[X] = getInverseMatrix(MATRIX[X], SQUARE);
	inverseMatrix[Y] = getInverseMatrix(MATRIX[Y], SQUARE);

	// 행렬 X, Y가 모두 역행렬이 존재할 때
	if (inverseMatrix[X] != NULL && inverseMatrix[Y] != NULL) {
		printf("X and Y are Invertible, \n");
		printf("Inverse X and Y\n");

		printf("X^(-1) = ");
		printDoubleMatrix(inverseMatrix[X], SQUARE);

		printf("Y^(-1) = ");
		printDoubleMatrix(inverseMatrix[Y], SQUARE);
	}
	// 행렬 X가 역행렬이 존재하지 않고, 행렬 Y만 역행렬이 존재할 때
	else if (inverseMatrix[X] == NULL && inverseMatrix[Y] != NULL) {
		printf("X is not invertible but Y is invertible, \n");
		printf("Inverse Y\n");

		printf("Y^(-1) = ");
		printDoubleMatrix(inverseMatrix[Y], SQUARE);
	}
	// 행렬 X만 역행렬이 존재하고, 행렬 Y는 역행렬이 존재하지 않을 때
	else if (inverseMatrix[X] != NULL && inverseMatrix[Y] == NULL) {
		printf("X is invertible but Y is not invertible, \n");
		printf("Inverse X\n");

		printf("X^(-1) = ");
		printDoubleMatrix(inverseMatrix[X], SQUARE);
	}
	// 기타 상황, 행렬 X, Y가 모두 역행렬이 존재하지 않을 때
	else {
		printf("X and Y are not invertible\n");
		deleteMatrix(inverseMatrix[X], SQUARE);
		deleteMatrix(inverseMatrix[Y], SQUARE);
	}

	for (int i = 0; i < MAT_SIZE; i++) {
		deleteMatrix(inverseMatrix[i], SQUARE);
	}
}

/********
* function : getInverseMatrix
* purpose : 역행렬을 반환한다.
* parameters
*	int** matrix : 원본 행렬
* return 
*	double** resultMatrix, 역행렬
*	또는 역행렬이 존재하지 않으면 NULL 반환
* description
*	행렬식 determinant를 구해서 역행렬을 계산하는 것은, 행렬의 크기에 따라 너무 복잡해지므로,
*	보다 간편하고 컴퓨터 친화적인 Gauss-Jordan 소거법을 이용하여 역행렬을 계산한다.
*	단, 행렬식이 0인지를 확인하여 해당 행렬의 역행렬을 가지는 지를 검사하기는 한다.
*	구한 역행렬이 실제 matrix의 역행렬인지 알기 위해 resultMatrix * matrix == IdentityMatrix(단위 행렬)인지를 확인한다.
*	만약 resultMatrix * matrix != IdentityMatrix 이면 matrix는 올바른 역행렬이 존재하지 않는 것이다. NULL을 리턴한다.
* note
*	원본 matrix는 수정되지 않는다.
*********/
double** getInverseMatrix(const int** matrix, int SQUARE) {
	if (getDeterminant(matrix, SQUARE) == 0) return NULL; // Det (Matrix) == 0 이면 역행렬이 존재할 수 없음

	const double ERROR = 1.0e-10; ///> 부동소수점 오류 기준값

	// *note : generateDoubleMatrix()는 0으로 초기화를 동시에 진행함.
	double** resultMatrix = generateDoubleMatrix(SQUARE); ///> 역행렬 결과를 저장할 행렬
	double** MatrixCopy = generateDoubleMatrix(SQUARE); ///> 원본 행렬의 복사본, 가우스 조던 소거법을 이용하기에 이 행렬을 수정한다.

	// MatrixCopy에 원본 matrix 복사
	// int -> double형으로 형변환하여 복사한다.
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			MatrixCopy[i][j] = (double)matrix[i][j];
		}
	}

	// 계산 결과가 저장되는 resultMatrix 행렬을 단위행렬로 초기화
	for (int i = 0; i < SQUARE; i++)
		for (int j = 0; j < SQUARE; j++)
			resultMatrix[i][j] = (i == j) ? 1 : 0;
	
	// 대각요소를 0이 아닌 수로 만든다.
	// 가우스 조던 방법의 해가 부정(해가 무수히 많음)일 경우를 대비한 과정이다.
	for (int i = 0; i < SQUARE; i++) {
		if (-ERROR < MatrixCopy[i][i] && MatrixCopy[i][i] < ERROR) { // MatrixCopy[i][i] == 0
			for (int k = 0; k < SQUARE; k++) {
				if (-ERROR < MatrixCopy[k][i] && MatrixCopy[k][i] < ERROR) // MatrixCopy[k][i] == 0
					continue;
				for (int j = 0; j < SQUARE; j++) {
					MatrixCopy[i][j] += MatrixCopy[k][j];
					resultMatrix[i][j] += resultMatrix[k][j];
				}
				break;
			}
			if (-ERROR < MatrixCopy[i][i] && MatrixCopy[i][i] < ERROR) {
				//수정 사항을 모두 완료했음에도 대각선 요소가 0 -> 가우스-조던 방법 불가능
				deleteMatrix(resultMatrix, SQUARE);
				deleteMatrix(MatrixCopy, SQUARE);

				return NULL;
			};
		}
	}
	

	/* Gauss-Jordan elimination */
	for (int i = 0; i < SQUARE; i++) {
		// 대각 요소를 1로 만듦
		double constant = MatrixCopy[i][i]; ///> 대각선 요소의 값 저장
		for (int j = 0; j < SQUARE; j++) {
			MatrixCopy[i][j] /= constant;   // MatrixCopy[i][i] 를 1 로 만드는 작업
			resultMatrix[i][j] /= constant;   // i 행 전체를 MatrixCopy[i][i] 로 나눔
		}

		// i 행을 제외한 k 행에서 MatrixCopy[k][i] 를 0 으로 만드는 단계
		for (int k = 0; k < SQUARE; k++) {
			if (k == i) continue;      // 자기 자신의 행은 건너뜀
			if (MatrixCopy[k][i] == 0) continue;   // 이미 0 이 되어 있으면 건너뜀

			// MatrixCopy[k][i] 행을 0 으로 만듦
			constant = MatrixCopy[k][i];
			for (int j = 0; j < SQUARE; j++) {
				MatrixCopy[k][j] = MatrixCopy[k][j] - MatrixCopy[i][j] * constant;
				resultMatrix[k][j] = resultMatrix[k][j] - resultMatrix[i][j] * constant;
			}
		}
	}

	deleteMatrix(MatrixCopy, SQUARE);

	return resultMatrix;
}

/********
* function : getDeterminant
* purpose : 행렬의 행렬식(Det)를 구한다
* parameters
*	int** matrix : 행렬 M
* return : 행렬의 행렬식
*********/
int getDeterminant(const int** matrix, int SQUARE)
{
	if (SQUARE == 1) return matrix[0][0]; // 1 * 1 행렬일 시 그 값 그대로 반환

	int*** minor_Matrix = malloc(sizeof(int**) * SQUARE);
	for (int i = 0; i < SQUARE; i++) {
		minor_Matrix[i] = generateBlankedMatrix(SQUARE);
	}
	for (int k = 0; k < SQUARE; k++) {
		for (int i = 0; i < SQUARE - 1; i++)
			for (int j = 0; j < SQUARE; j++) {
				if (j < k)
					minor_Matrix[k][i][j] = matrix[i + 1][j];
				else if (j > k)
					minor_Matrix[k][i][j - 1] = matrix[i + 1][j];
			}
	}
	int sum = 0;
	int test = 1; 
	for (int k = 0; k < SQUARE; k++) {
		sum += test * matrix[0][k] * getDeterminant(minor_Matrix[k], SQUARE - 1);
		test *= -1;
	}

	for (int i = 0; i < SQUARE; i++) {
		deleteMatrix(minor_Matrix[i], SQUARE);
	}
	return sum;
}

/********
* function : calculation
* purpose : menu 5_Calculation의 기능 실행
* description
*	getCalculationSelection() 을 이용해 계산 옵션(+, -, * 중 하나)를 선택받고, 그에 맞는 연산 결과를 출력한다.
*	연산 결과는 calc_함수들이 담당함(함수 자체에서 print하지는 않음)
*********/
void calculation(int** MATRIX[], int SQUARE)
{
	int calculationSelection = getCalculationSelection();
	switch (calculationSelection) {
	case PLUS:
		calc_plus(MATRIX, SQUARE);
		break;
	case MINUS:
		calc_minus(MATRIX, SQUARE);
		break;
	case MULTIPLICATIOIN:
		calc_multiplication(MATRIX, SQUARE);
		break;
	default:
		puts("ERROR : Wrong Calculation menu selected");
	}
}

/********
* function : getCalculationSelection
* purpose : calculationSelection을 입력받고 반환하는 함수
* return : calculationSelction(PLUS, MINUS, MULTIPLICATION) 반환
* description
*	getchar() 함수를 통해 +, -, * 중 하나를 입력받는다.
*	입력받은 이후, 나머지 입력은 모두 버퍼를 비운다.
*	+면 PLUS, -면 MINUS, *면 MULTIPLICATION을 반환한다.
*	모두 아니면, 잘못 선택되었다는 안내문을 출력한 후 다시 입력받는다.
* note
*	입력버퍼를 비우는 기능은 있으나, 여러 개의 문자가 입력된 상황에서 에러가 발생할 수 있다.
*********/
int getCalculationSelection()
{
	char selection; ///> char형 메뉴 선택지
	while (1) {
		printf("Input the calculation (+, -, or *): ");
		selection = getchar();
		while (getchar() != '\n'); // 입력버퍼 비우기
		if (selection == '+') return PLUS;
		else if (selection == '-') return MINUS;
		else if (selection == '*') return MULTIPLICATIOIN;
		else puts("Thou selected wrong menu. Try again"); //올바르지 않은 선택지면 에러메시지 출력
	}
}

/********
* function : calc_plus
* purpose : calculation menu 중 +(덧셈) 메뉴 기능 구현
* description
*	행렬 X, Y를 더한 결과를 출력한다.
* note
*	printMatrix 함수를 이용하기에, 출력 정렬이 깨지는 경우가 발생한다.
*	결과 행렬을 반환하지는 않는다.
*********/
void calc_plus(int** MATRIX[], int SQUARE)
{
	int** resultMatrix = generateBlankedMatrix(SQUARE); ///>덧셈 결과가 저장될 행렬
	fillMatrixWithZero(resultMatrix, SQUARE);
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			resultMatrix[i][j] = MATRIX[X][i][j] + MATRIX[Y][i][j];
		}
	}

	printf("X + Y = ");
	printMatrix(resultMatrix, SQUARE);
	deleteMatrix(resultMatrix, SQUARE);
}

/********
* function : calc_minus
* purpose : calculation menu 중 -(뺄셈) 메뉴 기능 구현
* description
*	행렬 X, Y를 뺀 결과를 출력한다.
* note
*	printMatrix 함수를 이용하기에, 출력 정렬이 깨지는 경우가 발생한다.
*	결과 행렬을 반환하지는 않는다.
*********/
void calc_minus(int** MATRIX[], int SQUARE)
{
	int** resultMatrix = generateBlankedMatrix(SQUARE);
	fillMatrixWithZero(resultMatrix, SQUARE);
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			resultMatrix[i][j] = MATRIX[X][i][j] - MATRIX[Y][i][j];
		}
	}

	printf("X + Y = ");
	printMatrix(resultMatrix, SQUARE);
	deleteMatrix(resultMatrix, SQUARE);
}

/********
* function : calc_multiplication
* purpose : calculation menu 중 *(곱셈) 메뉴 기능 구현
* description
*	행렬 X, Y를 곱한 결과를 출력한다.
* note
*	printMatrix 함수를 이용하기에, 출력 정렬이 깨지는 경우가 발생한다.
*	결과 행렬을 반환하지는 않는다.
*********/
void calc_multiplication(int** MATRIX[], int SQUARE)
{
	int** resultMatrix = generateBlankedMatrix(SQUARE);
	fillMatrixWithZero(resultMatrix, SQUARE);
	for (int i = 0; i < SQUARE; i++) {
		for (int j = 0; j < SQUARE; j++) {
			for (int k = 0; k < SQUARE; k++) {
				resultMatrix[i][j] += (MATRIX[X][i][k] * MATRIX[Y][k][j]);
				// i, j 칸에 대해 i행과 j열을 k로 순환하며 곱한 결과를 모두 합한다.
			}
		}
	}

	printf("X * Y = ");
	printMatrix(resultMatrix, SQUARE);
	deleteMatrix(resultMatrix, SQUARE);
}
