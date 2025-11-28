#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Estrutura Peca
typedef struct {
    char nome;
    int id;
} Peca;

// Estrutura Fila
#define CAPACIDADE 5
typedef struct {
    Peca elementos[CAPACIDADE];
    int frente;
    int tras;
    int tamanho;
} FilaPecas;

// Variavel global ID unico
int proximo_id = 0;
// Pecas disponiveis
const char tipos_peca[] = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
const int num_tipos = sizeof(tipos_peca) / sizeof(tipos_peca[0]);

// Funcao para inicializar a fila
void inicializarFila(FilaPecas *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

// Funcao para verificar se a fila esta cheia
int estaCheia(FilaPecas *f) {
    return f->tamanho == CAPACIDADE;
}

// Funcao para verificar se a fila esta vazia
int estaVazia(FilaPecas *f) {
    return f->tamanho == 0;
}

// Funcao para gerar uma nova peca automaticamente
Peca gerarPeca() {
    Peca nova_peca;
    // Gera um tipo de peca aleatorio
    nova_peca.nome = tipos_peca[rand() % num_tipos];
    // Atribui o proximo ID unico e incrementa
    nova_peca.id = proximo_id++;
    return nova_peca;
}

// Funcao para inserir uma peca na fila (enqueue)
void enqueue(FilaPecas *f, Peca p) {
    if (estaCheia(f)) {
        printf("A fila esta cheia. Nao e possivel adicionar mais pecas.\n");
    } else {
        f->tras = (f->tras + 1) % CAPACIDADE;
        f->elementos[f->tras] = p;
        f->tamanho++;
        printf("Peca [%c %d] inserida na fila.\n", p.nome, p.id);
    }
}

// Funcao para remover uma peca da fila (dequeue)
Peca dequeue(FilaPecas *f) {
    Peca p = {' ', -1}; // Peca invalida por padrao
    if (estaVazia(f)) {
        printf("A fila esta vazia. Nao ha pecas para jogar.\n");
    } else {
        p = f->elementos[f->frente];
        f->frente = (f->frente + 1) % CAPACIDADE;
        f->tamanho--;
        printf("Peca [%c %d] jogada (removida da frente da fila).\n", p.nome, p.id);
    }
    return p;
}

// Funcao para visualizar a fila no formato especificado
void visualizarFila(FilaPecas *f) {
    if (estaVazia(f)) {
        printf("Fila de pecas: Vazia\n");
    } else {
        printf("Fila de pecas: ");
        int i;
        int contador = 0;
        for (i = f->frente; contador < f->tamanho; i = (i + 1) % CAPACIDADE) {
            printf("[%c %d] ", f->elementos[i].nome, f->elementos[i].id);
            contador++;
        }
        printf("\n");
    }
}

int main() {
    FilaPecas minhaFila;
    inicializarFila(&minhaFila);

    // Inicializa o gerador de numeros aleatorios com base no tempo
    srand(time(NULL));

    // Inicializa a fila com 5 pecas
    for (int i = 0; i < CAPACIDADE; i++) {
        enqueue(&minhaFila, gerarPeca());
    }

    int opcao;
    do {
        printf("\nMenu de Acoes:\n");
        printf("1 - Jogar peca (dequeue)\n");
        printf("2 - Inserir nova peca (enqueue)\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                dequeue(&minhaFila);
                visualizarFila(&minhaFila);
                break;
            }
            case 2: {
                Peca nova = gerarPeca();
                enqueue(&minhaFila, nova);
                visualizarFila(&minhaFila);
                break;
            }
            case 0: {
                printf("Saindo do programa.\n");
                break;
            }
            default: {
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }
    } while (opcao != 0);

    return 0;
}