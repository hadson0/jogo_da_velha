#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>

/* Define o tamanho do tabuleiro */
#define L 20 /* Linhas */
#define C 41 /* Colunas */

void imprimirTabuleiro(int** tabuleiro); /* Imprime o tabuleiro com as marcações X e O */
void posicionarCursor(int x, int y) ; /* Posiciona o cursor do console dada as coordenadas x e y */
int jogarPC(int** tabuleiro); /* Seleciona uma jogada para o computador */
int verificarVencedor(int** tabuleiro); /* Verifica o resultado da partida, se houve vencedor ou se houve empate */

/*
    Casa vazia = -1
    Casa com cursor = 0
    Casa com X = 1
    Casa com O = 2
*/

int main(void){
    /* Declaração das variáveis */
    int** tabuleiro = (int**) malloc(3 * sizeof(int*));
    int game = -1, score = 0, highScore = 0, vencedor = 0, i = 0, j = 0, vez = 0, x = 0, o = 0;
    unsigned char tecla;
    FILE* pRanking;

    /* Inicia o tabuleiro */
    for (i = 0; i < 3; i++) { 
        tabuleiro[i] = (int*) malloc(3 * sizeof(int)); 
        for (j = 0; j < 3; j++) tabuleiro [i][j] = 0;
    }

    /* Abre o arquivo de highScore e acessa o valor */
    pRanking = fopen("HighScore.txt", "r");
    if (pRanking == NULL) {
        printf("Erro na criação do arquivo!");
        system("pause");
        return 1;
    }
    fscanf(pRanking,"%d",&highScore);
    fclose(pRanking);

    /*
    Casa vazia = 0
    Casa com cursor = -1
    Casa com X = 1
    Casa com O = 2
    */

    /* Seta o cursor na primeira posição */
    i = 0; j = 0;
    tabuleiro [i][j] = -1;

    /* Imprime o tabuleiro e reseta a tela */
    

    /* Pede para o jogador informar o modo de jogo */
    printf("Deseja jogar contra o computador [0] ou contra um jogador [1]?\n");
    imprimirTabuleiro(tabuleiro);
    posicionarCursor(0, 0);
    
    while ( game == -1) {
        tecla = getch();
        if (tecla == 48) game = 0;
        else if (tecla == 49) game = 1;
    }
    
    system("clear || cls");
    printf("|****| Score Atual: %d", score);
    printf(" | HighScore: %d|****|\n", highScore);
    imprimirTabuleiro(tabuleiro);
    posicionarCursor(0, 0);

    do {
        while (game == 0) {

            /* Se a vez for par, é a vez do X */
            if (vez % 2 == 0) {
                tecla = getch();

                if (tabuleiro[i][j] == -1) tabuleiro [i][j] = 0; /* Limpa a posição anteiror do cursor */

                /* Caso apertar Enter preenche a casa com X, caso apertar alguma tecla move o cusror*/
                if (tecla == 13) {
                if(tabuleiro[i][j] == 0 || tabuleiro[i][j] == -1) tabuleiro [i][j] = 1;
                vez++;
                } else if (tecla == 77) j++;
                else if (tecla == 75) j--;
                else if (tecla == 72) i--;
                else if (tecla == 80) i++;

                /* Caso passar do limite das linhas ou colunas, começa da primeira */
                if (i > 2)  i = 0;
                else if(i < 0)  i = 2;
                else if(j > 2)  j = 0;
                else if(j < 0) j = 2;

                if (tabuleiro[i][j] == 0) tabuleiro [i][j] = -1; /* Preenche a posição do cursor */            
            } else { /* Se a vez for impar, é a vez do O */
                if (!jogarPC(tabuleiro)) {
                    printf("Erro ao computador jogar!\n");
                    posicionarCursor(0, 0);
                    system("pause");
                    return 1;
                }
                vez++;
            }
            
            posicionarCursor(0, 0);
            printf("|****| Score Atual: %d", score);
            printf(" | HighScore: %d|****|\n", highScore);
            imprimirTabuleiro(tabuleiro);

            /* Verifica quem foi o vencedor */
            vencedor = verificarVencedor(tabuleiro);

            /* Caso houver um vencedor, finaliza o jogo */
            if (vencedor != 0) {
                switch(vencedor) {
                    case 1:
                        printf("\nPARABENS! VOCE VENCEU! Aperte Esc para fechar o jogo ou TAB para trocar de modo.");
                        score++;
                        pRanking = fopen("HighScore.txt", "r");
                        if (pRanking == NULL) {
                                printf("Erro na criação do arquivo!");
                                system("pause");
                                return 1;
                        }
                        if (score > highScore) {
                            highScore++;
                            rewind(pRanking);
                            fprintf(pRanking, "%d\n", score);
                            fclose(pRanking);
                        }
                        break;
                    case 2:
                        printf("\nO COMPUTADOR VENCEU! TENTE NOVAMENTE! Aperte Esc para fechar o jogo ou TAB para trocar de modo.");
                        break;
                    default:
                        printf("\nDEU VELHA! TENTE NOVAMENTE! Aperte Esc para fechar o jogo ou TAB para trocar de modo.");
                        break;
                }
                tecla = getch();
                if (tecla == 27) game = -1;
                else { /* Caso querer jogar novamente, limpa o tabuleiro e reseta a tela */
                    for(i = 0; i < 3; i++) for(j = 0; j < 3; j++) tabuleiro [i][j] = 0;
                    i = 0;
                    j = 0;
                    vez = 0;
                    tabuleiro [i][j] = 0;
                    system("clear || cls");
                    posicionarCursor(0, 0);
                    printf("|****| X: %d vs ", x);
                    printf(" O: %d|****|\n", o);
                    imprimirTabuleiro(tabuleiro);
                    if (tecla == 9) game = 1; /* Caso o jogador optou por mudar de modo */                    
                }     
            }
        }

        while (game == 1) {
            /* Se a vez for par, é a vez do X */
            if (vez % 2 == 0) {
                tecla = getch();

                if (tabuleiro[i][j] == -1) tabuleiro [i][j] = 0; /* Limpa a posição anteiror do cursor */

                /* Caso apertar Enter preenche a casa com X, caso apertar alguma tecla move o cusror*/
                if (tecla == 13) {
                    if (tabuleiro[i][j] == 0 || tabuleiro[i][j] == -1) tabuleiro [i][j] = 1;
                    vez++;
                } else if (tecla == 77) j++;
                else if (tecla == 75) j--;
                else if (tecla == 72) i--;
                else if (tecla == 80) i++;

                /* Caso passar do limite das linhas ou colunas, começa da primeira */
                if(i > 2)  i = 0;
                else if(i < 0)  i = 2;
                else if(j > 2)  j = 0;
                else if(j < 0) j = 2;

                if (tabuleiro[i][j] == 0) tabuleiro [i][j] = -1; /* Preenche a posição do cursor */            
            } else { 
                /* Se a vez for impar, é a vez do O */
                tecla = getch();

                if (tabuleiro[i][j] == -1) tabuleiro [i][j] = 0; /* Limpa a posição anteiror do cursor */

                /* Caso apertar Enter preenche a casa com X, caso apertar alguma tecla move o cusror*/
                if (tecla == 13) {
                    if (tabuleiro[i][j] == 0 || tabuleiro[i][j] == -1) tabuleiro [i][j] = 2;
                    vez++;
                } else if (tecla == 77) j++;
                else if (tecla == 75) j--;
                else if (tecla == 72) i--;
                else if (tecla == 80) i++;

                /* Caso passar do limite das linhas ou colunas, começa da primeira */
                if(i > 2)  i = 0;
                else if(i < 0)  i = 2;
                else if(j > 2)  j = 0;
                else if(j < 0) j = 2;

                if (tabuleiro[i][j] == 0) tabuleiro [i][j] = -1; /* Preenche a posição do cursor */
            }

            posicionarCursor(0, 0);
            printf("|****| X: %d vs ", x);
            printf(" O: %d|****|\n", o);
            imprimirTabuleiro(tabuleiro);

            /* Verifica quem foi o vencedor */
            vencedor = verificarVencedor(tabuleiro);

            /* Caso houver um vencedor, finaliza o jogo */
            if (vencedor != 0) {
                switch (vencedor) {
                    case 1:
                        printf("\nO JOGADOR *X* VENCEU! Aperte Esc para fechar o jogo ou TAB para trocar de modo.");
                        x++;
                        break;
                    case 2:
                        printf("\nO JOGADOR *O* VENCEU Aperte Esc para fechar o jogo ou TAB para trocar de modo.");
                        o++;
                        break;
                    default:
                        printf("\nDEU VELHA! TENTEM NOVAMENTE! Aperte Esc para fechar o jogo ou TAB para trocar de modo.");
                        break;
                }
                tecla = getch();
                if (tecla == 27) game = -1;
                else { 
                    /* Caso querer jogar novamente, limpa o tabuleiro e reseta a tela */
                    for (i = 0; i < 3; i++) 
                        for (j = 0; j < 3; j++) tabuleiro [i][j] = 0;
                    i = 0;
                    j = 0;
                    vez = 0;
                    tabuleiro [i][j] = 0;
                    system("clear || cls");
                    posicionarCursor(0, 0);
                    printf("|****| Score Atual: %d", score);
                    printf(" | HighScore: %d|****|\n", highScore);
                    imprimirTabuleiro(tabuleiro);                    
                    if (tecla == 9) game = 0; /* Caso o jogador optou por mudar de modo */                    
                }
            }
        }
    } while (game != -1);

    /* Libera a memória */
    free(tabuleiro);
    for (i = 0; i < 3; i++) free(tabuleiro [i]);

    return 0;
}

