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

const double PI = acos(-1);

int n;

struct Point
{
    int x, y, z;
    double radius;

    double distTo(Point p2) {return sqrt( (double) (p2.x-x)*(p2.x-x) + (p2.y-y)*(p2.y-y) + (p2.z-z)*(p2.z-z) );}
    double getVolume() {return (4.0/3.0)*PI*radius*radius*radius;}
};
Point points[10];
Point box[2];

double volume, volumeBox;

bool visited[10];

double findRadius(int i)
{
    //plus courte distance à un mur de la boite
    //(min marche pas pour les double)
    double distborder[6];
    distborder[0] = abs(points[i].x-box[0].x);
    distborder[1] = abs(points[i].y-box[0].y);
    distborder[2] = abs(points[i].z-box[0].z);
    distborder[3] = abs(points[i].x-box[1].x);
    distborder[4] = abs(points[i].y-box[1].y);
    distborder[5] = abs(points[i].z-box[1].z);

    double res=distborder[0];
    for (int j = 1 ; j < 6 ; j++)
    {
        if (distborder[j] < res)
            res = distborder[j];
    }

    //plus courte distance à un ballon déjà placé
    for(int j=0; j<n; j++)
    {
        if(i!=j && visited[j])
        {
            double newradius= points[i].distTo(points[j]) - points[j].radius;
            if(newradius<res)
                res=newradius;
        }
    }

    return res;
}

void dfs(int step, double volumeTmp)
{
    if(step==n)
    {
        if(volumeTmp>volume)
            volume=volumeTmp;
    }

    //cout << volumeTmp << endl;

    for(int i=0; i<n; i++)
    {
        if(!visited[i])
        {
            visited[i] = true;
            points[i].radius=findRadius(i);
            //b.radius peut etre <0 si jamais (--b--a (où (---- est la radius de a)
            if(points[i].radius>0)
                dfs( step+1, volumeTmp + points[i].getVolume());
            else
                dfs( step+1, volumeTmp);
            visited[i]=false;
        }
    }
}

int main()
{
    int casen=0;
    while(true)
    {
        scanf("%d", &n);
        if(!n)
            return 0;

        scanf("%d%d%d%d%d%d", &box[0].x, &box[0].y, &box[0].z, &box[1].x, &box[1].y, &box[1].z);
        volumeBox = abs( (box[0].x-box[1].x) * (box[0].y-box[1].y) * (box[0].z-box[1].z) );

        for (int i=0; i<n; i++)
        {
            scanf("%d%d%d", &points[i].x, &points[i].y, &points[i].z);
            points[i].radius = 0;
        }

        /*for(int i=0; i<2; i++)
            cout << box[i].x << box[i].y << box[i].z << endl;
        cout << endl;
        for(int i=0; i<n; i++)
            cout << points[i].x << points[i].x<< points[i].x << endl;
        */

        for(int i=0; i<n; i++)
            visited[i]=false;
        volume=0;

        dfs(0, 0.0);
        casen++;
        printf("Box %d: %.0lf\n\n", casen, volumeBox-volume);
    }
}
