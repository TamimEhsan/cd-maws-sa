#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt")
#include <bits/stdc++.h>
using namespace std;


namespace SuffixAutomaton{
    const int N = 3e7 + 5;
    struct vertex{
        int link, len;
        int next[4];
        vertex(){
            link = -1;
            len = 0;
            memset(next, -1, sizeof next);
        }
    };
    int vector_size = 16;
    vector<vertex> sa(16);
    int last = 0, sz = 1;
    
    void resize(int n){
        while(n >= vector_size) {
            vector_size *= 2;
            sa.resize(vector_size);
        }
    }

    void init(){
        for(int i = 0; i < sz; i++){
            SuffixAutomaton::resize(i + 1);
            sa[i] = vertex();
        }
        last = 0, sz = 1;
    }
    void addChar(char c){
        c = (c == 'A' ? 0 : c == 'C' ? 1 : c == 'G' ? 2 : 3);
        int cur = sz++;
        SuffixAutomaton::resize(cur + 1 ); SuffixAutomaton::resize(last + 1);
        sa[cur].len = sa[last].len + 1;
        int u = last;
        SuffixAutomaton::resize(u + 1);
        while(u != -1 && sa[u].next[c] == -1) {
            sa[u].next[c] = cur, u = sa[u].link;
            SuffixAutomaton::resize(u + 1);
        }
        

        if(u == -1){
            SuffixAutomaton::resize(cur + 1);
            sa[cur].link = 0;
        } else{
            SuffixAutomaton::resize(u + 1);
            int v = sa[u].next[c];
            SuffixAutomaton::resize(v + 1);
            if(sa[u].len + 1 == sa[v].len){
                SuffixAutomaton::resize(cur + 1);
                sa[cur].link = v;
            } else{
                int nw = sz++;
                SuffixAutomaton::resize(nw + 1); SuffixAutomaton::resize(v + 1); SuffixAutomaton::resize(u + 1);
                sa[nw].link = sa[v].link;
                sa[nw].len = sa[u].len + 1;
                memcpy(sa[nw].next, sa[v].next, sizeof sa[v].next);
                while(u != -1 && sa[u].next[c] == v){
                    sa[u].next[c] = nw, u = sa[u].link;
                    SuffixAutomaton::resize(u + 1);
                }
                SuffixAutomaton::resize(cur + 1); SuffixAutomaton::resize(v + 1);
                sa[cur].link = sa[v].link = nw;
            }
        }
        last = cur;
    }
}

void build(const string &s){
    SuffixAutomaton::init();
    for(char c : s)
        SuffixAutomaton::addChar(c);
}
// const int N = 1e7 + 5;
// string ans[N];
int cur = 0;
string ALP = "ACGT";
ofstream fout;
const int K = 40;
char str[K];
int len, minimumK, maximumK;
void dfs(int node){
    if(len >= maximumK)return;
    SuffixAutomaton::resize(node + 1);
    int link = SuffixAutomaton::sa[node].link;
    for(int i = 0; i < 4; i++){
        int u = SuffixAutomaton::sa[node].next[i];
        if(u == -1){
            if(len + 1 < minimumK)continue;
            SuffixAutomaton::resize(link + 1);
            int v = SuffixAutomaton::sa[link].next[i];
            if(v != -1 && SuffixAutomaton::sa[link].len + 1 >= len){
                // cout << SuffixAutomaton::sa[v].len << endl;
                str[len++] = ALP[i];
                str[len] = '\0';
                // ans[cur++] = str;
                fout << str << "\n";
                cur++;
                len--;
            }
        }else{
            str[len++] = ALP[i];
            dfs(u);
            len--;
        }    
    }
}

string input_file="input/input.in";
string output_file="output/output.out";
long double total_time = 0;

