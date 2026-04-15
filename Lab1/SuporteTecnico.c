#include <stdio.h>
#include <stdlib.h>

#define MAX_ITENS 20

typedef struct {
    int id, prioridade;  //Heap será ordenado de acordo com o nível de prioridade
    char descricao[100];

} Chamado

typedef struct {
    int itens[MAX_ITENS];        
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
    // Enquanto não é a raiz e o valor do nó for maior que o do pai
    while (index > 0 && heap->data[index] > heap->data[parent(index)]) {
        swap(&heap->data[index], &heap->data[parent(index)]);
        index = parent(index);
    }
}

// Ajusta de cima para baixo após remover
void heapify_down(HeapItens *heap, int index) {
    int left = left_child(index);
    int right = right_child(index);
    int largest = index;

    // Verifica se o filho esquerdo é maior que o atual
    if (left < heap->size && heap->data[left] > heap->data[largest]) {
        largest = left;
    }

    // Verifica se o filho direito é maior que o "maior" encontrado
    if (right < heap->size && heap->data[right] > heap->data[largest]) {
        largest = right;
    }

    // Se algum filho for maior, troca e continua descendo
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        heapify_down(heap, largest);
    }
}

// Inicializa o heap
void init_heap(HeapItens *heap) {
    heap->size = 0;
}

// Insere um valor no heap
void heap_insert(HeapItens *heap, int value) {
    if (heap->size == MAX_ITENS) {
        printf("Erro: Heap está cheio!\n");
        return;
    }

    // Coloca o novo valor no final do array
    int index = heap->size;
    heap->data[index] = value;
    heap->size++;

    // Ajusta de baixo para cima
    heapify_up(heap, index);
}

// Remove (extrai) e retorna o maior elemento do heap
int heap_extract_max(HeapItens *heap) {
    if (heap->size == 0) {
        printf("Erro: Heap está vazio!\n");
        return -1; // Ou algum valor que indique erro
    }

    int max_value = heap->data[0];          // Raiz (maior valor)
    heap->data[0] = heap->data[heap->size - 1]; // Substitui pela última folha
    heap->size--;

    // Ajusta de cima para baixo
    heapify_down(heap, 0);

    return max_value;
}

// Imprime o heap (apenas para debug)
void print_heap(HeapItens *heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

// Exemplo de uso
int main() {
    HeapItens heap;
    init_heap(&heap);

    // Inserindo alguns valores
    heap_insert(&heap, 10);
    heap_insert(&heap, 5);
    heap_insert(&heap, 30);
    heap_insert(&heap, 2);
    heap_insert(&heap, 100);
    heap_insert(&heap, 50);

    print_heap(&heap);

    int removido = heap_extract_max(&heap);
    printf("Maior valor removido: %d\n", removido);
    print_heap(&heap);

    removido = heap_extract_max(&heap);
    printf("Maior valor removido: %d\n", removido);
    print_heap(&heap);

    return 0;
}
