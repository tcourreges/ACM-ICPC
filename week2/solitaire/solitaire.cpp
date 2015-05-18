#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int nbcase;

int xa,  ya,  xb,  yb,  xc,  yc,  xd,  yd;
int xxa, yya, xxb, yyb, xxc, yyc, xxd, yyd;

struct pt
{
    int x;
    int y;

    pt(): x(0), y(0) {}
    pt(int _x, int _y): x(_x), y(_y) {}
};

pt add(pt a, pt b)
{
    return pt(a.x+b.x, a.y+b.y);
}

int ptCompare(pt a, pt b)
{
    if (a.x==b.x && a.y==b.y)
        return 0;
    if (a.x>b.x || (a.x==b.x && a.y>b.y))
        return 1;
    else
        return -1;
}

pt dRight = pt(1,0);
pt dLeft = pt(-1,0);
pt dUp = pt(0,1);
pt dDown = pt(0,-1);
pt dir[4] = {dRight, dLeft, dUp, dDown};

pt target[4];

bool isValid(pt a)
{
    return (a.x >=1 && a.x <=8 && a.y >= 1 && a.y <=8);
}

bool isPt(pt a, pt* pts)
{
    int i=0;
    while(i<4 && ptCompare(a,pts[i])!=0)
        i++;
    return (i!=4);
}

bool ptsEqual(pt* a, pt* b)
{
    int i=0;
    while(i<4 && ptCompare(a[i],b[i])==0)
        i++;
    return (i==4);
}

bool find(pt* pts, int moves)
{
    if(ptsEqual(pts,target))
        return true;
    if(moves==8)
        return false;

    //cout << moves << endl;
    for(int i=0; i<moves; i++)
        cout << "-";
    for(int i=0; i<4; i++)
        cout << pts[i].x << pts[i].y << " ";
    cout << endl;

    for(int i=0; i<4; i++)
    {
        pt orig=pts[i];
        //cout << "origine --- " << orig.x << orig.y << endl;

        for(int j=0; j<4; j++)
        {
            pt dest=add(orig,dir[j]);
            if(isValid(dest))
            {
                if(!isPt(dest, pts))
                {
                    //cout << dest.x << dest.y << endl;
                    pt newpts[4];
                    for (int i=0; i<4; i++) newpts[i]=pts[i];
                    newpts[i]=dest;
                    if (find(newpts, moves+1))
                        return true;
                }
                else
                {
                    dest=add(dest,dir[j]);
                    if(isValid(dest) && !isPt(dest, pts))
                    {
                        //cout << dest.x << dest.y << endl;
                        pt newpts[4];
                        for (int i=0; i<4; i++) newpts[i]=pts[i];
                        newpts[i]=dest;
                        if (find(newpts, moves+1))
                            return true;
                    }
                }
            }
        }
    }

    return false;
}

int main()
{
    cin >> nbcase;
    while(nbcase--)
    {
        cin >> xa   >> ya   >> xb   >> yb   >> xc   >> yc   >> xd   >> yd;
        cin >> xxa  >> yya  >> xxb  >> yyb  >> xxc  >> yyc  >> xxd  >> yyd;

        cout << dir[0].x << endl;
        cout << ptCompare(dUp, dDown) << ptCompare(dUp, dRight) << ptCompare(dUp,dUp) << isPt(dUp,dir) << isPt(pt(2,0), dir) << endl;

        pt pts[4]={pt(xa,ya),pt(xb,yb),pt(xc,yc),pt(xd,yd)};
        pt target[4]={pt(xa,ya),pt(xb,yb),pt(xc,yc),pt(xd,yd)};

        cout << find(pts,0) << endl;

        if(nbcase>0)
            cout << endl;
    }

    return 0;
}
