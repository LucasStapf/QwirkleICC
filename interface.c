#include <stdio.h>

#include "interface.h"
#include "erros.h"

void limparTela(){
  printf("\e[H\e[2J");
}
// ultErro ->
void printErro(Gerenciador g){

  switch(g.ultErro){

    case SUCESSO:
      break;

    case ERRO_MEMORIA: 
      printf("%s ERRO DETECTADO: %s Erro de memória.\n", BG_RED, BG_END);
      break;

    case ERRO_COORD_INVALIDA: 
      printf("%s ATENCAO: %s Essa posicao nao existe.\n", BG_RED, BG_END);
      break;

    case ERRO_COORD_OCUP:
      printf("%s ATENCAO: %s Essa posicao esta ocupada.\n", BG_RED, BG_END);
      break;

    case ERRO_LADR_IGUAL:
      printf("%s ATENCAO: %s Esse ladrilho ja foi utilizado nessa fila!\n", BG_RED, BG_END);
      break;
    
    case ERRO_FILA_INV:
      printf("%s ATENCAO: %s Fila invalida!\n", BG_RED, BG_END);
      break;

    case ERRO_CMD_INV:
      printf("%s ATENCAO: %s Comando invalido!\n", BG_RED, BG_END);
      break;
    
    default:
      printf("%s ERRO DETECTADO: %s Ocorreu um erro inesperado!\n", BG_RED, BG_END);
      break;
  }
}

void printLadrilho(Ladrilho lad){
  
  switch (lad.cor){

    case RED: 
      printf("%s %c%d \033[0m", BG_RED, lad.tipo, lad.cor);
      break;
      
    case GREEN: 
      printf("%s %c%d \033[0m", BG_GREEN, lad.tipo, lad.cor);
      break;

    case YELLOW: 
      printf("%s %c%d \033[0m", BG_YELLOW, lad.tipo, lad.cor);
      break;
    
    case BLUE: 
      printf("%s %c%d \033[0m", BG_BLUE, lad.tipo, lad.cor);
      break;

    case MAGENTA: 
      printf("%s %c%d \033[0m", BG_MAGENTA, lad.tipo, lad.cor);
      break;

    case CYAN:
      printf("%s %c%d \033[0m", BG_CYAN, lad.tipo, lad.cor);
      break;
    
    case GRAY:    
      printf("%s %c%d \033[0m", BG_GRAY, lad.tipo, lad.cor);
      break;

    default:
      printf("    ");
      break;
  }

}

/*
*   Funcao que printa o tabuleiro inteiro na tela.
*/
void printTabuleiro(Tabuleiro tab){

    //printar as coordenadas das colunas
    if(tab.cEsq <= -10) printf("     ");
    else printf("    ");
    for(int i = tab.cEsq - 1; i <= tab.cDir + 1; i++){

        if(i < 0){
            if(i <= -10) printf("  %d", i);
            else printf("   %d", i);
        } else {
            if(i <= 10) printf("    %d", i);
            else printf("   %d", i);
        }
    }

    printf("\n");

    //printar as linhas
    for(int i = tab.lSup - 1; i <= tab.lInf + 1; i++){
        
        printf("\n");

        if(i < 0){
            if(i <= -10) printf("%d   |    |", i);
            else printf(" %d   |    |", i);
        } else{
            if(i <= 9) printf("  %d   |    |", i);
            else printf(" %d   |    |", i);
        }

        if(i == tab.lSup - 1 || i == tab.lInf + 1){

            for(int j = tab.cEsq; j <= tab.cDir; j++) printf("    |");
            if(i < 0) printf("    |  %d", i);
            else printf("    |   %d", i);

        } else {

            for(int j = tab.cEsq; j <= tab.cDir; j++){
                printLadrilho(tab.matriz[convCoordJogoMatriz(i)][convCoordJogoMatriz(j)]);
                printf("|");
            } 
                //printf("%s %c%d \033[0m|", BG_RED, tab.matriz[convCoordJogoMatriz(i)][convCoordJogoMatriz(j)].type, tab.matriz[convCoordJogoMatriz(i)][convCoordJogoMatriz(j)].color);
            if(i < 0) printf("    |  %d", i);
            else printf("    |   %d", i);

        }

        printf("\n");

        if(i < tab.lInf + 1){
            printf("      ");
            int qnt = 5*((tab.cDir + 1) - (tab.cEsq - 1) + 1) + 1;
            for(int k = 0; k < qnt; k++) printf("-");
        }
    }

    printf("\n");

    //printar as coordenadas das colunas
    if(tab.cEsq <= -10) printf("     ");
    else printf("    ");
    for(int i = tab.cEsq - 1; i <= tab.cDir + 1; i++){

        if(i < 0){
            if(i <= -10) printf("  %d", i);
            else printf("   %d", i);
        } else {
            if(i <= 10) printf("    %d", i);
            else printf("   %d", i);
        }
    }

    printf("\n\n");
}

/*
*   Funcao printa todos os ladrilhos que estao na mao do jogador.
*/
void printPecasJogador(Jogador jog){

    printf("| ");
    for(int i = 0; i < jog.ladrMao; i++){
        printLadrilho(jog.ladr[i]);
        printf(" | ");
    }
}

void printJogo(Gerenciador gerenciador){

    limparTela();

    printf("\n");
    printTabuleiro(gerenciador.tab);
    printf("\n");

    printf("Comandos disponiveis: jogar <peca> <linha> <coluna> | trocar <peca> | passar\n\n");
    
    // printf("                  ");
    // for(int i = 0; i < gerenciador.listJog[gerenciador.jogDaVez].ladrMao; i++) printf("   (0%d)", i+1);
    // printf("\n");
    printf("Pecas disponiveis: ");
    printPecasJogador(gerenciador.listJog[gerenciador.jogDaVez]);
    printf("\n\n");
    
    printErro(gerenciador);
    printf("Jogador [%s] (Pontuacao Total: %d): ", gerenciador.listJog[gerenciador.jogDaVez].nome, gerenciador.listJog[gerenciador.jogDaVez].pontTotal);
}
