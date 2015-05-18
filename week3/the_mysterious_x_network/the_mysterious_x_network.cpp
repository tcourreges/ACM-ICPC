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

#define NMAX 100000

int nbcase, N, c1, c2, c, nc, ci;
vector<int> g[NMAX];
bool visited[NMAX];
int d[NMAX];

list<int> q;

int bfs()
{
    q.clear();
    q.push_back(c1);
    d[c1]=-1;
    memset(visited, 0, N+1);
    visited[c1]=true;

    while(!q.empty())
    {
        //on affiche t=front et on le vire de la queue
        int u = q.front();
        q.pop_front();

        if(u==c2)
            return d[u];

        for(int j=0; j<g[u].size(); j++)
        {
            int x = g[u][j];

            if(!visited[x])
            {
                visited[x]=true;
                d[x]=d[u]+1;
                q.push_back(x);
            }
        }
    }
}

int main()
{
    scanf("%d", &nbcase);
    while(nbcase--)
    {
        scanf("%d", &N);

        for(int i=0; i<N; i++)
        {
            scanf("%d %d", &c, &nc);
            g[i].clear();
            while(nc--)
            {
                scanf("%d", &ci);
                g[i].push_back(ci);
            }
        }
        scanf("%d %d", &c1, &c2);

        /*
        for(int i=0; i<N; i++) {
            for(int j=0; j<g[i].size(); j++)
                cout << g[i][j];
            cout << endl;
        }
        cout << c1 << "->" << c2 << endl;
        */

        cout << c1 << " " << c2 << " " << bfs() << endl;

        if(nbcase>0)
            cout << endl;
    }
    return 0;
}
