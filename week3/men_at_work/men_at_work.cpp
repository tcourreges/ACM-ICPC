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

#define NMAX 51
#define TMAX 2000

struct node
{
    int x;
    int y;
    int t;
    node(int _x, int _y, int _t): x(_x), y(_y), t(_t) {}
    //void display() {cout << this->x << " " << this->y << " " << this->t <<endl;}
};

bool maze[NMAX][NMAX];
int period[NMAX][NMAX];
bool visited[NMAX][NMAX][TMAX];
int N;

bool isEmpty(node n)
{
    if(n.x<0 || n.x>=N || n.y < 0 || n.y >= N)
        return false;

    if(period[n.x][n.y]==0)
        return maze[n.x][n.y];

    bool change=(n.t/period[n.x][n.y]) % 2;
    if(!change)
        return maze[n.x][n.y];
    else
        return !maze[n.x][n.y];
}

void setVisited(node x)
{
    visited[x.x][x.y][x.t]=true;
}
bool getVisited(node x)
{
    return visited[x.x][x.y][x.t];
}

/*
bool toDisplay[NMAX][NMAX];
void displayMaze(int t) {
    cout << t << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if(toDisplay[i][j])
                cout<<"X";
            else {
             if(isEmpty(node(i,j,t)))
                 cout << " ";
             else
                 cout << "#";
            }
        }
        cout << endl;
    }
    memset(toDisplay, 0, sizeof(toDisplay));
}*/

int etape;
list<node> q;
int bfs()
{
    q.clear();
    node orig=node(0,0,0);
    q.push_back(orig);

    memset(visited, 0, sizeof(visited));
    setVisited(orig);

    while(!q.empty())
    {
        node u = q.front();
        q.pop_front();
        /*
        if(u.t>etape) {
            displayMaze(etape);
            etape++;
        }
        toDisplay[u.x][u.y]=true;
        */
        if(u.t>TMAX)
            return -1;
        if(u.x==N-1 && u.y==N-1)
            return u.t;

        node voisins[5] = {
            node(u.x,   u.y,    u.t+1),
            node(u.x-1, u.y,    u.t+1),
            node(u.x+1, u.y,    u.t+1),
            node(u.x,   u.y-1,  u.t+1),
            node(u.x,   u.y+1,  u.t+1)
        };
        for(int j=0; j<5; j++)
        {
            node x=voisins[j];
            if(isEmpty(x) && !getVisited(x))
            {
                setVisited(x);
                q.push_back(x);
            }
        }
    }
    return -1;
}

int main()
{
    bool space=false;
    while(1)
    {
        int end=scanf("%d", &N);
        if(end==EOF)
            break;

        if(space)
            cout << endl;
        else
            space=true;

        for (int i = 0; i < N; i++)
        {
            string s;
            cin >> s;
            for (int j = 0; j < N; j++)
                maze[i][j] = (s[j] == '.');
        }

        for (int i = 0; i < N; i++)
        {
            string s;
            cin >> s;
            for (int j = 0; j < N; j++)
                period[i][j] = s[j] - '0';
        }
        /*
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << maze[i][j];
            cout << endl;
        }
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
                cout << period[i][j];
            cout << endl;
        }*/

        int res=bfs();
        if(res==-1)
            cout << "NO" << endl;
        else
            cout << res << endl;
    }
    return 0;
}
