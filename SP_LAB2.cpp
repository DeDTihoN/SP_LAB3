#pragma GCC optimize ("O3")
#pragma GCC optimize ("Ofast")
#pragma GCC optimize ("unroll-loops")
#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define all(a) a.begin(),a.end()
#define endl '\n'
#define ull unsigned long long
#define y1 ljhadglkjsadf
#define ios ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define iter set< pair<int,ll> >::iterator
#define iter1 set<int>::iterator
using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_set=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

template<class T>
using ordered_multiset=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rnd1(chrono::steady_clock::now().time_since_epoch().count());

//find_by_order
//order_of_key

const int N=1e4+7;
const int ALPHABET_SIZE=26+1;
const int inf=1e9+5;
const int mod=998244353;
const int LEN=(1LL<<19);
const ld eps=1e-9;

//const int MAX_MEM=1e8;
//int mpos=0;
//char mem[MAX_MEM];
//
//inline void * operator new(size_t n){
//    char *res=mem+mpos;
//    mpos+=n;
//    if (mpos>=MAX_MEM){
//        cout<<"BAD"<<endl;
//        exit(0);
//    }
//    return (void*)res;
//}
//
//inline void operator delete(void *) {}

string char_edge_to_string(int Char)
{
    if (Char==0)return "eps";
    else return string(1,Char+'a'-1);
}

struct finite_automaton
{
    int A,S,s0;
    vector<int>F;
    vector< vector< vector<int> > >f;
    string w0;
    vector<vector<pair< pair<int,int>, int > > > p;
    finite_automaton(int A,int S,int s0)
    {
        this->A=A;
        this->S=S;
        this->s0=s0;
        F.clear();
        f.clear();
        f.resize(S,vector< vector<int> >(A+1,vector<int>(0)));
    }
    void add_final_state(int x)
    {
        F.pb(x);
    }
    void add_transition(int q,string a,int t)
    {
        if (a=="eps"){
            f[q][0].pb(t);
        }
        else {
            f[q][a[0]-'a'+1].pb(t);
        }
    }
    void init_wo(string w0)
    {
        this->w0=w0;
        p.resize(S,vector< pair<pair<int,int>,int> >(w0.size()+1,mp(mp(-1,-1),-1)));
        p[s0][0]=mp(mp(s0,0),0);
    }
};

finite_automaton read_automaton()
{
    freopen("input.txt","r",stdin);
    int A,S,s0;
    cin>>A>>S>>s0;
    finite_automaton Automaton(A,S,s0);
    int F;
    cin>>F;
    for (int i=0;i<F;i++)
    {
        int x;
        cin>>x;
        Automaton.add_final_state(x);
    }
    string q,t;
    string a;
    while(cin>>q)
    {
        if (cin>>a){
            cin>>t;
            Automaton.add_transition(stoi(q),a,stoi(t));
        }
        else {
            string w0;
            w0=q;
            Automaton.init_wo(w0);
        }
    }
    return Automaton;
}

void UpdateWithEpsilon(finite_automaton& Automaton,vector<int>&Ver,int pref)
{
    bool used[Automaton.S];
    for (int i=0;i<Automaton.S;i++) used[i]=0;
    for (int i=0;i<Ver.size();++i)used[Ver[i]]=1;
    while(true){
        bool flagFindedNewState=0;
        for (int i=0;i<Ver.size();++i){
            int v=Ver[i];
            for (int j=0;j<Automaton.f[v][0].size();++j){
                int to=Automaton.f[v][0][j];
                if (!used[to]){
                    Ver.pb(to);
                    used[to]=1;
                    flagFindedNewState=1;
                    Automaton.p[to][pref]=mp(mp(v,pref),0);
                }
            }
        }
        if (!flagFindedNewState) break;
    }
    return;
}

void MakeTransition(finite_automaton& Automaton,vector<int>&Ver,int Char,int pref)
{
    vector<int>NewVerState;
    bool used[Automaton.S];
    for (int i=0;i<Automaton.S;i++) used[i]=0;
    for (int i=0;i<Ver.size();i++)
    {
        int v=Ver[i];
        for (int j=0;j<Automaton.f[v][Char].size();j++)
        {
            int to = Automaton.f[v][Char][j];
            if (!used[to]){
                NewVerState.pb(to);
                used[to]=true;
                Automaton.p[to][pref]=mp(mp(v,pref-1),Char);
            }
        }
    }
    UpdateWithEpsilon(Automaton,NewVerState,pref);
    Ver=NewVerState;
}

string getW(finite_automaton& Automaton )
{
    string w0=Automaton.w0;
    int s0=Automaton.s0;
    vector<int>States(1,s0);
    UpdateWithEpsilon(Automaton,States,0);
    for (int i=0;i<w0.size();++i){
        MakeTransition(Automaton,States,w0[i]-'a'+1,i+1);
    }
    int S=Automaton.S;
    bool used[S];
    pair<int,int> P[S];
    for (int i=0;i<S;++i){
        used[i]=0;
        P[i]=mp(-1,-1);
    }
    for (int i=0;i<States.size();++i){
        used[States[i]]=1;
    }
    while(true){
        bool flagFindedNewState=0;
        for (int i=0;i<States.size();++i){
            int v=States[i];
            for (int Char=0;Char<=Automaton.A;++Char){
                for (int j=0;j<Automaton.f[v][Char].size();++j){
                    int to=Automaton.f[v][Char][j];
                    if (!used[to]){
                        States.pb(to);
                        used[to]=1;
                        flagFindedNewState=1;
                        P[to]=mp(v,Char);
                    }
                }
            }
        }
        if (!flagFindedNewState) break;
    }
    int FinalState=-1;
    for (int i=0;i<Automaton.F.size();++i){
        if (used[Automaton.F[i]]){
            FinalState=Automaton.F[i];
            break;
        }
    }
    if (FinalState==-1) return "w string not found";
    else {
        vector<pair<int,string>>path;
        int v=FinalState;
        while(P[v].ff!=-1){
            path.pb(mp(v,char_edge_to_string(P[v].ss)));
            v=P[v].ff;
        }
        int pref=Automaton.w0.size();
        vector<vector< pair< pair<int,int>, int > > >P_Pref=Automaton.p;
        while(pref>0 || v!=s0){
            path.pb(mp(v,char_edge_to_string(P_Pref[v][pref].ss)));
            pair<int,int>new_state = P_Pref[v][pref].ff;
            v=new_state.ff;
            pref=new_state.ss;
        }
        reverse(all(path));
        string ans="";
        string first_line="";
        string second_line="";
        for (int i=0;i<path.size();++i){
            string s1=path[i].ss,s2=to_string(path[i].ff);
            int mx=max(s1.size(),s2.size());
            while(s1.size()<mx) s1+=" ";
            while(s2.size()<mx) s2+=" ";
            first_line+=s1;
            second_line+=s2;
            first_line+=" ";
            second_line+=" ";
        }
        ans+=first_line;
        ans+="\n";
        ans+=second_line;
        return ans;
    }
}

main ()
{
    ios;
    finite_automaton Automaton=read_automaton();
    cout<<getW(Automaton);
}
//8 4
//1 2 3 1 2 3 1 2
//1 2
//2 3
//4 5
//6 7
