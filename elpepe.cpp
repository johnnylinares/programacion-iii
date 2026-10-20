#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Vamos a trabajar en la construcción de un Algoritmo Genético
para resolver una instancia del problema de la Mochila, usando
orientación a objetos en C++.

Ej:
* 10 productos: {0, 1, 2, 3, ..., 9}
* Asociado a cada producto 'c' existe Pi (Peso) y Bi (Beneficio)
* La mochila tiene una capacidad 'c'
* Encontrar un subconjunto S <= {0, 1, ..., 9} que maximice la suma de los beneficios
sujeto a que la sumatoria de los pesos asociados de los productos sea menor o igual 
que la capacidad.

|  i  |  Peso  |  Beneficio  |
|----------------------------|
|  0  |   10   |     50      |
|  1  |   8    |     70      |
|  2  |   3    |     55      |
|  3  -----------------------|
|  4  -----------------------|
|  5  -----------------------|

| 0 | 0 | 1 | 0 | 0 | 1 | 1 | 0 | 1 | 1 | <- 0: No compra, 1: Compra
| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | <- Posicion de producto
 
Funcion fitness: Cuando se pasa de peso, se le puede asignar un valor negativo
para indicar que no está correcto, cuando se pasa de la capacidad de la mochila.
 
Crear 
Población 0: 100 individuos. Todas son diferentes. (0 o 1). En la primera población se genera al azar.
Población 1: A partir de la segunda generación se crea individuo a individuo, hasta que tenga tantos como la primera. 
Una vez termine se elimina por completo la primera población.
Población 2: Se repite y se elimina a la primera al terminar hasta conseguir la solución.
 
Selección: Cada objeto va a determinar una pareja con la cual cruzar sus nuevos genes para la siguiente población.
Se necesita un operador de selección. Los individuos con mejor fitness tienen mas probabilidades de ser seleccionados para esto.
 
Al crear un nuevo individuo sea hará un cruce, tomando algunas cosas de los objetos seleccionados
 
Seleccion cruce y mutacion, el objeto creado ahora es capaz de tomar un valor que no es del padre 1 ni el padre 2.
 
*/

class individuo {
	private:
		bool a[10];
		// Algo para fitness
	public:
		individuo() { // Constructor
			for (int i = 0; i < 10; i++) a[i] = 0;
		}
		
		individuo(bool arr[10]) {
			for (int i = 0; i < 10; i++) {
				a[i] = arr[i];
			}
		}
		
		void compra() { // Declarar como 1 a productos comprados de manera aleatoria.
			for (int i = 0; i < 10; i++) a[i] = rand() % 2;
		}
		
		void show() { // Mostrar el array de si los productos fueron comprados o no.
			for (int i = 0; i < 10; i++) cout << a[i] << " ";
		}
		
		int fitness(int c, int pe[10], int be[10]) { // Dar un coeficiente dependiendo si se pasa o no.
			int p_sum = 0, b_sum = 0;
			
			for (int i = 0; i < 10; i++) {
				if (a[i] == 1) {
					p_sum += pe[i];
					b_sum += be[i];
				}
			}
			
			if (p_sum <= c) return b_sum;
			else return c - p_sum;
		}
		
		// Seleccion (que tenga en cuenta el mejor fitness)
		int seleccion(individuo pob[2][100], int idx, int c, int p[10], int b[10]) { 
			// Probabilidades descritas por (n + 1)/(100) siendo n el idx de el individuo en el orden de fitness
			// Se tira una probabilidad entre 0 y 1 (ej: 0.47625) y el individuo que sea capaz de superar ese numero en cuestion de probabilidad sera el seleccionado
			
			int orden[3][100];
			int ok = 0;
			int aux;
			
			// Guardar todo para despues ordenar
			for (int i = 0; i < 100; i++) {
				// Se usa 0 para los fitness y 1 para el idx original para hacer el cruce.
				orden[0][i] = pob[idx][i].fitness(c, p, b);
			}
			
			// Ordenar
			do {
				// Asumo que está ordenado
				ok = 1;
				for (int j = 0; j < 99; j++) {
					if (orden[0][j] > orden[0][j + 1]) {
						ok = 0; // No está ordenado
						
						// Swap fitness
						aux = orden[0][j + 1];
						orden[0][j + 1] = orden[0][j];
						orden[0][j] = aux;
						
						// Swap index
						aux = orden[1][j + 1];
						orden[1][j + 1] = orden[1][j];
						orden[1][j] = aux;
					}
				}
			} while (ok == 0); // Mientras no está ordenado.
			
			for (int k = 0; k < 100; k++) {
				// Asignar probabilidades a cada uno.
				orden[3][k] = (k + 1)/(100);
			}
			
			// Generar numero flotante 0 y 1
			float s = rand() % 32767;
			
			
		}
		
		// Cruce, de manera aleatoria se mira todos menos el mismo.
		individuo cruce(individuo pareja) {
			bool h[10]; 
			
			
			for (int i = 0; i < 10; i++) {
				if (rand() % 2 == 0) h[i] = a[i];
				else h[i] = pareja.a[i];
			}
			
			individuo hijo(h);
			return hijo;
		}
		
		// Mutacion
		void mutacion(individuo hijo) {
			hijo.a[rand() % 10] = rand() % 2;
		}
};

void mostrarPoblacion(individuo pob[2][100], int idx, int c, int p[10], int b[10]) {
	cout << "| N° | Genes | Fitness |" << endl;
	for (int k = 0; k < 100; k++) {
		cout << " | " << k << " | ";
		pob[idx][k].show(); cout << " | ";
		cout << pob[idx][k].fitness(c, p, b) << " | " << endl;
	}
}

int main(void) {
	srand(time(0));
	individuo poblacion[2][100];
	int era = 0, act = 0;
	
	int c = 50;
	int p[10] = {20, 16, 6, 10, 16, 6, 14, 6, 10, 2};
	int b[10] = {50, 70, 55, 100, 30, 40, 50, 25, 90, 20};
	
	// Generación 0
	for (int i = 0; i < 100; i++) {
		poblacion[act][i].compra();
	}
	
	// Generación de n generaciones.
	for (era = 0; era < 10; era++) {
	    int sig = (act + 1) % 2; // Índice de la siguiente población
	    
	    // Generar nueva población a partir de la actual
	    for (int i = 0; i < 100; i++) {
	        int selec = poblacion[act][i].seleccion(poblacion[act][i], act, c, p, b);
	        
	        // Guardar el hijo en la población SIGUIENTE (sig)
	        poblacion[sig][i] = poblacion[act][i].cruce(poblacion[act][selec]);
	    }
	    
	    // Mostrar la población recién generada
	    cout << "Poblacion N" << era << endl;
	    mostrarPoblacion(poblacion, sig, c, p, b);
	    
	    // Cambiar de índice activo para la siguiente iteración
	    act = sig;
	}
	
	
	
}
