// Actividad Integradora 2
// Integrantes de equipo:
// Jesus Adrian Lopez Gaona		      | A00835462
// Danna Karina González Valencia 	| A00833606

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

// -------------------------------------------------------------------------------------------
//Inciso 1
struct Colony {
  string name;
  int x, y;
  bool isCentral;
};
struct Conexion {
  string colony1, colony2;
  int cost;
  bool isNewCabling; // Para saber si es del nuevo cableado
};
struct Edge {
  int src, dest, weight;
  bool isNewCabling;
  bool operator<(const Edge &other) const {
    if (isNewCabling != other.isNewCabling)
      return isNewCabling > other.isNewCabling; 
    return weight < other.weight;
  }
};
struct DisjointSets {
  vector<int> parent, rank;
  int n;

  DisjointSets(int n) : n(n), parent(n), rank(n, 0) {
    for (int i = 0; i < n; i++) {
      parent[i] = i;
    }
  }

  
  int find(int u) {
    if (u != parent[u])
      parent[u] = find(parent[u]); 
    return parent[u];
  }
  void merge(int x, int y) {
    x = find(x), y = find(y);

    if (rank[x] > rank[y])
      parent[y] = x;
    else
      parent[x] = y;

    if (rank[x] == rank[y])
      rank[y]++;
  }
};


string MST(vector<Conexion> &conexiones, const unordered_map<string, int> &colonyIndex) {
  int n = colonyIndex.size(); 
  vector<Edge> edges;
  string result;

  
  vector<string> indextoCol(n);
  for (const auto &pair : colonyIndex) {
    indextoCol[pair.second] = pair.first;
  }


  for (const auto &conn : conexiones) {
    int srcIdx = colonyIndex.at(conn.colony1);
    int destIdx = colonyIndex.at(conn.colony2);
    edges.push_back({srcIdx, destIdx, conn.cost, conn.isNewCabling});
  }

  
  sort(edges.begin(), edges.end());

  DisjointSets ds(n);

  int totalCost = 0;
  for (const auto &e : edges) {
    int set_u = ds.find(e.src);
    int set_v = ds.find(e.dest);

    
    if (set_u != set_v) {
      if (!e.isNewCabling) {
        result += indextoCol[e.src] + " - " + indextoCol[e.dest] +
                  " " + to_string(e.weight) + "\n";
        totalCost += e.weight;
      }
      ds.merge(set_u, set_v);
    }
  }

  result += "Costo Total: " + to_string(totalCost) + "\n";
  return result;
}


// -------------------------------------------------------------------------------------------
// Inciso 2


struct TSPNode {
    vector<bool> visited;
    vector<int> path;
    int position;
    int cost;
    int level;

    // Operador para comparar en la cola de prioridad (menor costo es mejor)
    bool operator<(const TSPNode& other) const {
        return cost > other.cost;
    }
};

pair<int, vector<int>> TSP(const vector<vector<int>>& matrix) {
    priority_queue<TSPNode> pq;
    TSPNode start = {/*visited=*/vector<bool>(matrix.size(), false), /*path=*/{}, /*position=*/0, /*cost=*/0, /*level=*/0};
    start.visited[0] = true;
    start.path.push_back(0);
    pq.push(start);

    int minCost = INT_MAX;
    vector<int> minPath;

    while (!pq.empty()) {
        TSPNode current = pq.top();
        pq.pop();

        if (current.level == matrix.size() - 1) {
            int returnCost = matrix[current.position][0];
            if (current.cost + returnCost < minCost) {
                minCost = current.cost + returnCost;
                minPath = current.path;
                minPath.push_back(0); 
            }
            continue;
        }

        for (int i = 0; i < matrix.size(); i++) {
            if (!current.visited[i]) {
                TSPNode next = current;
                next.level++;
                next.visited[i] = true;
                next.position = i;
                next.cost += matrix[current.position][i];
                next.path.push_back(i);
                pq.push(next);
            }
        }
    }

    return {minCost, minPath};
}


// -------------------------------------------------------------------------------------------
// Inciso 3

string FloydWarshall(const vector<Colony> &colonies, const vector<Conexion> &conexiones, const unordered_map<string, int> &colonyIndex) {
  const int INF = 1e9;
  int n = colonies.size();
  vector<vector<int>> dist(n, vector<int>(n, INF));
  vector<vector<int>> next(n, vector<int>(n, -1)); // Para reconstruir la ruta

  // Inicializar la matriz de distancias y la matriz next
  for (const auto &conn : conexiones) {
    int u = colonyIndex.at(conn.colony1);
    int v = colonyIndex.at(conn.colony2);
    dist[u][v] = conn.cost;
    dist[v][u] = conn.cost;
    next[u][v] = v;
    next[v][u] = u;
  }
  for (int i = 0; i < n; i++) {
    dist[i][i] = 0;
  }

  //Floyd-Warshall
  for (int k = 0; k < n; k++) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (dist[i][k] + dist[k][j] < dist[i][j]) {
          dist[i][j] = dist[i][k] + dist[k][j];
          next[i][j] = next[i][k];
        }
      }
    }
  }

  // Función auxiliar para reconstruir la ruta
  auto getPath = [&](int u, int v) {
    vector<int> path;
    if (next[u][v] == -1)
      return path;
    path.push_back(u);
    while (u != v) {
      u = next[u][v];
      path.push_back(u);
    }
    return path;
  };

  // print para archivo
  string result;
  for (int i = 0; i < n; i++) {
    if (!colonies[i].isCentral)
      continue;
    for (int j = i + 1; j < n; j++) {
      if (!colonies[j].isCentral)
        continue;
      auto path = getPath(i, j);
      result += colonies[i].name + " - ";
      for (int k = 0; k < path.size(); k++) {
        if (k > 0)
          result += " - ";
        result += colonies[path[k]].name;
      }
      result += " (" + to_string(dist[i][j]) + ")\n";
    }
  }

  return result;
}

