#include "pa2m.h"
#include "src/abb.h"
#include "src/abb_estructura_privada.h"

int comparador(void *e1, void *e2)
{
	if (e1 == NULL && e2 == NULL)
		return 0;
	else if (e2 == NULL)
		return -1;
	else if (e1 == NULL)
		return 1;

	int valor_1 = *(int *)e1;
	int valor_2 = *(int *)e2;

	if (valor_1 == valor_2)
		return 0;
	return (valor_1 < valor_2) ? -1 : 1;
}

bool funcion_recorrido(void *elemento, void *aux)
{
	if (elemento == NULL || aux == NULL)
		return false;
	int *valor = (int *)elemento;
	return *valor != *((int *)aux);
}

typedef struct claves_recorridas {
	int *claves_rec;
	size_t contador;
} claves_recorridas_t;

bool recorrido_guardar_clave(void *elemento, void *aux)
{
	int *valor = (int *)elemento;
	claves_recorridas_t *claves = (claves_recorridas_t *)aux;

	claves->claves_rec[claves->contador] = *valor;
	claves->contador++;
	return *valor != *((int *)aux);
}

void pruebas_creacion()
{
	abb_t *arbol = abb_crear(comparador);
	pa2m_afirmar(arbol != NULL, "Se pudo crear el arbol.");
	pa2m_afirmar(arbol->nodo_raiz == NULL, "El nodo raiz es nulo.");
	pa2m_afirmar(abb_vacio(arbol) == true, "El arbol se encuentra vacío.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El arbol tiene tamaño cero.");

	abb_destruir(arbol);
}

void pruebas_de_insercion()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 6 };

	pa2m_afirmar(abb_insertar(arbol, &numeros[0]) == arbol,
		     "Puedo insertar un elemento en el abb.");
	pa2m_afirmar(arbol->nodo_raiz->elemento == &numeros[0],
		     "El elemento queda como valor raíz");
	pa2m_afirmar(abb_vacio(arbol) == false, "El abb ya no está vacío.");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "La cantidad de elementos es 1");

	pa2m_afirmar(abb_insertar(arbol, &numeros[1]) == arbol,
		     "Puedo insertar un nuevo elemento en el abb.");
	pa2m_afirmar(arbol->nodo_raiz->izquierda != NULL &&
			     arbol->nodo_raiz->derecha == NULL,
		     "El abb queda con un hijo izquierdo y sin hijo derecho.");
	pa2m_afirmar(arbol->comparador(arbol->nodo_raiz->izquierda->elemento,
				       arbol->nodo_raiz->elemento) < 0,
		     "El elemento insertado queda a la izquierda de la raíz.");
	pa2m_afirmar(abb_tamanio(arbol) == 2, "La cantidad de elementos es 2");

	pa2m_afirmar(
		abb_insertar(arbol, &numeros[2]) == arbol,
		"Puedo insertar un elemento mayor que el que se encuentra en la raiz.");
	pa2m_afirmar(arbol->nodo_raiz->izquierda != NULL &&
			     arbol->nodo_raiz->derecha != NULL,
		     "El abb queda con un hijo izquierdo y un hijo derecho.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "La cantidad de elementos es 3");

	abb_destruir(arbol);
}

