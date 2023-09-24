#include <iostream>
#include <stack>
#include <cctype>
#include <cmath>
#include "arbol.h"

using namespace std;

// Definición de los métodos de Nodo
Nodo::Nodo(char _operador, int _valor) : operador(_operador), valor(_valor), izq(NULL), der(NULL) {}

bool Nodo::esOperador() { return operador != 0; }

char Nodo::getOperador() { return operador; }

int Nodo::getValor() { return valor; }

// Función auxiliar para determinar la precedencia de los operadores
int precedencia(char op)
{
    switch (op)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

Arbol::Arbol() : raiz(NULL), nnodos(0) {}

bool esAsociatividadIzquierda(char op)
{
    return op == '+' || op == '-' || op == '*' || op == '/';
}

bool esAsociatividadDerecha(char op)
{
    return op == '^';
}

void Arbol::construirArbolDesdeExpresion(const string &expresion)
{
    stack<Nodo *> valores;
    stack<Nodo *> operadores;

    for (int i = 0; i < expresion.length(); i++)
    {
        char c = expresion[i];
        
        if (isdigit(c))
        {
            int num = c - '0';  // Convierte el carácter numérico a int
            valores.push(new Nodo(0, num));
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        {
            bool condicionIzq = !esAsociatividadDerecha(c) && !operadores.empty() && precedencia(operadores.top()->getOperador()) >= precedencia(c);
            bool condicionDer = esAsociatividadDerecha(c) && !operadores.empty() && precedencia(operadores.top()->getOperador()) > precedencia(c);

            while (condicionIzq || condicionDer)
            {
                Nodo *operador = operadores.top();
                operadores.pop();
                operador->der = valores.top();
                valores.pop();
                if (valores.empty())
                {
                    cout << "----Problema de sintaxis----" << endl;
                    //return;
                }
                operador->izq = valores.top();
                valores.pop();
                valores.push(operador);

                // Actualizamos las condiciones para el bucle while
                condicionIzq = !esAsociatividadDerecha(c) && !operadores.empty() && precedencia(operadores.top()->getOperador()) >= precedencia(c);
                condicionDer = esAsociatividadDerecha(c) && !operadores.empty() && precedencia(operadores.top()->getOperador()) > precedencia(c);
            }
            
            operadores.push(new Nodo(c, 0));
        }
        else
        {
            cout << "----Problema de sintaxis----" << endl;
            //return;
        }
    }

    while (!operadores.empty())
    {
        Nodo *operador = operadores.top();
        operadores.pop();
        operador->der = valores.top();
        valores.pop();
        operador->izq = valores.top();
        valores.pop();
        valores.push(operador);
    }

    if (valores.size() != 1)
    {
        cout << "----Problema de sintaxis----" << endl;
        //return;
    }

    raiz = valores.top();
}


int Arbol::evaluar(Nodo *raiz)
{
    if (raiz == nullptr)
        return 0;
    if (raiz->izq == nullptr && raiz->der == nullptr)
        return raiz->valor;

    int valorIzquierdo = evaluar(raiz->izq);
    int valorDerecho = evaluar(raiz->der);

    switch (raiz->operador)
    {
    case '+': return valorIzquierdo + valorDerecho;
    case '-': return valorIzquierdo - valorDerecho;
    case '*': return valorIzquierdo * valorDerecho;
    case '/':
        if (valorDerecho == 0)
            throw runtime_error("División por cero");
        return valorIzquierdo / valorDerecho;
    case '^': return pow(valorIzquierdo, valorDerecho);
    default:
        throw runtime_error("Operador desconocido");
    }
}


int Arbol::evaluarExpresion()
{
    return evaluar(raiz);
}

stack<Nodo *> Arbol::obtenerRecorridoPosorden()
{
    stack<Nodo *> resultado;
    if (raiz == nullptr)
        return resultado;

    stack<Nodo *> s;
    s.push(raiz);

    while (!s.empty())
    {
        Nodo *nodo = s.top();
        s.pop();
        resultado.push(nodo);

        if (nodo->izq != nullptr)
            s.push(nodo->izq);
        if (nodo->der != nullptr)
            s.push(nodo->der);
    }

    return resultado;
}

void Arbol::mostrarPosord()
{
    stack<Nodo *> nodos = obtenerRecorridoPosorden();
    while (!nodos.empty())
    {
        Nodo *nodo = nodos.top();
        nodos.pop();
        if (nodo->esOperador())
        {
            cout << nodo->getOperador() << " ";
        }
        else
        {
            cout << nodo->getValor() << " ";
        }
    }
    cout << endl;
}
