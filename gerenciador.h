typedef struct Gerenciador Gerenciador;

#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#define NUM_MAX 18
#define Qwirkle 12

#include "jogador.h"
#include "tabuleiro.h"

typedef struct Gerenciador {

  Tabuleiro tab;

  char cheat;
  int primJogada;

  int coord[2];
  char fila; // a -> ambas, l -> linha, c -> coluna, n = null

  int jogDaVez;
  int qntJog; 
  Jogador *listJog;

} Gerenciador;

void distLadr(Gerenciador *g);
int iniciarGerenciador(Gerenciador *g);
void encerrarGerenciador(Gerenciador *g);

int verifTipo(Gerenciador *g, Ladrilho l, int x, int y);
int verifCor(Gerenciador *g, Ladrilho l, int x, int y);

int jogadaValida(Gerenciador *g, Ladrilho l, int x, int y);
int jogarLadr(Gerenciador *g, Ladrilho ladrilho, int x, int y);
int trocarLadr(Gerenciador *g, Ladrilho l);

#endif



