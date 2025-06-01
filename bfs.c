#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura do grafo
typedef struct {
    int numVertices;
    int matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

// Fila para BFS
typedef struct {
    int itens[MAX_VERTICES];
    int frente, tras;
} Fila;

// Criação do grafo
Grafo* criarGrafo(int n) {
    Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
    grafo->numVertices = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            grafo->matriz[i][j] = 0;
    return grafo;
}

// Adiciona aresta direcionada
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    grafo->matriz[origem][destino] = peso;
}

// Inicializa fila
void inicializarFila(Fila* f) {
    f->frente = 0;
    f->tras = -1;
}

// Verifica se a fila está vazia
int filaVazia(Fila* f) {
    return f->frente > f->tras;
}

// Enfileira
void enfileirar(Fila* f, int valor) {
    f->tras++;
    f->itens[f->tras] = valor;
}

// Desenfileira
int desenfileirar(Fila* f) {
    return f->itens[f->frente++];
}

// BFS com níveis
void bfsComNivel(Grafo* grafo, int inicio) {
    int visitado[MAX_VERTICES] = {0};
    int nivel[MAX_VERTICES] = {0};
    Fila fila;

    inicializarFila(&fila);
    visitado[inicio] = 1;
    nivel[inicio] = 0;
    enfileirar(&fila, inicio);

    printf("\n📘 Níveis dos vértices a partir do vértice %d:\n", inicio);

    while (!filaVazia(&fila)) {
        int atual = desenfileirar(&fila);
        printf("Vértice %d: nível %d\n", atual, nivel[atual]);

        for (int i = 0; i < grafo->numVertices; i++) {
            if (grafo->matriz[atual][i] && !visitado[i]) {
                visitado[i] = 1;
                nivel[i] = nivel[atual] + 1;
                enfileirar(&fila, i);
            }
        }
    }
}

// Exibe matriz de adjacência em formato gráfico
void imprimirGrafo(Grafo* grafo) {
    printf("\n🧩 Matriz de Adjacência (█ = aresta, . = vazio):\n\n");

    printf("    ");
    for (int i = 0; i < grafo->numVertices; i++)
        printf(" %d ", i);
    printf("\n");

    for (int i = 0; i < grafo->numVertices; i++) {
        printf(" %d |", i);
        for (int j = 0; j < grafo->numVertices; j++) {
            if (grafo->matriz[i][j])
                printf(" 1 ");
            else
                printf(" . ");
        }
        printf("\n");
    }
}

int main() {
    Grafo* grafo = criarGrafo(6);

    // Arestas: (0→1), (0→2), (1→3), (1→4), (2→4), (4→5)
    adicionarAresta(grafo, 0, 1, 1);
    adicionarAresta(grafo, 0, 2, 1);
    adicionarAresta(grafo, 1, 3, 1);
    adicionarAresta(grafo, 1, 4, 1);
    adicionarAresta(grafo, 2, 4, 1);
    adicionarAresta(grafo, 4, 5, 1);

    imprimirGrafo(grafo);

    bfsComNivel(grafo, 0);  // início do BFS no vértice 0

    free(grafo);
    return 0;
}
