#include<string.h>  
#include<iostream>  
#include<sstream>  
#include<string>  
#include<stdio.h>  
#include<map>  
using namespace std;  
int l[2],n;  
string v1[30][2],v2[30][2],v3[30][2];//存储变量  
char op[30][2];//存储操作符  
int n1[30][2],n2[30][2],n3[30][2];//存储常量  
map<string,int>mp;//hash  
struct node  
{  
    double t[12];  
    double r[2][2];  
    double p;  
    void init()  
    {  
        memset(t,0,sizeof(t));  
        memset(r,0,sizeof(r));  
        p=1.0;  
    }  
    void run(int id,int o)  
    {  
        int V1,V2,V3;  
        double u1,u2;  
        V1=mp[v1[(o-1)/4][id]];  
        V2=mp[v2[(o-1)/4][id]];  
        V3=mp[v3[(o-1)/4][id]];  
        if(V1)  
            u1=t[V1];  
        else  
            u1=n1[(o-1)/4][id];  
        if(V2)  
            u2=t[V2];  
        else  
            u2=n2[(o-1)/4][id];  
        switch(o%4)  
        {  
            case 1:r[0][id]=u1;break;  
            case 2:r[1][id]=u2;break;  
            case 3:  
                if(op[(o-1)/4][id]=='+')  
                    r[0][id]=r[0][id]+r[1][id];  
                else  
                    r[0][id]=r[0][id]-r[1][id];break;  
            case 0:t[V3]=r[0][id];break;  
        }  
  
    }  
}dp[125][125];  
bool check(string s,int &a)//读取常量  
{  
    if(s[0]-'0'>=0&&s[0]-'0'<=9)  
    {  
        istringstream sin(s);  
            sin>>a;  
        return 0;  
    }  
    return 1;  
}  
void solve()  
{  
    int i,j,k,k1,k2;  
    double p1,p2,p;  
    node f1,f2;  
    dp[0][0].init();  
    for(i=0;i<=l[0];i++)  
        for(j=0;j<=l[1];j++)  
        {  
            if(i|j)  
            {  
                if(i==0)  
                {  
                    f1=dp[i][j-1];  
                    p1=f1.p*0.5;p2=0;  
                    f1.run(1,j);  
                }  
                else if(j==0)  
                {  
                    f2=dp[i-1][j];  
                    p2=f2.p*0.5;  
                    p1=0;  
                    f2.run(0,i);  
                }  
                else  
                {  
                    f1=dp[i][j-1];  
                    f2=dp[i-1][j];  
                    p1=f1.p*(i==l[0]?1:0.5);  
                    p2=f2.p*(j==l[1]?1:0.5);  
                    f1.run(1,j);  
                    f2.run(0,i);  
                }  
                dp[i][j].p=p=p1+p2;  
                for(k=1;k<=n;k++)  
                {  
                    dp[i][j].t[k]=(f1.t[k]*p1+f2.t[k]*p2)/p;  
                }  
  
                for(k1=0;k1<=1;k1++)  
                    for(k2=0;k2<=1;k2++)  
                    {  
                        dp[i][j].r[k1][k2]=(f1.r[k1][k2]*p1+f2.r[k1][k2]*p2)/p;  
                    }  
            }  
        }  
    for(i=1;i<=n;i++)  
        printf("%.4lf\n",dp[l[0]][l[1]].t[i]);  
    printf("\n");  
}  
int main()  
{  
    int ti,i,j;  
    char ch;  
    string str;  
    scanf("%d",&ti);  
    while (cin.peek()=='\n')  
   getchar();  
    while(ti--)  
    {  
        mp.clear();  
        for(i=0;i<=1;i++)  
        {  
            while(cin.peek()=='\n')//吸收多余空行  
                getchar();  
            for(j=0;1;j++)  
            {  
                 v1[j][i]=v2[j][i]=v3[j][i]="";  
                 n1[j][i]=n2[j][i]=n3[j][i]=0;  
                while(cin.peek()!=':'&&cin.peek()!='\n')  
                {  
                    ch=getchar();  
                    if(ch!=' ')  
                    v3[j][i]+=toupper(ch);  
                }  
                if(v3[j][i]=="END")  
                    break;  
                if(check(v3[j][i],n3[j][i])==1)  
                    mp[v3[j][i]]++;  
                for(ch=getchar();cin.peek()==' ';)  
                    ch=getchar();  
                for(ch=getchar();cin.peek()==' ';)  
                    ch=getchar();  
                while(cin.peek()!='+'&&cin.peek()!='-')  
                {  
                    ch=getchar();  
                    if(ch!=' ')  
                    v1[j][i]+=toupper(ch);  
                }  
                if(check(v1[j][i],n1[j][i])==1)  
                    mp[v1[j][i]]++;  
                scanf("%c",&op[j][i]);  
                for(;cin.peek()==' ';)  
                    ch=getchar();  
                while(cin.peek()!=' '&&cin.peek()!='\n')  
                {  
                    ch=getchar();  
                    if(ch!=' ')  
                        v2[j][i]+=toupper(ch);  
                }  
                if(check(v2[j][i],n2[j][i])==1)  
                    mp[v2[j][i]]++;
                while(cin.peek()==' ')  
                ch=getchar();  
                while(cin.peek()=='\n')  
                    getchar();  
            }  
           l[i]=j*4;  
        }
        map<string,int>::iterator it=mp.begin();//map内部已排序  
        for(i=1;it!=mp.end();i++,it++)  
            mp[it->first]=i;  
        n=i-1;  
        solve();  
    }  
}  