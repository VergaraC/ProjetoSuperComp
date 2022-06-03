#include <algorithm>  
#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <cstdlib>
#include <iomanip>
#include <tuple>


using namespace std;

struct comparar2{
    __host__ __device__
    int operator()(const int& x, const int& y){
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
};

struct comparar1{
    int cima;
    int diagonal;
    char c;
    comparar1(int c_) : c(c_){};
    __host__ __device__
    int operator()(const thrust::tuple<char, int, int>& v){

        if(c == thrust::get<0>(v)){
            diagonal = thrust::get<1>(v) + 2;
        }else{
            diagonal = thrust::get<1>(v) - 1;
        }
        cima = thrust::get<2>(v) - 1;
        if ( diagonal > 0 && diagonal > cima ){
            return diagonal;
        }else if( cima > 0 && cima > diagonal){
            return cima;
        }else if(diagonal > 0 && diagonal == cima ){
            return cima; // n importa qual
        }else{
            return 0;
        }

    }

};
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

    thrust::device_vector<char> seq1G(len1+1);
    thrust::device_vector<char> seq2G(len2+1);
    thrust::device_vector<int> mat1(len2+1);
    thrust::device_vector<int> mat2(len2+1);

    //passando pra GPU
    for(int i = 0; i < len1 + 1; i++){
        seq1G[i] = seq1[i];
    }
    for(int i2 = 0; i2 < len2 + 1; i2++){
        seq2G[i2] = seq2[i2];
    }
    //thrust::fill(mat2.begin(), mat2.end(), 0);
    cout << "Preparação GPU feita"<< endl;
    //Prep Substring
    int lenMin = -1;
    int lenMax;
    if(len1 > len2){
        lenMax = len2;
    }else{
        lenMax = len1;
    }
    while(lenMax>= lenMin && lenMax > 1){
            for(int i1 = 0; i1 <= (len1 + 1 - lenMax) ; i1++){
                cout << i1 << endl;
                for(int i2 = 0; i2 <= (len2 + 1 - lenMax); i2++){
                    thrust::fill(mat1.begin(), mat1.end(), 0);

                    for(int i3 = 1; i3 < lenMax+1; i3++){
                        thrust::transform(thrust::make_zip_iterator(thrust::make_tuple(seq2G.begin()+1 + i2, mat1.begin(), mat1.begin()+1)),
                                            thrust::make_zip_iterator(thrust::make_tuple(seq2G.end() + 1 + i2 + lenMax, mat1.begin() + lenMax,mat1.begin() + lenMax + 1)),
                                            mat2.begin() + 1,
                                            comparar1(seq1G[i1]));

                        //cout << "Transform Feito" << endl;

                        thrust::inclusive_scan(mat2.begin(), mat2.begin() + lenMax, mat1.begin(), comparar2());

                        scoreAtual = thrust::reduce(mat1.begin(), mat1.begin() + lenMax, 0, thrust::maximum<int>());
                        
                        if(scoreAtual > bestScore){
                            bestScore = scoreAtual;
                            cout << "New Best: " << bestScore << endl;
                        }
                    }
                }
            }
            lenMax --;
            lenMin = 1 + (bestScore/2); //se n for no min isso ele vais er menor ou igual
            lenMax --;
            cout << "Best Score"<< bestScore << endl;

   
    }
    cout << "Best Score"<< bestScore << endl;
    return 0;
}