void imprimirTabuleiro(int** tabuleiro) {
    /* Variáveis de controle */
    int i, j;
    int a = 0;
    int b = 0;

    /* Imprime o tabuleiro*/
    printf("%c", 201);
    for (i = 0; i <= C; i++) {
        if(i == C) printf("%c", 187);
        else printf("%c", 205);
    }

    printf("\n");

    for (i = 0; i < L; i++) {
        if(i == 2) a = 0;
        else if(i == 9) a = 1;
        else if(i == 16) a = 2;

        printf("%c",186);

        if(i == 6 || i == 13) {
            for(j = 0; j < C; j++) printf("%c",205);
            printf("%c\n", 186);
        } else {
            for (j = 0; j < C; j++) {
                if(j == 6) b = 0;
                else if(j == 20) b = 1;
                else if(j == 34) b = 2;

                if (j == 13 || j == 27) printf("%c",186);
                else if(j == C - 1) printf("%c\n", 186);
                    else {
                        if (j == C - 2 ) printf("  ");
                        else { /* Imprime o conteúdo das casas, caso houver algum */ 
                            if (tabuleiro [a][b] == -1 && (i == 2 || i == 9 || i == 16) && (j == 6 || j == 20 || j == 34)) printf("_"); 
                            else if(tabuleiro[a][b] == 1 && (i == 2 || i == 9 || i == 16) && (j == 6 || j == 20 || j == 34)) printf("X");
                            else if(tabuleiro[a][b] == 2 && (i == 2 || i == 9 || i == 16) && (j == 6 || j == 20 || j == 34)) printf("O");
                            else printf(" "); /* Caso não tiver nada, deixa em branco */
                        }                         
                    } 
            }
        }
    }

    printf("%c", 200);

    for (i = 0; i <= C; i++) { 
        if (i == C) printf("%c", 188);
        else printf("%c", 205);
    }
}

