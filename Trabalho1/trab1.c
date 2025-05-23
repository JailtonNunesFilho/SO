//Trabalho 1 - Threads:
//Jailton Nunes Filho
//Pedro Henrique Marques de Labio

#include <pthread.h> 
#include <stdio.h>
#include <stdlib.h>

/*
#define M 3
#define K 2
#define N 3
#define NUM_THREADS (M*N) 

int A[M][K] = { {1,4}, {2,5}, {3,6} };
int B[K][N] = { {8,7,6}, {5,4,3} };
int C[M][N] = {0};
*/
#define MAX 100
#define MIN 0

int **A, **B, **C;
int linhaA, coluna_linha, colunaB;

struct v
{
	int i;
	int j;
};

void * multMatriz(void *data){
	struct v *ponto = (struct v *)(data);

	for(int n=0; n<coluna_linha; n++){
		C[ponto -> i][ponto -> j] += (A[ponto -> i][n] * B[n][ponto -> j]);
	}
	free(ponto);
}

void inicializarMatrizes(){

	A = (int**)malloc(linhaA * sizeof(int*));
        for(int i = 0; i < linhaA; i++)
                A[i] = (int *)malloc(coluna_linha * sizeof(int));

        B = (int**)malloc(coluna_linha * sizeof(int*));
        for(int i = 0; i < coluna_linha; i++)
                B[i] = (int *)malloc(colunaB * sizeof(int));

        C = (int**)malloc(linhaA * sizeof(int*));
        for(int i = 0; i < linhaA; i++)
                C[i] = (int *)malloc(colunaB * sizeof(int));
}

void preencherMatrizes(){

	srand(time(NULL));

        for(int i=0; i < linhaA; i++) for(int i=0; i < linhaA; i++)
                for(int j=0; j<coluna_linha; j++)
                        A[i][j] = MIN + rand() % (MAX - MIN + 1);

        for(int i=0; i < coluna_linha; i++)
                for(int j=0; j<colunaB; j++)
                        B[i][j] = MIN + rand() % (MAX - MIN + 1);

}

void liberarMemoriaMatrizes(){

	for(int i=0; i < linhaA; i++)
                free(A[i]);
        free(A);
        for(int i=0; i < coluna_linha; i++)
                free(B[i]);
        free(B);
        for(int i=0; i < linhaA; i++)
                free(C[i]);
        free(C);

}

int main(){

	printf("Digite o número de linhas da Matriz A: ");
	scanf("%d", &linhaA);
	printf("Digite o número de colunas da Matriz A (linhas da Matriz B): ");
        scanf("%d", &coluna_linha);
	printf("Digite o número de colunas da Matriz B: ");
        scanf("%d", &colunaB);
	//printf("Voce digitou: %d\n", a);
	
	inicializarMatrizes();

	preencherMatrizes();
	
	int NUM_THREADS = (linhaA * colunaB);

	pthread_t workers[NUM_THREADS];

	int t = 0;
	for(int i=0; i<linhaA; i++){
                for(int j=0; j<colunaB; j++){
                        struct v *data = (struct v*) malloc(sizeof(struct v));
                        data -> i = i;
                        data -> j = j;
			pthread_create(&workers[t], NULL, multMatriz, data);
			t++;
                }
        }

	for(int i=0; i < NUM_THREADS; i++)
		pthread_join(workers[i], NULL);

	printf("Matriz A: \n");
	for(int i=0; i<linhaA; i++){
                printf("| ");
                for(int j=0; j<coluna_linha; j++)
                        printf("%d\t", A[i][j]);
                printf("|\n");
        }
	printf("Matriz B: \n");
	for(int i=0; i<coluna_linha; i++){
                printf("| ");
                for(int j=0; j<colunaB; j++)
                        printf("%d\t", B[i][j]);
                printf("|\n");
        }
	printf("Matriz C: \n");
	for(int i=0; i<linhaA; i++){
		printf("| ");
		for(int j=0; j<colunaB; j++)
			printf("%d\t", C[i][j]);
		printf("|\n");
	}

	liberarMemoriaMatrizes();
	exit(0);

}
