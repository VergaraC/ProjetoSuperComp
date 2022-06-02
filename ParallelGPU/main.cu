#include <vector>
#include <algorithm>  
#include <iostream>
#include <string.h>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <tuple>


using namespace std;

struct comparar2{
    __host__ __device__
    int compararEsquerda()(const int& x, int>& y){
        int esq = x - 1;
        int agora = y;

        if (agora > esq && agora > 0){
            return agora;
        }else if(esq>agora && esq>0){
            return esq;
        }else if(agora == esq  && agora > 0){
            return agora;
        }else{
            return 0;
        }
    }
}

struct comparar1{
    int cima;
    int diagonal;
    char c;
    match(int c_) : c(c_){};
    __host__ __device__
    int compararCimaDiagonal()(const thrust::tuple<char, int, int>& v){

        if(c == thrust::get<0>(v)){
            diagonal = thrust::get<1>(v) + 2;
        }else{
            diagonal = thrust::get<1>(v) - 1;
        }
        cima = thrust::get<2>(v) - 1;
        if (diagonal > cima  && diag > 0){
            return diagonal;
        }else if(cima > diagonal && cima > 0){
            return cima;
        }else if(diagonal == cima && diagonal > 0){
            return cima; // n importa qual
        }else{
            return 0;
        }

    }

}
int main(){
    int len1, len2;
    string seq1, seq2;
    string seq11, seq22;

    cin >> len1;
    cin >> len2;

    cin >> seq1;
    cin >> seq2;

    seq1 = '0' + seq1;
    seq2 = '0' + seq2;

    int bestScore = -(len1 + len2);
    int scoreAtual;

    thrust::device_vector<char> seq1G(seq1+1);
    thrust::device_vector<char> seq2G(seq2+1);
    thrust::device_vector<int> mat1(seq2+1);
    thrust::device_vector<int> mat2(seq2+1);

    //passando pra GPU
    for(int i = 0; i < len1; i++){
        seq1G += seq1[i];
    }
    for(int i2 = 0; i2 < len2; i2++){
        seq2G += seq2[i2];
    }
    thrust::fill(mat1.begin(), mat1.end(), 0);
    thrust::fill(mat2.begin(), mat2.end(), 0);
    cout << "Preparação GPU feita"<< endl;

    for(int i3 = 1; i3 < len1+1; i3++){
        thrust::transform(thrust::make_zip_iterator(thrust::make_tuple(seq2G.begin()+1, mat1.begin(), mat1.begin()+1)),
                          thrust::make_zip_iterator(thrust::make_tuple(seq2G.end(), mat1.end() - 1, mat1.end())),
                          mat2.begin() + 1, comparar1(seq1G[i3]));
   
        cout << "Transform Feito" << endl;

        thrust::inclusive_scan(mat2.begin(), mat2.end(), mat1.begin(), comparar2());

        scoreAtual = thrust::reduce(mat1.begin(), mat1.end(), 0, thrust::maximum<int>());
        
        if(scoreAtual > bestScore){
            bestScore = scoreAtual;
            cout << "New Best: " << bestScore << endl;
        }
    }
   

    cout << "Best Score"<< bestScore << endl;
    return 0;
}

