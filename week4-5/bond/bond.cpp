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

struct Edge
{
    int a, b, d;
    Edge() {}
    Edge(int _a, int _b, int _d): a(_a), b(_b), d(_d) {}
    bool operator<(const Edge& e2) const {return d<e2.d;}
};
vector<Edge> edges;

vector<Edge> tree[NMAX];


//-----------------------------------

int connexe[NMAX];

void initConnexe()
{
    for(int i=1; i<=N; i++)
        connexe[i]=i;
}

void updateConnexe(int previous, int next)
{
    for(int i=1; i<=N; i++)
        if(connexe[i]==previous)
            connexe[i]=next;
}

bool pasuncycle(Edge e)
{
    if(connexe[e.a]!=connexe[e.b])
    {
        updateConnexe(connexe[e.b], connexe[e.a]);
        return true;
    }
    return false;
}

void resetTree()
{
    for(int i=0; i<=N; i++)
        tree[i].clear();
}

int kruskal()
{
    initConnexe();
    resetTree();

    for(int i=0; i<edges.size(); i++)
    {
        Edge e=edges[i];
        if(pasuncycle(e))
        {
            int x=e.a, y=e.b;
            tree[x].push_back(e);
            tree[y].push_back(e);
        }
    }
}
//-----------------------------------------

int depth[NMAX];
int pere[NMAX];
bool visited[NMAX];
int dang[NMAX];


list<int> q;
int bfs()
{
    q.clear();
    q.push_back(1);

    memset(visited, 0, N+1);
    memset(pere, 0, N+1);
    memset(dang, 0, N+1);
    memset(depth, 0, N+1);

    visited[1]=true;

    while(!q.empty())
    {
        int u = q.front();
        q.pop_front();

        //cout << "node " << u<<endl;

        for(int j=0; j<tree[u].size(); j++)
        {
            Edge e=tree[u][j];
            int x=e.a;
            if(x==u)
                x=e.b;

            //cout << "voisin " << x << endl;

            if(!visited[x])
            {
                pere[x]=u;
                depth[x]=depth[u]+1;
                visited[x]=true;
                dang[x]=max(dang[u],e.d);

                q.push_back(x);

                //cout << u << " --- "<< e.d << " ---> " << x << endl;
            }
        }
    }
}

int find(int x, int y, int d)
{
    //cout << x << " " << y << " " << d << endl;

    if(x==y)
        return d;

    if(depth[x]>depth[y])
        find(pere[x], y, max(d,dang[x]));
    else
        find(x, pere[y], max(d,dang[y]));
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

        edges.clear();
        for(int i=0; i<M; i++)
        {
            int x, y, d;
            scanf("%d%d%d", &x, &y, &d);
            //cout << x <<" "<< y<<" " << d << endl;
            edges.push_back(Edge(x,y,d));
        }
        sort(edges.begin(), edges.end());

        kruskal();
        bfs();

        scanf("%d", &nbtest);
        while(nbtest--)
        {
            scanf("%d%d", &s, &t);
            cout << find(s,t,0) << endl;
        }
    }
    return 0;
}
