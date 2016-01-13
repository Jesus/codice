#ifndef _LISTA_H
#define _LISTA_H

typedef struct TipoNodo {
  char palabra[100];
  int cuenta;
  struct TipoNodo *siguiente;
  struct TipoNodo *anterior;
} TNodo;

typedef struct {
  TNodo *primero, *ultimo;
  int longitud;
} TLista;

void inicializar_lista(TLista *);
TNodo *insertar_palabra(TLista *, char *);
TNodo *insertar_nueva_palabra(TLista *, char *);
TNodo *obtener_palabra(TLista *, char *);
int eliminar_palabra(TLista *, char *);
void terminar_lista(TLista *);

void mostrar_lista(TLista *);

#endif
