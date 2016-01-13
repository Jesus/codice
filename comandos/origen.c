#include <stdio.h>
#include <string.h>
#include "comandos.h"

void comando_origen(estado_t *estado, char *nombre_fichero) {
  FILE *f;

  f = fopen(nombre_fichero, "r");
  if (f == NULL) {
    fprintf(stderr, "El fichero '%s' no existe o no se puede abrir.\n",
            nombre_fichero);
  } else {
    if (estado->fd_origen != NULL) {
      fclose(estado->fd_origen);
    }
    strcpy(estado->nombre_origen, nombre_fichero);
    estado->fd_origen = f;

    cargar_palabras(&estado->origen, estado->fd_origen);
  }
}
