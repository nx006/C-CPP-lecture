#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
-- Menu --
1. Random Square Matrix Generation
2. Transpose (T)
3. Rotation (90, 180, 270, 360 degree)
4. Inverse (^-1)
5. Calculation (+, -, *)
6. Exit
*/

#include <time.h>

#define X 0
#define Y 1
#define MAT_SIZE 2
#define MATRIX_EXIST(flag)                             \
    if (flag == 0)                                     \
    {                                                  \
        puts("Error: Random Square Matrix Not Ready"); \
        return;                                        \
    }

int **MATRIX[MAT_SIZE];
int SQUARE;
typedef enum _CALCULATION_SETUP
{
    PLUS,
    MINUS,
    MULTIPLICATIOIN
} CALCULATION_SETUP;

void printMenu();
void selectMenu(int menuSeleciton);
int getMenuSelection();
void printMatrix(const int **matrix);
void printDoubleMatrix(const double **matrix);
void randomSquareMatrixGeneration();
int **generateBlankedMatrix();
void fillMatrixWithZero(int **matrix);
void fillMatrixWithRandom(int **matrix, const int seed);
void deleteMatrix(int **matrix);
void transpose();
void rotation();
int getDegree();
int **rotate90(const int **);
void inverse();
double **getInverseMatrix(const int **matrix);
void calculation();
CALCULATION_SETUP getCalculationSelection();
void calc_plus();
void calc_minus();
void calc_multiplication();

int main(void)
{
    int menuSelection = 0;
    while (menuSelection != 6)
    {
        printMenu();
        menuSelection = getMenuSelection();
        selectMenu(menuSelection);
    }

    for (int i = 0; i < MAT_SIZE; i++)
    {
        if (MATRIX[i] != NULL)
        {
            deleteMatrix(MATRIX[i]);
        }
    }

    return 0;
}

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

void selectMenu(int menuSeleciton)
{
    static int isMatrixGenerated = 0;

    switch (menuSeleciton)
    {
    case 1:
        randomSquareMatrixGeneration();
        isMatrixGenerated = 1;
        break;
    case 2:
        MATRIX_EXIST(isMatrixGenerated)
        transpose();
        break;
    case 3:
        MATRIX_EXIST(isMatrixGenerated)
        rotation();
        break;
    case 4:
        MATRIX_EXIST(isMatrixGenerated)
        inverse();
        break;
    case 5:
        MATRIX_EXIST(isMatrixGenerated)
        calculation();
        break;
    case 6:
        puts("Exit, thank you");
        return;
    default:
        puts("Thou selected wrong menu, try again");
    }
}

int getMenuSelection()
{
    int selection = 0;
    printf("Choose the item you want: ");
    scanf_s("%d", &selection);
    return selection;
}

void printMatrix(const int **matrix)
{
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            printf("%2d ", matrix[i][j]);
        }
        printf("\n");
        printf("    ");
    }
    printf("\n");
}

void printDoubleMatrix(const double **matrix)
{
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            printf("%9f ", matrix[i][j]);
        }
        printf("\n");
        printf("         ");
    }
    printf("\n");
}

void randomSquareMatrixGeneration()
{
    printf("Input the number of rows (2 or 3): ");
    scanf_s("%d", &SQUARE);

    for (int i = 0; i < MAT_SIZE; i++)
    {
        MATRIX[i] = generateBlankedMatrix();
    }

    for (int i = 0; i < MAT_SIZE; i++)
    {
        fillMatrixWithRandom(MATRIX[i], i);
        // i roles as a seed to fill different matrix of X and Y
    }

    printf("X = ");
    printMatrix(MATRIX[X]);

    printf("Y = ");
    printMatrix(MATRIX[Y]);
}

int **generateBlankedMatrix()
{
    int **matrix = (int **)malloc(sizeof(int *) * SQUARE);
    for (int i = 0; i < SQUARE; i++)
    {
        matrix[i] = (int *)malloc(sizeof(int) * SQUARE);
    }

    return matrix;
}

void fillMatrixWithZero(int **matrix)
{
    for (int i = 0; i < SQUARE; i++)
    {
        memset(matrix[i], 0, sizeof(int) * SQUARE);
    }
}

void fillMatrixWithRandom(int **matrix, const int seed)
{
    srand((unsigned int)time(NULL) * seed);
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            matrix[i][j] = rand() % 100;
        }
    }
}

