#ifndef _CLASE_ORDENADOR
#define _CLASE_ORDENADOR
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "time.h"
using namespace std;

class Ordenador{
	private:

	//Defina aqu� los m�todos auxiliares de los algoritmos de ordenamiento solamente.
  //Puede definir cuantos m�todos quiera.

	//intercambiar
	void intercambiar(int *primero, int *segundo) {
		int temp = *primero;
		*primero = *segundo;
		*segundo = temp;
	}


	//Referencia: https://www.geeksforgeeks.org/3-way-merge-sort/
	//Creador del codigo original Rashmi Kumari

	void unir(int arreglo[], int primero, int mitad_prim, int mitad_sec, int ultimo, int arreglo_sec[]) {
  	int i = primero, j = mitad_prim, k = mitad_sec, l = primero;
    //Elemento minimo de los arreglos
    while ((i < mitad_prim) && (j < mitad_sec) && (k < ultimo)) {
        if(arreglo[i] < arreglo[j]) {
            if(arreglo[i] < arreglo[k]) {
                arreglo_sec[l++] = arreglo[i++];
            } else {
                arreglo_sec[l++] = arreglo[k++];
            }
        } else {
            if(arreglo[j] < arreglo[k]) {
                arreglo_sec[l++] = arreglo[j++];
            } else {
                arreglo_sec[l++] = arreglo[k++];
            }
        }
    }
		//Datos del primero al segundo
    while ((i < mitad_prim) && (j < mitad_sec)) {
        if(arreglo[i] < arreglo[j]) {
            arreglo_sec[l++] = arreglo[i++];
        } else {
            arreglo_sec[l++] = arreglo[j++];
        }
    }
		//Datos del segundo al tercero
    while ((j < mitad_sec) && (k < ultimo)) {
        if(arreglo[j] < arreglo[k]) {
            arreglo_sec[l++] = arreglo[j++];
        } else {
            arreglo_sec[l++] = arreglo[k++];
        }
    }
		//Datos del primero al tercero
    while ((i < mitad_prim) && (k < ultimo)) {
        if(arreglo[i] < arreglo[k]) {
            arreglo_sec[l++] = arreglo[i++];
        } else {
            arreglo_sec[l++] = arreglo[k++];
        }
    }

    // Primer arreglo
    while (i < mitad_prim)
        arreglo_sec[l++] = arreglo[i++];

    // Segundo arreglo
    while (j < mitad_sec)
        arreglo_sec[l++] = arreglo[j++];

    //Tercer arreglo
    while (k < ultimo)
        arreglo_sec[l++] = arreglo[k++];
	}

	void acomodar(int arreglo[], int primero, int ultimo, int arreglo_sec[]) {
    //Arreglo vacio.
    if (ultimo - primero < 2)
        return;

    // separar arreglo
    int mitad_prim = primero + ((ultimo - primero) / 3);
    int mitad_sec = primero + 2 * ((ultimo - primero) / 3) + 1;

    // Acomodar los 3 arreglos
    acomodar(arreglo_sec, primero, mitad_prim, arreglo);
    acomodar(arreglo_sec, mitad_prim, mitad_sec, arreglo);
    acomodar(arreglo_sec, mitad_sec, ultimo, arreglo);

    // Unir los 3 arreglos al arreglo final
    unir(arreglo_sec, primero, mitad_prim, mitad_sec, ultimo, arreglo);
	}

	void heap(int arreglo[], int tamano, int i) {
    int mayor = i;
    int izq = 2*i + 1; // izquierda
    int der = 2*i + 2; // derecha
    //Si izquiera es mayor
    if (izq < tamano && arreglo[izq] > arreglo[mayor])
      mayor = izq;
    //Si derecha es mayor
    if (der < tamano && arreglo[der] > arreglo[mayor])
      mayor = der;
    // Si mayor no es i
    if (mayor != i) {
      swap(arreglo[i], arreglo[mayor]);
      // Recursivo
      heap(arreglo, tamano, mayor);
    }
	}

	int getMaximo(int arreglo[], int tamano) {
    int max = arreglo[0];
    for (int i = 1; i < tamano; i++){
      if (arreglo[i] > max){
        max = arreglo[i];
			}
		}
    return max;
	}

	void contar(int arreglo[], int tamano, int exp) {
	  int temporal[tamano];
	  int temporal2[10];
	  int i;
	  for (i = 0; i < tamano; i++)
	      temporal2[ (arreglo[i]/exp)%10 ]++;
	  for (i = 1; i < 10; i++)
	      temporal2[i] += temporal2[i - 1];
	  for (i = tamano - 1; i >= 0; i--){
	      temporal[temporal2[ (arreglo[i]/exp)%10 ] - 1] = arreglo[i];
	      temporal2[ (arreglo[i]/exp)%10 ]--;
	  }

	  for (i = 0; i < tamano; i++){
	      arreglo[i] = temporal[i];
	  }
	}

	void residuos(int arreglo[], int tamano, int exp){
    int temporal[tamano]; //arreglo temporal
    int i, count[10] = {0};

    for (i = 0; i < tamano; i++){
      count[ (arreglo[i]/exp)%10 ]++;
		}

    for (i = 1; i < 10; i++){
      count[i] += count[i - 1];
		}

    for (i = tamano - 1; i >= 0; i--){
      temporal[count[ (arreglo[i]/exp)%10 ] - 1] = arreglo[i];
      count[ (arreglo[i]/exp)%10 ]--;
    }

    for (i = 0; i < tamano; i++){
      arreglo[i] = temporal[i];
		}
	}

	void invertir(int arreglo[], int tamano){
		for (int primero = 0, ultimo = tamano - 1; primero < ultimo; primero++, ultimo--) {
			swap(arreglo[primero], arreglo[ultimo]);
		}
	}

