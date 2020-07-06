#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<string.h>

#include "util.h"
#include "interface.h"
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
  g->estado = 1;
  g->ultErro = SUCESSO;
  
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
int verifTipoFila(Gerenciador *g, Ladrilho l, int x, int y, char fila, int *count){

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
    *count += acres;

  // tipo  na linha pra direita
    acres = 1;
    while(coluna + acres < DIM && cmpLadr(g->tab.matriz[linha][coluna + acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna + acres].tipo == l.tipo){
        if (g->tab.matriz[linha][coluna + acres].cor == l.cor) return ERRO_LADR_IGUAL;
      } else return FALSE; 
      acres++; 
    }
    *count += acres;
    
  } else {
    
    //tipo na linha pra cima
    acres = 1;
    while(linha - acres >= 0 && cmpLadr(g->tab.matriz[linha - acres][coluna],LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha - acres][coluna].tipo == l.tipo){
        if (g->tab.matriz[linha - acres][coluna].cor == l.cor) return ERRO_LADR_IGUAL;
      } else return FALSE;
      acres++;  
    }
    *count += acres;

    // tipo na linha pra baixo
    acres = 1;
    while(linha + acres < DIM && cmpLadr(g->tab.matriz[linha + acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha + acres][coluna].tipo == l.tipo){
        if (g->tab.matriz[linha + acres][coluna].cor == l.cor) return ERRO_LADR_IGUAL;
      } else return FALSE;
      acres++;
    }
    *count += acres;

  }

  return SUCESSO;
}

