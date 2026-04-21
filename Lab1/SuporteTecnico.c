#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 20
#define TAM_DESC

typedef struct {
    int id, prioridade;  //Heap será ordenado de acordo com o nível de prioridade (inteira positiva), formando um MaxHeap
    char descricao[TAM_DESC];

} Chamado

typedef struct {
    Chamado itens[MAX_ITENS];        
    int tamanho;                 // Quantidade atual de elementos
} HeapItens;

// Funções auxiliares para cálculo de índice
int parent(int i) {
    return (i - 1) / 2;
}

int left_child(int i) {
    return (2 * i + 1);
}

int right_child(int i) {
    return (2 * i + 2);
}

// Função para trocar dois elementos de lugar no array
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Ajusta de baixo para cima após inserir
void heapify_up(HeapItens *heap, int index) {
    // Enquanto não é a raiz e o valor do nó for maior que o do pai (ainda pode subir)
    while (index > 0 && (heap->itens[index]->prioridade) > (heap->itens[parent(index)]->prioridade)) {
        swap(&heap->itens[index], &heap->itens[parent(index)]);
        index = parent(index);
    }
}

// Ajusta de cima para baixo após remover
void heapify_down(HeapItens *heap, int index) {
    int left = left_child(index);
    int right = right_child(index);
    int largest = index;

    // Verifica se o filho esquerdo é maior que o atual
    if (left < heap->tamanho && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    // Verifica se o filho direito é maior que o "maior" encontrado (atual ou direito)
    if (right < heap->tamanho && (heap->itens[right]->prioridade) > (heap->itens[largest]->prioridade)) {
        largest = right;
    }

    // Se algum filho for maior, troca e continua descendo (recursividade - stack call)
    if (largest != index) {
        swap(&heap->itens[index], &heap->itens[largest]);
        heapify_down(heap, largest);
    }
}

// Inicializa o heap
void init_heap(HeapItens *heap) {
    heap->tamanho = 0;
}

// Insere um valor no heap (usa heapfy UP)
void heap_insert(HeapItens *heap, int value, int id, char desc[]) {
    if (heap->tamanho == MAX_ITENS) {
        printf("Erro: Heap está cheio!\n");
        return;
    }
    //Verificando se a descrição inserida está de acordo com o tamanho máximo suportado
    if ((sizeof(desc)/sizeof(desc[0])) > TAM_DESC){
        printf("Erro: descricao muito longa!\n");
        return;
    }

    // Coloca o novo valor no final do array
    int index = heap->tamanho;
    heap->itens[index]->prioridade = value;
    heap->itens[index]->id = id;
    strcpy(heap->itens[index]->descricao, desc);
    heap->tamanho++;

    // Ajusta de baixo para cima
    heapify_up(heap, index);
}

// Remove (extrai) e retorna o maior elemento do heap (MaxHeap)
int heap_extract_max_prioridade(HeapItens *heap) {
    if (heap->tamanho == 0) {
        printf("Erro: Heap está vazio!\n");
        return -1; // Ou algum valor que indique erro
    }

    int max_prioridade = heap->itens[0]->prioridade;          // Raiz (maior valor)
    heap->itens[0] = heap->itens[heap->tamanho - 1]; // Substitui pela última folha
    heap->tamanho--;

    // Ajusta de cima para baixo
    heapify_down(heap, 0);

    return max_prioridade;
}

void heap_extract_max_chamado(HeapItens *heap) {
     if (heap->tamanho == 0) {
        printf("Erro: Heap está vazio!\n");
        return; // Ou algum valor que indique erro
    }

    int max_prioridade = heap->itens[0]->prioridade;          // Raiz (maior valor)
    int id = heap->itens[0]->id;
    char desc[TAM_DESC];
    strcpy(desc, heap->itens[0]->descricao);

    heap->itens[0] = heap->itens[heap->tamanho - 1]; // Substitui pela última folha
    heap->tamanho--;

    // Ajusta de cima para baixo
    heapify_down(heap, 0);

    printf("--CHAMADO ATENDIDO--");
    printf("ID: %d || Prioridade: %d || Descricao: %s", id, max_prioridade, desc);
}

// Imprime o heap (apenas para debug)
void print_heap(HeapItens *heap) {
    printf("CHAMADOS: ");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("Prioridade: %d, ID: %d, Descricao: %s", heap->[i]->prioridade, heap->[i]->id, heap->[i]->descricao);
    }
    printf("\n");
}

// Exemplo de uso
int main() {
    HeapItens heap;
    init_heap(&heap);


    return 0;
}
