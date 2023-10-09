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


char keywords[50][15]={"abstract","assert","boolean","break",
"byte","catch","case","char","const",
"continue","class","default","do",
"double","else","enum","extends",
"final","finally","float","for",
"goto","if","import","implements",
"int","interface","insatnceof","long",
"native","new","package","private",
"public","protected","return","short",
"static","switch","strictfp","super",
"synchronized","this","throw","throws","transient",
"try","volatile","void","while"};

const string RegexNumber = R"(0x[0-9A-F]+|\d+(\.\d*)?)";
const string RegexString = R"((\"[^\"]*\"))";
const string RegexChar = R"('[^']')";
const string RegexComment = R"(/\*[\s\S]*?\*/|//.*)";
const string RegexReservedWord = R"(\b(abstract|assert|boolean|break|byte|catch|case|char|const|continue|class|default|do|double|else|enum|extends|final|finally|float|for|goto|if|import|implements|int|interface|instanceof|long|native|new|package|private|public|protected|return|short|static|switch|strictfp|super|synchronized|this|throw|throws|transient|try|volatile|void|while)\b)";
const string RegexOperator = R"(\-\-|\+\+|>>>|>>=|<<=|>>>|>>|<<|\^=|\|=|&=|%=|/=|\*=|\-=|\+=|\|\||&&|>=|<=|!=|==|:|\?|=|<|!|~|\^|\||&|%|/|\*|\-|\+)";
const string RegexPunctuation = R"([;{},\(\)\[\]\.])";
const string RegexIdentifier = R"([a-zA-Z_]\w*)";
const string RegexSpaces = R"(\s+|$)";;
const string RegexAnything = R"([^;,"'\[\]\(\)\{\}\.\+\-\*\/%&\|\^~!<>?=:!\w\s]+)";

void solve_regular_expressions()
{
    // read input.txt
    ifstream Input("input.txt");
    string input((istreambuf_iterator<char>(Input)), istreambuf_iterator<char>());
    regex regexNumbers(RegexNumber); 
    regex regexStrings(RegexString);
    regex regexChars(RegexChar);
    regex regexComments(RegexComment); 
    regex regexReservedWords(RegexReservedWord); 
    regex regexOperators(RegexOperator); 
    regex regexPunctuation(RegexPunctuation); 
    regex regexIdentifiers(RegexIdentifier); 
    regex regexSpaces(RegexSpaces);
    regex regexAnything(RegexAnything);
    vector<pair<string, string>> lexemesInOrder; // Зберігаємо лексеми та їх типи в порядку зустрічі

    // Пошук та класифікація лексем
    regex regexAll(RegexSpaces + "|" + RegexNumber + "|" + RegexString + "|" + RegexChar + "|" + RegexComment + "|" + RegexReservedWord + "|" + RegexOperator + "|" + RegexPunctuation + "|" + RegexIdentifier + "|" + RegexAnything);
    auto words_begin = sregex_iterator(input.begin(), input.end(), regexAll);
    auto words_end = sregex_iterator();
    
    for (sregex_iterator it = words_begin; it != words_end; ++it) {
        string lexeme = it->str();
        string type;
        if (std::regex_match(lexeme, regexSpaces)) continue; // Пропускаємо пробіли
        if (std::regex_match(lexeme, regexNumbers)) {
            type = "Number";
        } else if (regex_match(lexeme, regexStrings)) {
            type = "String";
        } else if (regex_match(lexeme, regexChars)) {
            type = "Char";
        } else if (regex_match(lexeme, regexComments)) {
            type = "Comment";
        } else if (regex_match(lexeme, regexReservedWords)) {
            type = "Reserved Word";
        } else if (regex_match(lexeme, regexOperators)) {
            type = "Operator";
        } else if (regex_match(lexeme, regexPunctuation)) {
            type = "Punctuation";
        } else if (regex_match(lexeme, regexIdentifiers)) {
            type = "Identifier";
        }else {
            type = "Error";
        }
        lexemesInOrder.push_back(make_pair(lexeme, type));
    }
    Input.close();
    freopen("output1.txt", "w", stdout);
    for (const auto& entry : lexemesInOrder) {
        cout << "< " << entry.first << " , " << entry.second << " >\n";
    }
}

struct State {
    map<char, int> transitions;
    string type;
};
State states[1000];
int all=0;
const int Identifier_V=500;

