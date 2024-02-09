
#include <vector>
#include <iostream>

using namespace std;

int possibilities = 0; // crio as variaveis das linhas e colunas
int lines;
int columns;
vector<int> stairSettings;
int maxColumn;

void readScan();

vector<vector<int>> makeMatrix();

void makeCombinations(int, int, vector<vector<int>>);

bool checkSquare(int, int, int, vector<vector<int>>);

/*void printMatrix(const vector<vector<int>> &);*/

int main() {
    readScan();
    if (possibilities == 0) {
        cout << 0 << "\n";
        return 0;
    }
    vector<vector<int>> matrix = makeMatrix();
    lines=matrix.size();
    columns=matrix[0].size();
    /*printMatrix(matrix)*/;
    makeCombinations(0, 0, matrix);
    cout << possibilities << "\n";
}

void readScan() {
    int stair;
    int leadingZeroLines = 0;
    cin >> lines;
    cin >> columns;
    for (int i = 0; i < lines; i++) {
        cin >> stair;
        if (stair > maxColumn) // Gets the number of useful columns, after it only zeros
            maxColumn = stair;
        if (stair == 0 && possibilities == 0) // Gets the number of useless  leading lines of zeros
            leadingZeroLines++;
        else {
            possibilities = 1;
            stairSettings.push_back(stair);  // appends to vector
        }
    }
    lines -= leadingZeroLines;
    stairSettings.resize(lines);
}

vector<vector<int>> makeMatrix() {
    vector<vector<int>> matrix;
    int columnsLeft;
    for (int stairSetting: stairSettings) {
        vector<int> validColumns; // creates column
        for (int j = 0; j < stairSetting; j++)
            validColumns.push_back(1); // puts 1 in  the line's valid areas
        columnsLeft = maxColumn - stairSetting; // finds the remaining columns
        while (columnsLeft > 0) { // sets rest of the columns to zero
            validColumns.push_back(0);
            columnsLeft--;
        }
        matrix.push_back(validColumns); // adds line to matrix
    }
    return matrix;
}

/*Comenta aqui o processo que isto faz resumidamente para ver se percebo melhor
 */
void makeCombinations(int i, int j, vector<vector<int>> matrix) {

    for (; i < lines; i++) {
        for (; j < columns; j++) {   //search the matrix 
            int squareSize = 2;
            while (!(squareSize > lines || squareSize > columns || squareSize + i > lines ||squareSize + j > columns)) { // see if the square doesnt exceed the matriz
                if (!checkSquare(squareSize, i, j, matrix)) {
                    break;
                }
                squareSize++;//increases the size of the square that will be used to 
            }
        }
        j = 0;
    }
}

bool checkSquare(int t_quadrado, int i, int j, vector<vector<int>> matrix) {
    for (int t_quadrado_lines = t_quadrado - 1; t_quadrado_lines >= 0; t_quadrado_lines--)
        for (int t_quadrado_columns = t_quadrado - 1; t_quadrado_columns >= 0; t_quadrado_columns--) {  //see if the matriz can withstand the square(by seeing if the place is ocupied by 0 or 1)
            if (matrix[t_quadrado_lines + i][t_quadrado_columns + j] == 0){
                return false; //if the square doesnt fit in the area that i am searching for, return false
            }
            matrix[t_quadrado_lines + i][t_quadrado_columns + j] = 0; //if the square fits a spot matrix, i will substitute the number by 0  
        }

    possibilities++;
    makeCombinations(i, j, matrix);//with the new matrix created, the function will see if it can put more squares on the matrix
    /*printMatrix(matrix);*/
    return true;
}

