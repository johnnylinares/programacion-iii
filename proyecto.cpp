#include <iostream>
#include <cmath>

using namespace std;

// Herencia 27/10/26.

//Clase padre.
class Punto2d {
	protected: // Para que los hijos PUEDAN usar a la X e Y.
		float x;
		float y;
	public:
		Punto2d() {}
		Punto2d(float xx, float yy):
			x(xx), y(yy) {}
		
		// Get
		float getX() {
			return x;
		}
		float getY() {
			return y;
		}
		
		// Set
		void setX(float xx) {
			x = xx;
		}
		void setY(float yy) {
			y = yy;
		}
		
		// Calcular la distancia de dos puntos
		float calcDist(Punto2d &otro) {
			return sqrt(pow(otro.x - x, 2) + pow(otro.y - y, 2));
		}
};


// Clase hija.
class Punto3d: public Punto2d { // public, el modo generico donde se le asigna el atributo del padre al hijo.
	private: // En caso de no querer crear mas clases hijo a partir de aqui.
		float z;
	public:
		Punto3d(float xx, float yy, float zz):
			Punto2d(xx, yy), z(zz) {}
			
		// Get
		float getZ() {
			return z;
		}
		
		// Set
		void setZ(float zz) {
			z = zz;
		}
};

/* Desde ahora, se trabajará sobre:
- Resolver este problema es "el proyecto" del cual habrán de entregar distribuidas a lo largo del 2do y 3er corte.

* Dadas las coordenadas bidimensionales de una nube de n puntos.
* Encontrar el tour de costo mínimo. (tour -> secuencia de elementos de {1, 2, 3, ..., n} 
	que representa un recorrido que pasa por cada punto exactamente una vez y vuelve al punto de partida.
* Sea S el espacio donde viven los tours, la estrategia a seguir será , partir de un s E S aleatorio y realizar una caminata.
s - > S_0, S_1, S_2, ..., S_M, tal que Costo(S_i+1) < Costo(S_i).

* Algoritmos recomendados / Ideas
1. Siempre iniciar por el "nodo" 1 y elegir siempre el menor próximo, es decir si 8 y 3 están cerca, iría por el 3.
2. Apenas se cree el "camino", quitar 2 arcos y sustituirlos y probar combinacion, para en caso de que sea mejor (es decir, tenga menor recorrido) se cambie.

*/

int main(void) {
	
	
	return 0;
}
