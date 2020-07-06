#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interface.h"
#include "tabuleiro.h"
#include "erros.h"
#include "gerenciador.h"
#include "util.h"
#include "jogador.h"

//TERMINAR O jogo
//LOOP PRA JOGAR DNNV



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

  if(iniciarGerenciador(&g) != SUCESSO){
    printf("Deu ruim!\n");
    exit(0);
  }

  while(g.estado == 1){
    printJogo(g);
    // printPecasJogador(g.listJog[g.jogDaVez]);
    escolherComando(&g);
  }

  encerrarGerenciador(&g);
  

  /*
  Gerenciador g;
  if(iniciarGerenciador(&g) != SUCESSO){
    printf("Deu ruim!\n");
    exit(0);
  }
  
  Ladrilho l;
  printJogo(g);
  
  for(int i = 0; i < 2; i++){

    scanf("%d%c", &l.cor, &l.tipo);
    int x, y;
    scanf("%d %d", &x,&y);
    if(jogarLadr(&g, l, x, y) != SUCESSO) i--;
    printJogo(g);
  }

  verifPont(&g);
  printJogo(g);


  g.coord[0] = -1;
  g.coord[0] = -1;
  g.fila = 'n';
  
  
  for(int i = 0; i < 3; i++){

    scanf("%d%c", &l.cor, &l.tipo);

    int x, y;
    scanf("%d %d", &x,&y);
    if(jogarLadr(&g, l, x, y) != SUCESSO) i--;
    printJogo(g);

  }

  verifPont(&g);
  
  printJogo(g);
  encerrarGerenciador(&g);
  */

} 