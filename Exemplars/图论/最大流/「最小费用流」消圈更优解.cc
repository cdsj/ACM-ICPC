/*
Evacuation Plan
Time Limit: 1000MS		Memory Limit: 65536KB

Description
The City has a number of municipal buildings and a number of fallout shelters that were build specially to hide municipal workers in case of a nuclear war. Each fallout shelter has a limited capacity in terms of a number of people it can accommodate, and there's almost no excess capacity in The City's fallout shelters. Ideally, all workers from a given municipal building shall run to the nearest fallout shelter. However, this will lead to overcrowding of some fallout shelters, while others will be half-empty at the same time. 

To address this problem, The City Council has developed a special evacuation plan. Instead of assigning every worker to a fallout shelter individually (which will be a huge amount of information to keep), they allocated fallout shelters to municipal buildings, listing the number of workers from every building that shall use a given fallout shelter, and left the task of individual assignments to the buildings' management. The plan takes into account a number of workers in every building - all of them are assigned to fallout shelters, and a limited capacity of each fallout shelter - every fallout shelter is assigned to no more workers then it can accommodate, though some fallout shelters may be not used completely. 

The City Council claims that their evacuation plan is optimal, in the sense that it minimizes the total time to reach fallout shelters for all workers in The City, which is the sum for all workers of the time to go from the worker's municipal building to the fallout shelter assigned to this worker. 

The City Mayor, well known for his constant confrontation with The City Council, does not buy their claim and hires you as an independent consultant to verify the evacuation plan. Your task is to either ensure that the evacuation plan is indeed optimal, or to prove otherwise by presenting another evacuation plan with the smaller total time to reach fallout shelters, thus clearly exposing The City Council's incompetence. 

During initial requirements gathering phase of your project, you have found that The City is represented by a rectangular grid. The location of municipal buildings and fallout shelters is specified by two integer numbers and the time to go between municipal building at the location (Xi, Yi) and the fallout shelter at the location (Pj, Qj) is Di,j = |Xi - Pj| + |Yi - Qj| + 1 minutes. 

Input
The input consists of The City description and the evacuation plan description. The first line of the input file consists of two numbers N and M separated by a space. N (1 ≤ N ≤ 100) is a number of municipal buildings in The City (all municipal buildings are numbered from 1 to N). M (1 ≤ M ≤ 100) is a number of fallout shelters in The City (all fallout shelters are numbered from 1 to M). 

The following N lines describe municipal buildings. Each line contains there integer numbers Xi, Yi, and Bi separated by spaces, where Xi, Yi (-1000 ≤ Xi, Yi ≤ 1000) are the coordinates of the building, and Bi (1 ≤ Bi ≤ 1000) is the number of workers in this building. 

The description of municipal buildings is followed by M lines that describe fallout shelters. Each line contains three integer numbers Pj, Qj, and Cj separated by spaces, where Pi, Qi (-1000 ≤ Pj, Qj ≤ 1000) are the coordinates of the fallout shelter, and Cj (1 ≤ Cj ≤ 1000) is the capacity of this shelter. 

The description of The City Council's evacuation plan follows on the next N lines. Each line represents an evacuation plan for a single building (in the order they are given in The City description). The evacuation plan of ith municipal building consists of M integer numbers Ei,j separated by spaces. Ei,j (0 ≤ Ei,j ≤ 1000) is a number of workers that shall evacuate from the ith municipal building to the jth fallout shelter. 

The plan in the input file is guaranteed to be valid. Namely, it calls for an evacuation of the exact number of workers that are actually working in any given municipal building according to The City description and does not exceed the capacity of any given fallout shelter. 

Output
If The City Council's plan is optimal, then write to the output the single word OPTIMAL. Otherwise, write the word SUBOPTIMAL on the first line, followed by N lines that describe your plan in the same format as in the input file. Your plan need not be optimal itself, but must be valid and better than The City Council's one.

Sample Input
3 4
-3 3 5
-2 -2 6
2 2 5
-1 1 3
1 1 4
-2 -2 7
0 -1 3
3 1 1 0
0 0 6 0
0 3 0 2

Sample Output
SUBOPTIMAL
3 0 1 1
0 0 6 0
0 4 0 1
*/

//Result:wizmann	2175	Accepted	640K	235MS	C++	3064B	2012-10-06 10:54:02

