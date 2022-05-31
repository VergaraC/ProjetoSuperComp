#include <vector>
#include <algorithm>  
#include <iostream>
#include <string.h>
#include <random>
#include<omp.h>
#include<bits/stdc++.h>
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
}
int main(){
    int len1, len2;
    string seq1, seq2;
    string seq11, seq22;

    cin >> len1;
    cin >> len2;
    cin >> seq1;
    cin >> seq2;

    vector<default_random_engine> randomEngs;
    random_device random;
    default_random_engine gen1(random());
    randomEngs.push_back(gen1);
    default_random_engine gen2(random());
    randomEngs.push_back(gen2);
    default_random_engine gen3(random());
    randomEngs.push_back(gen3);
    default_random_engine gen4(random());
    randomEngs.push_back(gen4);
    default_random_engine gen5(random());
    randomEngs.push_back(gen5);
    default_random_engine gen6(random());
    randomEngs.push_back(gen6);
    default_random_engine gen7(random());
    randomEngs.push_back(gen7);
    default_random_engine gen8(random());
    randomEngs.push_back(gen8);

    int bestScore = -(len1+len2);
    int atualScore;

    time_t start, end;
    uniform_int_distribution<int> d1(1,len1);
    uniform_int_distribution<int> d2(1,len2);
    uniform_int_distribution<int> dsqrt(20,sqrt(2*len1*len2));

    int iMax = 10000;
    string subSeq1;
    string subSeq2;
    int p, k;
    

    #pragma omp parallel for shared(seq11, seq22, bestScore) firstprivate(a, b){
         
        for(int i = 0; i<iMax; i++){
            if(len1>len2){ 
                k = d2(randomEngs[i%8]);
            }
            else{
                k = d1(randomEngs[i%8]);
            }
            uniform_int_distribution<int> d(0, len2-k);
            subSeq1 = seq1.substr(0, k);
            p = dsqrt(randomEngs[i%8]);
            for(int i = 0; i < p; i++){
                atualScore = 0;
                int j = d(randomEngs[i%8]);
                subSeq2 = seq2.substr(j, k);
                /*for(int i2 = 0; i2 < k; i2++){
                    if(subSeq1[i2]==subSeq2[i2]){
                        atualScore += 2;
                    }
                    else{
                        atualScore += -1;
                    } */
                atualScore += compararSeqs(subSeq1, subSeq2);
                //cout << "Score: " << atualScore << endl;
                //}

                #pragma omp critical{
                    cout << "crit";
                    if(atualScore > bestScore){
                        bestScore = atualScore;
                        seq11 = subSeq1;
                        seq22 = subSeq2;
                        cout << "BestScore:  ";
                        cout << bestScore << endl;
                    }
                }
            }
        }
    }
}

    
    