// -------------------------------------------------------------------------------------------
//Inciso 4
double euclideanDistance(int x1, int y1, int x2, int y2) {
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}


string connectNewColonies(const vector<Colony> &colonies, const vector<Colony> &newColonies) {
  string result;
  for (const auto &newCol : newColonies) {
    double minDist = numeric_limits<double>::max();
    string closestCol;
    for (const auto &colony : colonies) {
      double dist =
          euclideanDistance(colony.x, colony.y, newCol.x, newCol.y);
      if (dist < minDist) {
        minDist = dist;
        closestCol = colony.name;
      }
    }
    result += newCol.name + " debe conectarse con " + closestCol + "\n";
  }
  return result;
}

int main() {
  int n, m, k, q;
  cin >> n >> m >> k >> q;

  vector<Colony> colonies(n);
  for (int i = 0; i < n; i++) {
    cin >> colonies[i].name >> colonies[i].x >> colonies[i].y >>
        colonies[i].isCentral;
  }

  vector<Conexion> conexiones(m);
  for (int i = 0; i < m; i++) {
    cin >> conexiones[i].colony1 >> conexiones[i].colony2 >> conexiones[i].cost;
    conexiones[i].isNewCabling = false;
  }


  for (int i = 0; i < k; i++) {
    string col1, col2;
    cin >> col1 >> col2;

    for (int j = 0; j < conexiones.size(); j++) {
        if ((conexiones[j].colony1 == col1 && conexiones[j].colony2 == col2) || 
            (conexiones[j].colony1 == col2 && conexiones[j].colony2 == col1)) {
            conexiones[j].isNewCabling = true;
            break; 
        }
    }
}


  vector<Colony> newColonies(q);
  for (int i = 0; i < q; i++) {
    cin >> newColonies[i].name >> newColonies[i].x >> newColonies[i].y;
    newColonies[i].isCentral =
        false; 
  }

  unordered_map<string, int> colonyIndex;
  for (int i = 0; i < n; ++i) {
    colonyIndex[colonies[i].name] = i;
  }

  vector<Colony> ncCol;
  unordered_map<string, int> nonCenIndx;
  int noCentCont = 0;

  for (int i = 0; i < colonies.size(); i++) {
      if (!colonies[i].isCentral) {
          ncCol.push_back(colonies[i]);
          nonCenIndx[colonies[i].name] = noCentCont++;
      }
  }

  vector<vector<int>> tspAdjMat(noCentCont, vector<int>(noCentCont, INT_MAX));

  for (int i = 0; i < conexiones.size(); i++) {
      if (nonCenIndx.find(conexiones[i].colony1) != nonCenIndx.end() &&
          nonCenIndx.find(conexiones[i].colony2) != nonCenIndx.end()) {
          int u = nonCenIndx[conexiones[i].colony1];
          int v = nonCenIndx[conexiones[i].colony2];
          tspAdjMat[u][v] = conexiones[i].cost;
          tspAdjMat[v][u] = conexiones[i].cost;
      }
  }


  ofstream outputFile("checking2.txt");
  if (outputFile.is_open()) {
    outputFile << "-------------------\n";
    outputFile << "1 - Cableado óptimo de nueva conexión.\n";
    outputFile << MST(conexiones, colonyIndex) << "\n";
    outputFile << "-------------------\n";
    outputFile << "2 - La ruta óptima.\n";
    auto [tspCost, tspPath] = TSP(tspAdjMat);
    for (int i = 0; i < tspPath.size(); i++) {
      if (i > 0) {
        outputFile << " - ";
      }
      outputFile << ncCol[tspPath[i]].name;
    }
    outputFile << "\nLa Ruta Óptima tiene un costo total de: " << tspCost << "\n";
    outputFile << "-------------------\n";
    outputFile << "3 - Caminos más cortos entre centrales.\n";
    outputFile << FloydWarshall(colonies, conexiones, colonyIndex) << "\n";
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

/*

Input EX:

5 8 1 2
LindaVista 200 120 1
Purisima 150 75 0
Tecnologico -50 20 1
Roma -75 50 0
AltaVista -50 40 0
LindaVista Purisima 48
LindaVista Roma 17
Purisima Tecnologico 40
Purisima Roma 50
Purisima AltaVista 80
Tecnologico Roma 55
Tecnologico AltaVista 15
Roma AltaVista 18
Purisima Tecnologico
Independencia 180 -15
Roble 45 68

Output EX:

-------------------
1 – Cableado óptimo de nueva conexión.
Tecnologico - AltaVista 15
LindaVista - Roma 17
Roma - AltaVista 18
Costo Total: 50
-------------------
2 – La ruta óptima.
Purisima - Roma - AltaVista - Tecnologico - Purisima
La Ruta Óptima tiene un costo total de: 123
-------------------
3 – Caminos más cortos entre centrales.
LindaVista - Roma - AltaVista - Tecnologico (50)
-------------------
4 – Conexión de nuevas colonias.
Independencia debe conectarse con Purisima
Roble debe conectarse con AltaVista
-------------------

*/