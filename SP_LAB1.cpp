#include<bits/stdc++.h>
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define all(a) a.begin(),a.end()
#define ios ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define endl '\n'
#define ull unsigned long long
#define iter set<int>::iterator
#define iter1 set<int>::iterator
#define y1 ajsdkflhasdkf
using namespace std;

const int N=1e6+7;
const int mod=1e9+7;
const ld eps=1e-9;

map<char,bool>usedChars;
map<string,bool>usedStrings;

main ()
{
    ios;
    freopen("input.txt","r",stdin);
    string s;
    
    while(cin>>s){
        usedChars.clear();
        bool stringIsOk=1;
        for (int i=0;i<s.size();++i){
            if (usedChars[s[i]]){
                stringIsOk=0;
                break;
            }
            else {
                usedChars[s[i]]=1;
            }
        }
        if (stringIsOk){
            if (!usedStrings[s]){
                cout<<s<<endl;
                usedStrings[s]=1;
            }
        }
    }
}
//������
//10 1
//cbcccaacaa
//7 8
