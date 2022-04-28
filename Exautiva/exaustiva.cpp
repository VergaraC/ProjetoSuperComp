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
    }
}
int compararSeqs(string seq1, string seq2){
    int res = 0;
    for(int i = 0; i < int(seq1.size()); i++){
        res += comparar(seq1[i], seq2[i]);
    }
    return res;
}
vector<string> getSubStrings(string A, int n){
    vector<string> all;
    for(int i = 0; i < n; i++){
        for (int j = i+1; j < n; j++ ){
            all.push_back(A.substr(i,j));
        }
    }
    return all;
}
int main(){
    int len1, len2;
    string seq1, seq2;
    //string seq11, seq22;

    cin >> len1;
    cin >> len2;

    cin >> seq1;
    cin >> seq2;
    
    vector<string> seq1All = getSubStrings(seq1,len1);
    vector<string> seq2All = getSubStrings(seq2,len2);

    int score = 0;
    int bestScore = 0;

    string best1, best2;
    
    for(auto&seq1: seq1All){
        for(auto&seq2: seq2All){
            if(seq2.length() == seq1.length()){
                score = compararSeqs(seq1, seq2);
                if(score > bestScore){
                    bestScore = score;
                    best1 = seq1;
                    best2 = seq2;
                }
            }
        }
    }
    cout << "Max Score" << bestScore << endl;
    cout << "Best Seq1" << seq1 << endl;
    cout << "Best Seq2" << seq2 << endl;
}