void add_transition(int from,int to,const string& characters)
{
    for (char c : characters) {
        states[from].transitions[c] = to;
    }
}

void add_digit_transition()
{
    int v1 = ++all;
    add_transition(0, v1, "123456789");
    add_transition(v1, v1, "0123456789");
    states[v1].type = "Number";
    int v2=++all;
    add_transition(v2, v2, "0123456789");
    states[v2].type = "Number";
    int v3=++all;
    add_transition(0, v3, "0");
    int v5=++all;
    add_transition(v1, v5, ".");
    add_transition(v3, v5, ".");
    add_transition(v5, v2, "0123456789");
    int v4=++all;
    add_transition(v3, v4, "x");
    add_transition(v4, v4, "0123456789ABCDEF");
    states[v3].type = "Number";
    states[v4].type = "Number";
}

void add_string_transition()
{
    int v1 = ++all;
    add_transition(0, v1, "\"");
    string all_c_string_characters = "";
    for (int c = 0; c < 128; ++c) {
        char ch=c;
        if (ch != '\"' && ch!='\n') {
            all_c_string_characters += ch;
        }
    }
    add_transition(v1, v1, all_c_string_characters);
    int v2 = ++all;
    add_transition(v1, v2, "\"");
    states[v2].type = "String";
    int v3 = ++all;
    add_transition(0, v3, "'");
    int v4=++all;
    add_transition(v3, v4, all_c_string_characters);
    int v5=++all;
    add_transition(v4, v5, "'");
    states[v5].type = "Char";
}

