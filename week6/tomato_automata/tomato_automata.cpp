#include<iostream>
#include<cstdio>
#include<cstring>
#include<string.h>
#include<vector>
#include<queue>
#include<stack>
#include<sstream>
using namespace std;

#define NMAX 100001

enum command { IFGO, JUMP, PASS, LOOP, DIE };

int n;
int cmds[NMAX][3];

//ifgo, jump, pass, loop, die
int addCommand(string str, int n0, int arg1, int arg2)
{
    char lower=tolower(str[0]);

    switch(lower)
    {
        case 'i':
            cmds[n0][0]=IFGO;
            cmds[n0][1]=arg1;
            //cout << "ifgo"<< arg1 << endl;
        break;
        case 'j':
            cmds[n0][0]=JUMP;
            cmds[n0][1]=arg1;
            //cout << "jump"<< arg2 << endl;
        break;
        case 'p':
            cmds[n0][0]=PASS;
            cmds[n0][1]=arg1;
            //cout << "pass"<<endl;
        break;
        case 'l':
            cmds[n0][0]=LOOP;
            cmds[n0][1]=arg1;
            cmds[n0][2]=arg2;
            //cout << "loop"<< arg1<<arg2<<endl;
        break;
        case 'd':
            cmds[n0][0]=DIE;
            //cout << "die"<<endl;
        break;
    }
}

int mod(int i) { return ((i>n) ? 1 : i); }

vector<int> g[NMAX];
int loop[NMAX][2];
int add(int i)
{
    switch(cmds[i][0])
    {
        case IFGO:
            //cout << "adding " << i<<"->"<<i+1<<" "<<i<<"->"<<cmds[i][1]<<endl;
            g[i].push_back(mod(i+1));
            g[i].push_back(mod(cmds[i][1]));
        break;

        case JUMP:
            //cout << "adding " <<i<<"->"<<cmds[i][1]<<endl;
            g[i].push_back(mod(cmds[i][1]));
        break;

        case PASS:
            //cout << "adding " << i<<"->"<<i+1<<endl;
            g[i].push_back(mod(i+1));
        break;

        case LOOP:
            loop[i][0]=cmds[i][1];
            loop[i][1]=cmds[i][2];
            //cout << "adding " << i<<"->"<<i+1;
            //cout << " LOOP("<<loop[i][0]<<" * "<<loop[i][1]<<")"<<endl;
            g[i].push_back(mod(i+1));
        break;

        case DIE:
            //cout << "adding " << i<<"->"<<0<<endl;
            g[i].push_back(0);
        break;
    }
}

void buildAutomata()
{
    memset(loop, 0, sizeof(loop));

    for(int i=0; i<=n; i++)
        g[i].clear();

    for(int i=1; i<=n; i++)
        add(i);
}

void displayAutomata()
{
    for(int i=1; i<=n; i++)
    {
        for(int jj=0; jj<g[i].size(); jj++)
        {
            int j=g[i][jj];
            cout << j;
            if(loop[i][0])
                cout << " (" << loop[i][0]<<"*"<<loop[i][1] << ")";
            cout <<" - ";
        }
        cout << endl;
    }
    cout << endl << endl;
}


int d[NMAX];
bool visited[NMAX];
int dRes;
bool infin=false;
void dfs(int i, int dTmp)
{
    int a=dTmp;
    /*while(a--)
        cout << " ";
    cout << "line "<<i<<" ("<<dTmp<<")"<<endl;
    */
    /*if(i==0) {
        if(dTmp>dRes)
            dRes=dTmp;
    }*/

    d[i]=max(d[i], dTmp);
    if(i==0)
        dRes=max(dRes, d[0]);

    for(int jj=0; jj<g[i].size(); jj++)
    {
        int j=g[i][jj];
        if(!visited[j])
        {
            int di1=dTmp+1;
            if(loop[i][0])
            {
                //di1 + (di1-dstart) * (n-1)

                int dstart=d[loop[i][0]];
                int times=loop[i][1];
                di1 += (di1-dstart) * (times -1);

                int b=dTmp;
                /*while(b--)
                    cout << " ";
                cout << "*LOOPING" << endl;*/
            }

            if(di1>d[j])
            {
                visited[j]=true;
                d[j]=di1;
                dfs(j, d[j]);
                visited[j]=false;
            }

            //d[j]=prev;
        }
        else
        {
            //cout << j << " FROM " << i << " ALREADY VISITED"<<endl;
            infin=true;
        }
    }
}

void solve()
{
    /*
    for(int i=1; i<=n; i++)
        cout << cmds[i][0]<<endl;
    cout << endl;
    */

    buildAutomata();
    //displayAutomata();

    infin = false;
    dRes=0;
    dfs(1, 0);
    memset(d,0,sizeof(visited));
    memset(visited,0,sizeof(visited));

    if(infin)
        cout << "infinity"<<endl;
    else
        cout << dRes << endl;
    //cout <<endl<<endl;
}

int main()
{
    string line, cmd;
    int arg1, arg2;

    bool done=false;
    while(getline(cin, line))
    {
        done=false;
        istringstream iss(line);
        if((iss)>> cmd)
        {
            n++;
            iss >> arg1;
            iss >> arg2;
            //cout << cmd<<arg1<<arg2<<endl;
            addCommand(cmd, n, arg1, arg2);
        }
        else
        {
            //memset(memo, -1, sizeof(memo));
            solve();
            done=true;
            n=0;
        }
    }

    if(!done)
        solve();

    return 0;
}
