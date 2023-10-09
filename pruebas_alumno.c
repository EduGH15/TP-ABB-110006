#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int comparador(void* e1, void* e2){
	if(e1 == NULL || e2 == NULL)
		return 0;

	if(e1 == e2)
		return 1;
	else	
		return 0;
}

void pruebas_creacion(){
	abb_t* arbol = abb_crear(comparador);
	pa2m_afirmar(arbol != NULL, "Se pudo crear el arbol.");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raiz es nulo.");
	pa2m_afirmar(abb_vacio(arbol) == true, "El arbol se encuentra vacío.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El arbol tiene tamaño cero.");
	
	abb_destruir(arbol);
}

void pruebas_de_insercion(){
	abb_t* arbol = abb_crear(comparador);
	int numeros[] = {5,3,4};
	for(int i = 0; i < 3; i++){
		abb_insertar(arbol, &numeros[i]);
	}
	
	pa2m_afirmar(abb_vacio(arbol) == false, "El arbol no se encuentra vacío.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "El arbol tiene tamaño 3.");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->elemento == 5, "El primer elemento insertado queda como raiz ");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->izquierda->elemento == 3, "El hijo izquierdo es el esperado.");
	pa2m_afirmar(*(int*)arbol->nodo_raiz->derecha->elemento == 4, "El hijo derecho es el esperado.");
	//pa2m_afirmar(*(int*)arbol->nodo_raiz->derecha->elemento == 4, "El hijo derecho es el esperado.");

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Creación ========================");
	pruebas_creacion();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Inserción ========================");
	pruebas_de_insercion();

	return pa2m_mostrar_reporte();
}
