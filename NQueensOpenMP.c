/*
Introducao ao Processamento Paralelo e Distribuido
1� trabalho - parte 1

N-Queens com OpenMP

Marina Souza Cruzeiro
Roger Dilli Afonso

Abril/2021
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

#define N 5

int insert(int count, int board[N][N]);
int verify(int row, int column, int board[N][N]);
void printQueens(int board[N][N]);

// -------------------------------------------

int main(int argc, char *argv[])
{

    int row, column;
    int i, j;
    int board[N][N];
	double startTime, endTime, finalTime;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }

    srand((unsigned)time(NULL));

    // utiliza uma posicao aleatoria como primeira
    column = rand() % N;
    row = 0;
    board[row][column] = 1;
    
    startTime = omp_get_wtime();
    
#pragma omp parallel
    {
#pragma omp single
        insert(0, board);
    }
    
    endTime = omp_get_wtime();
	finalTime = endTime - startTime;
    
    printQueens(board);
    
    printf("Tempo: %f\n", finalTime);
}

// -------------------------------------------

int insert(int count, int board[N][N])
{

    int i, j;

    // verifica se ja completou o tabuleiro
    if (count == N - 1)
    {
        return true;
    }

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {

            // verifica se pode inserir a rainha no local
            
            bool y ;
            y= verify(i, j, board);
            if (y)
            {
                board[i][j] = 1;

                // recursao para ver se as outras posicoes ficam ok
                bool x;
                
                x = insert(count + 1, board);
                if (x)
                {
                    return true;
                }

                board[i][j] = 0;
            }
        }
    }

    return false;
}

int verify(int row, int column, int board[N][N])
{

    int i, j, k;
    int isFalse = 0;

    // verifica linha
    #pragma omp task shared(isFalse, i, j) firstprivate(board)
    //printf("Thread ----: %d\n", omp_get_thread_num());
    for (i = row, j = N - 1; j >= 0; j--)
    {
        if (board[i][j])
        {
            isFalse = 1;
        }
    }
    // verifica coluna
    #pragma omp task shared(isFalse, i, j) firstprivate(board)
    //printf("Thread ----: %d\n", omp_get_thread_num());
    for (i = N - 1, j = column; i >= 0; i--)
    {
        if (board[i][j])
        {
            isFalse = 1;
        }
    }

    // verifica diagonais

    // para a esquerda
    #pragma omp task shared(isFalse, i, j) firstprivate(board)
    //printf("Thread ----: %d\n", omp_get_thread_num());
    i = row - 1;
    k = row + 1;
    for (j = column - 1; j >= 0; j--)
    {

        if (i >= 0)
        {
            if (board[i][j])
            {
                isFalse = 1;
            }
        }
        i--;
        if (k < N)
        {
            if (board[k][j])
            {
                isFalse = 1;
            }
        }
        k++;
    }
    // para a direita
    #pragma omp task shared(isFalse, i, j) firstprivate(board)
    //printf("Thread ----: %d\n", omp_get_thread_num());
    i = row - 1;
    k = row + 1;
    for (j = column + 1; j < N; j++)
    {

        if (i >= 0)
        {
            if (board[i][j])
            {
                isFalse = 1;
            }
        }
        i--;
        if (k < N)
        {
            if (board[k][j])
            {
                isFalse = 1;
            }
        }
        k++;
    }
	
	#pragma omp taskwait
	if (isFalse) {
		return false;
	} else {
		return true;
	}
	
}

void printQueens(int board[N][N])
{

    int i, j;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
