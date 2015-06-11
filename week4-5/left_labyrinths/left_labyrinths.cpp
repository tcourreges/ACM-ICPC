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

#define NMAX 101

int nbcase, n, m;
bool maze[NMAX][NMAX];
bool visited[NMAX][NMAX];

struct Point
{
    int x, y, dx, dy;
    Point() {}
    Point(int _x, int _y): x(_x), y(_y) {}
    Point(int _x, int _y, int _dx, int _dy): x(_x), y(_y), dx(_dx), dy(_dy) {}

    Point forward() {   return Point(x+dx,y+dy, dx, dy);}
    Point left() {      return Point(x-dy,y+dx, -dy, dx);}
    Point right() {     return Point(x+dy,y-dx, dy, -dx);}
    Point turnback() {  return Point(x,y, -dx, -dy);}

    void display() {cout << x << " " << y << endl;}

    bool equals(Point p) {return x==p.x && y==p.y;}
};

bool empty(Point p) {return maze[p.x][p.y];}
void visit(Point p) {visited[p.x][p.y]=true;}

Point entrance;

void displayMaze()
{
    cout << endl;
    for (int i = 0 ; i < n ; i++)
    {
        for (int j = 0 ; j < m ; j++)
        {
            if(visited[i][j])
                cout << ".";
            else if(maze[i][j])
                cout << " ";
            else
                cout << "#";
        }
        cout << endl;
    }
}

bool hasWall(Point p)
{
    int i=p.x, j=p.y;
    return
    (i-1>=0 && !maze[i-1][j]) ||
    (i+1<=n-1 && !maze[i+1][j]) ||
    (j-1>=0 && !maze[i][j-1]) ||
    (j+1<=m-1 && !maze[i][j+1])
    ;
}

bool isEntrance(Point p)
{
    int i=p.x, j=p.y;
    return
    (i-1>=0 && i+1<=n-1 && !maze[i-1][j] && !maze[i+1][j]) ||
    (j-1>=0 && j+1<=m-1 && !maze[i][j-1] && !maze[i][j+1])
    ;
}

bool isCourt(Point p)
{
    Point f=p.right();
    Point f1=f.left();
    Point f2=f.right();
    return empty(f)&&empty(f1)&&empty(f2);
}

Point atFirstWall(Point p)
{
    if(!empty(p.left()))
        return p;

    if(!empty(p.right()))
        return p.turnback();

    if(!empty(p.forward()))
        return p.right();
}

Point findFirstWall()
{
    memset(visited, 0, sizeof(visited));

    Point p=Point(0,0,1,0);

    while(!hasWall(p))
    {
        while(!hasWall(p) && p.x<n-1)
        {
            p=p.forward();
            visit(p);
        }

        if(!hasWall(p))
        {
            p=p.left();
            visit(p);
        }
        if(!hasWall(p))
        {
            p=p.left();
            visit(p);
        }

        while(!hasWall(p) && p.x>0)
        {
            p=p.forward();
            visit(p);
        }

        if(!hasWall(p))
        {
            p=p.right();
            visit(p);
        }
        if(!hasWall(p)) {
            p=p.right();
            visit(p);
        }
    }

   p=atFirstWall(p);
   visit(p);
   return p;
}


Point nextPoint(Point p)
{
    Point voisins[4]={p.left(), p.forward(), p.right(), p.turnback()};

    bool chosen=false;
    for(int i=0; i<4; i++)
    {
        if(!chosen && empty(voisins[i]))
        {
            chosen=true;
            visit(voisins[i]);
            return(voisins[i]);
        }
    }
}

int main()
{
    scanf("%d",&nbcase);
    while (nbcase--)
    {
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; i++)
        {
            string s;
            cin >> s;
            for (int j = 0; j < m; j++)
                maze[i][j] = (s[j] == '.');
        }

        entrance=findFirstWall();

        while(!isEntrance(entrance))
            entrance=nextPoint(entrance);
        //displayMaze();

        Point p=nextPoint(entrance);
        while(!p.equals(entrance) && !isCourt(p))
        {
            p=nextPoint(p);
            visit(p);
        }
        //displayMaze();

        if(p.equals(entrance))
            cout << "NO" << endl;
        else
            cout << "YES" << endl;

        if(nbcase)
            cout << endl;
    }
    return 0;
}
