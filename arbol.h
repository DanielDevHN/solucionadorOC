#ifndef ARBOL_H
#define ARBOL_H

#include <iostream>
#include <stack>
#include <string>

using namespace std;

class Nodo {
private:
    char operador;
    int valor;
    Nodo* izq;
    Nodo* der;

public:
    Nodo(char _operador, int _valor);
    bool esOperador();
    char getOperador();
    int getValor();
    
    friend class Arbol; 
};

class Arbol {
private:
    Nodo* raiz;         
    int nnodos;          
    int evaluar(Nodo*);  

public:
    Arbol();
    void construirArbolDesdeExpresion(const string&);
    void mostrarPosord();
    int evaluarExpresion();
    stack<Nodo*> obtenerRecorridoPosorden();
};

#endif // ARBOL_H
