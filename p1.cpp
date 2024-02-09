/*************************************
* ASA 2022/2023                      *
* Miguel Teixeira - 103449           *
* Miguel Noronha - 103192            *
* Primeiro Projeto - p1              *
*************************************/
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int n_quadrados = 0; // numero de quadrados comeca em 0
int n,m;
vector<int> v_escada; // guardar as escadas de cada linha
int maxCol;

// Funcoes
void LerInput(); // Leitura do input
vector<vector<int>> FazerMatriz(); // fazer uma matriz do problema
void CalculaCombinacoes(int, int, vector<vector<int>>); // calcular o numero de combinacoes possiveis
bool ValidaQuadrado(int, int, int, vector<vector<int>>); // ver se pode meter um quadrado


void LerInput() { // Leitura do input
    
    int escada;
    int linhas_zeros = 0;
    cin >> n; // obter numero de linhas
    cin >> m; // obter numero de colunas

    for (int i = 0; i < n; i++) { // para selecionar a escada em cada linha
        cin >> escada; // obter a escada
        if (escada > maxCol) { // colunas que se vai usar
            maxCol = escada;
        }
        if (escada == 0 && n_quadrados == 0) // numero de linhas de zeros
            linhas_zeros++;
        else {
            n_quadrados = 1; // se nao forem todos zeros comeca com a figura inicial, +1
            v_escada.push_back(escada);
        }
    }
    n -= linhas_zeros; // retiramos as colunas que nao vamos usar
    v_escada.resize(n); // diminuir o tamanho do vetor para apenas o necessario, para aumentar a eficiencia
}


vector<vector<int>> FazerMatriz() { // fazer uma matriz do problema
    
    vector<vector<int>> matriz; // vetor de vetor (matriz)
    int restoColunas;

    for (int escada: v_escada) { // para cada vetor na lista de escadas
        vector<int> colunaValida; // cria coluna
        for (int j = 0; j < escada; j++){
            colunaValida.push_back(1); // poe 1 nos lugares validos
        }
        
        restoColunas = maxCol - escada; // descobre o resto das colunas para meter 0's
        while (restoColunas > 0) { // poe o resto a 0's
            colunaValida.push_back(0);
            restoColunas--;
        }
        matriz.push_back(colunaValida); // adiciona a linha a matriz
    }
    return matriz; // retorna a matriz
}


void CalculaCombinacoes(int i, int j, vector<vector<int>> matrix) {  // calcular o numero de combinacoes possiveis
    for (; i < n; i++) { // procurar a matriz pelas linhas 
        for (; j < m; j++) {  // e colunas
            int tamanho_quadrado = 2; // comecar por ver quadrados tamanho 2x2
            while (!(tamanho_quadrado > n || tamanho_quadrado > m || tamanho_quadrado + i > n ||tamanho_quadrado + j > m)) { 
                // ver se excede a matriz
                if (!ValidaQuadrado(tamanho_quadrado, i, j, matrix)) { // se nao puder meter um quadrado
                    break;
                }
                tamanho_quadrado++; // aumentar para o numero seguinte de quadrados NxN
            }
        }
        j = 0; // comeca pela coluna inicial de novo
    }
}

bool ValidaQuadrado(int tamanho_quadrado, int i, int j, vector<vector<int>> matriz) { // ver se pode meter um quadrado
    for (int t_quadrado_linhas = tamanho_quadrado - 1; t_quadrado_linhas >= 0; t_quadrado_linhas--) { // ver se o lugar e 0 ou 1
        for (int t_quadrado_columns = tamanho_quadrado - 1; t_quadrado_columns >= 0; t_quadrado_columns--) {
            if (matriz[t_quadrado_linhas + i][t_quadrado_columns + j] == 0){ // e 0
                return false; // nao encaixa
            }
            matriz[t_quadrado_linhas + i][t_quadrado_columns + j] = 0; // encaixa, e metemos a zona a 0's
        }
    }
    n_quadrados++; // aumentamos o numero de combinacoes
    CalculaCombinacoes(i, j, matriz); // ver se se pode por mais quadrados na matriz
    return true;
}


int main() {
    clock_t start, end;
     /* Recording the starting clock tick.*/
    start = clock();
    LerInput();  // Leitura do input
    if (n_quadrados == 0) { // verificar se as escadas sao zero
        cout << 0 << "\n";
        return 0; // ta vazio, retorna 0
    }
    vector<vector<int>> matriz = FazerMatriz(); // criar a matriz
    
    n = matriz.size();
    m = matriz[0].size();

    CalculaCombinacoes(0, 0, matriz);

    cout << n_quadrados << "\n"; // retorna o numero de combinacoes
    // Recording the end clock tick.
    end = clock();
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC);
    cout << "Time taken by program is : " << fixed 
         << time_taken;
    cout << " sec " << endl;
    return 0;
}
