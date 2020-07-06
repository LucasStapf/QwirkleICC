typedef struct Gerenciador Gerenciador;

#ifndef GERENCIADOR_H
#define GERENCIADOR_H

#define NUM_MAX 18
#define QWIRKLE 12

#include "jogador.h"
#include "tabuleiro.h"

typedef struct Gerenciador {

  Tabuleiro tab;

  int estado;

  char cheat;
  int primJogada;

  int coord[2];
  char fila; // a -> ambas, l -> linha, c -> coluna, n = null

  int jogDaVez;
  int qntJog; 
  Jogador *listJog;

  int jogadasRodada;
  int ultJogadas[6][2];

  int ultErro;

} Gerenciador;

void distLadr(Gerenciador *g);
int iniciarGerenciador(Gerenciador *g);
void encerrarGerenciador(Gerenciador *g);

int verifTipo(Gerenciador *g, Ladrilho l, int x, int y);
int verifCor(Gerenciador *g, Ladrilho l, int x, int y);

int jogadaValida(Gerenciador *g, Ladrilho l, int x, int y);
int jogarLadr(Gerenciador *g, Ladrilho ladrilho, int x, int y);
int trocarLadr(Gerenciador *g, Ladrilho l);

void verifPont(Gerenciador *g);

void escolherComando(Gerenciador *g);

#endif



