#include <stdio.h>

#include "help.h"
#include "interface.h"
#include "util.h"
#include "erros.h"

int pag = 1;

void proxPag(){
  if(pag < 2) pag++;
}

void voltarPag(){
  if(pag > 1) pag--;
}

void printPrimPag(){
  
  limparTela();
  printLogo();

  printf("\nREGRAS BASICAS:\n\n");
  printf("- Existem 108 ladrilhos no tabuleiro, com um limite maximo de 6 pecas por jogador, comportando portanto ate 18 jogadores.\n\n");
  printf("- Cada jogador podera somente jogar uma determinada peca se esta estiver disponivel em sua mao (excecao: modo CHEAT).\n\n");
  printf("- Uma jogada e valida se atender os seguintes requisitos:\n");
  printf(" > A peca jogada deve estar conectada (pela linha ou coluna) com outras pecas (excecao: primeira jogada);\n");
  printf(" > Nao ha, entre a sequencia de pecas que o ladrilho jogado toca, um ladrilho igual ja jogado;\n");
  printf(" > O formato (A, B, C, D, E ou F) do ladrilho ou sua cor (1, 2, 3, 4, 5 ou 6) devem ser os mesmos das sequencias de pecas que aparecem nas filas que passam pela posicao jogada;\n");
  printf(" > Nao pode haver espacos vazios entre dois ladrilhos jogados em uma mesma rodada;\n\n");
  printf("- O jogador so podera trocar pecas se ele nao tiver realizado nenhuma jogada na rodada.\n\n");
  printf("- E possivel trocar quantos ladrilhos desejar durante uma troca, mas e possivel realizar somente uma troca por rodada.\n\n");

  printf("\n%s 1 %s 2  3  4  5  6\n\n", BG_RED, BG_END);
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");

}

void printSegunPag(){

  limparTela();
  printLogo();

  printf("\nEXEMPLOS BASICOS:\n\n");

  Ladrilho l1, l2, l3;
  l1.tipo = 'A';
  l2.tipo = 'A';
  l3.tipo = 'A';
  l1.cor = 1;
  l2.cor = 3;
  l3.cor = 6;

  printf("- Exemplo de sequencias validas de ladrilhos: ");
  printLadrilho(l1);
  printf(" ");
  printLadrilho(l2);
  printf(" ");
  printLadrilho(l3);
  printf(" ou ");

  l1.tipo = 'A';
  l2.tipo = 'C';
  l3.tipo = 'F';
  l1.cor = 4;
  l2.cor = 4;
  l3.cor = 4;
  printLadrilho(l1);
  printf(" ");
  printLadrilho(l2);
  printf(" ");
  printLadrilho(l3);
  printf("\n\n");



  printf("\n 1 %s 2 %s 3  4  5  6\n\n", BG_GREEN, BG_END);
  printf("1 - Proxima pagina\n");
  printf("2 - Voltar pagina\n");
  printf("3 - Sair\n");
}

int getCmd(){
  
  int n;
  char cmd[20];

  do {

    fgets(cmd, 20, stdin);
    setbuf(stdin, NULL);

  } while(cmd[0] != '1' && cmd[0] != '2' && cmd[0] != '3');

  if(cmd[0] == '1') n = 1;
  else if(cmd[0] == '2') n = 2;
  else n = 3;
  
  if(n == 1) proxPag();
  else if(n == 2) voltarPag();

  return n;
}

void gerenHelp(){

  int help = 1;

  while(help == 1){

    switch (pag){

      case 1:
        printPrimPag();
        if(getCmd() == 3) help = 0;
        break;

      case 2:
        printSegunPag();
        if(getCmd() == 3) help = 0;
        break;

    }

  }

}

