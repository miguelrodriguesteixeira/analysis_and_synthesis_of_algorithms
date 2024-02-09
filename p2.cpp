/*************************************
* ASA 2022/2023                      *
* Miguel Teixeira - 103449           *
* Miguel Noronha - 103192            *
* Segundo Projeto - p2               *
*************************************/
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Par de vertices (arcos)
typedef pair<int, int> Par;

/* Estrutura para representar um grafo */
struct Grafo {
    int V, E;
    vector <pair<int, Par>> arcos; // vetor para guardar os arcos
  
    // Construtor
    Grafo(int V, int E) {
        this->V = V;
        this->E = E;
    }
  
    // Adicionar um arco ao grafo
    void addArco(int v1, int v2, int w) {
        arcos.push_back({w, {v1, v2}});
    }
  
    // Algoritmo Kraskal
    int KruskalMST();
};
  

/* Estrutura para representar os conjuntos disjuntos */
struct ConjuntosDisjuntos {
    int *parent, *rank;
    int n;
  
    // Construtor
    ConjuntosDisjuntos(int n) {
        this->n = n;
        parent = new int[n+1];
        rank = new int[n+1];
  
        for (int i = 0; i <= n; i++){
            rank[i] = 0; // inicialmente tem todos rank 0
            parent[i] = i; // e cada elemento tem parent a si mesmo
        }
    }
  
    // representante do conjunto onde esta u
    int find(int u) {
        if (u != parent[u])
            parent[u] = find(parent[u]);
        return parent[u];
    }

    // uniao pelo rank
    void merge(int x, int y) {
        x = find(x), y = find(y);
  
        if (rank[x] > rank[y])
            parent[y] = x;
        
        else // se rank[x] <= rank[y]
            parent[x] = y;
  
        if (rank[x] == rank[y])
            rank[y]++;
    }
};


/* Funcao que retorna o peso MST */
int Grafo::KruskalMST() {
    int mst_wt = 0; 
  
    // organizar os arcos por ordem decrescente de peso
    sort(arcos.begin(), arcos.end(), greater<pair<int, Par>>());
  
    // criar os conjuntos disjuntos
    ConjuntosDisjuntos conjunto(V);
  
    // Iterar pelos arcos
    vector< pair<int, Par> >::iterator it;

    for (it = arcos.begin(); it != arcos.end(); it++) {
        int u = it->second.first;
        int v = it->second.second;
  
        int set_u = conjunto.find(u);
        int set_v = conjunto.find(v);
  
        // verificar se cria um ciclo
        if (set_u != set_v) {
            mst_wt += it->first; // Atualizar o peso MST
            conjunto.merge(set_u, set_v); // Unir os dois sets
        }
    }
    return mst_wt;
}


int main() {
    clock_t start, end;
     /* Recording the starting clock tick.*/
    start = clock();
    /* Leitura do input */
    int V,E;
    scanf("%d%d", &V, &E); // obter numero de arcos e obter numero de vertices

    Grafo G(V, E); // criamos o grafo
    
    // adicionamos os arcos
    for (int i = 0; i < E; i++) { // selecionar cada arco
        int v1, v2, w;
        scanf("%d%d%d", &v1, &v2, &w);
        G.addArco(v1, v2, w);
    }

    int mst_wt = G.KruskalMST();
    /* Apresentar o resultado */
    cout << mst_wt << "\n";

    // Recording the end clock tick.
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken;
    cout << " sec " << endl;
  
    return 0;
}
