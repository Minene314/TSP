#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <random>
#include <map>
using namespace std;

const int GEN = 10;
int N;

vector<vector<int>> init(vector<vector<int>>);
vector<vector<int>> shuffle(vector<vector<int>>);
void select();
void cross();
void mutation();
double eval(vector<int>, double**);
bool second_cmp(const pair<vector<int>, double>& a, const pair<vector<int>, double>& b);

int main() {
    FILE *fp;
    char fname[] = "../test.txt";
    int a, b;
    double dist;
    if((fp = fopen(fname,"r"))==NULL){
        printf("errer\n");
        return -1;
    }else{
        printf("%s file opened\n",fname);
    }
    fscanf(fp,"%d",&N);
    double **net;
    net = (double**)malloc(sizeof(double*)*N);
    for(int i = 0; i < N; i++) net[i] = (double*)malloc(sizeof(double)*N);
    vector<vector<int>> gen(GEN, vector<int>(N));
    while(fscanf(fp,"%d %d %lf",&a, &b, &dist)!=EOF) {
        net[a][b] = net[b][a] = dist;
    }
    fclose(fp);
    gen = init(gen);
    vector<pair<vector<int>, double>> vp;
    for(int i = 0; i < GEN; i++) {
        vp.push_back(make_pair(gen.at(i), eval(gen.at(i), net)));
    }
    sort(vp.begin(), vp.end(), second_cmp);
    for(int i = 0; i < GEN; i++) {
        gen.at(i) = vp.at(i).first;
    }
    for(int i = 0; i < GEN; i++) {
        for(int j = 0; j < N; j++) {
            if(j == 0) cout << "gen: ";
            if(j != 0) cout << " ";
            cout << gen.at(i).at(j);
        }
        cout << ", dist: " << vp.at(i).second << endl;
    }
    cout << endl;
    /*
    while(true) {
        vector<pair<vector<int>, double>> vp;
        for(int i = 0; i < GEN; i++) {
            vp.push_back(make_pair(gen.at(i), eval(gen.at(i), net)));
        }
        sort(vp.begin(), vp.end(), second_cmp);
        vector<vector<int>> next_gen;
        while(next_gen.size() < GEN) {
            select();
            cross();
        }
        gen = next_gen;
    }
    */
    return 0;
}

vector<vector<int>> init(vector<vector<int>> gen) {
    for(int i = 0; i < GEN; i++) {
        for(int j = 0; j < N; j++) {
            gen.at(i).at(j) = j;
        }
    }
    gen = shuffle(gen);
    return gen;
}

vector<vector<int>> shuffle(vector<vector<int>> gen) {
    random_device rnd;
    mt19937 mt(rnd());
    for(int i = 0; i < GEN; i++) {
        for(int  j = 0; j < N; j++) {
            int tmp = mt()%N;
            int t = gen.at(i).at(j);
            gen.at(i).at(j) = gen.at(i).at(tmp);
            gen.at(i).at(tmp) = t; 
        }
    }
    return gen;
}

double eval(vector<int> gen, double** net) {
    double dist = net[gen.at(0)][gen.at(gen.size()-1)];
    for(int i = 0; i < N-1; i++) dist += net[gen.at(i)][gen.at(i+1)];
    return dist;
}


bool second_cmp(const pair<vector<int>, double>& a, const pair<vector<int>, double>& b) {
    return a.second < b.second;
}