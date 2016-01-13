#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

void inicializar_lista(TLista *lista) {
  lista->primero = lista->ultimo = NULL;
  lista->longitud = 0;
}

TNodo *crear_nodo(char *palabra) {
  TNodo *nodo;

  nodo = malloc(sizeof(TNodo));
  strcpy(nodo->palabra, palabra);
  nodo->cuenta = 1;
  nodo->siguiente = 0;
  nodo->anterior = 0;

  return nodo;
}

TNodo *insertar_palabra(TLista *lista, char *palabra) {
  TNodo *nodo;

  /* Primero tratamos de obtener el nodo correspondiente a la palabra que
   * deseamos insertar. */
  nodo = obtener_palabra(lista, palabra);
  if (nodo != NULL) {
    // Si la palabra ya se encuentra en el diccionario, incrementamos la cuenta
    nodo->cuenta++;
  } else {
    // Si la palabra no esta, la insertamos en el lugar adecuado
    nodo = insertar_nueva_palabra(lista, palabra);
  }

  return nodo;
}

TNodo *insertar_nueva_palabra(TLista *lista, char *palabra) {
  TNodo *nuevo_nodo = crear_nodo(palabra);
  TNodo *cursor;

  if (lista->longitud == 0) {
    // Insertar nodo en una lista vacia
    lista->primero = nuevo_nodo;
    lista->ultimo = nuevo_nodo;
  } else {
    // Insertar al lado de cierto nodo, hay que determinar cual
    cursor = lista->primero;
    while (cursor != NULL && strcmp(cursor->palabra, palabra) < 0) {
      cursor = cursor->siguiente;
    }

    if (cursor == lista->primero) {
      // Insertar al principio
      lista->primero->anterior = nuevo_nodo;
      nuevo_nodo->siguiente = lista->primero;

      lista->primero = nuevo_nodo;
    } else if (cursor == NULL) {
      // Insertar al final
      lista->ultimo->siguiente = nuevo_nodo;
      nuevo_nodo->anterior = lista->ultimo;

      lista->ultimo = nuevo_nodo;
    } else {
      // Insertar justo antes de `cursor`
      nuevo_nodo->anterior = cursor->anterior;
      nuevo_nodo->siguiente = cursor;

      nuevo_nodo->siguiente->anterior = nuevo_nodo;
      nuevo_nodo->anterior->siguiente = nuevo_nodo;
    }
  }

  lista->longitud++;
  return nuevo_nodo;
}

TNodo *obtener_palabra(TLista *lista, char *palabra) {
  TNodo *nodo = lista->primero;
  int cmp;

  while (nodo) {
    cmp = strcmp(nodo->palabra, palabra);
    if (cmp == 0) {
      return nodo;
    } else if (cmp > 0) {
      return NULL;
    } else {
      nodo = nodo->siguiente;
    }
  }

  return NULL;
}

int eliminar_palabra(TLista *lista, char *palabra) {
  TNodo *nodo;
  nodo = obtener_palabra(lista, palabra);

  if (nodo) {
    if (nodo->siguiente)
      nodo->siguiente->anterior = nodo->anterior;

    if (nodo->anterior)
      nodo->anterior->siguiente = nodo->siguiente;

    if (lista->primero == nodo)
      lista->primero = nodo->siguiente;

    if (lista->ultimo == nodo)
      lista->ultimo = nodo->anterior;

    free(nodo);
    return 1;
  } else {
    return 0;
  }
}

void terminar_lista(TLista *lista) {
  TNodo *cursor, *nodo = lista->primero;

  // Liberar todos los nodos que se hayan reservado
  while (nodo) {
    cursor = nodo->siguiente;
    free(nodo);
    nodo = cursor;
  }

  inicializar_lista(lista);
}

void mostrar_lista(TLista *lista) {
  TNodo *nodo = lista->primero;

  while (nodo != NULL) {
    printf("  - %s (%i)\n", nodo->palabra, nodo->cuenta);
    nodo = nodo->siguiente;
  }
}