/* 最小费用流消圈算法
 * 给出一个费用流的可行解（非最优），让你求出比这个解更优化（可以非最优）的解
 * 
 * 解法：用SPFA找出图中的负环，然后沿着负环将解进行处理，从而使解更优化
*/

/* 题意：给你N座大楼和M个避难所，大楼里面有人，避难所可以装人，但有容量限制。
 * 现在要求给一个方案使得所有人从大楼里跑到避难所里的时间总和最小。
 * 委员会已经搞出了一个方案，你需要看看是不是最优的。如果不是最优的，只需要提出一个更优的。
 *
 * 输入：n个大楼和m个避难所的位置坐标和容量
 * 然后是委员会给出的方案
 * 输出：更优的方案
 */


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 256
#define INF 1<<28
#define abs(x) ((x)>0?(x):(-(x)))

struct CPoint
{
	int x,y,val;
	CPoint(){}
	CPoint(int ix,int iy,int ival)
	{
		x=ix;y=iy;val=ival;
	}
};

struct CEdge
{
	int dest,cost,next;
	CEdge(){}
	CEdge(int idest,int icost,int inext)
	{
		dest=idest;cost=icost;next=inext;
	}
};

inline int pntDis(const CPoint &a,const CPoint &b)
{
	return abs(a.x-b.x)+abs(a.y-b.y)+1;
}

CPoint hause[SIZE],shell[SIZE];
int n,m;
int head[SIZE];
CEdge g[SIZE*SIZE*5];
int ind;
int pre[SIZE];
int method[SIZE][SIZE];
int sum[SIZE];
char visit[SIZE];

void addEdge(int u,int v,int cost)
{
	g[ind]=CEdge(v,cost,head[u]);
	head[u]=ind++;
}


int spfa(int source,int sink,int sz)
{
	int dis[SIZE];
	int cnt[SIZE]={0};
	memset(visit,0,sizeof(visit));
	memset(pre,-1,sizeof(pre));
	
	queue<int> q;
	q.push(source);
	visit[source]=1;
		
	fill(dis,dis+SIZE,INF);
	dis[source]=0;
	
	while(!q.empty())
	{
		int now=q.front();
		q.pop();
		visit[now]=0;
		for(int i=head[now];i!=-1;i=g[i].next)
		{
			int next=g[i].dest;
			int cost=g[i].cost;

			if(dis[next]>dis[now]+cost)
			{
				dis[next]=dis[now]+cost;
				pre[next]=now;
				if(!visit[next])
				{
					q.push(next);
					visit[next]=1;
					if(++cnt[next]>sz) return next;
				}
			}
		}
	}
	return -1;
}


int main()
{
	int a,b,c;
	while(input(n>>m))
	{
		memset(head,-1,sizeof(head));
		memset(method,0,sizeof(method));
		memset(sum,0,sizeof(sum));
		ind=0;
		
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			hause[i]=CPoint(a,b,c);
		}
		for(int i=0;i<m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			shell[i]=CPoint(a,b,c);
		}
		
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				scanf("%d",&method[i][j]);
			}
		}
		
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				addEdge(i,j+n,pntDis(hause[i],shell[j]));
				if(method[i][j]) addEdge(j+n,i,-pntDis(hause[i],shell[j]));
				sum[j]+=method[i][j];
			}
		}
		
		for(int i=0;i<m;i++)
		{
			if(sum[i]<shell[i].val) addEdge(i+n,m+n,0);
			if(sum[i]>0) addEdge(m+n,i+n,0);
		}
		
		int v=spfa(0,n+m,n+m);
		if(v==-1) puts("OPTIMAL");
		else
		{
			puts("SUBOPTIMAL");
			
			memset(visit,0,sizeof(visit));
			while(true)
			{
				if(!visit[v])
				{
					visit[v]=1;
					v=pre[v];
				}
				else break;
			}
			int end=v;
			do
			{
				int from = pre[v],to=v;
				if (from<n && to >= n && to<n+m) method[from][to-n]++;
				if (to < n && from >= n && from<n+m) method[to][from - n]--;
				v = pre[v];
			}while(v!=end);
			
			for(int i=0;i<n;i++)
			{
				for(int j=0;j<m;j++)
				{
					if(j) printf(" ");
					printf("%d",method[i][j]);
				}
				puts("");
			}
		}
	}
	return 0;
}

