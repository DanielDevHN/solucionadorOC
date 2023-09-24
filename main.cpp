#include <iostream>
#include <string>
#include "arbol.h"

using namespace std;

int main() {
    char respuesta;

    do {
        cout << "--- Calculadora de expresiones aritmeticas ---\n";
        cout << "Ingrese una operacion compuesta:\n> ";
        string expresion;
        getline(cin, expresion);

        Arbol arbol;
        arbol.construirArbolDesdeExpresion(expresion);

        try {
            cout << "> " << arbol.evaluarExpresion() << endl;
        } catch (const exception& e) {
            cout << "----Problema de sintaxis----\nPresione una tecla para continuar...";
            cin.ignore();
            continue;
        }

        cout << "Desea realizar otra operacion? (s/n): ";
        cin >> respuesta;
        cin.ignore();
        system("cls");

    } while (respuesta == 's' || respuesta == 'S');

    return 0;
}
