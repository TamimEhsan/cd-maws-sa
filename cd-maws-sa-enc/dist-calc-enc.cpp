#include<bits/stdc++.h>
#include <chrono>
using namespace std;
using cloc = chrono::system_clock;
using sec = chrono::duration<double>;
#define ll long long
#define pii pair<ll,ll>

const int MAX = 100;
ll mods[2] = {1000000007, 1000000009};
//Some back-up primes: 1072857881, 1066517951, 1040160883
ll bases[2] = {137, 281};
ll pwbase[3][MAX];


void Preprocess(){
    pwbase[0][0] = pwbase[1][0] = 1;
    for(ll i = 0; i < 2; i++){
        for(ll j = 1; j < MAX; j++){
            pwbase[i][j] = (pwbase[i][j - 1] * bases[i]) % mods[i];
        }
    }
}

pii getHash(string s){
    ll h1 = 0, h2 = 0;
    for(ll i = 0; i < s.size(); i++){
        h1 = (h1 + (s[i] - 'a' + 1) * pwbase[0][i]) % mods[0];
        h2 = (h2 + (s[i] - 'a' + 1) * pwbase[1][i]) % mods[1];
    }
    return {h1, h2};
}


struct MAW{
    long long encode;
    int len;
};

vector<vector<MAW>> maws;
vector<string> taxa;

void readFile(){

    string s;
    while(cin>>s){
        if( s[0] == '>' ){
            vector<MAW> v;
            maws.push_back(v);
            taxa.push_back(s.substr(1));
            //cout<<s<<endl;
        }
        else if( s.size() > 0 ){
            long long int encode = stoi(s); // string to int
            int len;
            cin >> len;
            //cout<<encode<<" "<<len<<endl;
            maws.back().push_back({encode, len});
        }
    }

    //cout<<"Reading done"<<endl;
    //cout<<maws.size()<<endl;
}


int compare(MAW a, MAW b){
    if( a.len  == b.len ){
        if( a.encode == b.encode ){
            return 0;
        }
        return a.encode < b.encode ? -1 : 1;
    } else if ( a.len < b.len ){
        long long int b_encode = b.encode >> ((b.len - a.len)*2);
        return a.encode <= b_encode ? -1 : 1;
    } else {
        long long int a_encode = a.encode >> ((a.len - b.len)*2);
        return a_encode < b.encode ? -1 : 1;
    }
}

int distance(int x,int y){
    int same = 0;
    int i=0,j=0;
    while(i<maws[x].size() && j<maws[y].size()){
        int cmp = compare(maws[x][i],maws[y][j]);
        if( cmp == 0 ){
            same++;
            i++;
            j++;
        }
        else if( cmp < 0 ){
            i++;
        }
        else{
            j++;
        }
    }
    return same;
}

void CalculateDistanceMatrix(){
    for(int i=0;i<maws.size();i++){
        cout<<","<<taxa[i];
    }
    cout<<'\n';
    for(int i=0;i<maws.size();i++){
        //cout<<i<<" "<<maws[i].size()<<"\n";
        cout<<taxa[i];
        for(int j=0;j<maws.size();j++){
            int same = distance(i,j);
            double la = sqrt(maws[i].size());
            double lb = sqrt(maws[j].size());
            double dis = 1.0 - (double)(same)/(la*lb);
            if( i == j) dis = 0;
            cout<<","<<dis;
        }
        cout<<'\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input-file> <output-file>" << std::endl;
        return 1;
    }
    string inputFilePath = argv[1];
    string outputFilePath = argv[2];

    //auto start = cloc::now();
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    if( inputFilePath != "stdin" )
        freopen(inputFilePath.c_str(),"r",stdin);
    if( outputFilePath != "stdout" )
    freopen(outputFilePath.c_str(),"w",stdout);

    readFile();
    CalculateDistanceMatrix();
    //sec duration = cloc::now() - start;
    //cout << "Total time taken (sec)--> " << duration.count() << endl;
}
