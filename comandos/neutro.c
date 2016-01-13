#include <stdio.h>
#include "comandos.h"

#define FICHERO_NEUTROS "neutro.txt"

void comando_neutro_on(TLista *neutros) {
  FILE *f;

  f = fopen(FICHERO_NEUTROS, "r");
  if (f == NULL) {
    fprintf(stderr, "El fichero '%s' no existe o no se puede abrir.\n",
            FICHERO_NEUTROS);
  } else {
    cargar_palabras(neutros, f);

    fclose(f);
  }
}

void comando_neutro_off(TLista *neutros) {
  if (neutros->longitud > 0) {
    terminar_lista(neutros);
    inicializar_lista(neutros);
  }
}

void comando_neutro_agregar(TLista *neutros, char *palabra) {
  TNodo *nodo = insertar_palabra(neutros, palabra);

  if (nodo->cuenta > 1) {
    printf("La palabra '%s' ya estaba en la lista de neutros\n", palabra);
  }
}

void comando_neutro_eliminar(TLista *neutros, char *palabra) {
  int resultado = eliminar_palabra(neutros, palabra);

  if (resultado == 0) {
    printf("La palabra '%s' no se encuentra en la lista de neutros\n", palabra);
  }
}

void comando_neutro_actualizar(TLista *neutros) {
  TNodo *nodo;
  FILE *f;

  f = fopen(FICHERO_NEUTROS, "w");
  if (f == NULL) {
    fprintf(stderr, "El fichero '%s' no se puede abrir para escribir.\n",
            FICHERO_NEUTROS);
  } else {
    for (nodo = neutros->primero; nodo; nodo = nodo->siguiente) {
      fprintf(f, "%s\n", nodo->palabra);
    }

    fclose(f);
  }
}
