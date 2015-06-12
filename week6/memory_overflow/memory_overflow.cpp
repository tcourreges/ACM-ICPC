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

int nbcase, n, k;
char rencontre[NMAX];
int lastMet[26];

int main()
{
    int cases=0;
    scanf("%d", &nbcase);
    while(nbcase--) {
        scanf("%d%d", &n, &k);
        scanf("%s",rencontre);

        memset(lastMet, -1, sizeof(lastMet));

        int res=0;
        for(int day=0; day<n; day++) {
            int i=rencontre[day]-'A';
            if(lastMet[i]!=-1 && day-lastMet[i]<=k) {
                res++;
                //cout << "RECOGNIZES ";
            }
            /*else {
                cout << "forgot     ";
            }
            cout << rencontre[day] << " from " << day-lastMet[i] << " ago"<< endl;
            */
            lastMet[i]=day;

        }
        printf("Case %d: %d\n", ++cases, res);

    }
    return 0;
}
