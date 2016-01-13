#include <stdio.h>
#include <string.h>
#include "comandos.h"

void comando_buscar(estado_t *estado, char *palabra) {
  TNodo *nodo;

  nodo = obtener_palabra(&estado->origen, palabra);

  if (nodo == NULL) {
    printf("Palabra '%s' no encontrada\n", palabra);
  } else {
    printf("La palabra '%s' aparece %i veces\n", palabra, nodo->cuenta);
  }
}
