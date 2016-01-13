#include <stdio.h>
#include "comandos.h"

int obtener_max_repeticiones(TLista *lista) {
  TNodo *nodo;
  int max = 0;

  for (nodo = lista->primero; nodo; nodo = nodo->siguiente) {
    if (nodo->cuenta > max) max = nodo->cuenta;
  }

  return max;
}

void mostrar_ranking(TLista *lista, int n) {
  TNodo *nodo;
  int rank = obtener_max_repeticiones(lista);
  int i = 1;

  // Hemos determinado que el 0 indica que se muestre el ranking completo
  if (n == 0) {
    n = lista->longitud;
  }

  while (rank > 0) {
    for (nodo = lista->primero; nodo && i <= n; nodo = nodo->siguiente) {
      if (nodo->cuenta == rank) {
        printf("%3i. '%s' (%i)\n", i, nodo->palabra, nodo->cuenta);
        i++;
      }
    }
    rank--;
  }
}

void comando_ranking_caracteres(estado_t *estado, int n) {
  TLista caracteres;
  char palabra[] = "X";
  char c;

  inicializar_lista(&caracteres);

  fseek(estado->fd_origen, 0, SEEK_SET);
  while ((c = fgetc(estado->fd_origen)) != EOF) {
    palabra[0] = c;
    insertar_palabra(&caracteres, palabra);
  }

  mostrar_ranking(&caracteres, n);
}

void comando_ranking_palabras(estado_t *estado, int n) {
  mostrar_ranking(&estado->origen, n);
}