void deleteMatrix(int **matrix)
{
    for (int i = 0; i < SQUARE; i++)
    {
        free(matrix[i]);
    }

    free(matrix);
}

void transpose()
{
    printf("Transpose X and Y\n");

    printf("X^T = ");
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            printf("%2d ", MATRIX[X][j][i]);
        }
        printf("\n");
        printf("      ");
    }
    printf("\n");

    printf("Y^T = ");
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            printf("%2d ", MATRIX[Y][j][i]);
        }
        printf("\n");
        printf("      ");
    }
    printf("\n");
}

void rotation()
{
    int degree = getDegree();
    int rotationCycle = degree / 90;

    int **rotatedMatrix[2] = {generateBlankedMatrix(), generateBlankedMatrix()};
    for (int i = 0; i < MAT_SIZE; i++)
    {
        memcpy(rotatedMatrix[i], MATRIX[i], sizeof(int *) * SQUARE);
    }

    // rotate Matrix for rotation Cycle
    // ex : if degree == 180, cycle is 2 and rotate for 2 times
    for (int k = 0; k < MAT_SIZE; k++)
    {
        for (int i = 0; i < rotationCycle; i++)
        {
            int **rotationMat = rotate90(rotatedMatrix[k]);
            memcpy(rotatedMatrix[k], rotationMat, sizeof(int *) * SQUARE);
        }
    }

    printf("X = ");
    printMatrix(rotatedMatrix[X]);

    printf("Y = ");
    printMatrix(rotatedMatrix[Y]);

    for (int i = 0; i < MAT_SIZE; i++)
    {
        deleteMatrix(rotatedMatrix[i]);
    }
}

int getDegree()
{
    int degree = 0;
    while (!(degree == 90 || degree == 180 || degree == 270 || degree == 360))
    {
        printf("Input the degree to rotate: ");
        scanf_s("%d", &degree);
        if (!(degree == 90 || degree == 180 || degree == 270 || degree == 360))
        {
            printf("Wrong degree, try again\n");
        }
    }
    return degree;
}

int **rotate90(const int **originalMatrix)
{
    int **transposedMatrix = generateBlankedMatrix();
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            transposedMatrix[j][SQUARE - i - 1] = originalMatrix[i][j];
        }
    }

    return transposedMatrix;
}

void inverse()
{
    double **inverseMatrix[MAT_SIZE];
    inverseMatrix[X] = getInverseMatrix(MATRIX[X]);
    inverseMatrix[Y] = getInverseMatrix(MATRIX[Y]);

    if (inverseMatrix[X] != NULL && inverseMatrix[Y] != NULL)
    {
        printf("X and Y are Invertible, \n");
        printf("Inverse X and Y\n");

        printf("X^(-1) = ");
        printDoubleMatrix(inverseMatrix[X]);

        printf("Y^(-1) = ");
        printDoubleMatrix(inverseMatrix[Y]);
    }
    else if (inverseMatrix[X] == NULL && inverseMatrix != NULL)
    {
        printf("X is not invertible but Y is invertible, \n");
        printf("Inverse Y\n");

        printf("Y^(-1) = ");
        printDoubleMatrix(inverseMatrix[Y]);
    }
    else if (inverseMatrix[X] != NULL && inverseMatrix == NULL)
    {
        printf("X is invertible but Y is not invertible, \n");
        printf("Inverse X\n");

        printf("X^(-1) = ");
        printDoubleMatrix(inverseMatrix[X]);
    }
    else
    {
        printf("X and Y are not invertible\n");
    }

    for (int i = 0; i < MAT_SIZE; i++)
    {
        deleteMatrix(inverseMatrix[i]);
    }
}

