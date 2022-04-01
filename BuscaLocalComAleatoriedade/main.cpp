#include <vector>
#include <algorithm>  
#include <iostream>
#include <string.h>
#include <random>


#include<fstream>


using namespace std;


int comparar(char seq1, char seq2){
    if(seq1 == seq2){ //match
        return 2;
    }else{
        return -1; //mismatch ou gap
    };
};
int compararSeqs(string seq1, string seq2){
    int res = 0;
    for(int i = 0; i < int(seq1.size()); i++){
        res += comparar(seq1[i], seq2[i]);
    };
    return res;
};
int main(){
    int len1, len2;
    string seq1, seq2;
    string seq11, seq22;

    cin >> len1;
    cin >> len2;

    cin >> seq1;
    cin >> seq2;

    random_device rd;
    unsigned seed = rd();
    default_random_engine generator(seed);
    uniform_int_distribution<int> distribution(1, len1);
    int k = distribution(generator);
    cout <<"K:  " << k << endl;

    //seq 1
    string seq1Random;
    unsigned seed1 = rd();
    default_random_engine generator1(seed1);
    uniform_int_distribution<int> distribution1(0, len1-k);
    int index1 = distribution1(generator1);
    
    if (index1 > int(seq1.size())){
        index1 = int(seq1.size());
    }
    cout << "INDEX1: " << index1 << endl;
    
    while(int(seq1Random.size())< k){
        seq1Random += seq1[index1];
        index1++;
    }
    cout << "SEQ1RANDOM: " << seq1Random << endl;


    //seq 2
    int nSeq2 = distribution(generator);
    cout << nSeq2 << "Sequencias de B a serem geradas"<< endl;

    vector<string> subSeq2Vector; 
    int bestScore = 0;
    int bestScoreIndex;

    for(int i = 0; i < nSeq2; i++){
        string subSeq2;
        unsigned seed2 = rd();
        default_random_engine generator2(seed2);
        uniform_int_distribution<int> distribution2(0, len2-k);

        int index2 = distribution2(generator2);
        if (index2 > int(seq2.size())){
            index2 = seq2.size();
        }
        while(int(subSeq2.size())< k){
            subSeq2 += seq2[index2];
            index2++;
        }
        cout << i << "  SUBSEQ2: " << subSeq2 << endl;
        subSeq2Vector.push_back(subSeq2);

        //score pra cada seq2
        int score = compararSeqs(seq1Random, subSeq2);
        if (score > bestScore){
            bestScore = score;
            bestScoreIndex = i;
        }
    }
    cout << endl;
    cout << endl;
    cout << "BEST SCORE: " << bestScore << endl;
    cout << "Seq 1 utilizada: " << seq1Random << endl;
    cout << "Melhor Seq2  " << subSeq2Vector[bestScoreIndex] << endl;


    return 0;
}

