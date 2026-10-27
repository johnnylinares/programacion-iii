#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct impresion {
	int id;
	string nombre;
	string usuario;
	int paginas;
};

class cola {
	private:
		int frente;
		int final;
		int max;
		char *elementos;
	public:
		// Constructor
		cola(int maximo){		
			max = maximo;
			elementos = new char[max];
			frente = 0;
			final = 0; // Inicialmente vacia
		}
		//Destructor
		~cola(){
			delete[] elementos;
		}
		
		// Metodos principales
		bool vacia(){
			return (frente == final);
		}
		
		bool llena(){
			return (final == max);
		}
		
		// Metodos secundarios
		void insertar(char valor){
			if (llena()) cout << "Error: La cola esta llena." << endl;
			else {
				elementos[final] = valor;
				final++;
			}
		}
		
		char remover(){
			if (vacia()) {
				cout << "Error: La cola esta vacia." << endl;
				return '\0';
			} else {
				char valor = elementos[frente];
				frente++;
				reacomodar();
				return valor;
			}
		}
		
		void reacomodar(){
			if (vacia()) return;
			
			if (frente == 0) return;
			
			int j = 0;
			for (int i = frente; i < final; i++) {
				elementos[j++] = elementos[i];
			}
			
			final = j;
			frente = 0;
		}
};

int main(){
	/* 
		*/
	
	cola c1(3);
	
	c1.insertar('a');
	c1.insertar('b');
	c1.insertar('c');
	c1.insertar('d');
	
	cout << c1.remover() << endl;
	cout << c1.remover() << endl;
	cout << c1.remover() << endl;
	cout << c1.remover() << endl;
	
	return 0;
}