int verifCorFila(Gerenciador *g, Ladrilho l, int x, int y, char fila, int *count){
  
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
    *count += acres;

  // cor  na linha pra direita
    acres = 1;
    while(coluna + acres < DIM && cmpLadr(g->tab.matriz[linha][coluna+acres], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha][coluna+acres].cor == l.cor){
        if (g->tab.matriz[linha][coluna+acres].tipo == l.tipo) return ERRO_LADR_IGUAL;
      } else return FALSE;  
      acres++;  
    }
    *count += acres;    
  
  } else {

    //cor na linha pra cima
    acres = 1;
    while(linha - acres >= 0 && cmpLadr(g->tab.matriz[linha - acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha - acres][coluna].cor == l.cor){
        if (g->tab.matriz[linha - acres][coluna].tipo == l.tipo) return ERRO_LADR_IGUAL;
      } else return FALSE;
      acres++;
    }
    *count += acres;

    // cor na linha pra baixo
    while(linha + acres < DIM && cmpLadr(g->tab.matriz[linha + acres][coluna], LADR_VAZIO()) == FALSE){ // ladrilho existente
      if (g->tab.matriz[linha + acres][coluna].cor == l.cor){
        if (g->tab.matriz[linha + acres][coluna].tipo == l.tipo) return ERRO_LADR_IGUAL;
      } else return FALSE;  
      acres++;
    }
    *count += acres;
    
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

  int count = 0;
  if(verifCorFila(g, l, x, y, 'l', &count) == SUCESSO){
    if(verifCorFila(g, l, x, y, 'c', &count) != SUCESSO){
      if(verifTipoFila(g, l, x, y, 'c', &count) != SUCESSO) return ERRO;
    } else if(count == 4 && g->primJogada == FALSE) return ERRO;
  } else {
    if(verifTipoFila(g, l, x, y, 'l', &count) == SUCESSO){
      if(verifTipoFila(g, l, x, y, 'c', &count) != SUCESSO){
        if(verifCorFila(g, l, x, y, 'c', &count) != SUCESSO) return ERRO;
      } else if(count == 4 && g->primJogada == FALSE) return ERRO;
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

  if(g->fila == 'a'){

    for(int i = 0; i < 6; i++){
      g->ultJogadas[i][0] = 0;
      g->ultJogadas[i][1] = 0;
    }
      g->ultJogadas[0][0] = x;
      g->ultJogadas[0][1] = y;
      g->jogadasRodada = 1;

  } else {

    g->ultJogadas[g->jogadasRodada][0] = x;
    g->ultJogadas[g->jogadasRodada][1] = y;
    g->jogadasRodada++;
  }

  if(x <= g->tab.lSup) g->tab.lSup = x;
  if(x >= g->tab.lInf) g->tab.lInf = x;

  if(y <= g->tab.cEsq) g->tab.cEsq = y;
  if(y >= g->tab.cDir) g->tab.cDir = y;

  return SUCESSO;
}

int trocarLadr(Gerenciador *g, Ladrilho l){

  if(g->tab.ladrDisp <= 0) return erro(ERRO); //
  
  unsigned static int r;
  srand(time(NULL) + r);
  
  int i;
  for(i = 0; i < g->listJog[g->jogDaVez].ladrMao; i++){
    if(cmpLadr(g->listJog[g->jogDaVez].ladr[i], l) == TRUE) break;
  }

  if(i == g->listJog[g->jogDaVez].ladrMao) return ERRO;

  int j = rand() % g->tab.ladrDisp;
  // printf("**random: %d**\n", j);
  Ladrilho aux = l;
  g->listJog[g->jogDaVez].ladr[i] = g->tab.ladr[j];
  g->tab.ladr[j] = aux;

  ordenarListLadr(g->tab.ladr, QNT_PECAS);
  r++;

  return SUCESSO;
}

/*
*
*/
int pontuacaoFila(Gerenciador g, int x, int y, char fila){

  int pont = 0;

  int l = convCoordJogoMatriz(x);
  int c = convCoordJogoMatriz(y);

  if(fila == 'l'){
    
    int acres = 1;
    while(cmpLadr(g.tab.matriz[l][c - acres], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }

    acres = 1;
    while(cmpLadr(g.tab.matriz[l][c + acres], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }

    if(pont != 0) pont++;
    
    if(pont == 6) return QWIRKLE;
    else return pont;
    
  } else {
    
    int acres = 1;
    while(cmpLadr(g.tab.matriz[l - acres][c], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }

    acres = 1;
    while(cmpLadr(g.tab.matriz[l + acres][c], LADR_VAZIO()) == FALSE){
      pont += 1;
      acres++;
    }
    
    if(pont != 0) pont++;

    if(pont == 6) return QWIRKLE;
    else return pont;
  }
}

void verifPont(Gerenciador *g){

  if(g->fila == 'a'){ // apenas 1 jogada

    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'l');
    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'c');

  } else if(g->fila == 'l'){ //

    for(int i = 0; i < g->jogadasRodada; i++){
      printf("Pont[%d]: %d\n", i,  g->listJog[g->jogDaVez].pontTotal);
      printf("(%d, %d)\n", g->ultJogadas[i][0], g->ultJogadas[i][1]);
      g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[i][0], g->ultJogadas[i][1], 'c');
    }
    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'l');

  } else if(g->fila == 'c'){

    for(int i = 0; i < g->jogadasRodada; i++){
      g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[i][0], g->ultJogadas[i][1], 'l');
    }
    g->listJog[g->jogDaVez].pontTotal += pontuacaoFila(*g, g->ultJogadas[0][0], g->ultJogadas[0][1], 'c');
  }
}

