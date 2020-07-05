#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

#include "util.h"
#include "erros.h"
#include "gerenciador.h"
#include "jogador.h"

/*
*
*/
void distLadr(Gerenciador *g){
  
  int cont = 0;
  for(int i = 0; i < g->qntJog; i++){
    for(int j = 0; j < LADR_MAO; j++, cont++){
      g->listJog[i].ladr[j] = g->tab.ladr[cont];
      g->listJog[i].ladrMao++;
      g->tab.ladr[cont] = LADR_VAZIO();
      g->tab.ladrDisp--;
    }
  }

  ordenarListLadr(g->tab.ladr, QNT_PECAS);
}

/*
*
*/
int iniciarGerenciador(Gerenciador *g){
  
  printf("Escolha o numero de jogadores: ");
  int n;
  while (lerIntSTDIN(&n) == ERRO || n <= 0 || n > NUM_MAX){
    printf("Numero de jogadores invalido. Escolha novamente.\n");
    setbuf(stdin, NULL);  
  }

  g->listJog = (Jogador*) malloc(n*sizeof(Jogador)); 
  if(g->listJog == NULL) return ERRO_MEMORIA;

  g->qntJog = n;
  g->jogDaVez = 0;
  g->coord[0] = -1;
  g->coord[1] = -1;
  g->fila = 'n';
  g->primJogada = TRUE;
  
  for (int i = 0; i < n; i++){
    
    printf("Digite o nome do Jogador [%d]: ", i+1);
    fgets(g->listJog[i].nome, 16, stdin);
    g->listJog[i].nome[strlen(g->listJog[i].nome) - 1] = '\0';
    g->listJog[i].pontTotal = 0;
    g->listJog[i].pontJogada = 0;
    g->listJog[i].ladrMao = 0;
  }

  printf("Modo CHEAT(S/N): ");
  g->cheat = fgetc(stdin);
  
  if(iniciarTabuleiro(&g->tab) != SUCESSO){

    free(g->listJog);
    return ERRO;
  }

  distLadr(g);

  return SUCESSO;
}

/*
*
*/
void encerrarGerenciador(Gerenciador *g){

  liberarTabuleiro(&g->tab);
  free(g->listJog);
}

/*
*
*/
int verifTipoFila(Gerenciador *g, Ladrilho l, int x, int y, char fila){

  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);
  
  int acres = 1;
  
  if(fila == 'l'){

    //tipo na linha comecando na esquerda
    while(coluna - acres >= 0 && cmpLadr(g->tab.matriz[linha][coluna-acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna-acres].tipo == l.tipo){
        if (g->tab.matriz[linha][coluna-acres].cor == l.cor) return ERRO_LADR_IGUAL;
      } else return FALSE; 
      acres++;
    }

  // tipo  na linha pra direita
    acres = 1;
    while(coluna + acres < DIM && cmpLadr(g->tab.matriz[linha][coluna + acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna + acres].tipo == l.tipo){
        if (g->tab.matriz[linha][coluna + acres].cor == l.cor) return ERRO_LADR_IGUAL;
      } else return FALSE; 
      acres++; 
    }

    
  } else {
    
    //tipo na linha pra cima
    acres = 1;
    while(linha - acres >= 0 && cmpLadr(g->tab.matriz[linha - acres][coluna],LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha - acres][coluna].tipo == l.tipo){
        if (g->tab.matriz[linha - acres][coluna].cor == l.cor) return ERRO_LADR_IGUAL;
      } else return FALSE;
      acres++;  
    }

    // tipo na linha pra baixo
    acres = 1;
    while(linha + acres < DIM && cmpLadr(g->tab.matriz[linha + acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha + acres][coluna].tipo == l.tipo){
        if (g->tab.matriz[linha + acres][coluna].cor == l.cor) return ERRO_LADR_IGUAL;
      } else return FALSE;
      acres++;
    }

  }

  return SUCESSO;
}

int verifCorFila(Gerenciador *g, Ladrilho l, int x, int y, char fila){
  
  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);
  
  int acres = 1;
  
  if(fila == 'l'){  

    //cor na linha comecando na esquerda
    while(coluna - acres >= 0 && cmpLadr(g->tab.matriz[linha][coluna-acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna-acres].cor == l.cor){
        if (g->tab.matriz[linha][coluna-acres].tipo == l.tipo) return ERRO_LADR_IGUAL;
      } else return FALSE;
        
      acres++;
        
    }


  // cor  na linha pra direita
    acres = 1;
    while(coluna + acres < DIM && cmpLadr(g->tab.matriz[linha][coluna+acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna+acres].cor == l.cor){
        if (g->tab.matriz[linha][coluna+acres].tipo == l.tipo) return ERRO_LADR_IGUAL;
      } else return FALSE;  
      acres++;
        
    }
    
  
  } else {

    //cor na linha pra cima
    acres = 1;
    while(linha - acres >= 0 && cmpLadr(g->tab.matriz[linha - acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha - acres][coluna].cor == l.cor){
        if (g->tab.matriz[linha - acres][coluna].tipo == l.tipo) return ERRO_LADR_IGUAL;
      } else return FALSE;
      acres++;
    }

    // cor na linha pra baixo
    while(linha + acres < DIM && cmpLadr(g->tab.matriz[linha + acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha + acres][coluna].cor == l.cor){
        if (g->tab.matriz[linha + acres][coluna].tipo == l.tipo) return ERRO_LADR_IGUAL;
      } else return FALSE;  
      acres++;
    }
    
  }

  return SUCESSO;
}

