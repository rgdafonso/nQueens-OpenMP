/*
Introducao ao Processamento Paralelo e Distribuido
1º trabalho - parte 1



Abril/2021
*/

#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>

#define N 8

int insert (int count, int board[N][N]);
int verify (int row, int column, int board[N][N]);
void printQueens (int board[N][N]);

// -------------------------------------------

int main (int argc, char *argv[]) {
	
	int row, column;
	int i, j;
	int board[N][N];
	
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			board[i][j] = 0;
		}
	}
	
	srand((unsigned)time(NULL));
	
	// utiliza uma posicao aleatoria como primeira
	column = rand()%N;
	row = 0;
	board[row][column] = 1;
	
	insert(0, board);

	printQueens(board);

}

// -------------------------------------------

int insert (int count, int board[N][N]) {
	
	int i, j;
	
	// verifica se já completou o tabuleiro
	if (count == N-1) {
		return true;
	}

	for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {	
			
			// verifica se pode inserir a rainha no local
            if (verify(i, j, board)) {
                board[i][j] = 1;

				// recursao para ver se as outras posicoes ficam ok
                if (insert(count+1, board)) {
                    return true;
                }
                
                board[i][j] = 0;
            }
        }
    }

    return false;
}

int verify (int row, int column, int board[N][N]) {

	int i, j, k;
		
	// verifica linha
	for (i = row, j = N-1; j >= 0; j--) {
		if (board[i][j]) {
			return false;
		}
	}
	// verifica coluna
	for (i = N-1, j = column; i >= 0; i--) {
		if (board[i][j]) {
			return false;
		}
	}
	
	// verifica diagonais
	
	// para a esquerda
	i = row-1;
	k = row+1;
	for (j = column-1; j>=0; j--) {
		
		if (i >= 0) {
			if (board[i][j]) {
				return false;
			}
		}
		i--;
		if (k < N) {
			if (board[k][j]) {
				return false;
			}
		}
		k++;
	}
	// para a direita
	i = row-1;
	k = row+1;
	for (j = column+1; j < N; j++) {
		
		if (i >= 0) {
			if (board[i][j]) {
				return false;
			}
		}
		i--;
		if (k < N) {
			if (board[k][j]) {
				return false;
			}
		}
		k++;
	}
	
	return 1;
}

void printQueens (int board[N][N]) {
	
	int i, j;
	
	for (i = 0; i<N; i++) {
		for (j = 0; j<N; j++) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
}

