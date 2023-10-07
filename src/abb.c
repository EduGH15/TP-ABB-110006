#include "abb.h"
#include "abb_estructura_privada.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if(comparador == NULL)
		return NULL;

	abb_t* abb = calloc(1, sizeof(abb_t));
	if(abb == NULL)
		return NULL;

	abb->comparador = comparador;
	return abb;
}

nodo_abb_t* nodo_insertar(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){
	if(nodo == NULL){
		nodo_abb_t* nodo_nuevo = calloc(1, sizeof(nodo_abb_t));
		if(nodo_nuevo == NULL){
			return NULL;
		}
		nodo_nuevo->elemento = elemento;
		return nodo_nuevo;
	}

	int comparacion = comparador(elemento, nodo->elemento);

	if(comparacion <= 0)
		nodo->izquierda = nodo_insertar(nodo->izquierda, elemento, comparador);
	else
		nodo->derecha = nodo_insertar(nodo->derecha, elemento, comparador);

	return nodo;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{	
	if(arbol == NULL)
		return NULL;
	
	arbol->nodo_raiz = nodo_insertar(arbol->nodo_raiz, elemento, arbol->comparador);
	if(arbol->nodo_raiz != NULL)
		(arbol->tamanio)++;

	return arbol;
}

nodo_abb_t* nodo_buscar(nodo_abb_t* nodo, void* elemento, abb_comparador comparador){
	if(nodo == NULL)
		return NULL;

	int comparacion = comparador(elemento, nodo->elemento);
	
	if(comparacion == 0)
		return nodo;
	if(comparacion < 0)
		return nodo_buscar(nodo->izquierda, elemento, comparador);
	else
		return nodo_buscar(nodo->derecha, elemento, comparador);
}

nodo_abb_t* extraer_predecesor_inorden(nodo_abb_t* nodo, void** elemento_eliminado){
	if(nodo->derecha == NULL){
		*elemento_eliminado = nodo->elemento;
		nodo_abb_t* izquierda = nodo->izquierda;
		free(nodo);
		return izquierda;
	}
	nodo->derecha = extraer_predecesor_inorden(nodo->derecha, elemento_eliminado);
	return nodo;
}

void* nodo_quitar(nodo_abb_t* nodo, void* elemento, abb_comparador comparador, void** elemento_eliminado){
	if(nodo == NULL){
		return NULL;
	}
	int comparacion = comparador(elemento, nodo->elemento);

	if(comparacion == 0){
		nodo_abb_t* izquierda = nodo->izquierda;
		nodo_abb_t* derecha = nodo->derecha;
		*elemento_eliminado = nodo->elemento;

		if(izquierda != NULL && derecha != NULL){
			void* predecesor = NULL;
			nodo->izquierda = extraer_predecesor_inorden(nodo->izquierda, &predecesor);
			nodo->elemento = predecesor;
		}else{
			free(nodo);
			if(izquierda == NULL)
				return derecha;
			return izquierda;
		}
	}else if(comparacion < 0)
		nodo->izquierda = nodo_quitar(nodo->izquierda, elemento, comparador, elemento_eliminado);
	else
		nodo->derecha = nodo_quitar(nodo->derecha, elemento, comparador, elemento_eliminado);
	
	return nodo;
}

void *abb_quitar(abb_t *arbol, void *elemento)
{	
	if(arbol == NULL)
		return NULL;
	
	void* elemento_eliminado = NULL;
	arbol->nodo_raiz = nodo_quitar(arbol->nodo_raiz, elemento, arbol->comparador, &elemento_eliminado);
	(arbol->tamanio)--;
	return elemento_eliminado;
}

void *abb_buscar(abb_t *arbol, void *elemento)
{	
	if(arbol == NULL)
		return NULL; 
	
	nodo_abb_t* nodo_buscado = NULL;
	nodo_buscado = nodo_buscar(arbol->nodo_raiz, elemento, arbol->comparador);

	if(nodo_buscado == NULL)
		return NULL;
	return nodo_buscado->elemento;
}

bool abb_vacio(abb_t *arbol)
{
	if(arbol == NULL)
		return true;
	return arbol->tamanio == 0;
}

size_t abb_tamanio(abb_t *arbol)
{	
	if(arbol == NULL)
		return 0;
	return arbol->tamanio;
}

void nodo_destruir(nodo_abb_t *nodo, void (*destructor)(void*)){
	if(nodo == NULL)
		return;

	if(destructor != NULL)
		destructor(nodo->elemento);

	nodo_destruir(nodo->izquierda, destructor);
	nodo_destruir(nodo->derecha, destructor);
	free(nodo);
}

void abb_destruir(abb_t *arbol)
{
	if(arbol == NULL)
		return;
	abb_destruir_todo(arbol, NULL);
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if(arbol == NULL)
		return;

	nodo_destruir(arbol->nodo_raiz, destructor);
	free(arbol);
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	return 0;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	return 0;
}
