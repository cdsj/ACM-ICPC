/*
Travel
Time Limit: 5000MS		Memory Limit: 32768KB

Description
　　PP loves travel. Her dream is to travel around country A which consists of N cities and M roads connecting them. PP has measured the money each road costs. But she still has one more problem: she doesn't have enough money. So she must work during her travel. She has chosen some cities that she must visit and stay to work. In City_i she can do some work to earn Ci money, but before that she has to pay Di money to get the work license. She can't work in that city if she doesn't get the license but she can go through the city without license. In each chosen city, PP can only earn money and get license once. In other cities, she will not earn or pay money so that you can consider Ci=Di=0. Please help her make a plan to visit all chosen cities and get license in all of them under all rules above.
　　PP lives in city 1, and she will start her journey from city 1. and end her journey at city 1 too.
 
Input
　　The first line of input consists of one integer T which means T cases will follow.
　　Then follows T cases, each of which begins with three integers: the number of cities N (N <= 100) , number of roads M (M <= 5000) and her initiative money Money (Money <= 10^5) .
　　Then follows M lines. Each contains three integers u, v, w, which means there is a road between city u and city v and the cost is w. u and v are between 1 and N (inclusive), w <= 10^5.
　　Then follows a integer H (H <= 15) , which is the number of chosen cities.
　　Then follows H lines. Each contains three integers Num, Ci, Di, which means the i_th chosen city number and Ci, Di described above.(Ci, Di <= 10^5)
 
Output
　　If PP can visit all chosen cities and get all licenses, output "YES", otherwise output "NO".
 
Sample Input
2
4 5 10
1 2 1
2 3 2
1 3 2
1 4 1
3 4 2
3
1 8 5
2 5 2
3 10 1
2 1 100
1 2 10000
1
2 100000 1
 
Sample Output
YES
NO
*/ 

/*
无向图存在欧拉回路条件
　　一个无向图存在欧拉回路，当且仅当该图所有顶点度数都是偶数。
有向图存在欧拉回路条件
　　一个有向图存在欧拉回路，且所有顶点的入度等于出度
混合图存在欧拉回路条件
　　要判断一个混合图G（V,E）（既有有向边又有无向 欧拉回路的判断　　一下判断基于此图的基图连通。
无向图存在欧拉回路条件
　　一个无向图存在欧拉回路，当且仅当该图所有顶点度数都是偶数。
有向图存在欧拉回路条件
　　一个有向图存在欧拉回路，且所有顶点的入度等于出度
汉密尔顿定义:
给定图G，若存在一条路经过图中的每个结点恰好一次，这条路称作汉密尔顿路。若存在一条回路，经过图中的每个结点恰好一次，这条回路称作汉密尔顿回路。
*/

/*
题目：给出一些城市，从1出发，旅游一圈回到1，由于花费可能不够，所以选择一些城市打工，打工之前需要花费d买一个证，工资为c。选中的城市必须去工作一次，而且只能工作一次，问能不能完成旅行
*/

//Result:2012-09-10 23:44:34	Accepted	4284	265MS	340K	1958 B	C++	Wizmann
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 101
#define N 16
#define INF 1<<28

struct city
{
	int nr,ci,di;
	
	city(){}
	city(int inr,int ici,int idi)
	{
		nr=inr;ci=ici;di=idi;
	}
	friend bool operator < (const city &a,const city &b)
	{
		return a.nr<b.nr;
	}
};


int g[SIZE][SIZE];
int n,m,gold,h;
city tour[N];
int gg[N][N];
char visit[N];

bool dfs(int cur,int num,int coin)
{
	if(num==h)
	{
		if(coin-gg[cur][0]>=0) return true;
		//如果修改最后的条件就是汉密尔顿路
		//不修改就是欧拉回路
		else return false;
	}
	bool ans=false;
	for(int i=0;i<h;i++)
	{
		int v=i;
		if( (coin-gg[cur][v]-tour[i].di>=0) && !visit[v] )
		{
			int res=coin+(tour[i].ci-tour[i].di)-gg[cur][v];
            visit[v]=true;
            if(res>=0) ans|=dfs(v,num+1,res);
            visit[v]=false;
            if(ans) return ans;
       }
   }
   return false;
}
          

int main()
{
	freopen("input.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T,a,b,c;
	input(T);
	while(T--)
	{
		scanf("%d%d%d",&n,&m,&gold);
		for(int i=0;i<SIZE;i++)
		{
			for(int j=0;j<SIZE;j++) g[i][j]=INF;
			g[i][i]=0;
		}
		for(int i=0;i<m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			g[a][b]=g[b][a]=min(g[a][b],c);
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++)
			{
				for(int k=1;k<=n;k++)
				{
					g[j][k]=min(g[j][k],g[j][i]+g[i][k]);
				}
			}
		}
		input(h);
		bool start=false;
		for(int i=0;i<h;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			if(a==1) start=true;
			tour[i]=city(a,b,c);
		}
		if(!start) tour[h++]=city(1,0,0);
		sort(tour,tour+h);
		for(int i=0;i<h;i++)
		{
			for(int j=0;j<h;j++)
			{
				gg[i][j]=gg[j][i]=g[tour[i].nr][tour[j].nr];
			}
		}
		memset(visit,0,sizeof(visit));
		bool ok=dfs(0,0,gold);
		if(ok) puts("YES");
		else puts("NO");
	}
	return 0;
}




