#include <stdio.h>
#include <stdlib.h>

#include "tabuleiro.h"
#include "erros.h"
#include "interface.h"


int erro(int erro){

  switch(erro){

    case SUCESSO:
      return SUCESSO;

    case ERRO_MEMORIA: 
      printf("%s ERRO DETECTADO: %s Erro de memória.\n", BG_RED, BG_END);
      return erro;

    case ERRO_COORD_INVALIDA: 
      printf("%s ATENCAO: %s Essa posicao nao existe.\n", BG_RED, BG_END);
      return erro;

    case ERRO_COORD_OCUP:
      printf("%s ATENCAO: %s Essa posicao esta ocupada.\n", BG_RED, BG_END);
      return erro;

    case ERRO_LADR_IGUAL:
      printf("%s ATENCAO: %s Esse ladrilho ja foi utilizado nessa fila!\n", BG_RED, BG_END);
      return erro;
    
    case ERRO_FILA_INV:
      printf("%s ATENCAO: %s Fila invalida!\n", BG_RED, BG_END);
      return erro;

    case ERRO_CMD_INV:
      printf("%s ATENCAO: %s Comando invalido!\n", BG_RED, BG_END);
      return erro;
    
    default:
      printf("%s ERRO DETECTADO: %s Ocorreu um erro inesperado!\n", BG_RED, BG_END);
      return erro;
  }
}
