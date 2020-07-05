#include <stdio.h>
#include <stdlib.h>

#include "interface.h"
#include "tabuleiro.h"
#include "erros.h"
#include "gerenciador.h"
#include "util.h"
#include "jogador.h"


//x  y coordenada do jogo
//linha e coluna  coordenada da matriz

/*
listar as pecasd para os usuarios
substituir A2 pela posicao
trocar ladrilhos
calcular pontos
*/

int main(void) {

  Gerenciador g;
  if(iniciarGerenciador(&g) != SUCESSO) printf("Deu ruim!\n");
  
  Ladrilho l;
  /*
  l.cor = 1;
  l.tipo = 'F';
  
  int x1 = convCoordJogoMatriz(0);
  int y1 = convCoordJogoMatriz(0);

  g.tab.matriz[x1][y1] = l;
  */
  // g.primJogada = FALSE;
  printJogo(g);
  
  for(int i = 0; i < 4; i++){

    /*if(i == 2) {
      printf("Trocar: ");
      scanf("%d%c", &l.cor, &l.tipo);
      trocarLadr(&g, l);
      printJogo(g);
      // continue;
    }*/
    // limparTela();
    //printf("Digite o ladrilho: ");
    scanf("%d%c", &l.cor, &l.tipo);
    //printf("Digite as coords: ");
    int x, y;
    scanf("%d %d", &x,&y);
    if(jogarLadr(&g, l, x, y) != SUCESSO) i--;
    printJogo(g);
  }

  g.coord[0] = -1;
  g.coord[0] = -1;
  g.fila = 'n';
  
  for(int i = 0; i < 4; i++){

    /*if(i == 2) {
      printf("Trocar: ");
      scanf("%d%c", &l.cor, &l.tipo);
      trocarLadr(&g, l);
      printJogo(g);
      // continue;
    }*/
    // limparTela();
    //printf("Digite o ladrilho: ");
    scanf("%d%c", &l.cor, &l.tipo);
    //printf("Digite as coords: ");
    int x, y;
    scanf("%d %d", &x,&y);
    if(jogarLadr(&g, l, x, y) != SUCESSO) i--;
    printJogo(g);
  }

  encerrarGerenciador(&g);


  /*Tabuleiro tab;
  iniciarTabuleiro(&tab);

  scanf("%d", &tab.lSup); // -
  scanf("%d", &tab.lInf); // +
  scanf("%d", &tab.cEsq); // -
  scanf("%d", &tab.cDir); // +

  Ladrilho l1;
  l1.cor = 5;
  l1.tipo = 'A';

  int x1 = convCoordJogoMatriz(2);
  int y1 = convCoordJogoMatriz(2);

  tab.matriz[x1][y1] = l1;



  Ladrilho l2;
  l2.cor = 3;
  l2.tipo = 'A';

  int x2 = convCoordJogoMatriz(3);
  int y2 = convCoordJogoMatriz(3);

  tab.matriz[x2][y2] = l2;

  printTabuleiro(tab);*/

  

 
 
} 