/*
*
*/
int jogadaValida(Gerenciador *g, Ladrilho l, int x, int y){

  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);

  if(linha < 0 || linha >= DIM || coluna < 0 || coluna >= DIM) return erro(ERRO_COORD_INVALIDA);
  if(cmpLadr(g->tab.matriz[linha][coluna], LADR_VAZIO()) == FALSE) return erro(ERRO_COORD_OCUP);

  int i = 0;
  if(g->cheat != 'S' && g->cheat != 's'){
    for (i = 0; i < g->listJog[g->jogDaVez].ladrMao; i++){
      if(cmpLadr(l, g->listJog[g->jogDaVez].ladr[i]) == TRUE) break;
    }
  }

  if(i >= g->listJog[g->jogDaVez].ladrMao) return erro(ERRO);

  if(verifCorFila(g, l, x, y, 'l') == SUCESSO){
    if(verifCorFila(g, l, x, y, 'c') != SUCESSO){
      if(verifTipoFila(g, l, x, y, 'c') != SUCESSO) return ERRO;
    }
  } else {
    if(verifTipoFila(g, l, x, y, 'l') == SUCESSO){
      if(verifTipoFila(g, l, x, y, 'c') != SUCESSO){
        if(verifCorFila(g, l, x, y, 'c') != SUCESSO) return ERRO;
      }
    } else return ERRO;
  } 

  if(g->fila == 'n'){

    if(g->primJogada == FALSE){
      g->coord[0] = linha;
      g->coord[1] = coluna;
    } else {
      g->coord[0] = convCoordJogoMatriz(0);
      g->coord[1] = convCoordJogoMatriz(0);
    }
      g->fila = 'a';  
      
  } else if(g->fila == 'a'){

    if(g->coord[0] == linha) g->fila = 'l';
    else if(g->coord[1] == coluna) g->fila = 'c';
    else return erro(ERRO_FILA_INV);

  } else if(g->fila == 'l'){
    if(g->coord[0] != linha) return erro(ERRO_FILA_INV);

  } else if(g->fila == 'c'){
    if(g->coord[1] != coluna) return erro(ERRO_FILA_INV);
  }

  if(linha == g->coord[0] && coluna != g->coord[1]){
    
    int sent;
    if(coluna > g->coord[1]) sent = 1; //verficar a direita
    else sent = -1; //verificar a esquerda
    
    int c = g->coord[1] + sent;
    while(c != coluna){
      if(cmpLadr(g->tab.matriz[linha][c], LADR_VAZIO()) == TRUE) return ERRO;
      c += sent;
    }
  } else if(coluna == g->coord[1] && linha != g->coord[0]){

    int sent;
    if(linha > g->coord[0]) sent = 1; // verificar para baixo
    else sent = -1; // veficar para cima

    int l = g->coord[0] + sent;
    while(l != linha){
      if(cmpLadr(g->tab.matriz[l][coluna], LADR_VAZIO()) == TRUE) return ERRO;
      l += sent;
    }


  }

  if(g->cheat != 'S' && g->cheat != 's'){
    g->listJog[g->jogDaVez].ladr[i] = LADR_VAZIO();
    ordenarListLadr(g->listJog[g->jogDaVez].ladr, LADR_MAO);
    g->listJog[g->jogDaVez].ladrMao--;
  }

  return SUCESSO;
}

/*
*
*/
int jogarLadr(Gerenciador *g, Ladrilho ladrilho, int x, int y){
  
  int linha = convCoordJogoMatriz(x);
  int coluna = convCoordJogoMatriz(y);

  if(jogadaValida(g, ladrilho, x, y) != SUCESSO) return ERRO;
  
  if(g->primJogada == TRUE){
    linha = convCoordJogoMatriz(0);
    coluna = convCoordJogoMatriz(0);
    x = 0;
    y = 0;
  }

  g->primJogada = FALSE;
  g->tab.matriz[linha][coluna] = ladrilho;

  if(x <= g->tab.lSup) g->tab.lSup = x;
  if(x >= g->tab.lInf) g->tab.lInf = x;

  if(y <= g->tab.cEsq) g->tab.cEsq = y;
  if(y >= g->tab.cDir) g->tab.cDir = y;

  return SUCESSO;
}

int trocarLadr(Gerenciador *g, Ladrilho l){

  if(g->tab.ladrDisp <= 0) return erro(ERRO); //
  
  srand(time(NULL));
  
  int i;
  for(i = 0; i < g->listJog[g->jogDaVez].ladrMao; i++){
    if(cmpLadr(g->listJog[g->jogDaVez].ladr[i], l) == TRUE) break;
  }

  int j = rand() % g->tab.ladrDisp;
  Ladrilho aux = l;
  g->listJog[g->jogDaVez].ladr[i] = g->tab.ladr[j];
  g->tab.ladr[j] = aux;

  return SUCESSO;
}

int verifPont(Gerenciador *g){
  
  g->listJog[g->jogDaVez].pontJogada ;

  if(g->fila == 'a') g->listJog[g->jogDaVez].pontJogada +=1;

  if(g->fila == 'l'){
    
    while(cmpLadr(g->tab.ladr[i], LADR_VAZIO()) ){
      
    }

  }

  if(g->fila == 'c'){


  }
    
  
  // l -> verificar colunas dps linha
  // c -> verificar linhas dps coluna

  /*
  
  */

  
  g->listJog[g->jogDaVez].pontTotal += g->listJog[g->jogDaVez].pontJogada;

  return SUCESSO;
}




