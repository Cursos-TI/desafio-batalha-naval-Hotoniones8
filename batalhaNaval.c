#include <stdio.h>
#include <stdlib.h>

// Desafio Batalha Naval - MateCheck
// Este código inicial serve como base para o desenvolvimento do sistema de Batalha Naval.
// Siga os comentários para implementar cada parte do desafio.
#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define SKILL_SIZE 5   // tamanho das matrizes de habilidade (5x5)
#define EMPTY 0
#define SHIP 3
#define AFFECT 5
/*
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
*/
// Função para inicializar tabuleiro com zeros
void initTabuleiro(int tab[TAM_TABULEIRO][TAM_TABULEIRO]) {
    for (int i = 0; i < TAM_TABULEIRO; i++)
        for (int j = 0; j < TAM_TABULEIRO; j++)
            tab[i][j] = EMPTY;
}

// Função auxiliar que verifica sobreposição para um conjunto de coordenadas
int verificaSobreposicao(int tab[TAM_TABULEIRO][TAM_TABULEIRO], int linhas[], int colunas[], int tamanho) {
    for (int k = 0; k < tamanho; k++) {
        if (tab[linhas[k]][colunas[k]] == SHIP) return 1;
    }
    return 0;
}

// Posiciona navio (marca com SHIP)
void posicionaNavio(int tab[TAM_TABULEIRO][TAM_TABULEIRO], int linhas[], int colunas[], int tamanho) {
    for (int k = 0; k < tamanho; k++) {
        tab[linhas[k]][colunas[k]] = SHIP;
    }
}

