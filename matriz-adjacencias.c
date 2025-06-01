#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

// Estrutura para o grafo
typedef struct {
    int numVertices;
    int matriz[MAX_VERTICES][MAX_VERTICES];
} Grafo;

// Cria o grafo
Grafo* criarGrafo(int n) {
    Grafo* grafo = (Grafo*) malloc(sizeof(Grafo));
    grafo->numVertices = n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            grafo->matriz[i][j] = 0;
    return grafo;
}

// Adiciona aresta não direcionada
void adicionarArestaNaoDirecionada(Grafo* grafo, int i, int j, int peso) {
    if (i >= 0 && j >= 0 && i < grafo->numVertices && j < grafo->numVertices) {
        grafo->matriz[i][j] = peso;
        grafo->matriz[j][i] = peso;
    }
}

// Imprime a matriz de adjacência
void imprimirMatriz(Grafo* grafo) {
    printf("\nMatriz de Adjacência:\n");
    for (int i = 0; i < grafo->numVertices; i++) {
        for (int j = 0; j < grafo->numVertices; j++) {
            printf("%d ", grafo->matriz[i][j]);
        }
        printf("\n");
    }
}

// Desenha o grafo no terminal (apenas para 4 vértices)
void imprimirGrafoVisual(Grafo* grafo) {
    if (grafo->numVertices != 4) {
        printf("\nVisualização gráfica disponível apenas para 4 vértices.\n");
        return;
    }

    printf("\nVisualização do Grafo:\n");

    // Representação baseada em layout fixo
    //      0
    //     / \
    //    1---2
    //         \
    //          3

    // Verifica conexões e imprime visualmente
    printf("     %d\n", 0);
    printf("    ");

    if (grafo->matriz[0][1]) printf("/"); else printf(" ");
    printf("   ");

    if (grafo->matriz[0][2]) printf("\\"); else printf(" ");
    printf("\n");

    printf("   %d", grafo->matriz[0][1] ? 1 : ' ');
    printf(" ");

    if (grafo->matriz[1][2]) printf("---"); else printf("   ");
    printf(" %d\n", grafo->matriz[0][2] ? 2 : ' ');

    printf("             ");

    if (grafo->matriz[2][3]) {
        printf("\\\n");
        printf("              %d\n", 3);
    }
}

// Função principal
int main() {
    Grafo* grafo = criarGrafo(4);

    adicionarArestaNaoDirecionada(grafo, 0, 1, 1);
    adicionarArestaNaoDirecionada(grafo, 0, 2, 1);
    adicionarArestaNaoDirecionada(grafo, 1, 2, 1);
    adicionarArestaNaoDirecionada(grafo, 2, 3, 1);

    imprimirMatriz(grafo);
    imprimirGrafoVisual(grafo);

    free(grafo);
    return 0;
}
