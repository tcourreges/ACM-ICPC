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

#define NMAX 40001
int nbcase, N;

int rain[NMAX];
vector<int> receiveFrom[NMAX];

struct bord
{
    int x, id, lower;

    bord() {}
    bord(int _x, int _id, int _lower): x(_x), id(_id), lower(_lower) {}

    bool operator < (bord b2)const{
        return x < b2.x;
    }
};
bord bords[2*NMAX];

struct seg
{
    int x1, y1, x2, y2, id, xlow;

    seg(){}
    seg(int _x1, int _y1, int _x2, int _y2, int _id): x1(_x1), y1(_y1), x2(_x2), y2(_y2), id(_id)
    {
        xlow=x1;
        if(y1>y2)
            xlow=x2;
    }

    bord bord1()
    {
        if(y1>y2)
            return bord(x1,id,0);
        else
            return bord(x1,id,1);
    }

    bord bord2(){

        if(y1>y2)
            return bord(x2,id,1);
        else
            return bord(x2,id,0);
    }
};
seg segs[NMAX];

int memo[NMAX];
int recu(int i){
    int &res = memo[pos];

    if(res == -1) {
        res= rain[pos];//recu directement
        for(int j=0; j<receiveFrom[pos].size(); i--)
            res += recu(receiveFrom[i][j]);//recu des autres

    }
    return res;
}



int main(){
    scanf("%d",&nbcase);

    while(nbcase--){
        scanf("%d",&N);

        for(int i = 0;i < N;++i) {
            int a,b,c,d;
            scanf("%d %d %d %d", &a, &b, &c, &d);
            segs[i]=seg(a,b,c,d,i);

            bords[i]=     segs[i].bord1();
            bords[N+i]=   segs[i].bord2();
        }

        /*for(int i = 0;i < N;++i) {
            seg s=segs[i];
            cout << s.x1 << " " << s.y1 << " " << s.x2 << " " << s.y2 << endl;
        }*/

        memset(water, 0, sizeof(water));

        sort(bords,bords+2*N);


        list<bord> l;
        int i=0;
        while(i<2^N)
        {
            memset(bordEnd, false, sizeof(bordEnd));

            int b=i; xi=bords[i].x;

            //on rajoute à la liste tous les bords situés à xi
            while(b<2*N && bords[i].x==xi) {
                l.push_back(b);
                b++;
            }

        }




    }
   return 0;
}
