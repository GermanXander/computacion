//     EJEMPLO DE ORDENAR LISTA ENLAZADA      //
//     =================================      //
//           Método de burbujas               //
//      Ing. Germán Andrés Xander 2026.       //

#include<iostream>
using namespace std;

struct datos {
    float valor;
    struct datos *pprox;
};

void agregar_final(datos *&puntero);
void listar(datos *puntero);
void ordenar(datos *&puntero);

int main() {
    char opcion;
    datos *lista = nullptr;          //creo el puntero en main()
    do {
        cout << "\t a para agregar al final" << endl
             << "\t l para listar" << endl
             << "\t o ordenar la lista" << endl;
        cin >> opcion;
        switch(opcion) {
        case 'a':
            agregar_final(lista);
            break;
        case 'l':
            listar(lista);
            break;
        case 'o':
            ordenar(lista);
            break;
        }
    } while(opcion != 's');
    return 0;
}

void agregar_final(datos *&puntero) { //paso por referencia para poder modificar "a dónde apunta"
    if(!puntero) {                   //la primer vez el puntero es nullptr y evalua por true.
        //"...the null pointer is implicitly converted into boolean false
        //while non-null pointers are converted into true..."
        puntero = new datos;          //para la primer instancia debo modificar "a dónde apunta" el puntero original (lista)
        cout << "ingrese valor" << endl;
        cin >> puntero->valor;
        puntero->pprox = nullptr;
    } else {                       // para las instancia posteriores debo trabajar sobre una copia del puntero
        datos *puntero2 = puntero;          // para no perder la dirección de la 1er instancia
        while(puntero2->pprox != 0) {     //me posiciono en la última instancia
            puntero2 = puntero2->pprox;
        }
        puntero2->pprox = new datos;      //solicito una nueva instancia y asigno la dirección en el puntero al prox de la última
        cout << "ingrese valor" << endl;
        cin >> puntero2->pprox->valor;
        puntero2->pprox->pprox = nullptr;
    }
}

void listar(datos *puntero) { //como no pasa por referencia no se alterar el original
    while(puntero != 0) {
        cout << "valor: " << puntero->valor << "\t dirección al próximo: " << puntero->pprox << endl;
        puntero = puntero->pprox;
    }
    cout << endl << endl;
}

void ordenar(datos *&puntero) {
    if(!puntero|| !puntero->pprox) {
        cout << "hay solo una instancia o no hay instancias" << endl;
        return;
    }

    bool intercambio;

    do {
        intercambio = false;
        datos *actual = puntero;
        datos *anterior = puntero;
        datos *siguiente;

        while (actual->pprox != nullptr) {
            if (actual->pprox->valor < actual->valor) { 
				// Intercambiar actual y actual->pprox
                siguiente = actual->pprox; //guardo el siguiente en puntero auxiliar
                actual->pprox = siguiente->pprox;
                siguiente->pprox = actual;

                if (anterior == puntero) { // es la 1er instancia
                    puntero = siguiente;
                } else {
                    anterior->pprox = siguiente;
                }

                // Actualizar punteros para continuar
                anterior = siguiente;
                // actual ahora es la instancia que se movió hacia adelante,
                // pero no avanzamos actual porque ya apunta a la que estaba después
                intercambio = true;
            } else {
                // No hay intercambio, avanzamos
                anterior = actual;
                actual = actual->pprox;
            }
        }
    } while (intercambio); // si intercambio es false significa que no se realizaron intercambios
						   // por ende la lista está ordenada
}