void pruebas_de_eliminacion()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 4, 6 };
	for (int i = 0; i < 4; i++) {
		abb_insertar(arbol, &numeros[i]);
	}
	pa2m_afirmar(abb_tamanio(arbol) == 4, "La cantidad de elementos es 4.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[0]) == &numeros[0],
		     "Puedo borrar un nodo raiz");
	pa2m_afirmar(abb_buscar(arbol, &numeros[0]) == NULL,
		     "El nodo eliminado no existe más.");
	pa2m_afirmar(abb_tamanio(arbol) == 3, "La cantidad de elementos es 3.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[0]) == NULL,
		     "No puedo borrar un elemento que no existe en el arbol");
	pa2m_afirmar(abb_tamanio(arbol) == 3,
		     "La cantidad de elementos sigue siendo 3.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[3]) == &numeros[3],
		     "Puedo borrar un nodo hoja.");
	pa2m_afirmar(abb_buscar(arbol, &numeros[3]) == NULL,
		     "El nodo eliminado no existe más.");
	pa2m_afirmar(abb_tamanio(arbol) == 2, "La cantidad de elementos es 2.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[1]) == &numeros[1],
		     "Puedo borrar un nodo hoja");
	pa2m_afirmar(abb_buscar(arbol, &numeros[1]) == NULL,
		     "El nodo eliminado no existe más.");
	pa2m_afirmar(abb_tamanio(arbol) == 1, "La cantidad de elementos es 1.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[2]) == &numeros[2],
		     "Puedo borrar el ultimo nodo que queda");
	pa2m_afirmar(abb_buscar(arbol, &numeros[2]) == NULL,
		     "El nodo eliminado no existe más.");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "La cantidad de elementos es 0.");
	pa2m_afirmar(abb_vacio(arbol) == true, "El arbol está vacio.");

	pa2m_afirmar(abb_quitar(arbol, &numeros[2]) == NULL,
		     "No puedo borrar un elemento en un arbol vacio");

	abb_destruir(arbol);
}

void pruebas_de_busqueda()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 4, 6 };
	abb_insertar(arbol, &numeros[0]);
	abb_insertar(arbol, &numeros[1]);
	abb_insertar(arbol, &numeros[2]);

	pa2m_afirmar(abb_buscar(arbol, &numeros[0]) == &numeros[0],
		     "Busco el primer elemento insertado y lo encuentro");
	pa2m_afirmar(abb_buscar(arbol, &numeros[2]) == &numeros[2],
		     "Busco un nuevo elemento y lo encuentro");
	pa2m_afirmar(
		abb_buscar(arbol, &numeros[3]) == NULL,
		"Busco un elemento que no está en el arbol y se devuelve NULL");

	abb_quitar(arbol, &numeros[0]);
	pa2m_afirmar(
		abb_buscar(arbol, &numeros[0]) == NULL,
		"Elimino un elemento del arbol y al buscarlo de nuevo devuelve NULL");

	abb_destruir(arbol);
}

void pruebas_abb_recorrido_inorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 2, 4, 8, 7, 9 };

	for (size_t i = 0; i < 7; i++) {
		abb_insertar(arbol, &numeros[i]);
	}

	void *elementos_inorden[7];
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, elementos_inorden, 7) == 7,
		"La función de recorrido inorden devuelve la cantidad de elementos esperados.");
	pa2m_afirmar(elementos_inorden[0] == &numeros[2] &&
			     elementos_inorden[1] == &numeros[1] &&
			     elementos_inorden[2] == &numeros[3] &&
			     elementos_inorden[3] == &numeros[0] &&
			     elementos_inorden[4] == &numeros[5] &&
			     elementos_inorden[5] == &numeros[4] &&
			     elementos_inorden[6] == &numeros[6],
		     "Los elementos en el vector tienen el orden esperado.");

	void *elementos_inorden_chico[4];
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, elementos_inorden_chico, 4) == 4,
		"Pido recorrer menos elementos de los existentes para hacer el recorrido.");
	pa2m_afirmar(
		elementos_inorden_chico[0] == &numeros[2] &&
			elementos_inorden_chico[1] == &numeros[1] &&
			elementos_inorden_chico[2] == &numeros[3] &&
			elementos_inorden_chico[3] == &numeros[0],
		"Los elementos en el vector tienen el orden y cantidad esperado.");

	void *elementos_inorden_grande[10];
	pa2m_afirmar(
		abb_recorrer(arbol, INORDEN, elementos_inorden_grande, 10) == 7,
		"Pido recorrer más elementos de los existentes para hacer el recorrido.");
	pa2m_afirmar(
		elementos_inorden_grande[0] == &numeros[2] &&
			elementos_inorden_grande[1] == &numeros[1] &&
			elementos_inorden_grande[2] == &numeros[3] &&
			elementos_inorden_grande[3] == &numeros[0] &&
			elementos_inorden_grande[4] == &numeros[5] &&
			elementos_inorden_grande[5] == &numeros[4] &&
			elementos_inorden_grande[6] == &numeros[6],
		"Los elementos en el vector tienen el orden y cantidad esperado.");

	abb_destruir(arbol);
}

