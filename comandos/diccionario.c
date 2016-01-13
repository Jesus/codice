#include <stdio.h>
#include "comandos.h"

void comando_diccionario(estado_t *estado, char *nombre_fichero) {
  FILE *f;

  f = fopen(nombre_fichero, "r");
  if (f == NULL) {
    fprintf(stderr, "El fichero '%s' no existe o no se puede abrir.\n",
            nombre_fichero);
  } else {
    cargar_palabras(&estado->diccionario, f);

    printf("Diccionario cargado: %i palabras\n", estado->diccionario.longitud);

    fclose(f);
  }
}