void posicionarCursor(int x, int y) {
    /* Seta o cursor do console para a primeira posição */
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = x;
    Position.Y = y;

    SetConsoleCursorPosition(hOut, Position);
}

int jogarPC(int** tabuleiro) {
    /* Variáveis de controle */
    int i, j, k = 0, s = 0, temp[2] = {0, 0};
    
    for (i = 0; i < 3; i++) {
        /* Verificar nas linhas se há derrota ou vitória eminentes, sem prioridades para ficar mais fácil para o jogador */
        for (j = 0; j < 3; j++) { 
            if (tabuleiro[i][j] != 0 ) {
                s += j;
                k++;
                temp[k - 1] = tabuleiro[i][j];
            }
        }
        if (k == 2 && temp[0] == temp[1] && temp[0] != 0 && tabuleiro[i][3 - s] == 0) {
            tabuleiro[i][3 - s] = 2;
            return 1;
        } 
        temp[0] = 0;
        temp[1] = 0;
        k = 0;
        s = 0;

        /* Verificar nas colunas se há derrota ou vitória eminentes, sem prioridades para ficar mais fácil para o jogador */
        for (j = 0; j < 3; j++) { 
            if(tabuleiro[j][i] != 0){
                s += j;  
                k++;
                temp[k - 1] = tabuleiro[j][i];
            }
        }
        if (k == 2 && temp[0] == temp[1] && temp[0] != 0 && tabuleiro[3 - s][i] == 0){
            tabuleiro[3 - s][i] = 2;
            return 1;
        } 
        k = 0;
        s = 0;
        temp[0] = 0;
        temp[1] = 0;
    }

    if (tabuleiro[0][0] == 1 && tabuleiro[2][2] == 0) { 
        tabuleiro[2][2] = 2;
        return 1;
    } else if(tabuleiro[2][2] == 1 && tabuleiro[0][0] == 0) {
        tabuleiro[0][0] = 2;
        return 1;
    } else if(tabuleiro[0][2] == 1 && tabuleiro[2][0] == 0) { 
        tabuleiro[2][0] = 2;
        return 1;
    } else if(tabuleiro[2][0] == 1 && tabuleiro[0][2] == 0) { 
        tabuleiro[0][2] = 2;
        return 1;
    } else if(tabuleiro[1][1] == 0) {
        tabuleiro[1][1] = 2;
        return 1;
    } else {
        for (i = 0; i < 3; i++) {
            for (j = 0; j < 3; j++ ){
                if (tabuleiro[i][j] == 0) {
                    tabuleiro[i][j] = 2;
                    return 1;
                }

            }
        }
    }
    return 0;
}

