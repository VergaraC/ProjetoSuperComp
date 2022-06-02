#include <vector>
#include <algorithm>  
#include <iostream>
#include <string.h>
#include <random>
#include <omp.h>
#include <bits/stdc++.h>
#include <fstream>


using namespace std;

int comparar(char seq1, char seq2){
    if(seq1 == seq2){ //match
        return 2;
    }else{
        return -1; //mismatch ou gap
    }
}
int compararSeqs(string seq1, string seq2){
    int res = 0;
    for(int i = 0; i <= int(seq1.size()); i++){
        res += comparar(seq1[i], seq2[i]);
    }
    return res;
}
vector<string> getSubStrings(string A){
    vector<string> all;
    for(int i = 0; i <= int(A.size()); i++){
        for (int j = 0; j < int(A.size()); j++ ){
            all.push_back(A.substr(i,j));
        }
    }
    return all;
}
int main(){
    omp_set_num_threads(8);
    int len1, len2;
    string seq1, seq2;

    cin >> len1;
    cin >> len2;

    cin >> seq1;
    cin >> seq2;
    
    vector<string> seq1All = getSubStrings(seq1);
    vector<string> seq2All = getSubStrings(seq2);

    int score = 0;
    int bestScore = -(len1+len2);

    string best1, best2;
    #pragma omp parallel for reduction(max:bestScore) 
    for(auto&s1: seq1All){
        for(auto&s2: seq2All){
            if(s2.length() == s1.length()){
                score = compararSeqs(s1, s2);
                if(score > bestScore){
                    bestScore = score;
                    best1 = s1;
                    best2 = s2;
                }
            }
        }
    }
    cout << "Max Score:  " << bestScore << endl;
    cout << "Best Seq1:  " << best1 << endl;
    cout << "Best Seq2:  " << best2 << endl;
}