#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <Windows.h>
#define ANCHO 59
#define ALTO 25

using namespace std;

const int tablaAncho = 5;
const int tablaAlto = 5;
const int separacionVertical = 1;
const char simboloJugador = '$';
const char simboloMeta = '#';
const int vidasIniciales = 8;

void gotoxy(int x, int y)
{
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hCon, dwPos);
}

void dibujarTabla(int tabla[tablaAlto][tablaAncho], int filaJugador, int columnaJugador)
{
    int anchoCelda = 4;

    for (int i = 0; i < tablaAlto; i++)
    {
        for (int k = 0; k < separacionVertical; k++)
        {
            for (int j = 0; j < tablaAncho; j++)
            {
                cout << "|";
                for (int l = 0; l < anchoCelda; l++)
                {
                    cout << "-";
                }
            }
            cout << "|" << endl;
        }

        for (int j = 0; j < tablaAncho; j++)
        {
            cout << "|";
            gotoxy(j * (anchoCelda + 1) + 1, i * (separacionVertical + 1) + 1);

            if (i == filaJugador && j == columnaJugador)
            {
                cout << setw(anchoCelda) << setfill(' ') << simboloJugador;
            }
            else if (i >= filaJugador - 1 && i <= filaJugador + 1 && j >= columnaJugador - 1 && j <= columnaJugador + 1)
            {
                int numero = tabla[i][j];
                if (numero != 0)
                {
                    cout << setw(anchoCelda) << setfill(' ') << numero;
                }
                else
                {
                    cout << string(anchoCelda, ' ');
                }
            }
            else if (tabla[i][j] == 9)
            {
                cout << setw(anchoCelda) << setfill(' ') << simboloMeta;
            }
            else
            {
                cout << string(anchoCelda, ' ');
            }

            for (int k = 0; k < separacionVertical; k++)
            {
                cout << " ";
            }
        }
        cout << "|" << endl;
    }

    for (int k = 0; k < separacionVertical; k++)
    {
        for (int j = 0; j < tablaAncho; j++)
        {
            cout << "+";
            for (int l = 0; l < anchoCelda; l++)
            {
                cout << "-";
            }
        }
        cout << "+" << endl;
    }
}

void llenarTablaRandom(int tabla[tablaAlto][tablaAncho])
{
    srand(time(0));

    for (int i = 0; i < tablaAlto; i++)
    {
        for (int j = 0; j < tablaAncho; j++)
        {
            tabla[i][j] = rand() % 9 + 1;
        }
    }


    int filaMeta = rand() % tablaAlto;
    int columnaMeta = rand() % tablaAncho;
    tabla[filaMeta][columnaMeta] = 9;
}

bool validarOperacion(int tabla[tablaAlto][tablaAncho], int filaJugador, int columnaJugador)
{
    int suma = 0;
    int multiplicacion = 1;

    for (int i = filaJugador - 1; i <= filaJugador + 1; i++)
    {
        for (int j = columnaJugador - 1; j <= columnaJugador + 1; j++)
        {
            if (i >= 0 && i < tablaAlto && j >= 0 && j < tablaAncho && !(i == filaJugador && j == columnaJugador))
            {
                suma += tabla[i][j];
            }
        }
    }

    multiplicacion = suma * tabla[filaJugador][columnaJugador];

    int respuesta;
    cout << "Operación: (";
    if (filaJugador > 0) {
        cout << tabla[filaJugador - 1][columnaJugador];
    } else {
        cout << "0";
    }
    cout << " + ";
    if (columnaJugador > 0) {
        cout << tabla[filaJugador][columnaJugador - 1];
    } else {
        cout << "0";
    }
    cout << " + ";
    if (filaJugador < tablaAlto - 1) {
        cout << tabla[filaJugador + 1][columnaJugador];
    } else {
        cout << "0";
    }
    cout << ") * ";
    if (columnaJugador < tablaAncho - 1) {
        cout << tabla[filaJugador][columnaJugador + 1];
    } else {
        cout << "0";
    }
    cout << " = ";
    cin >> respuesta;

    return respuesta == multiplicacion;
}

int main()
{
    system("cls");
    system("color 90");


    int tabla[tablaAlto][tablaAncho] = {{0}};
    int filaJugador = 3;
    int columnaJugador = 2;
    int vidas = vidasIniciales;

    llenarTablaRandom(tabla);

    while (true)
    {
        system("cls");
        dibujarTabla(tabla, filaJugador, columnaJugador);

        cout << "Vidas restantes: " << vidas << endl;

        char movimiento;
        cout << "Ingrese el movimiento (8 - Arriba, 2 - Abajo, 4 - Izquierda, 6 - Derecha): ";
        cin >> movimiento;

        int nuevaFilaJugador = filaJugador;
        int nuevaColumnaJugador = columnaJugador;

        if (movimiento == '8' || movimiento == '8')
        {
            nuevaFilaJugador--;
        }
        else if (movimiento == '2' || movimiento == '2')
        {
            nuevaFilaJugador++;
        }
        else if (movimiento == '4' || movimiento == '4')
        {
            nuevaColumnaJugador--;
        }
        else if (movimiento == '6' || movimiento == '6')
        {
            nuevaColumnaJugador++;
        }
        else
        {
            cout << "Movimiento no válido. Intente nuevamente." << endl;
            continue;
        }

        if (nuevaFilaJugador < 0 || nuevaFilaJugador >= tablaAlto || nuevaColumnaJugador < 0 || nuevaColumnaJugador >= tablaAncho)
        {
            cout << "Movimiento no válido. Intente nuevamente." << endl;
            continue;
        }

        if (!validarOperacion(tabla, nuevaFilaJugador, nuevaColumnaJugador))
        {
            cout << "Respuesta incorrecta. Pierdes una vida." << endl;
            vidas--;
            if (vidas == 0)
            {
                cout << "¡Perdiste todas tus vidas! Fin del juego." << endl;
                break;
            }
        }

        filaJugador = nuevaFilaJugador;
        columnaJugador = nuevaColumnaJugador;

        if (tabla[filaJugador][columnaJugador] == 9)
        {
            cout << "¡Has llegado a la meta! ¡Ganaste!" << endl;
            break;
        }
    }

    return 0;
}
