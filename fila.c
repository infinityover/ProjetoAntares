#include "fila_vetor.h"

int main() {
  elemento fila;
  int elementos;
  inicializar(&fila);
  remover(&fila);
  adicionar(&fila, 10);
  imprimir_fila(&fila);
  remover(&fila);
  adicionar(&fila, 20);
  imprimir_fila(&fila);
  return 0;
}
