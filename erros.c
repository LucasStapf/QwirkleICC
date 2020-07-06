#include <stdio.h>
#include <stdlib.h>

#include "tabuleiro.h"
#include "erros.h"
#include "interface.h"

int ultErro = SUCESSO;

int erro(int erro){

  ultErro = erro;
  return erro;
}

int getUltErro(){
  return ultErro;
}
