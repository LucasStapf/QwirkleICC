#include <stdio.h>
#include <stdlib.h>

#include "tabuleiro.h"
#include "erros.h"


int erro(int erro){

  switch(erro){

    case ERRO_MEMORIA: 
      printf("Erro de memória.\n");
      return erro;

    case ERRO_COORD_INVALIDA: 
      printf("Essa posicao nao existe.\n");
      return erro;

    case ERRO_COORD_OCUP:
      printf("Essa posicao esta ocupada.\n");
      return erro;

    case ERRO_LADR_IGUAL:
      printf("Esse ladrilho ja foi utilizado nessa fila!\n");
      return erro;
    
    case ERRO_FILA_INV:
      printf("Fila invalida!\n");
      return erro;
      
    default:
      printf("Ocorreu um erro inesperado!\n");
      return erro;
  }
}