int verificarVencedor(int** tabuleiro){
    /* Variáveis de controle */
    int i, j, k = 0;

    /* Caso o X ganhar, retorna 1 */
    if ((tabuleiro[0][0] == 1 && tabuleiro[1][1] == 1 && tabuleiro[2][2] == 1) || 
        (tabuleiro[0][2] == 1 && tabuleiro[1][1] == 1 && tabuleiro[2][0] == 1) ||
        (tabuleiro[0][0] == 1 && tabuleiro[0][1] == 1 && tabuleiro[0][2] == 1) ||
        (tabuleiro[1][0] == 1 && tabuleiro[1][1] == 1 && tabuleiro[1][2] == 1) ||
        (tabuleiro[2][0] == 1 && tabuleiro[2][1] == 1 && tabuleiro[2][2] == 1) ||
        (tabuleiro[0][0] == 1 && tabuleiro[1][0] == 1 && tabuleiro[2][0] == 1) ||
        (tabuleiro[0][1] == 1 && tabuleiro[1][1] == 1 && tabuleiro[2][1] == 1) ||
        (tabuleiro[0][2] == 1 && tabuleiro[1][2] == 1 && tabuleiro[2][2] == 1))
            return 1;

    /* Caso o O ganhar, retorna 2 */
    else if ((tabuleiro[0][0] == 2 && tabuleiro[1][1] == 2 && tabuleiro[2][2] == 2) || 
            (tabuleiro[0][2] == 2 && tabuleiro[1][1] == 2 && tabuleiro[2][0] == 2) ||
            (tabuleiro[0][0] == 2 && tabuleiro[0][1] == 2 && tabuleiro[0][2] == 2) ||
            (tabuleiro[1][0] == 2 && tabuleiro[1][1] == 2 && tabuleiro[1][2] == 2) ||
            (tabuleiro[2][0] == 2 && tabuleiro[2][1] == 2 && tabuleiro[2][2] == 2) ||
            (tabuleiro[0][0] == 2 && tabuleiro[1][0] == 2 && tabuleiro[2][0] == 2) ||
            (tabuleiro[0][1] == 2 && tabuleiro[1][1] == 2 && tabuleiro[2][1] == 2) ||
            (tabuleiro[0][2] == 2 && tabuleiro[1][2] == 2 && tabuleiro[2][2] == 2))
            return 2;

    /* Caso nenhum ganhar, verifica empate */
    else {
        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
                if (tabuleiro[i][j] < 1) k++;

        if (k == 0) return 3; /* Se empatar, retorna 3 */
        else return 0; /* Se não houve ganhador ou empate, retorna 0 */
    }
}