void pruebas_abb_recorrido_preorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 2, 4, 8, 7, 9 };

	for (size_t i = 0; i < 7; i++) {
		abb_insertar(arbol, &numeros[i]);
	}

	void *elementos_preorden[7];
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, elementos_preorden, 7) == 7,
		"La función de recorrido preorden devuelve la cantidad de elementos esperados.");
	pa2m_afirmar(elementos_preorden[0] == &numeros[0] &&
			     elementos_preorden[1] == &numeros[1] &&
			     elementos_preorden[2] == &numeros[2] &&
			     elementos_preorden[3] == &numeros[3] &&
			     elementos_preorden[4] == &numeros[4] &&
			     elementos_preorden[5] == &numeros[5] &&
			     elementos_preorden[6] == &numeros[6],
		     "Los elementos en el vector tienen el orden esperado.");

	void *elementos_preorden_chico[4];
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, elementos_preorden_chico, 4) == 4,
		"Pido recorrer menos elementos de los existentes para hacer el recorrido.");
	pa2m_afirmar(
		elementos_preorden_chico[0] == &numeros[0] &&
			elementos_preorden_chico[1] == &numeros[1] &&
			elementos_preorden_chico[2] == &numeros[2] &&
			elementos_preorden_chico[3] == &numeros[3],
		"Los elementos en el vector tienen el orden y cantidad esperado.");

	void *elementos_preorden_grande[10];
	pa2m_afirmar(
		abb_recorrer(arbol, PREORDEN, elementos_preorden_grande, 10) ==
			7,
		"Pido recorrer más elementos de los existentes para hacer el recorrido.");
	pa2m_afirmar(
		elementos_preorden[0] == &numeros[0] &&
			elementos_preorden[1] == &numeros[1] &&
			elementos_preorden[2] == &numeros[2] &&
			elementos_preorden[3] == &numeros[3] &&
			elementos_preorden[4] == &numeros[4] &&
			elementos_preorden[5] == &numeros[5] &&
			elementos_preorden[6] == &numeros[6],
		"Los elementos en el vector tienen el orden y cantidad esperado.");

	abb_destruir(arbol);
}

void pruebas_abb_recorrido_postorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 2, 4, 8, 7, 9 };

	for (size_t i = 0; i < 7; i++) {
		abb_insertar(arbol, &numeros[i]);
	}

	void *elementos_postorden[7];
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, elementos_postorden, 7) == 7,
		"La función de recorrido postorden devuelve la cantidad de elementos esperados.");
	pa2m_afirmar(elementos_postorden[0] == &numeros[2] &&
			     elementos_postorden[1] == &numeros[3] &&
			     elementos_postorden[2] == &numeros[1] &&
			     elementos_postorden[3] == &numeros[5] &&
			     elementos_postorden[4] == &numeros[6] &&
			     elementos_postorden[5] == &numeros[4] &&
			     elementos_postorden[6] == &numeros[0],
		     "Los elementos en el vector tienen el orden esperado.");

	void *elementos_postorden_chico[4];
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, elementos_postorden_chico, 4) ==
			4,
		"Pido recorrer menos elementos de los existentes para hacer el recorrido.");
	pa2m_afirmar(
		elementos_postorden_chico[0] == &numeros[2] &&
			elementos_postorden_chico[1] == &numeros[3] &&
			elementos_postorden_chico[2] == &numeros[1] &&
			elementos_postorden_chico[3] == &numeros[5],
		"Los elementos en el vector tienen el orden y cantidad esperado.");

	void *elementos_postorden_grande[10];
	pa2m_afirmar(
		abb_recorrer(arbol, POSTORDEN, elementos_postorden_grande,
			     10) == 7,
		"Pido recorrer más elementos de los existentes para hacer el recorrido.");
	pa2m_afirmar(
		elementos_postorden_grande[0] == &numeros[2] &&
			elementos_postorden_grande[1] == &numeros[3] &&
			elementos_postorden_grande[2] == &numeros[1] &&
			elementos_postorden_grande[3] == &numeros[5] &&
			elementos_postorden_grande[4] == &numeros[6] &&
			elementos_postorden_grande[5] == &numeros[4] &&
			elementos_postorden_grande[6] == &numeros[0],
		"Los elementos en el vector tienen el orden y cantidad esperado.");

	abb_destruir(arbol);
}

