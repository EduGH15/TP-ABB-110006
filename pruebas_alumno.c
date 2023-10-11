#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int comparador(void* e1, void* e2){
	int valor_1 = *(int*)e1;
	int valor_2 = *(int*)e2;

	if(valor_1 < valor_2)
		return -1;
	else if(valor_1 > valor_2)
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
	int numeros[] = {5,3,6};
		
    pa2m_afirmar(abb_insertar(arbol, &numeros[0]) == arbol, "Puedo insertar un elemento en el abb.");
    pa2m_afirmar(arbol->nodo_raiz->elemento == &numeros[0], "El elemento queda como valor raíz");
    pa2m_afirmar(abb_vacio(arbol) == false, "El abb ya no está vacío.");
    pa2m_afirmar(abb_tamanio(arbol) == 1, "La cantidad de elementos es 1");

	pa2m_afirmar(abb_insertar(arbol, &numeros[1]) == arbol, "Puedo insertar un nuevo elemento en el abb.");
    pa2m_afirmar(arbol->nodo_raiz->izquierda != NULL && arbol->nodo_raiz->derecha == NULL, "El abb queda con un hijo izquierdo y sin hijo derecho.");
    pa2m_afirmar(arbol->comparador(arbol->nodo_raiz->izquierda->elemento, arbol->nodo_raiz->elemento) < 0, "El elemento insertado queda a la izquierda de la raíz.");
    pa2m_afirmar(abb_tamanio(arbol) == 2, "La cantidad de elementos es 2");
    
    pa2m_afirmar(abb_insertar(arbol, &numeros[2]) == arbol, "Puedo insertar un elemento mayor que el que se encuentra en la raiz.");
    pa2m_afirmar(arbol->nodo_raiz->izquierda != NULL && arbol->nodo_raiz->derecha != NULL, "El abb queda con un hijo izquierdo y un hijo derecho.");
    pa2m_afirmar(abb_tamanio(arbol) == 3, "La cantidad de elementos es 3");
  
	abb_destruir(arbol);
	}

void pruebas_de_eliminacion(){
	abb_t* arbol = abb_crear(comparador);
	int numeros[] = {5,3,4,6};
	for(int i = 0; i < 4; i++){
		abb_insertar(arbol, &numeros[i]);
	}
	pa2m_afirmar(abb_tamanio(arbol) == 4, "La cantidad de elementos es 4.");

    pa2m_afirmar(abb_quitar(arbol, &numeros[0]) == &numeros[0], "Puedo borrar un nodo raiz");
	pa2m_afirmar(abb_buscar(arbol, &numeros[0]) == NULL, "El nodo eliminado no existe más.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "La cantidad de elementos es 3.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[0]) == NULL, "No puedo borrar un elemento que no existe en el arbol");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "La cantidad de elementos sigue siendo 3.");

    pa2m_afirmar(abb_quitar(arbol, &numeros[3]) == &numeros[3], "Puedo borrar un nodo hoja.");
    pa2m_afirmar(abb_buscar(arbol, &numeros[3]) == NULL, "El nodo eliminado no existe más.");
	pa2m_afirmar(abb_tamanio(arbol) == 2, "La cantidad de elementos es 2.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[1]) == &numeros[1], "Puedo borrar un nodo hoja");
	pa2m_afirmar(abb_buscar(arbol, &numeros[1]) == NULL, "El nodo eliminado no existe más.");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "La cantidad de elementos es 1.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[2]) == &numeros[2], "Puedo borrar el ultimo nodo que queda");
    pa2m_afirmar(abb_buscar(arbol, &numeros[2]) == NULL, "El nodo eliminado no existe más.");
    pa2m_afirmar(abb_tamanio(arbol) == 0, "La cantidad de elementos es 0.");
    pa2m_afirmar(abb_vacio(arbol) == true, "El arbol está vacio.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[2]) == NULL, "No puedo borrar un elemento en un arbol vacio");

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

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Eliminación ========================");
	pruebas_de_eliminacion();

	return pa2m_mostrar_reporte();
}