int add_single_word(string s,string type)
{
    int last=0;
    for (int i=0;i<s.size();++i){
        char c=s[i];
        if (states[last].transitions[c] && states[last].transitions[c]!=Identifier_V){
            last=states[last].transitions[c];
        }
        else {
            int v=++all;
            states[last].transitions[c]=v;
          //  cout<<last<<' '<<c<<' '<<v<<" ? "<<endl;
            last=v;
            if (type=="Reserved Word"){
                states[last].type = "Identifier";
                add_transition(last, Identifier_V, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789");
            }
        }
    }
    states[last].type = type;
    return last;
    // last=0;
    // for (int i=0;i<s.size();++i){
    //     char c=s[i];
    //     last=states[last].transitions[c];
    //     cout<<last<<' '<<c<<' '<<states[last].type<<" ! "<<endl;
    // }
    // cout<<" ---------- "<<endl;
}

void add_comment_transition()
{
    int v2=add_single_word("/*", "Error");
    string all_c_comment_characters = "";
    for (int c = 0; c < 128; ++c) {
        char ch=c;
        if (ch!='*' && ch!='/')all_c_comment_characters += ch;
    }
    add_transition(v2, v2, all_c_comment_characters+"/");
    int v3 = ++all;
    add_transition(v2, v3, "*");
    int v4 = ++all;
    add_transition(v3,v2,all_c_comment_characters);
    add_transition(v3, v3, "*");
    add_transition(v3, v4, "/");
    states[v4].type = "Comment";
}

void add_two_slashes_comment_trasition()
{
    int v2=add_single_word("//", "Comment");
    string all_c_comment_characters = "";
    for (int c = 0; c < 128; ++c) {
        char ch=c;
        if (ch != '\n') {
            all_c_comment_characters += ch;
        }
    }
    add_transition(v2, v2, all_c_comment_characters);
}

void add_all_operators()
{
    add_single_word("++", "Operator");
    add_single_word("--", "Operator");
    add_single_word("+=", "Operator");
    add_single_word("-=", "Operator");
    add_single_word("*=", "Operator");
    add_single_word("/=", "Operator");
    add_single_word("%=", "Operator");
    add_single_word("&=", "Operator");
    add_single_word("|=", "Operator");
    add_single_word("^=", "Operator");
    add_single_word("<<", "Operator");
    add_single_word(">>", "Operator");
    add_single_word(">>>", "Operator");
    add_single_word("<<=", "Operator");
    add_single_word(">>=", "Operator");
    add_single_word(">>>=", "Operator");
    add_single_word("==", "Operator");
    add_single_word("!=", "Operator");
    add_single_word("<=", "Operator");
    add_single_word(">=", "Operator");
    add_single_word("&&", "Operator");
    add_single_word("||", "Operator");
    add_single_word("+", "Operator");
    add_single_word("-", "Operator");
    add_single_word("*", "Operator");
    add_single_word("/", "Operator");
    add_single_word("%", "Operator");
    add_single_word("&", "Operator");
    add_single_word("|", "Operator");
    add_single_word("^", "Operator");
    add_single_word("~", "Operator");
    add_single_word("!", "Operator");
    add_single_word("=", "Operator");
    add_single_word("<", "Operator");
    add_single_word(">", "Operator");
    add_single_word("?", "Operator");
    add_single_word(":", "Operator");
}

void add_all_punctuations()
{
    int v1=++all;
    add_transition(0, v1, ";{}(),[].");
    states[v1].type = "Punctuation";
}

int add_identifier_transition()
{
    for (char c = 'a'; c <= 'z'; ++c) {
        if (!states[0].transitions[c]){
            states[0].transitions[c] = Identifier_V;
        }
    }
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (!states[0].transitions[c]){
            states[0].transitions[c] = Identifier_V;
        }
    }
    if (!states[0].transitions['_']){
        states[0].transitions['_'] = Identifier_V;
    }

    add_transition(Identifier_V, Identifier_V, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789");
    states[Identifier_V].type = "Identifier";
    return Identifier_V;
}

void add_reserved_words()
{
    for (int i=0;i<50;++i){
        add_single_word(keywords[i], "Reserved Word");
    }
}

void add_space_words_and_error()
{
    int v1 = ++all;
    add_transition(0, v1, " \n\t");
    add_transition(v1, v1, " \n\t");
    states[v1].type = "Space";
    int v2 = ++all;
    string error_symbols = "";
    for (int c = 0; c < 128; ++c) {
        char ch=c;
        if (!states[0].transitions[ch]){
            error_symbols += ch;
        }
    }
    add_transition(0, v2, error_symbols);
    add_transition(v2, v2, error_symbols);
    states[v2].type = "Error";
}

void build_automaton()
{
    add_reserved_words();
    add_identifier_transition();
    add_digit_transition();
    add_string_transition();
    add_comment_transition();
    add_two_slashes_comment_trasition();
    add_all_operators();
    add_all_punctuations();
    add_space_words_and_error();
}

void solve_with_automaton()
{
    ifstream Input("input.txt");
    string input((istreambuf_iterator<char>(Input)), istreambuf_iterator<char>());
    int currentState = 0;
    string currentLexeme = "";
    vector<pair<string, string>> lexemesInOrder; // Зберігаємо лексеми та їх типи в порядку зустрічі
    queue<char> q;
    for (char c : input) {
        q.push(c);
    }
    while(q.size()>0){
        char c=q.front();
        if (states[currentState].transitions[c]){
            currentState = states[currentState].transitions[c];
            currentLexeme += c;
            q.pop();
        }
        else {
            if (currentLexeme.size()>0){
                if (states[currentState].type!="")lexemesInOrder.push_back(make_pair(currentLexeme, states[currentState].type));
                else lexemesInOrder.push_back(make_pair(currentLexeme, "Error"));
            }
            currentLexeme = "";
            currentState = 0;
        }
    }
    if (currentLexeme.size()>0){
        lexemesInOrder.push_back(make_pair(currentLexeme, states[currentState].type));
    }
    Input.close();
    freopen("output2.txt", "w", stdout);
    for (const auto& entry : lexemesInOrder) {
      if (entry.second!="Space")  {
            cout << "< " << entry.first << " , " << entry.second << " >\n";
      }
    }

}

main ()
{
    //ios;
    build_automaton();
    auto start1 = chrono::high_resolution_clock::now();
    solve_regular_expressions();
    auto finish1 = chrono::high_resolution_clock::now();
    auto start2 = chrono::high_resolution_clock::now();
    solve_with_automaton();
    auto finish2 = chrono::high_resolution_clock::now();
    freopen("CON", "w", stdout);
    auto time1 = chrono::duration_cast<chrono::nanoseconds>(finish1 - start1).count();
    auto time2 = chrono::duration_cast<chrono::nanoseconds>(finish2 - start2).count();
    cout << "Час виконання регулярними виразами: " << (ld)(time1 * 1e-6) << " секунд" << endl;
    cout << "Час виконання автоматом: " << (ld)(time2 * 1e-6) << " секунд" << endl;
}
//8 4
//1 2 3 1 2 3 1 2
//1 2
//2 3
//4 5
//6 7
