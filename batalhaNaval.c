#include <stdio.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função auxiliar para verificar se há sobreposição
int verificaSobreposicao(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha[], int coluna[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (tabuleiro[linha[i]][coluna[i]] == 3) {
            return 1; // sobreposição detectada
        }
    }
    return 0;
}

// Função para posicionar um navio
void posicionaNavio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha[], int coluna[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[linha[i]][coluna[i]] = 3;
    }
}
int main() {
    // Nível Novato - Posicionamento dos Navios
    // Sugestão: Declare uma matriz bidimensional para representar o tabuleiro (Ex: int tabuleiro[5][5];).
    // Sugestão: Posicione dois navios no tabuleiro, um verticalmente e outro horizontalmente.
    // Sugestão: Utilize `printf` para exibir as coordenadas de cada parte dos navios.
    // Matriz representando o tabuleiro (10x10)
/*
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Vetores representando os navios (3 posições cada)
    int navio_horizontal[TAM_NAVIO] = {3, 3, 3};
    int navio_vertical[TAM_NAVIO] = {3, 3, 3};

    // Coordenadas iniciais (linha, coluna) definidas no código
    // Você pode alterar para testar diferentes posições
    int linha_horizontal = 2, coluna_horizontal = 4; // navio horizontal começa em (2,4)
    int linha_vertical = 5, coluna_vertical = 7;     // navio vertical começa em (5,7)

    int i;

    // ===== Validação do navio horizontal =====
    if (coluna_horizontal + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: o navio horizontal nao cabe no tabuleiro!\n");
        return 1;
    }

    // ===== Validação do navio vertical =====
    if (linha_vertical + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: o navio vertical nao cabe no tabuleiro!\n");
        return 1;
    }

    // ===== Verificação de sobreposição =====
    for (i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha_horizontal][coluna_horizontal + i] == 3 ||
            tabuleiro[linha_vertical + i][coluna_vertical] == 3) {
            printf("Erro: sobreposicao detectada!\n");
            return 1;
        }
    }

    // ===== Posiciona o navio horizontal =====
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha_horizontal][coluna_horizontal + i] = navio_horizontal[i];
    }

    // ===== Posiciona o navio vertical =====
    for (i = 0; i < TAM_NAVIO; i++) {
        tabuleiro[linha_vertical + i][coluna_vertical] = navio_vertical[i];
    }

    // ===== Exibir o tabuleiro =====
    printf("\nTabuleiro (0 = agua, 3 = navio):\n\n");
    for (int linha = 0; linha < TAM_TABULEIRO; linha++) {
        for (int coluna = 0; coluna < TAM_TABULEIRO; coluna++) {
            printf("%d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
*/
    // Nível Aventureiro - Expansão do Tabuleiro e Posicionamento Diagonal
    // Sugestão: Expanda o tabuleiro para uma matriz 10x10.
    // Sugestão: Posicione quatro navios no tabuleiro, incluindo dois na diagonal.
    // Sugestão: Exiba o tabuleiro completo no console, mostrando 0 para posições vazias e 3 para posições ocupadas.
    // Coordenadas iniciais dos navios (definidas no código)
    // Tabuleiro inicializado com 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};
    
    int linha_h = 0, coluna_h = 0; // navio horizontal
    int linha_v = 2, coluna_v = 5; // navio vertical
    int linha_d1 = 5, coluna_d1 = 0; // navio diagonal ↘
    int linha_d2 = 7, coluna_d2 = 9; // navio diagonal ↙

    // Vetores auxiliares para armazenar coordenadas dos navios
    int linhas[TAM_NAVIO], colunas[TAM_NAVIO];

    // ===== NAVIO HORIZONTAL =====
    if (coluna_h + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: navio horizontal nao cabe!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        linhas[i] = linha_h;
        colunas[i] = coluna_h + i;
    }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao no navio horizontal!\n");
        return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // ===== NAVIO VERTICAL =====
    if (linha_v + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: navio vertical nao cabe!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        linhas[i] = linha_v + i;
        colunas[i] = coluna_v;
    }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao no navio vertical!\n");
        return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // ===== NAVIO DIAGONAL ↘ =====
    if (linha_d1 + TAM_NAVIO > TAM_TABULEIRO || coluna_d1 + TAM_NAVIO > TAM_TABULEIRO) {
        printf("Erro: navio diagonal ↘ nao cabe!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        linhas[i] = linha_d1 + i;
        colunas[i] = coluna_d1 + i;
    }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao no navio diagonal ↘!\n");
        return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // ===== NAVIO DIAGONAL ↙ =====
    if (linha_d2 + TAM_NAVIO > TAM_TABULEIRO || coluna_d2 - (TAM_NAVIO - 1) < 0) {
        printf("Erro: navio diagonal ↙ nao cabe!\n");
        return 1;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        linhas[i] = linha_d2 + i;
        colunas[i] = coluna_d2 - i;
    }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao no navio diagonal ↙!\n");
        return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // ===== EXIBIR TABULEIRO =====
    printf("\nTabuleiro (0 = agua, 3 = navio):\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    // Nível Mestre - Habilidades Especiais com Matrizes
    // Sugestão: Crie matrizes para representar habilidades especiais como cone, cruz, e octaedro.
    // Sugestão: Utilize estruturas de repetição aninhadas para preencher as áreas afetadas por essas habilidades no tabuleiro.
    // Sugestão: Exiba o tabuleiro com as áreas afetadas, utilizando 0 para áreas não afetadas e 1 para áreas atingidas.

    // Exemplos de exibição das habilidades:
    // Exemplo para habilidade em cone:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 1 1 1 1 1
    
    // Exemplo para habilidade em octaedro:
    // 0 0 1 0 0
    // 0 1 1 1 0
    // 0 0 1 0 0

    // Exemplo para habilidade em cruz:
    // 0 0 1 0 0
    // 1 1 1 1 1
    // 0 0 1 0 0

    return 0;
}
