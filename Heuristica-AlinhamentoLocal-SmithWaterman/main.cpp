#include <vector>
#include <algorithm>  
#include <iostream>
#include<string.h>


using namespace std;

struct item{
    int i;
    int j;
    int value;
    int jump; // diagonal = 0, esquerda = 1, sobe = 2
};
struct Max{
    int iMax;
    int jMax;
    int valueMax;
};
struct funct{
    Max max;
    vector<vector<item>> matrizHtemp;
};

int comparar(char seq1, char seq2){
    if(seq1 == seq2){ //match
        return 2;
    }else{
        return -1; //mismatch ou gap
    };
};

funct heuristicaSmithWaterman(vector<vector<item>> matrizH, int len1, int len2, string seq1, string seq2){
    int valorMatch;
    int diagonal, sobe, esquerda;
    Max max;
    max.iMax = 0;
    max.jMax = 0;
    max.valueMax = 0;
    
    for (int i = 1; i < len1; i++){
        for (int j = 1; j < len2; j++){
            valorMatch = comparar(seq1[i-1], seq2[j-1]);
            diagonal = matrizH[i-1][j-1].value + valorMatch;
            sobe = matrizH[i][j-1].value - 1;
            esquerda = matrizH[i-1][j].value - 1;
            if(diagonal >= esquerda and diagonal >= sobe and diagonal >= 0){
                matrizH[i][j].jump = 1;
            }else if(esquerda >= sobe and esquerda >= 0){
                matrizH[i][j].jump = 2;
            }else if(sobe >= 0){
                matrizH[i][j].jump = 3;
            }else{
                matrizH[i][j].jump = 0;
            }
            matrizH[i][j].i = i;
            matrizH[i][j].j = j;

            if(matrizH[i][j].jump == 1){
                matrizH[i][j].value = diagonal;
            }else if(matrizH[i][j].jump == 2){
                matrizH[i][j].value = esquerda;
            }else if(matrizH[i][j].jump == 3){
                matrizH[i][j].value = sobe;
            }else{
                matrizH[i][j].value = 0;
            }

            if (matrizH[i][j].value > max.valueMax){
                max.valueMax = matrizH[i][j].value;
                max.iMax = matrizH[i][j].i;
                max.jMax = matrizH[i][j].j;
            }
        }
    }
    funct result;
    result.max.iMax = max.iMax;
    result.max.jMax = max.jMax;
    result.max.valueMax = max.valueMax;
    result.matrizHtemp = matrizH;

    cout << max.iMax << " " << max.jMax << " " << max.valueMax<< endl;
    cout << result.max.iMax << " " << result.max.jMax << " " << result.max.valueMax<< endl;
    //copy(matrizH.begin(), matrizH.end(), back_inserter(result.matrizHtemp));
    return result;   
};
void printMatriz(vector<vector<item>> matrizH, int len1, int len2){
    cout << endl;
  cout << "MATRIZ" << endl;
  for(int i = 0; i < len1; i++){
    cout << endl;
    for(int j = 0; j < len2; j++){
      cout << " " << matrizH[i][j].value;
    }
  }
  cout << endl;
  cout <<"     " << "FIM DA MATRIZ" << endl;
  cout << endl;
  cout << endl;
};

int main(){
    int len1, len2;
    string seq1, seq2;
    string seq11, seq22;

    cin >> len1;
    cin >> len2;

    cin >> seq1;
    cin >> seq2;

    vector<vector<item>> matrizH;
    item itemMax;
    cout <<"pre resize" << endl;
    
    matrizH.resize(len1);
    for(int i = 0 ; i < len1 ; i++){
        cout << i<< endl;
        matrizH[i].resize(len2);
    }
    cout <<"pre heuristica" << endl;
    funct all;
    all = heuristicaSmithWaterman(matrizH, len1, len2, seq1, seq2);
  
    printMatriz(all.matrizHtemp, len1, len2);

    cout << "Max i: " << all.max.iMax << " Max j: " << all.max.jMax << endl;
    cout << "Max Value: " << all.max.valueMax << endl;
    cout << "Max Jump: " << all.matrizHtemp[all.max.iMax][all.max.jMax].jump << endl;

    itemMax.i = all.max.iMax;
    itemMax.j = all.max.jMax;
    itemMax.value = all.max.valueMax;
    itemMax.jump = all.matrizHtemp[all.max.iMax][all.max.jMax].jump;

    while(itemMax.i > 0 && itemMax.j > 0 && itemMax.value > 0){
        cout << itemMax.jump << endl;
        if(itemMax.jump == 1){
            seq11 += seq1[itemMax.i-1];
            seq22 += seq2[itemMax.j-1];
            itemMax.i --;
            itemMax.j --;
        }else if(itemMax.jump == 2){
            seq11 += seq1[itemMax.i-1];
            seq22 += '-';
            itemMax.i --;
        }else if(itemMax.jump == 3){
            seq11 += '-';
            seq22 += seq2[itemMax.j-1];
            itemMax.i --;
        }
        itemMax.value = matrizH[itemMax.i][itemMax.j].value;
        itemMax.jump = matrizH[itemMax.i][itemMax.j].jump;

    }
    reverse(seq11.begin(), seq11.end());
    reverse(seq22.begin(), seq22.end());

    cout << "Seq1: " << seq11 << endl;
    cout << "Seq2: " << seq22 << endl;


    return 0;
}