void escolherComando(Gerenciador *g){

  g->ultErro = SUCESSO;
  
  setbuf(stdin, NULL);
  
  char cmd[100];
  fgets(cmd, 100, stdin);
  cmd[strlen(cmd) - 1] = '\0';
  printf("\nO comando eh: %s\n", cmd);
  //jogar, passar, trocar
  char *token;
  token = strtok(cmd, " ");

  if(cmpStr(token, "jogar") == TRUE || cmpStr(token, "j") == TRUE){

    printf("Jogar!\n");

    token = strtok(NULL, " ");

    if(token == NULL){
      printf("Comando invalido!\n");
      return;
    }

    if(strlen(token) != 2){
      printf("Peca invalida! Jogue novamente!\n");
      return;
    }

    if((token[0] < 'A' || token[0] > 'F') && (token[0] < 'a' || token[0] > 'f')){
      printf("Peca invalida! Jogue novamente!\n");
      return;
    } 
    
    if(token[1] < '0' || token[1] > '9'){
      printf("Peca invalida! Jogue novamente!\n");
      return;
    }

    Ladrilho l;
    l.tipo = token[0];
    l.cor = atoi(&token[1]);

    token = strtok(NULL, " ");

    if(token == NULL){
      printf("Comando invalido!\n");
      return;
    }
    
    for(int i = 0; token[i] != '\0'; i++){ 
      if(token[0] == '-' && i == 0) continue;
      if(token[i] < '0' || token[i] > '9'){
        printf("Coordenada invalida! Jogue novamente!\n");
        return;
      }
    }

    if(strlen(token) == 1 && token[0] == '-') return;
    int x = atoi(token);

    token = strtok(NULL, " ");
    if(token == NULL){
      printf("Comando invalido!\n");
      return;
    }
    
    for(int i = 0; token[i] != '\0'; i++){
      if(token[0] == '-' && i == 0) continue;
      if(token[i] < '0' || token[i] > '9'){
        printf("Coordenada invalida! Jogue novamente!\n");
        return;       
      }
    }

    if(strlen(token) == 1 && token[0] == '-') return;
    int y = atoi(token);
    
    if(jogarLadr(g, l, x, y) != SUCESSO){
      printf("Jogada invalida! Jogue novamente!\n");
      return;
    }
    
  } else if(cmpStr(token, "passar") == TRUE || cmpStr(token, "p") == TRUE){
    
    printf("Passar!\n");
    verifPont(g);

    g->fila = 'n';
    g->coord[0] = -1;
    g->coord[1] = -1;

    if(g->tab.ladrDisp > 0 && g->listJog[g->jogDaVez].ladrMao < LADR_MAO){
      
      int lm = g->listJog[g->jogDaVez].ladrMao;
      for(int i = 0; i < LADR_MAO - lm && g->tab.ladrDisp > 0; i++){
        trocarLadr(g, LADR_VAZIO());
        g->tab.ladrDisp--;
        g->listJog[g->jogDaVez].ladrMao++;
      }
    }

    g->jogDaVez++;
    if(g->jogDaVez >= g->qntJog) g->jogDaVez = 0;      
    
  } else if(cmpStr(token, "trocar") == TRUE || cmpStr(token, "t") == TRUE){
    printf("Trocar!\n");

    int qntLadr = 0;
    Ladrilho ladrCMD[6];
    token = strtok(NULL, " ");
    //t A1 A2 A3
    do {
      
      if(token == NULL){
        printf("Comando invalido!\n");
        return;
      }

      if(strlen(token) != 2){
        printf("Peca invalida! Jogue novamente!\n");
        return;
      }

      if((token[0] < 'A' || token[0] > 'F') && (token[0] < 'a' || token[0] > 'f')){
        printf("Peca invalida! Jogue novamente!\n");
        return;
      } 
    
      if(token[1] < '0' || token[1] > '9'){
        printf("Peca invalida! Jogue novamente!\n");
        return;
      }

      Ladrilho l;
      l.tipo = token[0];
      l.cor = atoi(&token[1]);

      ladrCMD[qntLadr] = l;
      qntLadr++;

      token = strtok(NULL, " ");

    } while (token != NULL && qntLadr < 6);

    Ladrilho aux[6];
    for(int i = 0; i < g->listJog[g->jogDaVez].ladrMao; i++){
      aux[i] = g->listJog[g->jogDaVez].ladr[i];
    }

    for(int i = 0; i < qntLadr; i++){
      if(trocarLadr(g, ladrCMD[i]) != SUCESSO){
        for(int j = 0; j < g->listJog[g->jogDaVez].ladrMao; j++){
          g->listJog[g->jogDaVez].ladr[j] = aux[j];
        }
        return;
      }
    }
  
  } else {

    g->ultErro = ERRO_CMD_INV;
    return;
  }
}