void buildMaw(const string &s, int minK, int maxK){
    fout.open(output_file);
    cur = 0;
    cerr << "String size: " << s.size() << endl;
    // cerr << "Minimum K: " << minK << endl;
    // cerr << "Maximum K: " << maxK << endl;
    auto start = clock();
    
    build(s);   
    auto build_time = (clock() - start) / (double)CLOCKS_PER_SEC;
    // cerr << fixed << setprecision(6) << "Suffix Automata Build time: " << build_time << " sec" << endl;
    len = 0;
    minimumK = minK;
    maximumK = maxK;
    start = clock();
    dfs(0);
    auto maw_time = (clock() - start) / (double)CLOCKS_PER_SEC;
    // cerr << "Generating Maws time: " << maw_time << " sec" << endl;
    
    // cerr << "Total Time: "<< build_time + maw_time << " sec" << endl;
    total_time += build_time + maw_time;
    fout.close();

}

// string bruteAns[N];
// int bruteCur = 0;
// void goBrute(string &s, string &str, int minK, int maxK){
//     if(str.size() >= minK && str.size() <= maxK){
//         if(s.find(str.substr(0, str.size() - 1)) < s.size() && s.find(str.substr(1, str.size() - 1)) < s.size() && s.find(str) >= s.size()){
//             bruteAns[bruteCur++] = str;
//         }
//     }
//     if(str.size() > maxK)return;

//     for(int i = 0; i < 4; i++){
//         str += ALP[i];
//         goBrute(s, str, minK, maxK);
//         str.pop_back();
//     }
// }
// void buildMawBrute(string s, int minK, int maxK){
//     string temp = "";
//     bruteCur = 0;
//     goBrute(s, temp, minK, maxK);
// }



mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
T getRandInt(T l, T r){
	std::uniform_int_distribution<T> distrib(l, r);
	return distrib(rng);
}
string getString(int n){
	string ans;
	for(int i = 0; i < n; i++)ans += (char)(ALP[getRandInt(0, 3)]);
	return ans;
}
string getString(int n, int mask){
	string ans;
	for(int i = 0; i < n; i++)ans += (char)(ALP[mask & 3]), mask >>= 2;
	return ans;
}

int main(int argc, char *argv[]){
    int minK = 3;
    int maxK = 4;
    if(argc != 5){
        cerr << "Usage: " << argv[0] << " <input-file> <output-file> <minK> <maxK>" << endl;
        return 1;
    }
    input_file=argv[1];
    output_file = argv[2];
    minK = atoi(argv[3]);
    maxK = atoi(argv[4]);
    

    auto start = clock();
    
    ifstream fin(input_file);
    // ifstream fin("in.txt");

    string dna;
    string line;
    while( fin>>line ){
        if( line.size() > 0 && line[0] != '>' ){
            dna += line;
        }else if( line[0] == '>' ){
            string s = dna;
            dna="";
            if(minK > maxK)swap(minK, maxK);
            buildMaw(s, minK, maxK);
            // cout <<" (" << cur << " Maws) "<< "\n";
            cout.flush();

        }
    }

    string s = dna;
    dna="";
    if(minK > maxK)swap(minK, maxK);
    buildMaw(s, minK, maxK);
    // cout <<" (" << cur << " Maws) "<< "\n";
    cout.flush();

    auto total_time = (clock() - start) / (double)CLOCKS_PER_SEC;
    // cerr << fixed << setprecision(6) << "Total Time: " << total_time << " sec" << endl;
    // cout << "Size of Suffix Automata: " << sizeof(SuffixAutomaton::sa) / 1e9 << " GB" << endl;
    // string s = "TGAGCTTGCA";
    // // cin >> s;

    // buildMaw(s, 3, 9);
    // buildMawBrute(s, 3, 9);
    // cout << "SOLUTION:" << endl;
    // for(int i = 0; i < cur; i++)cout << ans[i] << endl;
    // cout << "BRUTE" << endl;
    // for(int i = 0; i < bruteCur; i++)cout << bruteAns[i] << endl;
    
    
    
    
}