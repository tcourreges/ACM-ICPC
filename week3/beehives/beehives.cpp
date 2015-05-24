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

#define NMAX 501
#define MMAX 20001

int nbcase, N, M, a, b;
vector<int> g[NMAX];
int resultat;
int pere[NMAX]; //-2 origine, -1 undef, i>=0 sommet par lequel on arrive
int dist[NMAX];
list<int> q;

bool liaison(int a, int b)
{
    return (std::find(g[a].begin(), g[a].end(), b)!=g[a].end());
}

int c1, c2;
int longueur_cycle(int a, int b)
{
    //cout << a << " " << b << endl;
    if(!(a==c1&&b==c2))
    {
        if(a==b)
            return 1;
        if(liaison(a,b))
            return 2;
    }

    int aa=NMAX+1, bb=NMAX+1;
    if(pere[a]>=0)
        aa=longueur_cycle(pere[a],b);
    if(pere[b]>=0)
        bb=longueur_cycle(a,pere[b]);
    return 1+min(aa,bb);
}

int bfs(int orig)
{
    //cout << "bfs" << endl;
    q.clear();
    q.push_back(orig);

    pere[orig]=-2;
    dist[orig]=0;

    while(!q.empty())
    {
       int u = q.front();
       q.pop_front();

       //cout<<u<<" "<<dist[u]<<endl;

       //printf("salut");

       for(int j=0; j<g[u].size(); j++)
       {
           int x = g[u][j];
           //cout << "->" << x <<" pere="<<pere[x];

           if(pere[x]==-1)
           {
               pere[x]=u;
               dist[x]=dist[u]+1;
               //cout <<" newdist="<<dist[x];
               q.push_back(x);
           }
           else if(pere[u]!=x)
           {
               c1=u; c2=x;
               resultat=min(resultat, longueur_cycle(u, x));
           }
           //cout << endl;
        }
    }
    return resultat;
}

int main()
{
    scanf("%d", &nbcase);
    int c=1;
    while(nbcase--)
    {
        scanf("%d %d", &N, &M);
        for(int i=0; i<N; i++)
            g[i].clear();
        for(int i=0; i<M; i++)
        {
            scanf("%d %d", &a, &b);
            g[a].push_back(b);
            g[b].push_back(a);
        }

        /*
        cout << endl << endl;
        for(int i=0; i<N; i++) {
            for(int j=0; j<g[i].size(); j++)
                cout << g[i][j];
            cout << endl;
        }*/

        for(int i=0; i<N; i++)
            pere[i]=-1;
        resultat=NMAX+1;

        int i=0;
        //on cherche un cycle;
        while(resultat>3 && i<N)
        {
            if(pere[i]==-1)
                bfs(0);
            i++;
        }

        printf("Case %d: ", c);
        if(resultat==NMAX+1)
            printf("impossible\n");
        else
            printf("%d\n", resultat);
        c++;
    }
    return 0;
}