void pruebas_abb_con_cada_elemento_inorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 2, 4, 8, 7, 9 };

	for (size_t i = 0; i < 7; i++) {
		abb_insertar(arbol, &numeros[i]);
	}

	int claves_recorridas[7];
	claves_recorridas_t data = { claves_recorridas, 0 };
	size_t cantidad_elementos = abb_con_cada_elemento(
		arbol, INORDEN, recorrido_guardar_clave, &data);

	int claves_esperadas[] = { 2, 3, 4, 5, 7, 8, 9 };

	bool claves_iguales = true;
	for (size_t i = 0; i < cantidad_elementos; i++) {
		if (claves_recorridas[i] != claves_esperadas[i]) {
			claves_iguales = false;
			break;
		}
	}

	pa2m_afirmar(
		cantidad_elementos == 7,
		"La función de recorrido inorden devuelve la cantidad de elementos esperados.");
	pa2m_afirmar(claves_iguales,
		     "Las claves se recorrieron en el orden esperado.");

	pa2m_afirmar(
		abb_con_cada_elemento(arbol, INORDEN, funcion_recorrido,
				      &numeros[2]) == 1,
		"Cuando la función devuelve false, deja de iterar y devuelve la cantidad correcta.");

	abb_destruir(arbol);
}

void pruebas_abb_con_cada_elemento_preorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 2, 4, 8, 7, 9 };

	for (size_t i = 0; i < 7; i++) {
		abb_insertar(arbol, &numeros[i]);
	}

	int claves_recorridas[7];
	claves_recorridas_t data = { claves_recorridas, 0 };
	size_t cantidad_elementos = abb_con_cada_elemento(
		arbol, PREORDEN, recorrido_guardar_clave, &data);

	int claves_esperadas[] = { 5, 3, 2, 4, 8, 7, 9 };

	bool claves_iguales = true;
	for (size_t i = 0; i < cantidad_elementos; i++) {
		if (claves_recorridas[i] != claves_esperadas[i]) {
			claves_iguales = false;
			break;
		}
	}

	pa2m_afirmar(
		cantidad_elementos == 7,
		"La función de recorrido preorden devuelve la cantidad de elementos esperados.");
	pa2m_afirmar(claves_iguales,
		     "Las claves se recorrieron en el orden esperado.");

	pa2m_afirmar(
		abb_con_cada_elemento(arbol, PREORDEN, funcion_recorrido,
				      &numeros[2]) == 3,
		"Cuando la función devuelve false, deja de iterar y devuelve la cantidad correcta.");

	abb_destruir(arbol);
}

void pruebas_abb_con_cada_elemento_postorden()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 2, 4, 8, 7, 9 };

	for (size_t i = 0; i < 7; i++) {
		abb_insertar(arbol, &numeros[i]);
	}

	int claves_recorridas[7];
	claves_recorridas_t data = { claves_recorridas, 0 };
	size_t cantidad_elementos = abb_con_cada_elemento(
		arbol, POSTORDEN, recorrido_guardar_clave, &data);

	int claves_esperadas[] = { 2, 4, 3, 7, 9, 8, 5 };

	bool claves_iguales = true;
	for (size_t i = 0; i < cantidad_elementos; i++) {
		if (claves_recorridas[i] != claves_esperadas[i]) {
			claves_iguales = false;
			break;
		}
	}

	pa2m_afirmar(
		cantidad_elementos == 7,
		"La función de recorrido postorden devuelve la cantidad de elementos esperados.");
	pa2m_afirmar(claves_iguales,
		     "Las claves se recorrieron en el orden esperado.");

	pa2m_afirmar(
		abb_con_cada_elemento(arbol, POSTORDEN, funcion_recorrido,
				      &numeros[2]) == 1,
		"Cuando la función devuelve false, deja de iterar y devuelve la cantidad correcta.");

	abb_destruir(arbol);
}

