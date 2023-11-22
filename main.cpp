// Integrantes:
// Jesus Adrian Lopez Gaona A00835462
// Danna Karina Gonzales A

// Evidencia 2 / Actividad Integradora 2

#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>

using namespace std;

// data structures
struct Colony{
    string name;
    int x, y;
    bool isCentral;
};
struct Conexion {
    string colony1, colony2;
    int cost;
    bool isNewCabling; // Para saber si es del nuevo cableado
};





// MST
/*
Deberá el programa debe desplegar cuál es la forma óptima de cablear con una nueva fibra óptica conectando colonias de tal forma que se pueda compartir información entre cuales quiera dos colonias en el menor costo pósible, aprovechando que ya existen conexiones del nuevo cableado (las cuales no deben incluir en el costo)
*/
// find the Optimal Cabling
string MST(const vector<Conexion>& conexiones) {
    string test = "test";
    return test;
}

// TSP Kurskal
/*
Debido a que las ciudades apenas están entrando al mundo tecnológico, se requiere que alguien visite cada colonia que "no son centrales" para ir a dejar estados de cuenta físicos, publicidad, avisos y notificaciones impresos. por eso se quiere saber ¿cuál es la ruta más corta posible que visita cada colonia exactamente una vez y al finalizar regresa a la colonia origen? Tomar en cuenta que muchas veces el costo mínimo puede pasar por una colonia central o más intermedias. El programa debe desplegar la ruta a considerar así como el costo.
*/
string TSP(const vector<Colony>& colonies) {
    string test = "test";
    return test;
}

// Floyd-Warshall
/*
El programa deberá generar la ruta óptima para ir de todas las centrales entre si, se puede pasar por una colonia no central.
*/
// find the s hortest path between central colonies
string FloydWarshall(const vector<Colony>& colonies, const vector<Conexion>& conexiones) {
    string test = "test";
    return test;
}


//
/*
Se leera a continuación una serie de puntos cartecianos en el mapa de la ciudad en donde se planea conectar nuevas colonias, y se deberá decir cual es la colina y punto carteciano más cercano con el cual se debe conectar.
*/
string connectNewColonies(const vector<Colony>& colonies, const vector<Colony>& newColonies) {
    string test = "test";
    return test;
}




int main(){
    int n, m, k, q;
    //n = cantidad de colonias, 
    //m = número de conexiones entre colonias, 
    //k = las conexiones con el nuevo cableado, 
    //q = futuras nuevas colonias que se desean conectar.
    cin >> n >> m >> k >> q;
    

    vector<Colony> colonies(n);
    for (int i = 0; i < n; i++) {
        cin >> colonies[i].name >> colonies[i].x >> colonies[i].y >> colonies[i].isCentral;
    }

    vector<Conexion> conexiones(m);
    for (int i = 0; i < m; i++) {
        cin >> conexiones[i].colony1 >> conexiones[i].colony2 >> conexiones[i].cost;
        conexiones[i].isNewCabling = false; // Por defecto, no es nuevo cableado
    }

    
    for (int i = 0; i < k; i++) {
        string col1, col2;
        cin >> col1 >> col2;
        // Marcar las conexiones como nuevo cableado
        auto it = find_if(conexiones.begin(), conexiones.end(), [&](const Conexion& c) {
            return (c.colony1 == col1 && c.colony2 == col2) || (c.colony1 == col2 && c.colony2 == col1);
        });
        if (it != conexiones.end()) {
            it->isNewCabling = true;
        }
    }

    vector<Colony> newColonies(q);
    for (int i = 0; i < q; i++) {
        cin >> newColonies[i].name >> newColonies[i].x >> newColonies[i].y;
        newColonies[i].isCentral = false;  // Asumiendo que las nuevas colonias no son centrales
    }




    ofstream outputFile("checking2.txt");
    if (outputFile.is_open()) {
        outputFile << "-------------------\n";
        outputFile << "1 - Cableado óptimo de nueva conexión.\n";
        outputFile << MST(conexiones) << "\n";
        outputFile << "-------------------\n";
        outputFile << "2 - La ruta óptima.\n";
        outputFile << TSP(colonies) << "\n";
        outputFile << "-------------------\n";
        outputFile << "3 - Caminos más cortos entre centrales.\n";
        outputFile << FloydWarshall(colonies, conexiones) << "\n";
        outputFile << "-------------------\n";
        outputFile << "4 - Conexión de nuevas colonias.\n";
        outputFile << connectNewColonies(colonies, newColonies) << "\n";
        outputFile << "-------------------\n";
        outputFile.close();
    } else {
        cout << "Failed to open the output file.\n";
        return 1;
    }            


    return 0;
}