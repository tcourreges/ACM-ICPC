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

#define NMAX 50001
#define MMAX 100001
#define D 16
#define dmax 1000000000

int N, M, s, t, nbtest;

struct trans
{
    int to, d;
    trans(int _to, int _d): to(_to), d(_d) {}
};

vector<trans> g[NMAX];

bool visited[NMAX];
int dres;
void initdfs()
{
    dres=dmax+1;
    for(int i=1; i<=N; i++)
        visited[i]=false;
}

void dfs(int x, int dtmp)
{
    //cout << "visiting " << x << " d=" << dtmp << " dres="<< dres<< endl;

    for(int j=0; j<g[x].size(); j++)
    {
        int to=g[x][j].to;
        int d=g[x][j].d;

        if(!visited[to])
        {
            d=max(d, dtmp);
            if(d<=dres)
            {
                if(to==t)
                    dres=d;
                else
                {
                    visited[to]=true;
                    dfs(to, d);
                    visited[to]=false;
                }
            }
       }
    }
}



int main()
{
    bool first=true;
    while(true)
    {
        int sc=scanf("%d%d", &N, &M);
        if(sc!=2)
            return 0;

        if(first)
            first=false;
        else
            cout << endl;

        for(int i=1; i<=N; i++)
            g[i].clear();

        for(int i=0; i<M; i++)
        {
            int x, y, d;
            scanf("%d%d%d", &x, &y, &d);
            //cout << x <<" "<< y<<" " << d << endl;
            g[x].push_back(trans(y,d));
            g[y].push_back(trans(x,d));
        }

        /*
        cout << endl << endl;
        for(int i=1; i<=    N; i++)
            for(int j=0; j<g[i].size(); j++)
                cout << i << " " << g[i][j].to << " " << g[i][j].d << endl;
        */

        scanf("%d", &nbtest);
        while(nbtest--)
        {
            scanf("%d%d", &s, &t);
            initdfs();
            dfs(s,0);
            cout << dres << endl;
            //cout << "resultat" << endl;
        }
    }
    return 0;
}
