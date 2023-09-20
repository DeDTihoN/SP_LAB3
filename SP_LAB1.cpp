#include<bits/stdc++.h>
#include <locale>
#include <iostream>
#include<codecvt>
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#define ff first
#define ss second
#define pb push_back
#define mp make_pair
#define ll long long
#define ld long double
#define all(a) a.begin(),a.end()
#define ull unsigned long long
#define iter set<int>::iterator
#define iter1 set<int>::iterator
#define y1 ajsdkflhasdkf
using namespace std;

const int N=1e6+7;
const int mod=1e9+7;
const ld eps=1e-9;

map<wchar_t, bool> usedChars;
map<wstring, bool> usedStrings;

wstring convertToWide(const string& s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring wide = converter.from_bytes(s);
    return wide;
}

string convertToString(const wstring& s) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::string narrow = converter.to_bytes(s);
    return narrow;
}

wchar_t englishOrUkranianToLowerCase(wchar_t ch)
{
    if (ch>=L'A' && ch<=L'Z')
        ch+=32;
    if(ch>=L'А' && ch<=L'Я')
        ch+=32;
    if (ch==L'Ї' || ch==L'Є' || ch==L'І')ch+=80;
    return ch;
}

bool checkWord(string s) {
    auto& facet = std::use_facet<std::ctype<wchar_t>>(std::locale());
    wstring wide = convertToWide(s);
    usedChars.clear();
    for (wchar_t ch : wide) {
        ch = englishOrUkranianToLowerCase(ch);
        if (usedChars[ch]) {
            return false;
        }
        usedChars[ch] = true;
    }
    return true;
}

bool checkIfWordIsUnique(const string& s) {
    if (usedStrings[convertToWide(s)]) {
        return false;
    }
    usedStrings[convertToWide(s)] = true;
    return true;
}

int main() {
   // _wsetlocale(LC_ALL, L"uk_UA.UTF-8");
   // _setmode(_fileno(stdout), _O_U8TEXT);
   // _setmode(_fileno(stdin), _O_U8TEXT);
   // SetConsoleCP(CP_UTF8);
   // SetConsoleOutputCP(CP_UTF8);
    ifstream file("input.txt");
    if (!file.is_open()) {
        wcerr << L"Відсутній файл input.txt у папці проекту" << endl;
        return 1; 
    }

    string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    file.close();

    // regular expression to match Ukrainian and English words
    regex wordRegex("([a-zA-Z'-]+)|([АаБбВвГгДдЕеЖжЗзИиЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщЬьЮюЯяҐґЄєІіЇї'-]+)");

    smatch matches;
    string::const_iterator searchStart(content.cbegin());

    while (regex_search(searchStart, content.cend(), matches, wordRegex)) {
        string word = matches.str(); 

        if (checkWord(word) && checkIfWordIsUnique(word)) {
            cout << word << endl;
        }
        searchStart = matches[0].second; 
    }

    return 0;
}
