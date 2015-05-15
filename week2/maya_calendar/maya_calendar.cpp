#include <map>
#include <string>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int nbcase;

map<string,int> T; //dico tolzkin
map<string,int> H; //dico haab

void init()
{
    T["Imix"]=      0;
    T["Ik"]=        1;
    T["Akbal"]=     2;
    T["Kan"]=       3;
    T["Chikchan"]=  4;
    T["Kimi"]=      5;
    T["Manik"]=     6;
    T["Lamat"]=     7;
    T["Muluk"]=     8;
    T["Ok"]=        9;
    T["Chuen"]=     10;
    T["Eb"]=        11;
    T["Ben"]=       12;
    T["Ix"]=        13;
    T["Men"]=       14;
    T["Kib"]=       15;
    T["Kaban"]=     16;
    T["Etznab"]=    17;
    T["Kawak"]=     18;
    T["Ajaw"]=      19;

    H["Pohp"]=      0;
    H["Wo"]=        1;
    H["Sip"]=       2;
    H["Zotz"]=      3;
    H["Sek"]=       4;
    H["Xul"]=       5;
    H["Yaxkin"]=    6;
    H["Mol"]=       7;
    H["Chen"]=      8;
    H["Yax"]=       9;
    H["Sak"]=       10;
    H["Keh"]=       11;
    H["Mak"]=       12;
    H["Kankin"]=    13;
    H["Muan"]=      14;
    H["Pax"]=       15;
    H["Kayab"]=     16;
    H["Kumku"]=     17;
    H["Wayeb"]=     18;
}

int roundT = 18980; //periode roundcalendar

int a0, b0, c0, d0; //reference
int a1, b1, c1, d1; //target
int a,  b,  c,  d;  //iteration
int baktun, katun, tun, winal, kin; //longcount

//a,b c,d
void incrementR()
{
    a=1+a%13;
    b=(b+1)%20;
    c=1+c%20;
    if(d==18 && c==6)
        c=1;
    if(c==1)
        d=(d+1)%19;
}

int q, ret;
int longCount(int value, int base)
{
    int res;

    res=(value + q%base + ret)%base;
    ret=(value + q%base + ret)/base;
    q=q/base;

    return res;
}
void addLC(int days)
{
    q=days;
    ret=0;

    kin=    longCount(kin, 20);
    winal=  longCount(winal, 18);
    tun=    longCount(tun, 20);
    katun=  longCount(katun, 20);
    baktun= longCount(baktun, 20);
}

int compteur;
void findFirstDate()
{
    a=a0; b=b0; c=c0; d=d0;
    compteur=0;
    while(!(a==a1 && b==b1 && c==c1 && d==d1))
    {
        if(compteur>roundT)
            break;
        //cout << a << " " << b << " " <<c << " " <<d << "   ";
        compteur++;
        incrementR();
        addLC(1);
    }
}

/* ----- partie propre/rapide avec algebre/congruence, mais ne detecte pas les cas impossibles ----- */
//20*2*a + 13*(-3)*b
int xt(int a, int b)
{
    int res=40*a - 39*b;
    if(res<0)
        res+=260;
    return res;
}
int xh(int c, int d)
{
    return d*20 + c;
}
int x(int a, int b, int c, int d)
{
    int nh=(xt(a,b)-xh(c,d))%52;
    while(nh<0)
        nh+=52;
    return 365*nh + xh(c,d);
}
int xref;
int delta(int a, int b, int c, int d)
{
    int xx=x(a,b,c,d);
    int res=xx-xref;
    while(res<0)
        res+=roundT;
    return res;
}
/* -------------------------------------------------------------------------------------------------------- */

int main()
{
	init();

    a0=9; b0=T["Ajaw"]; c0=3; d0=H["Sip"];

    xref=x(a0,b0,c0,d0);
    //cout << xref << endl;

    cin >> nbcase;
    while(nbcase--)
    {
        string sb, sd;
        scanf("%d.", &a1);
        cin >> sb; b1=T[sb];
        scanf("%d.", &c1);
        cin >> sd; d1=H[sd];

        //cout << a1 << " " << b1 << " " <<c1 << " " <<d1 << endl;

        baktun=8; katun=0; tun=0; winal=0; kin=0;

        //on trouve la premiere date en incrementant comme une brute
        findFirstDate();

        //ou alors on calcule directement le nombre de jours qui sépare target de reference (mais comment detecter exception?)
        //addLC(delta(a1,b1,c1,d1));

        if(compteur>roundT)
        {
            cout << "NO SOLUTION" << endl;
        }
        else
        {
            //on incremente avec la  periode round calendar
            while(baktun<10)
            {
                cout << baktun << "." << katun << "." << tun << "." << winal << "." << kin << endl;
                addLC(roundT);
            }
        }

        if(nbcase>0)
		    cout << endl;
	}

	return 0;
}
