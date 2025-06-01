#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição de estrutura para um vértice
typedef struct {
    int id;            // identificador único
    char nome[50];     // nome do vértice
} Vertice;

// Definição de estrutura para uma aresta
typedef struct {
    int destino;       // vértice de destino
    int peso;          // peso da aresta
} Aresta;

// Nó da lista de adjacência
typedef struct NoAresta {
    Aresta aresta;
    struct NoAresta* prox;
} NoAresta;

// Estrutura básica para um grafo com lista de adjacência
typedef struct {
    int numVertices;
    int numArestas;
    Vertice* vertices;
    NoAresta** listaAdj;
} Grafo;

// Função para criar o grafo
Grafo* criarGrafo(int numVertices) {
    Grafo* g = malloc(sizeof(Grafo));
    g->numVertices = numVertices;
    g->numArestas = 0;
    g->vertices = malloc(numVertices * sizeof(Vertice));
    g->listaAdj = calloc(numVertices, sizeof(NoAresta*));
    return g;
}

// Função para adicionar vértice
void adicionarVertice(Grafo* g, int id, const char* nome) {
    if (id >= g->numVertices) {
        printf("ID de vértice inválido!\n");
        return;
    }
    g->vertices[id].id = id;
    strncpy(g->vertices[id].nome, nome, sizeof(g->vertices[id].nome) - 1);
}

// Função para adicionar aresta
void adicionarAresta(Grafo* g, int origem, int destino, int peso) {
    if (origem >= g->numVertices || destino >= g->numVertices) {
        printf("Vértice inválido!\n");
        return;
    }

    NoAresta* novo = malloc(sizeof(NoAresta));
    novo->aresta.destino = destino;
    novo->aresta.peso = peso;
    novo->prox = g->listaAdj[origem];
    g->listaAdj[origem] = novo;

    g->numArestas++;
}

// Função para imprimir o grafo
void imprimirGrafo(Grafo* g) {
    printf("Grafo (%d vértices, %d arestas):\n", g->numVertices, g->numArestas);
    for (int i = 0; i < g->numVertices; i++) {
        printf("Vértice %d (%s): ", g->vertices[i].id, g->vertices[i].nome);
        NoAresta* atual = g->listaAdj[i];
        while (atual != NULL) {
            printf("-> %d (peso %d) ", atual->aresta.destino, atual->aresta.peso);
            atual = atual->prox;
        }
        printf("\n");
    }
}

// Liberação de memória
void liberarGrafo(Grafo* g) {
    for (int i = 0; i < g->numVertices; i++) {
        NoAresta* atual = g->listaAdj[i];
        while (atual != NULL) {
            NoAresta* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
    free(g->listaAdj);
    free(g->vertices);
    free(g);
}

// Exemplo de uso
int main() {
    Grafo* g = criarGrafo(3);

    adicionarVertice(g, 0, "A");
    adicionarVertice(g, 1, "B");
    adicionarVertice(g, 2, "C");

    adicionarAresta(g, 0, 1, 5);
    adicionarAresta(g, 1, 2, 3);
    adicionarAresta(g, 2, 0, 2);

    imprimirGrafo(g);

    liberarGrafo(g);
    return 0;
}
