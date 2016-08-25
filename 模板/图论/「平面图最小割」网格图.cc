/*
Catch the Theves
Time Limit: 2000MS 		Memory Limit: 32768KB

Description
A group of thieves is approaching a museum in the country of zjsxzy,now they are in city A,and the museum is in city B,where keeps many broken legs of zjsxzy.Luckily,GW learned the conspiracy when he is watching stars and told it to zjsxzy.
Zjsxzy decided to caught these thieves,and he let the police to do this,the police try to catch them on their way from A to B. Although the thieves might travel this way by more than one group, zjsxzy's excellent police has already gather the statistics that the cost needed on each road to guard it.
Now ,zjsxzy's conutry can be described as a N*N matrix A,Aij indicates the city(i,j) have bidirectionals road to city(i+1,j) and city(i,j+1),gurad anyone of them costs Aij.
Now give you the map,help zjsxzy to calculate the minimium cost.We assume thieves may travel in any way,and we will catch all passing thieves on a road if we guard it.
 

Input
The first line is an integer T,followed by T test cases.
In each test case,the first line contains a number N(1<N<=400).
The following N lines,each line is N numbers,the jth number of the ith line is Aij.
The city A is always located on (1,1) and the city B is always located on (n,n).
Of course,the city (i,j) at the last row or last line won't have road to (i,j+1) or (i+1,j).
 
Output
For each case,print a line with a number indicating the minimium cost to arrest all thieves.
 
Sample Input

1 
3 
10 5 5 
6 6 20 
4 7 9

Sample Output

18

*/
//Result:2012-09-12 22:26:04	Accepted	3870	234MS	25452K	2057 B	C++	Wizmann

/*
 * 平面图最小割
 * S _______________
 * |		|		|
 * |		|		|
 * |		|		|
 * |		|		|
 * |--------|-------|
 * |		|		|
 * |		|		|
 * |		|		|
 * |________|_______T
 * 
 * S,T在图的两端点，图呈正网格状，网格的每一条边都有对应的边权
 * 求S到T的最大流就可以转化为平面图上对偶图的最短路
 */

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
#define SIZE (400*400*12)
#define INF 0x3f3f3f3f

struct _link
{
	int dest,cost,next;
	_link(){}
	_link(int idest,int icost,int inext)
	{
		dest=idest;cost=icost;next=inext;
	}
};

struct node
{
	int from,cost;
	node(){}
	node(int icost,int ifrom)
	{
		from=ifrom;cost=icost;
	}
	friend bool operator < (const node& a,const node& b)
	{
		return a.cost>b.cost;
	}
};

_link g[SIZE*2];
int head[SIZE];
int ind,n;
int dis[SIZE];
char visit[SIZE];


void addEdge(int a,int b,int c)
{
	g[ind]=_link(b,c,head[a]);
	head[a]=ind++;
	
	g[ind]=_link(a,c,head[b]);
	head[b]=ind++;	
}

void spfa(int st)
{
	memset(visit,0,sizeof(visit));
	memset(dis,INF,sizeof(dis));
	priority_queue<node> q;
	dis[st]=0;
	q.push(node(dis[st],st));
	while(!q.empty())
	{
		node now=q.top();
		q.pop();
		int to=now.from;
		if(visit[to]) continue;
		visit[to]=1;
		
		for(int i=head[to];i!=-1;i=g[i].next)
		{
			int next=g[i].dest;
			int cost=g[i].cost;
			if(dis[next]>dis[to]+cost)
			{
				dis[next]=dis[to]+cost;
				q.push(node(dis[next],next));
			}
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	int T;
	int mp[420][420];
	input(T);
	while(T--)
	{
		ind=0;
		memset(head,-1,sizeof(head));
		input(n);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++)
			{
				scanf("%d",&mp[i][j]);
			}
		}

		for(int i=0;i<n-1;i++)
		{
			addEdge(0,i+1,mp[0][i]);
			addEdge(0,(i+1)*(n-1),mp[i][n-1]);
			addEdge((n-1)*i+1,(n-1)*(n-1)+1,mp[i][0]);
			addEdge((n-2)*(n-1)+i+1,(n-1)*(n-1)+1,mp[n-1][i]);
		}
		for(int i=0;i<n-1;i++)
		{
			for(int j=0;j<n-1;j++)
			{
				if(i<n-2) addEdge(i*(n-1)+j+1,(i+1)*(n-1)+j+1,mp[i+1][j]);
				if(j<n-2) addEdge(i*(n-1)+j+1,i*(n-1)+j+2,mp[i][j+1]);
			}
		}
		spfa(0);
		printf("%d\n",dis[(n-1)*(n-1)+1]);
	}
	return 0;
}
	
