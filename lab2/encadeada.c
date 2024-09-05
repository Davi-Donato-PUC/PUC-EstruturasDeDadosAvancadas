// Davi Donato : 2320399
// João Pedro Gonçalves Zaidman : 2320464

#include  <stdio.h>
#include <stdlib.h>
#include <string.h>

int r = 0;
int y = 0;
int g = 0;

typedef struct elemento Elemento;
struct elemento {
    char cor;
    int  num;
    Elemento* pNext;
};

// Converte inicial da cor em string com nome da cor
unsigned char* NC(char color) {
    char* cor = malloc(20);
    if      (color == 'R') strcpy(cor, "Vermelho");
    else if (color == 'Y') strcpy(cor, "Amarelo");
    else if (color == 'G') strcpy(cor, "Verde");
    return cor;
}

// Classificar cor em prioridade representado por um inteiro
unsigned char TN(char color) {
    if (color == 'R') return 1;
    else if (color == 'Y') return 2;
    else if (color == 'G') return 3;
}

// Exibe lista encadeada e quntidade de cadaa elemento
void exibirLista(Elemento* pElemento) {
    while (pElemento != NULL) {
        printf("%s - %d \n", NC(pElemento->cor), pElemento->num);
        pElemento = pElemento->pNext;
    }
    printf("\n%d Vermelho(s)\n%d Amarelo(s)\n%d Verde(s)", r, y, g);
}

// Adiciona um elemento
Elemento* adicionarElemento(Elemento* pElemento, char cor, int num) {
    printf("ADICIONADO %s %d:\n", NC(cor), num);
    Elemento* new_pElemento = (Elemento*)malloc(sizeof(Elemento));
    new_pElemento->cor = cor;
    new_pElemento->num = num;
    new_pElemento->pNext = NULL;

    if (pElemento == NULL) return new_pElemento;

    if (TN(cor) < TN(pElemento->cor)) {
        new_pElemento->pNext = pElemento; 
        pElemento = new_pElemento; 
        return pElemento; 
    }

    Elemento* aux = pElemento;
    while (aux->pNext != NULL) {
        if ((TN(cor) < TN(aux->pNext->cor)) || ((TN(cor) == TN(aux->pNext->cor)) && (num < aux->pNext->num))) {
            new_pElemento->pNext = aux->pNext;
            aux->pNext = new_pElemento;
            return pElemento;
        }
        aux = aux->pNext;
    }

    aux->pNext = new_pElemento;
    return pElemento;
}

// Retira um elemento
Elemento* retirarElemento(Elemento* pElemento, char cor, int num) {
    printf("RETIRADO %s %d:\n", NC(cor), num);
 
    if (pElemento->pNext == NULL) return NULL;

    if (pElemento->cor == cor && pElemento->num == num) return pElemento->pNext;
    Elemento* aux1 = pElemento, * aux2 = pElemento;
    while (aux2 != NULL) {
        if (aux2->cor == cor && aux2->num == num) {
            aux1->pNext = aux2->pNext;
            return pElemento; 
        }
        aux1 = aux2;
        aux2 = aux2->pNext;
    }
    return pElemento;
}

// Gere o processo de atualizar a lista conforme chegada e sa�da de pacientes
Elemento* gerarListas(Elemento* pElemento, FILE* Arquivo) {
    char cor; char es; int  num;

    while (fscanf(Arquivo, "%d - %c %c\n", &num, &cor, &es) == 3) {
        if (es == 'E') {
            pElemento = adicionarElemento(pElemento, cor, num);
            if (cor == 'R') r++;
            else if (cor == 'Y') y++;
            else if (cor == 'G') g++;
        }
        if (es == 'S') {
            pElemento = retirarElemento(pElemento, cor, num);
            if (cor == 'R') r--;
            else if (cor == 'Y') y--;
            else if (cor == 'G') g--;
        }
        exibirLista(pElemento);
        printf("\n\n");
    }
    fclose(Arquivo);
    return pElemento;
}

void main() {
    FILE* Arquivo = fopen("entrada.txt", "r");
    Elemento* Lista = NULL;

    Lista = gerarListas(Lista, Arquivo);

    printf("LISTA FINAL:\n");
    exibirLista(Lista);
}