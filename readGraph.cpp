#include <stdio.h>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

list<int>*_listAdj;
int _v, _E;

void readGraph(){
    scanf("%d, %d", &_v, &_E);
    for (int i = 0; i < _E; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        _listAdj[u-1].push_front(v-1);
    }
}

void computeList(){
    vector<int> hist(_v);
    for (int i = 0; i < _v; i++){ 
        int count = 0;
        for (list<int>:: iterator it; it != _listAdj[i].end(); it++){
            count++;
        }
        hist[count]++;
    }
    cout << "Histograma," << endl;
    for (int i = 0; i < _v; i++){
        cout << hist[i] << endl;
    }
}

int main(){
    readGraph();
    computeList();
}