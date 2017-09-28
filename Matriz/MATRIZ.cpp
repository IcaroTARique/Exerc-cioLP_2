#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>

using namespace std;

//Valor máximo que o elemento pode alcançar
#define VALOR_MAXIMO 10

//****************função que cria matriz escolhendo os números de cada****************
void EncheMatriz (int lin, int col, int **m){
    for (int i=0; i<lin; i++){
        for (int j=0; j<col; j++){
          m[i][j] = ((i+1)*10)+(j+1);
        }
    }
}
//****************Função que cria matriz randomica****************
void EncheMatrizRandomica (int lin, int col, int **m){
srand(time(NULL));
    for (int i=0; i<lin; i++){
        for (int j=0; j<col; j++){
          m[i][j] = rand() % VALOR_MAXIMO + 1;
      }
    }
}
//****************Função que cria matriz com zeros****************
void EncheMatrizComZero (int lin, int col, int **m){
srand(time(NULL));
    for (int i=0; i<lin; i++){
        for (int j=0; j<col; j++){
          m[i][j] = 0;
      }
    }
}

//****************Função que exibe a matriz passada****************
void ExibeMatriz (int lin, int col, int **m) {
int cont = 0;
    for (int i=0; i<lin; i++){
        for (int j=0; j<col; j++){
              cout  << m[i][j] << " " ;
              // cont para fazer quebra de linha na quantidade de colunas
              cont++;
              // If para detectar onde deve ser feita a quebra da  linha
              if(cont % col == 0) {
                cout << endl;
              }
        }
    }
    cout << endl;
}
//****************Função que executa a multiplicação****************
void MultiplicaMatrizes( int i, int j, int col_a, int **ma, int **mb, int **mc ){
    int k, val_a, val_b;
        for(k = 0; k < col_a; k++){
            val_a = ma[i][k];
            val_b = mb[k][j];

            mc[i][j] += val_a * val_b;

            cout << "OLHAAAAA A THREEEEAAAAADAAAÊÊÊÊÊ... NEGAAAAAADA" << endl;
        }
}


int main() {
    int linha_a, coluna_a, linha_b, coluna_b, linha_c, coluna_c;
    int choice = 0, index = 0;

    //recebe do goto caso haja erro
    redefine:
    cout <<"Defina a dimensão da matriz A - LINHA - COLUNA - "<<endl;
    cin >> linha_a;
    cin >> coluna_a;
    cout <<"Defina a dimensão da matriz B - LINHA - COLUNA - " << endl;
    cin >> linha_b ;
    cin >> coluna_b;

    if(linha_a != coluna_b){
        cout << "O numero de linhas é diferente do numero de colunas na matriz A" << endl;
        //Manda para a lable redefine caso haja erro
        goto redefine;
    }

    // Alocando a matrizA de modo dinamico com comando new --
    int **matrizA = new int*[linha_a];
    for (int i=0; i<linha_a; i++){
        matrizA[i] = new int[coluna_a];
    }
    // Alocando a matrizB de modo dinamico com comando new --
    int **matrizB = new int*[linha_b];
    for (int i=0; i<linha_b; i++){
        matrizB[i] = new int[coluna_b];
    }
    // Alocando a matrizC de modo dinamico com comando new --
    int **matrizC = new int*[linha_a];
    for (int i=0; i<linha_c; i++){
        matrizC[i] = new int[coluna_b];
    }

    EncheMatrizComZero(linha_a, coluna_b, matrizC);

    cout << "Deseja criar a matriz __A__ RANDOMICAMENTE ???" << endl;
    cin >> choice;

    //função preenche matriz
    if(!choice){
        EncheMatriz(linha_a, coluna_a, matrizA);
    }else{
    //função preenche matriz randomicamente
        EncheMatrizRandomica(linha_a, coluna_a, matrizA);
    }

    //Define a quantidade de elementos existentes na matriz C, que virá a ser
    //A quantidade de THREADS do programa
    int numElementosMatrizC = linha_a * coluna_b;
    thread objThread[numElementosMatrizC];

// A SEPARAÇÃO OCORRE PARA TERMOS UM TEMPO DIFERENTE EM ORDEM DE
//OBTERMOS MATRIZES DIFERENTES NA GERAÇÃO

    cout << "Deseja criar a matriz __B__ RANDOMICAMENTE ???" << endl;
    cin >> choice;

    // função preenche matriz
    if(!choice){
        EncheMatriz(linha_b, coluna_b, matrizB);
    }else{
    //função preenche matriz randomicamente
        EncheMatrizRandomica(linha_b, coluna_b, matrizB);
    }

    //função exibe matriz
    ExibeMatriz(linha_a, coluna_a, matrizA);
    ExibeMatriz(linha_b, coluna_b, matrizB);

    for ( int i = 0; i < linha_a; i++){
        for ( int j = 0; j < coluna_b; j++){
            MultiplicaMatrizes(i, j, coluna_a, matrizA, matrizB, matrizC );
        }
    }

    cout << " RESULTADO DA MATRIZ SEQUENCIALMENTE" << endl;
    ExibeMatriz(linha_a, coluna_b, matrizC);
    EncheMatrizComZero(linha_a, coluna_b, matrizC);

    cout << endl;
    cout << "RESULTADO DA MATRIZ CONCORRENTEMENTE" << endl;

    for ( int i = 0; i < linha_a; i++){
        for ( int j = 0; j < coluna_b; j++){
            objThread[index ++] = std::thread(MultiplicaMatrizes, i , j, coluna_a, matrizA, matrizB, matrizC);
        }
    }

for (int i = 0; i < numElementosMatrizC; ++i)
{
    objThread[i].join();
}

    ExibeMatriz(linha_a, coluna_b, matrizC);

return 0;
}