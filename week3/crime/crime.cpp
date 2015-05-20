#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdio>
#include <string>
#include <math.h>
#include <list>
#include <cstring>

using namespace std;

#define NMAX 1001

int nbcase, N, M, c1, c2;
vector<int> g[NMAX];
int part[NMAX]; //2 undef, 0/1 partition
int resultat;

list<int> q;

int bfs(int orig)
{
    q.clear();
    q.push_back(orig);

    part[orig]=1;
    int card[2]; card[0]=0, card[1]=1;

    while(!q.empty())
    {
        //on affiche t=front et on le vire de la queue
        int u = q.front();
        q.pop_front();

        //cout << u << "--" << part[u] << endl;

        for(int j=0; j<g[u].size(); j++)
        {
            int x = g[u][j];
            //cout << x << " "<< part[u] << endl;
            if(part[x]==2)
            {
                part[x]=1-part[u];
                card[part[x]]++;
                q.push_back(x);
            }
            else if(part[x]==part[u])
            {
                // cout << "aa";
                return false;
            }
        }
    }
    resultat+=min(card[0],card[1]);
    return true;
}

bool search()
{
    resultat=0;
    for(int i=1; i<=N; i++)
        part[i]=2;

    for(int i=1; i<=N; i++)
    {
        //on verifie que la bfs marche depuis chaque sommet pas marqué(=d'une nouvelle composante connexe)
        if(part[i]==2 && !bfs(i))
            return false;
    }
    return true;
}

int main()
{
    bool firstcase=true;
    while(1)
    {
        int end=scanf("%d %d", &N, &M);
        if(end==EOF)
            break;

        for(int i=1; i<=N; i++)
            g[i].clear();

        while(M--)
        {
            scanf("%d %d\n", &c1, &c2);
            //cout << c1 << c2 << "--"<<endl;
            g[c1].push_back(c2);
            g[c2].push_back(c1);
        }

        /*
        for(int i=1; i<=N; i++) {
            for(int j=0; j<g[i].size(); j++)
                cout << g[i][j];
            cout << endl;
        }*/

        if(search())
            cout << resultat << endl;
        else
            cout << "Impossible" << endl;
    }
    return 0;
}
