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
#define MMAX 1001

struct Point
{
    int x, y;
    Point() : x(0), y(0) {}
    Point(int _x, int _y) : x(_x), y(_y) {}
    int distTo(Point p2) {return (p2.x-x)*(p2.x-x) + (p2.y-y)*(p2.y-y);}
};
Point nodes[NMAX];

struct Edge
{
    int a, b, dist;
    Edge() : a(0), b(0), dist(0) {}
    Edge(int _a, int _b) : a(_a), b(_b), dist(nodes[a].distTo(nodes[b])) {}
    bool operator<(const Edge& e2) const {return dist<e2.dist;}
};
vector<Edge> edges;

vector<int> subnetworks[10];
int cost[10];

int nbcase, n, q;

//-----------------------------------------------------
int connexe[NMAX];
/*void displayConnexe()
{
    for(int i=1; i<=n; i++)
        cout << connexe[i];
    cout << endl;
}*/

void initConnexe()
{
    for(int i=1; i<=n; i++)
        connexe[i]=i;
}

void updateConnexe(int previous, int next)
{
    for(int i=1; i<=n; i++)
        if(connexe[i]==previous)
            connexe[i]=next;
}

bool pasuncycle(Edge e)
{
    //cout << "arete " << e.a << e.b << " " << connexe[e.a] << connexe[e.b];
    if(connexe[e.a]!=connexe[e.b]) {
        updateConnexe(connexe[e.b], connexe[e.a]);
        //cout << "->ajout" << endl;
        //displayConnexe();
        return true;
    }
    //cout << endl;
    return false;
}

int kruskal()
{
    int res=0;
    for(int i=0; i<edges.size(); i++)
    {
        if(pasuncycle(edges[i]))
            res+=edges[i].dist;
    }
    return res;
}

bool selected(int setup, int sub)
{
    int tmp=setup;
    for(int i=0; i<sub; i++)
        tmp=tmp/2;
    return tmp%2;
}

int main()
{
    cin >> nbcase;
    while(nbcase--)
    {
        cin >> n >> q;

        for(int i=0; i<q; i++)
            subnetworks[i].clear();

        for(int i=0; i<q; i++)
        {
            int nb;
            scanf("%d%d", &nb, &cost[i]);
            for(int j=0; j<nb; j++)
            {
                int node;
                scanf("%d", &node);
                subnetworks[i].push_back(node);
            }
        }

        for(int i=1; i<=n; i++)
            scanf("%d%d", &nodes[i].x, &nodes[i].y);

        edges.clear();
        for (int i=1; i<=n; i++)
            for (int j=i+1; j<=n; j++)
                edges.push_back(Edge(i,j));

        sort(edges.begin(), edges.end());

        //fin input

        /*for(int i=1; i<=n; i++)
            cout << nodes[i].x << nodes[i].y << endl;
        for(int e=0; e<edges.size(); e++)
            cout << edges[e].a << " " << edges[e].b << " " << edges[e].dist << endl;
        */
        //-----------------

        int smax=1;
        for(int i=0; i<q; i++)
            smax=smax*2;

        initConnexe();
        int res=kruskal();

        //boucle sur le choix des subnetworks
        for(int setup=1; setup<smax; setup++)
        {
            //cout << endl << endl <<"setup=" << setup << endl;

            initConnexe();
            int c=0;
            for(int sub=0; sub<q; sub++)
            {
                if(selected(setup,sub))
                {
                    //cout << "ajout du sub "<<sub<<"..."<<endl;
                    c+=cost[sub];

                    vector<int> toadd=subnetworks[sub];
                    for(int j=1; j<toadd.size(); j++)
                        pasuncycle(Edge(toadd[j-1],toadd[j]));
                }
            }
            //cout << "kruskal..." << endl;
            int newres=c+kruskal();
            res=min(res, newres);
            //cout << "kruskal=" <<newres << " res=" << res << endl;
        }

        cout << res << endl;

        if(nbcase>0)
            cout << endl;
    }
    return 0;
}
