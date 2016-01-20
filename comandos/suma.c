#include <stdio.h>
#include <stdlib.h>
#include "comandos.h"
#include "util.h"

void comando_suma(TLista *lista) {
  TNodo *nodo;
  int suma = 0;

  for (nodo = lista->primero; nodo; nodo = nodo->siguiente) {
    if (es_numero(nodo->palabra)) {
      suma += atoi(nodo->palabra);
    }
  }

  printf("Suma: %i\n", suma);
}
