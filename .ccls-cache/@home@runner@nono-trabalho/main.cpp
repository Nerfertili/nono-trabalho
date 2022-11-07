// Grafos - Lista de adjacência

#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <list>
#include <random>
#include <stack>
#include <vector>
#include <queue>

using namespace std;
class grafo_matriz {
public:
  vector<vector<int>> tab;
  vector<int> header;
  vector<int> rows;
  grafo_matriz(vector<int> vertices) {
    rows = vertices;
    vector<int> header = {-2};
    for (int i = 0; i < vertices.size(); i++) {
      header.push_back(vertices.at(i));
    }
    vector<int> row = header;
    tab.push_back(row);
    int row_ind = 0;
    for (int i = 0; i < vertices.size(); i++) {
      row = {};
      for (int w = 0; w < vertices.size(); w++) {
        if (w == 0) {
          row.push_back(vertices.at(row_ind));
          row_ind++;
        } else {
          row.push_back(0);
        }
      }
      tab.push_back(row);
    }
  }
  void adicionarAresta(int v1, int v2) {
    int v1_ind;
    int v2_ind;
    for (int i = 0; i < rows.size(); i++) {
      if (rows.at(i) == v1)
        v1_ind = i;
      if (rows.at(i) == v2)
        v2_ind = i;
    }
    tab.at(v2_ind + 1).at(v1_ind) = 1;
  }
  vector<vector<int>> get_tab() { return tab; }
};
class grafo_lista {
public:
  vector<int> vert;
  vector<vector<int>> adj;
  grafo_lista(vector<int> vert_) {
    vert = vert_;
    for (int i = 0; i < vert_.size(); i++) {
      adj.push_back({});
    }
  }
  void adicionarAresta(int v1, int v2) {
    int index;
    for (int i = 0; i < vert.size(); i++) {
      if (vert.at(i) == v1)
        index = i;
    }
    adj.at(index).push_back(v2);
  }
  vector<int> get_vert() { return vert; }
  vector<vector<int>> get_adj() { return adj; }
};

int buscar(stack<int> base, int searched) {
  int size = base.size();
  for (int i = 0; i < size; i++) {
    if (base.top() == searched) {
      return searched;
    }
    base.pop();
  }
  return 0;
}

void print_single(stack<int> base) {
  int size = base.size();
  for (int i = 0; i < size; i++) {
    cout << base.top() << "-";
    base.pop();
  }
}
void print_single(queue<int> base) {
  int size = base.size();
  for (int i = 0; i < size; i++) {
    cout << base.front() << "-";
    base.pop();
  }
}

int buscar(queue<int> base, int searched){
  int size = base.size();
  for (int i = 0; i < size; i++) {
    if (base.front() == searched) {
      return searched;
    }
    base.pop();
  }
  return 0;
}

void DFS(grafo_lista grafo){
  queue<int> visited;
  vector<int> vertices = grafo.get_vert();
  vector<vector<int>> adj = grafo.get_adj();
  int raiz = vertices[0];
  visited.push(raiz);
  int root_index;
  for (int i = 0; i < vertices.size(); i++) {
      if (vertices[i] == raiz)
        root_index = i;
    }
  vector<int> ligs;
  int current=raiz,current_index=root_index;
  bool valid;
  while (true){
    cout << "visited: ";
    print_single(visited);
    cout << endl;
    ligs = adj[current_index];
    valid=false;
    for(int i=0;i<ligs.size();i++){
      if(!buscar(visited,ligs[i])) {
        current = ligs[i];
        valid = true;
      }
    }
    if(valid){
      visited.push(current);
      for (int i = 0; i < vertices.size(); i++) {
        if (vertices[i] == current)
          current_index = i;
      }
    }
    else{
      current=raiz;
      current_index=root_index;
      ligs = adj[current_index];
      bool root_full=true;
      for(int i=0;i<ligs.size();i++){
        if(!buscar(visited,ligs[i])) {
          root_full = false;
        }
      }
      if(root_full){
        break;
      }
    }
  }
}

void BFS(grafo_lista grafo) {
  stack<int> visited;
  stack<int> to_visit;
  vector<int> vertices = grafo.get_vert();
  vector<vector<int>> adj = grafo.get_adj();
  to_visit.push(vertices[0]);
  // cout << vertices[0] << endl;
  int current, current_index;
  vector<int> current_ligs;

  while (to_visit.size() > 0) {
    cout << "to visit: ";
    print_single(to_visit);
    cout << endl << "visited: ";
    print_single(visited);
    cout << endl;
    current = to_visit.top();
    for (int i = 0; i < vertices.size(); i++) {
      if (vertices[i] == current)
        current_index = i;
    }
    current_ligs = adj[current_index];
    to_visit.pop();
    visited.push(current);
    for (int k = 0; k < current_ligs.size(); k++) {
      bool pres_visited = false, pres_to_visit = false;
      if (buscar(to_visit, current_ligs[k]))
        pres_to_visit = true;
      if (buscar(visited, current_ligs[k]))
        pres_visited = true;
      if (pres_visited == false && pres_to_visit == false) {
        to_visit.push(current_ligs[k]);
      }
    }
  }
}

int dis() {
  int aleatorio = 1 + rand() % 1000;
  return aleatorio;
}
int dis_2() {
  int aleatorio = 1 + rand() % 3;
  return aleatorio;
}
int dis_3() {
  int aleatorio = 1 + rand() % 20;
  return aleatorio;
}
int main() {
  auto inicio = std::chrono::high_resolution_clock::now();
  auto resultado = std::chrono::high_resolution_clock::now() - inicio;
  long long liliseconds =
      std::chrono::duration_cast<std::chrono::milliseconds>(resultado).count();

  vector<int> role;
  for (int i = 0; i < 20; i++) {
    role.push_back(dis());
  }

  grafo_lista grafo({});
  array<long long, 1> tempos;
  for (int j = 0; j < 1; j++) {
    inicio = std::chrono::high_resolution_clock::now();

    grafo_lista grafo(role);
    for (int i = 0; i < 20; i++) {
      for (int u = 0; u < dis_2(); u++) {
        grafo.adicionarAresta(role[i], role[dis_3()]);
      }
    }
    resultado = std::chrono::high_resolution_clock::now() - inicio;
    liliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(resultado)
            .count();
    tempos.at(j) = liliseconds;
    ofstream fw("lista_adjacencias.txt");
    vector<vector<int>> adj = grafo.get_adj();
    for (int w = 0; w < 20; w++) {
      fw << role[w] << " ";
      for (int k = 0; k < adj.at(w).size(); k++) {
        fw << adj.at(w).at(k) << " ";
      }
      fw << "\n";
    }
    cout << "DFS"<< endl;
    DFS(grafo);
    cout <<"\n\n\n\n" << "BFS"<< endl;
    BFS(grafo);
  }
  //*
  // for (int j = 1; j < 1; j++) {
  // tempos.at(0) = tempos.at(0) + tempos.at(j);
  //}
  // cout << "o tempo que levou para a execução da lista é : " << tempos[0] / 50
  //   << " milisegundos" << endl;
  //
}