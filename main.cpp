// Integrantes
// Jesus Adrian Lopez Gaona A00835462
// Danna Karina Gonzales A

// Evidencia 2 / Actividad Integradora 2

#include <iostream>
#include <string>

using namespace std;

// MST
/*
Deberá el programa debe desplegar cuál es la forma óptima de cablear con una nueva fibra óptica conectando colonias de tal forma que se pueda compartir información entre cuales quiera dos colonias en el menor costo pósible, aprovechando que ya existen conexiones del nuevo cableado (las cuales no deben incluir en el costo)
*/

// TSP Kurskal
/*
Debido a que las ciudades apenas están entrando al mundo tecnológico, se requiere que alguien visite cada colonia que "no son centrales" para ir a dejar estados de cuenta físicos, publicidad, avisos y notificaciones impresos. por eso se quiere saber ¿cuál es la ruta más corta posible que visita cada colonia exactamente una vez y al finalizar regresa a la colonia origen? Tomar en cuenta que muchas veces el costo mínimo puede pasar por una colonia central o más intermedias. El programa debe desplegar la ruta a considerar así como el costo.
*/

// Floyd-Warshall
/*
El programa deberá generar la ruta óptima para ir de todas las centrales entre si, se puede pasar por una colonia no central.
*/


//
/*
Se leera a continuación una serie de puntos cartecianos en el mapa de la ciudad en donde se planea conectar nuevas colonias, y se deberá decir cual es la colina y punto carteciano más cercano con el cual se debe conectar.
*/





int main(){
    int n, m, k, q;
    //n = cantidad de colonias, 
    //m = número de conexiones entre colonias, 
    //k = las conexiones con el nuevo cableado, 
    //q = futuras nuevas colonias que se desean conectar.
    cin >> n >> m >> k >> q;
    

    for (int i = 0; i< n; i++){

        string nCol; // Nombre de colonia
        int x, y;
        bool isCentral;
        cin >> nCol >> x >> y >> isCentral;
    }
    
    for (int i = 0; i< m; i++){
        string conCol1;
        string conCol2;
        int cost;
        cin >> conCol1 >> conCol2 >> cost; // cLen can input as null aka " "
    
    }


    for (int i = 0; i< k; i++){
        string conCol1;
        string conCol2;
        cin >> conCol1 >> conCol2; // cLen can input as null aka " "
    }
    for (int i = 0; i< q; i++){
        string newCol;
        int x, y;
        cin >> newCol >> x >> y;
    }

    
    


    return 0;
}