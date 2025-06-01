#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura do grafo direcionado
typedef struct {
    int numVertices;
    int matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

// Cria grafo vazio
Grafo* criarGrafo(int n) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->numVertices = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            grafo->matriz[i][j] = 0;
    return grafo;
}

// Adiciona aresta direcionada
void adicionarAresta(Grafo* grafo, int origem, int destino, int peso) {
    if (origem >= 0 && destino >= 0 && origem < grafo->numVertices && destino < grafo->numVertices) {
        grafo->matriz[origem][destino] = peso;
    }
}

// Imprime a matriz de adjacência como um gráfico ASCII
void imprimirMatriz(Grafo* grafo) {
    printf("\nMatriz de Adjacência:\n    ");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("%2d ", i);
    }
    printf("\n   ");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("---");
    }
    printf("\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        printf("%2d| ", i);
        for (int j = 0; j < grafo->numVertices; j++) {
            printf("%2d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

// DFS com rastreamento da ordem de visita
void dfsComOrdem(Grafo* grafo, int vertice, int* visitado, int* ordem, int* contador) {
    visitado[vertice] = 1;
    ordem[vertice] = ++(*contador);
    printf("Vértice %d visitado na ordem: %d\n", vertice, ordem[vertice]);

    for (int i = 0; i < grafo->numVertices; i++) {
        if (grafo->matriz[vertice][i] && !visitado[i]) {
            dfsComOrdem(grafo, i, visitado, ordem, contador);
        }
    }
}

// Função auxiliar para executar a DFS a partir de um vértice inicial
void iniciarDFS(Grafo* grafo, int inicio) {
    int* visitado = (int*) calloc(grafo->numVertices, sizeof(int));
    int* ordem = (int*) calloc(grafo->numVertices, sizeof(int));
    int contador = 0;

    printf("\n--- DFS iniciada a partir do vértice %d ---\n", inicio);
    dfsComOrdem(grafo, inicio, visitado, ordem, &contador);

    // Exibe ordem final de visitação
    printf("\nOrdem de visitação final:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        if (ordem[i] > 0)
            printf("Vértice %d → Ordem %d\n", i, ordem[i]);
    }

    free(visitado);
    free(ordem);
}

// Função principal
int main() {
    Grafo* grafo = criarGrafo(5);

    // Arestas: (0→1), (0→2), (1→2), (1→3), (2→4), (3→4), (4→0)
    adicionarAresta(grafo, 0, 1, 1);
    adicionarAresta(grafo, 0, 2, 1);
    adicionarAresta(grafo, 1, 2, 1);
    adicionarAresta(grafo, 1, 3, 1);
    adicionarAresta(grafo, 2, 4, 1);
    adicionarAresta(grafo, 3, 4, 1);
    adicionarAresta(grafo, 4, 0, 1); // fecha ciclo

    // Imprime o grafo em forma de matriz
    imprimirMatriz(grafo);

    // Executa DFS a partir de diferentes vértices
    iniciarDFS(grafo, 0);
    iniciarDFS(grafo, 2);
    iniciarDFS(grafo, 4);

    free(grafo);
    return 0;
}