double **getInverseMatrix(const int **matrix)
{
    const double ERROR = 1.0e-10;

    double **resultMatrix = (double **)malloc(sizeof(double *) * SQUARE);
    for (int i = 0; i < SQUARE; i++)
    {
        resultMatrix[i] = (double *)malloc(sizeof(double) * SQUARE);
    }

    double **tmpWork = (double **)malloc(sizeof(double *) * SQUARE);
    for (int i = 0; i < SQUARE; i++)
    {
        tmpWork[i] = (double *)malloc(sizeof(double) * SQUARE);
    }

    // tmpWork�� ���� matrix ����
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            tmpWork[i][j] = (double)matrix[i][j];
        }
    }

    // ��� ����� ����Ǵ� resultMatrix ����� ������ķ� �ʱ�ȭ
    for (int i = 0; i < SQUARE; i++)
        for (int j = 0; j < SQUARE; j++)
            resultMatrix[i][j] = (i == j) ? 1 : 0;

    /* �밢 ��Ҹ� 0 �� �ƴ� ���� ���� */
    for (int i = 0; i < SQUARE; i++)
        if (-ERROR < tmpWork[i][i] && tmpWork[i][i] < ERROR)
        {
            for (int k = 0; k < SQUARE; k++)
            {
                if (-ERROR < tmpWork[k][i] && tmpWork[k][i] < ERROR)
                    continue;
                for (int j = 0; j < SQUARE; j++)
                {
                    tmpWork[i][j] += tmpWork[k][j];
                    resultMatrix[i][j] += resultMatrix[k][j];
                }
                break;
            }
            if (-ERROR < tmpWork[i][i] && tmpWork[i][i] < ERROR)
                return NULL;
        }

    /* Gauss-Jordan elimination */
    for (int i = 0; i < SQUARE; i++)
    {
        // �밢 ��Ҹ� 1�� ����
        double constant = tmpWork[i][i]; // �밢 ����� �� ����
        for (int j = 0; j < SQUARE; j++)
        {
            tmpWork[i][j] /= constant;      // tmpWork[i][i] �� 1 �� ����� �۾�
            resultMatrix[i][j] /= constant; // i �� ��ü�� tmpWork[i][i] �� ����
        }

        // i ���� ������ k �࿡�� tmpWork[k][i] �� 0 ���� ����� �ܰ�
        for (int k = 0; k < SQUARE; k++)
        {
            if (k == i)
                continue; // �ڱ� �ڽ��� ���� �ǳʶ�
            if (tmpWork[k][i] == 0)
                continue; // �̹� 0 �� �Ǿ� ������ �ǳʶ�

            // tmpWork[k][i] ���� 0 ���� ����
            constant = tmpWork[k][i];
            for (int j = 0; j < SQUARE; j++)
            {
                tmpWork[k][j] = tmpWork[k][j] - tmpWork[i][j] * constant;
                resultMatrix[k][j] = resultMatrix[k][j] - resultMatrix[i][j] * constant;
            }
        }
    }

    deleteMatrix(tmpWork);
    return resultMatrix;
}

void calculation()
{
    CALCULATION_SETUP selection = getCalculationSelection();
    int **resultMatrix = NULL;
    switch (selection)
    {
    case PLUS:
        calc_plus();
        break;
    case MINUS:
        calc_minus();
        break;
    case MULTIPLICATIOIN:
        calc_multiplication();
        break;
    default:
        puts("ERROR : Wrong Calculation menu selected");
    }
}

CALCULATION_SETUP getCalculationSelection()
{
    char selection;
    while (1)
    {
        printf("Input the calculation (+, -, or *): ");
        while (getchar() != '\n')
            ; // clear the input buffer
        selection = getchar();
        if (selection == '+')
            return PLUS;
        else if (selection == '-')
            return MINUS;
        else if (selection == '*')
            return MULTIPLICATIOIN;
        else
            puts("Thou selected wrong menu. Try again");
    }
}

void calc_plus()
{
    int **resultMatrix = generateBlankedMatrix();
    fillMatrixWithZero(resultMatrix);
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            resultMatrix[i][j] = MATRIX[X][i][j] + MATRIX[Y][i][j];
        }
    }

    printf("X + Y = ");
    printMatrix(resultMatrix);
    deleteMatrix(resultMatrix);
}

void calc_minus()
{
    int **resultMatrix = generateBlankedMatrix();
    fillMatrixWithZero(resultMatrix);
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            resultMatrix[i][j] = MATRIX[X][i][j] - MATRIX[Y][i][j];
        }
    }

    printf("X + Y = ");
    printMatrix(resultMatrix);
    deleteMatrix(resultMatrix);
}

void calc_multiplication()
{
    int **resultMatrix = generateBlankedMatrix();
    fillMatrixWithZero(resultMatrix);
    for (int i = 0; i < SQUARE; i++)
    {
        for (int j = 0; j < SQUARE; j++)
        {
            for (int k = 0; k < SQUARE; k++)
            {
                resultMatrix[i][j] += (MATRIX[X][i][k] * MATRIX[Y][k][j]);
            }
        }
    }

    printf("X * Y = ");
    printMatrix(resultMatrix);
    deleteMatrix(resultMatrix);
}