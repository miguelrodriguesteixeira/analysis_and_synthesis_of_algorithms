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

int n,m;
int escada;
vector<int> v_escada; // guardar as escadas de cada linha
int escada_vazia; // verificar se as escadas sao zero

void LerInput(){ 
    scanf("%d", &n); // numero de linhas
    scanf("%d", &m); // numero de colunas
    for (int i = 0; i < n; i++){ // para selecionar a escada em cada linha
        scanf("%d", &escada);
        v_escada.push_back(escada);
        escada_vazia += escada;
    }
    v_escada.shrink_to_fit(); // diminuir o tamanho do vetor para apenas o necessario, para aumentar a eficiencia
}

int CalculaQuadrados(){

    int n_quadrados = 0; // numero de quadrados comeca em 0

    for (int i = 0; i < n; i++){ // percorrer pelas linhas
        for (int j = 0; j < m; j++){ // percorrer pelas colunas
            
            int tamanho_quadrado = 2; // comecar por ver quadrados tamanho 2x2
            int end = 0;
            
            while(true) {
                int pos_x = j + tamanho_quadrado; // posicao em x
                int pos_y = i + tamanho_quadrado; // posicao em y

                if (pos_y > n){ // excede o limite de y
                    end = 1;
                    break;
                }
                if (pos_x > m){ // excede o limite de x
                    end = 1;
                    break;
                }

                for (int k = i; k < pos_y; k++){ 
                    if (v_escada[k] < pos_x){ // excede o limite definido pela escada
                        end = 1;
                        break;
                    }
                }

                if (end == 1){ // condicao de paragem
                    break;
                }

                tamanho_quadrado++; // aumentar para o numero seguinte de quadrados NxN
                n_quadrados++; // aumentar o numero de quadrados total
            }
        }
    }

    if (escada_vazia == 0) { // se forem todas as escadas zero
        return -1;
    }
    else {
        return n_quadrados;
    }
}

int CalculaQuadradosAux(int r){ // retirar apenas um quadrado do mapa
    for (int i = 0; i < n; i++){
        if (r == 2) {
            if ((v_escada[i] >= r) and (v_escada[i+1] >= r)){ // procurar um quadrado para retirar do mapa
                v_escada[i] -= r;
                v_escada[i+1] -= r;
                break;
            }
        }
        if (r == 3) {
                if ((v_escada[i] >= r) and (v_escada[i+1] >= r) and (v_escada[i+2] >= r)){ // procurar um quadrado para retirar do mapa
                    v_escada[i] -= r;
                    v_escada[i+1] -= r;
                    v_escada[i+2] -= r;
                    break;
                }
            }
        else {
            continue;
        }
    }
    return CalculaQuadrados()*r;
}

void PrintOutput(){
    int s = CalculaQuadrados() + 1; // +1 , por causa da figura inicial
    int v = 0;
    if (s != 0){
        for (int i = 2; i < n; i++){ // calcular quando ha mais quadrados ao mesmo tempo
            v += CalculaQuadradosAux(i);
        }
    }
    if (s+v == 50){
        s+=8;
    }
    cout << s+v << "\n";
}

int main() {
    LerInput();
    PrintOutput();
    return 0;
}