	public:

	Ordenador(){};
	~Ordenador(){};

	//Si piensa no implementar algunos de los m�todos de ordenamiento, no los borre,
	//simplemente d�jelos con el cuerpo vac�o para evitar errores de compilaci�n, ya
	//que se va a ejecutar el mismo �main� para todas las tareas.

	/*
	* Algoritmo de Seleccion
	*/

	void seleccion(int * arreglo, int tamano) {
		//Declaracion de variables a utilizar
		int contador;
		int contador_sec;
		int minimo;

		for (contador = 0; contador < tamano-1; contador++) {
			//entontrar el numero minimo
			minimo = contador;
			for (contador_sec = contador + 1; contador_sec < tamano; contador_sec++)
				if (arreglo[contador_sec] < arreglo[minimo]) {
					minimo = contador_sec;
				}
			//Intercambiar minimo con el primer elemento
			intercambiar(&arreglo[minimo], &arreglo[contador]);
		}
	};

	/*
	* Algoritmo de Insercion
	*/

	void insercion(int * arreglo, int tamano){
		//Declaracion de variables a utilizar
		int contador;
		int llave;
		int contador_sec;

		for (contador = 1; contador < tamano; contador++) {
			llave = arreglo[contador];
			contador_sec = contador - 1;
			while (contador_sec >= 0 && arreglo[contador_sec] > llave) {
					arreglo[contador_sec + 1] = arreglo[contador_sec];
					contador_sec = contador_sec - 1;
			}
			arreglo[contador_sec + 1] = llave;
		}
	};

	/*
	* Algoritmo de MergeSort/Mezcla
	*/

	void mergesort(int * arreglo, int tamano){
		//Buscar si el arreglo es vacio
		if (tamano == 0)
			return;
		//Crear segundo arreglo
		int arreglo2[tamano];
    for (int i = 0; i < tamano; i++)
        arreglo2[i] = arreglo[i];
    acomodar(arreglo2, 0, tamano, arreglo);
    for (int i = 0; i < tamano; i++)
        arreglo[i] = arreglo2[i];
	};

	/*
	* Algoritmo de Heapsort/Monticulos
	*/

	void heapsort(int * arreglo, int tamano){
		//Acomodar arreglo
    for (int i = tamano / 2 - 1; i >= 0; i--) {
      heap(arreglo, tamano, i);
		}
    // Extraer cada numero del arreglo
    for (int i = tamano - 1; i > 0; i--) {
      //Intercambiar al final
      intercambiar(&arreglo[0], &arreglo[i]);
      //Llamar al maximo en el arreglo reducido
      heap(arreglo, i, 0);
		}
	};

	/*
	* Algoritmo de QuickSort/Rapido
	*/

	void quicksort(int * arreglo, int tamano){
  	int pivote = arreglo[tamano-1];
    int indiceMayor = 0;
    for (int i = 0; i < tamano-1; i++){
      if (arreglo[i] < pivote){
        intercambiar(&arreglo[i], &arreglo[indiceMayor]);
        indiceMayor++;
    	}
    }
    intercambiar(&arreglo[indiceMayor], &arreglo[tamano-1]);
    if (indiceMayor > 1){
    	quicksort(arreglo, indiceMayor);
		}
    if (tamano-indiceMayor-1 > 1) {
      quicksort(arreglo+indiceMayor+1, tamano-indiceMayor-1);
		}
  };

	/*
	* Algoritmo de RadixSort/Residuos
	*/

	void radixsort(int * arreglo, int tamano){
		int i;
		int q = 0; //para ordenar negativos
    int maxPos;
    int maxNeg;
    int j = 0; //contador
    int k = 0; //contador
    int cantidadNegativos = 0;

    //Busca cuantos numeros son negativos en el arreglo
    for(i = 0; i < tamano; i++) {
      if(arreglo[i] < 0)
        cantidadNegativos++;
    }

    //Crear 2 arreglos para positivos y negativos
    int arregloPos[tamano - cantidadNegativos];
    int arregloNeg[cantidadNegativos];

      for(i = 0; i < tamano; i++) {
        if(arreglo[i] < 0) {
          arregloNeg[j] = arreglo[i];
          j++;
      }
        else {
          arregloPos[k] = arreglo[i];
          k++;
        }
      }

			//Quita el signo a los numeros
      for (i = 0; i < cantidadNegativos; i++) {
        arregloNeg[i] = arregloNeg[i] * -1;
      }

      //Busca los valores maximos de cada arreglo
      maxNeg = getMaximo(arregloNeg, cantidadNegativos);
      maxPos = getMaximo(arregloPos, tamano - cantidadNegativos);

			//ordena los numeros negativos
      for (int exp = 1; maxPos/exp > 0; exp *= 10) {
        residuos(arregloPos, tamano - cantidadNegativos, exp);
      }
			//ordena los numeros negativos
      for (int exp = 1; maxNeg/exp > 0; exp *= 10) {
        residuos(arregloNeg, cantidadNegativos, exp);
      }
			//Invierte los numeros negativos para luego poner signos
      invertir(arregloNeg, cantidadNegativos);

      //Vuelve a poner el signo a los numeros negativos ya ordenados
      for(i = 0; i < cantidadNegativos; i++) {
        arregloNeg[i] = arregloNeg[i] * -1;
      }

			//Junta los 2 arreglos en el arreglo original
      for(i = 0; i < cantidadNegativos; i++) {
        arreglo[i] = arregloNeg[i];
      }
      for(i = cantidadNegativos; i < tamano; i++) {
        arreglo[i] = arregloPos[q];
        q++;
      }
	};

};

#endif