void pruebas_null()
{
	abb_t *arbol = abb_crear(comparador);
	int numeros[] = { 5, 3, 2, 4, 8, 7, 9 };

	pa2m_afirmar(abb_insertar(NULL, &numeros[0]) == NULL,
		     "No puedo insertar nada en un abb nulo.");

	abb_insertar(arbol, &numeros[0]);

	pa2m_afirmar(abb_buscar(NULL, &numeros[0]) == NULL,
		     "No puedo buscar nada en un abb nulo.");

	pa2m_afirmar(abb_quitar(NULL, &numeros[0]) == NULL,
		     "No puedo borrar nada de en un abb nulo.");

	pa2m_afirmar(abb_vacio(NULL) == true, "Un abb nulo es vacío.");
	pa2m_afirmar(abb_tamanio(NULL) == 0,
		     "La cantidad de elementos de un abb NULL es 0");

	pa2m_afirmar(abb_con_cada_elemento(NULL, INORDEN, funcion_recorrido,
					   &numeros[0]) == 0,
		     "No puedo iterar inorden un abb nulo.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, NULL, &numeros[0]) ==
			     0,
		     "No puedo iterar inorden con una función nula.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, INORDEN, funcion_recorrido,
					   NULL) != 0,
		     "Puedo iterar inorden con puntero extra nulo.");

	pa2m_afirmar(abb_con_cada_elemento(NULL, PREORDEN, funcion_recorrido,
					   &numeros[0]) == 0,
		     "No puedo iterar preorden un abb nulo.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, NULL,
					   &numeros[0]) == 0,
		     "No puedo iterar preorden con una función nula.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, PREORDEN, funcion_recorrido,
					   NULL) != 0,
		     "Puedo iterar preorden con puntero extra nulo.");

	pa2m_afirmar(abb_con_cada_elemento(NULL, POSTORDEN, funcion_recorrido,
					   &numeros[0]) == 0,
		     "No puedo iterar postorden un abb nulo.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, NULL,
					   &numeros[0]) == 0,
		     "No puedo iterar postorden con una función nula.");
	pa2m_afirmar(abb_con_cada_elemento(arbol, POSTORDEN, funcion_recorrido,
					   NULL) != 0,
		     "Puedo iterar postorden con puntero extra nulo.");

	pa2m_afirmar(abb_insertar(arbol, NULL) == arbol,
		     "Puedo insertar elementos NULL sin problemas");

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

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Búsqueda ========================");
	pruebas_de_busqueda();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas de Recorrido e iterador interno ========================");
	pa2m_nuevo_grupo("\n============= iterador preorden ===============");
	pruebas_abb_recorrido_inorden();

	pa2m_nuevo_grupo("\n============= iterador preorden ===============");
	pruebas_abb_recorrido_preorden();

	pa2m_nuevo_grupo("\n============= iterador postorden ===============");
	pruebas_abb_recorrido_postorden();

	pa2m_nuevo_grupo("\n============= recorrido inorden ===============");
	pruebas_abb_con_cada_elemento_inorden();

	pa2m_nuevo_grupo("\n============= recorrido preorden ===============");
	pruebas_abb_con_cada_elemento_preorden();

	pa2m_nuevo_grupo("\n============= recorrido postorden ===============");
	pruebas_abb_con_cada_elemento_postorden();

	pa2m_nuevo_grupo(
		"\n======================== Pruebas NULL ========================");
	pruebas_null();

	return pa2m_mostrar_reporte();
}
