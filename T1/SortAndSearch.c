#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10000.0
#define QTD 10000
void geraAleatorios(float* vetorFloat, int quantidade) {
	for (int i = 0; i < quantidade; i++) {
		vetorFloat[i] = ((float)
			rand() / RAND_MAX) * MAX;
	}
}
int busca_binaria(float vetor[], int tamanho, float valor) {
	int inicio = 0;
	int fim = tamanho - 1;
	while (inicio <= fim) {
		int meio = (inicio + fim) / 2;
		if (vetor[meio] == valor) {
			return 1; // Valor encontrado
		}
		else if (vetor[meio] < valor) {
			inicio = meio + 1;
		}
		else {
			fim = meio - 1;
		}
	}
	return 0; // Valor n�o encontrado
}
int main() {
	srand(time(NULL));
	// Gerando 10 mil aleat�rios
	float vetorFloat1[QTD];
	geraAleatorios(vetorFloat1, QTD);
	// M�todo : Bubble sort
	float TEMP;
	int CHANGE = 1;
	while (CHANGE != 0) {
		CHANGE = 0;
		for (int i = 0; i < QTD - 1; i++) {
			if (vetorFloat1[i] > vetorFloat1[i + 1]) {
				TEMP = vetorFloat1[i + 1];
				vetorFloat1[i + 1] = vetorFloat1[i];
				vetorFloat1[i] = TEMP;
				CHANGE += 1;
			}
		}
	}
	// Gerando mais 10 mil aleat�rios
	float vetorFloat2[QTD];
	geraAleatorios(vetorFloat2, QTD);
	// Verificar corresp�nd�ncia entre vetores #faz mais sentido com inteiros...
		int ID_NotFound = 0;
	int correspondencia = 0;
	float vetorFloatNaoEncontrados[QTD];
	clock_t START, END;
	double TempoDeExecucao;
	START = clock();
	for (int i = 0; i < QTD; i++) {
		if (busca_binaria(vetorFloat1, QTD, vetorFloat2[i]) == 0) {
			vetorFloatNaoEncontrados[ID_NotFound] = vetorFloat2[i];
			ID_NotFound++;
		}
	}
	END = clock();
	TempoDeExecucao = ((double)(END - START)) / CLOCKS_PER_SEC;
	// Vetor 1 ordenado
	for (int i = 0; i < 10000; i++) {
		printf("%d : %f\n", i,
			vetorFloat1[i]);
	}
	// N�meros n�o encontrados do vetor 2 no vetor 1
	for (int i = 0; i < ID_NotFound - 1; i++) {
		printf("%d : %f\n", i,
			vetorFloatNaoEncontrados[i]);
	}
	// Tempo de execu��o para achar nao correspond�ncias
	printf("Tempo de execucao: %f segundos\n", TempoDeExecucao);
	return 0;
}