// Constrói uma matriz SKILL_SIZE x SKILL_SIZE para o Cone (apontando para baixo).
// A ideia: o "topo" do cone é a linha 0, coluna center; cada linha aumenta o raio.
// Matriz recebe 1 para afetado, 0 para não-afetado.
void buildCone(int skill[SKILL_SIZE][SKILL_SIZE]) {
    int center = SKILL_SIZE / 2; // para size=5, center=2
    for (int r = 0; r < SKILL_SIZE; r++) {
        for (int c = 0; c < SKILL_SIZE; c++) {
            // coluna afetada se a distância ao centro for <= r (linha atual)
            if (abs(c - center) <= r) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

// Constrói uma matriz para a Cruz (linha e coluna central marcadas)
void buildCross(int skill[SKILL_SIZE][SKILL_SIZE]) {
    int center = SKILL_SIZE / 2;
    for (int r = 0; r < SKILL_SIZE; r++) {
        for (int c = 0; c < SKILL_SIZE; c++) {
            if (r == center || c == center) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

// Constrói matriz que representa a vista frontal de um "octaedro" (diamante/losango).
// Usamos condição de distância de Manhattan <= center para formar o losango.
void buildOctahedron(int skill[SKILL_SIZE][SKILL_SIZE]) {
    int center = SKILL_SIZE / 2;
    for (int r = 0; r < SKILL_SIZE; r++) {
        for (int c = 0; c < SKILL_SIZE; c++) {
            if (abs(r - center) + abs(c - center) <= center) skill[r][c] = 1;
            else skill[r][c] = 0;
        }
    }
}

// Aplica a skill (matriz skill) sobre o tabuleiro centrando-a na origem (orig_r, orig_c).
// Se a posição da skill é 1 e a célula do tabuleiro estiver dentro dos limites,
// marcamos com AFFECT (5) somente se lá não houver navio (SHIP).
void applySkillToBoard(int tab[TAM_TABULEIRO][TAM_TABULEIRO],
                       int skill[SKILL_SIZE][SKILL_SIZE],
                       int orig_r, int orig_c) {
    int center = SKILL_SIZE / 2;
    for (int r = 0; r < SKILL_SIZE; r++) {
        for (int c = 0; c < SKILL_SIZE; c++) {
            if (skill[r][c] != 1) continue; // posição não afetada
            int board_r = orig_r - center + r;
            int board_c = orig_c - center + c;
            // valida limites simplificada
            if (board_r < 0 || board_r >= TAM_TABULEIRO || board_c < 0 || board_c >= TAM_TABULEIRO)
                continue;
            // Se há navio, mantemos o navio (prioridade ao SHIP). Caso contrário, marcamos AFFECT.
            if (tab[board_r][board_c] == SHIP) {
                // mantém SHIP
            } else {
                tab[board_r][board_c] = AFFECT;
            }
        }
    }
}

// Função para imprimir o tabuleiro com legenda
void printBoard(int tab[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("\nLegenda: 0=agua  3=navio  5=area_efeito\n\n");
    // cabeçalho de colunas (opcional)
    printf("   ");
    for (int c = 0; c < TAM_TABULEIRO; c++) printf("%d ", c);
    printf("\n");
    for (int r = 0; r < TAM_TABULEIRO; r++) {
        printf("%2d ", r); // índice da linha
        for (int c = 0; c < TAM_TABULEIRO; c++) {
            // imprimimos com um espaço para alinhamento
            printf("%d ", tab[r][c]);
        }
        printf("\n");
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
/*
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
*/
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

       int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO];
    initTabuleiro(tabuleiro);

    // -------------------------
    // Posicionamento dos 4 navios (tam=3) - coordenadas já escolhidas para não sobrepor
    // -------------------------
    // 1) Horizontal -> começa (0,0) : ocupa (0,0) (0,1) (0,2)
    int linhas[TAM_NAVIO], colunas[TAM_NAVIO];

    int lh = 0, ch = 0;
    for (int i = 0; i < TAM_NAVIO; i++) { linhas[i] = lh; colunas[i] = ch + i; }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao ao colocar navio horizontal\n"); return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // 2) Vertical -> começa (2,5) : ocupa (2,5) (3,5) (4,5)
    int lv = 2, cv = 5;
    for (int i = 0; i < TAM_NAVIO; i++) { linhas[i] = lv + i; colunas[i] = cv; }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao ao colocar navio vertical\n"); return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // 3) Diagonal ↘ -> começa (5,0) : ocupa (5,0) (6,1) (7,2)
    int ld1 = 5, cd1 = 0;
    for (int i = 0; i < TAM_NAVIO; i++) { linhas[i] = ld1 + i; colunas[i] = cd1 + i; }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao ao colocar navio diagonal ↘\n"); return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // 4) Diagonal ↙ -> começa (7,9) : ocupa (7,9) (8,8) (9,7)
    int ld2 = 7, cd2 = 9;
    for (int i = 0; i < TAM_NAVIO; i++) { linhas[i] = ld2 + i; colunas[i] = cd2 - i; }
    if (verificaSobreposicao(tabuleiro, linhas, colunas, TAM_NAVIO)) {
        printf("Erro: sobreposicao ao colocar navio diagonal ↙\n"); return 1;
    }
    posicionaNavio(tabuleiro, linhas, colunas, TAM_NAVIO);

    // -------------------------
    // Construir as matrizes de habilidade (5x5) dinamicamente usando loops + condicionais
    // -------------------------
    int cone[SKILL_SIZE][SKILL_SIZE];
    int cross[SKILL_SIZE][SKILL_SIZE];
    int octa[SKILL_SIZE][SKILL_SIZE];

    buildCone(cone);
    buildCross(cross);
    buildOctahedron(octa);

    // -------------------------
    // Pontos de origem (centro) para cada habilidade - definidos no código
    // (linha, coluna) -> ajustáveis para testar
    // -------------------------
    int origin_cone_r = 1, origin_cone_c = 2;   // cone perto do topo
    int origin_cross_r = 4, origin_cross_c = 4; // cruz no meio
    int origin_octa_r = 8, origin_octa_c = 2;   // octaedro mais abaixo à esquerda

    // -------------------------
    // Aplicar as skills no tabuleiro (sem sobrescrever navios)
    // -------------------------
    applySkillToBoard(tabuleiro, cone, origin_cone_r, origin_cone_c);
    applySkillToBoard(tabuleiro, cross, origin_cross_r, origin_cross_c);
    applySkillToBoard(tabuleiro, octa, origin_octa_r, origin_octa_c);

    // -------------------------
    // Exibir resultado final
    // -------------------------
    printBoard(tabuleiro);
 

    return 0;
}
