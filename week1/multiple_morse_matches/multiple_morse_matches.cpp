#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <math.h>

using namespace std;

int nbcase, N;
string code, word;
vector<string> words;
vector<int> cache; // cache[i]==find(code, i)

map<char,string> letter;

void fillLetter()
{
    letter['A'] = ".-";
    letter['B'] = "-...";
    letter['C'] = "-.-.";
    letter['D'] = "-..";
    letter['E'] = ".";
    letter['F'] = "..-.";
    letter['G'] = "--.";
    letter['H'] = "....";
    letter['I'] = "..";
    letter['J'] = ".---";
    letter['K'] = "-.-";
    letter['L'] = ".-..";
    letter['M'] = "--";
    letter['N'] = "-.";
    letter['O'] = "---";
    letter['P'] = ".--.";
    letter['Q'] = "--.-";
    letter['R'] = ".-.";
    letter['S'] = "...";
    letter['T'] = "-";
    letter['U'] = "..-";
    letter['V'] = "...-";
    letter['W'] = ".--";
    letter['X'] = "-..-";
    letter['Y'] = "-.--";
    letter['Z'] = "--..";
}

string toMorse(string s)
{
    string res="";
    for (int i=0; i<s.size(); i++)
        res += letter[s[i]];
    return res;
}

int find(string& _code, int startpos)
{
    //si on a déjà calculé, on recupere le resultat
    if(cache[startpos] != -1)
        return cache[startpos];

    //sinon on essaie de caser chaque mot au début
    int res = 0;
    for(int i=0 ; i < words.size(); i++)
    {
        int l=words[i].size();
        if(_code.compare(startpos, l, words[i]) == 0)
        {
            //cout << "match for word " << words[i] << endl;

            if(startpos + l == _code.size()) //match direct
                res++;
            else //il reste des caractères
                res += find(code, startpos+l);
        }
    }
    cache[startpos] = res;
    return res;
}

int main()
{
    fillLetter();
    cin >> nbcase;
    for (int i=0; i<nbcase; i++)
    {
        cin >> code;
        cin >> N;

        //cout << "code= " << code << endl;

        words.clear();
        cache.clear();
        cache = vector<int>(code.size(), -1); //-1 pour "non calculé"

        //on traduit directement le dictionnaire en morse
        for(int j=0; j<N; j++)
        {
            cin >> word;
            //cout << word << " = " << toMorse(word) << endl;
            words.push_back(toMorse(word));
        }

        //recursion
        cout << find(code, 0) << endl;

        if(i<nbcase -1)
            cout << endl;
    }

    return 0;
}
