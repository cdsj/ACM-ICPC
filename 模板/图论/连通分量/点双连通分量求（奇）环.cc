/*
Knights of the Round Table
Time Limit: 7000MS		Memory Limit: 65536KB

Description
Being a knight is a very attractive career: searching for the Holy Grail, saving damsels in distress, and drinking with the other knights are fun things to do. Therefore, it is not very surprising that in recent years the kingdom of King Arthur has experienced an unprecedented increase in the number of knights. There are so many knights now, that it is very rare that every Knight of the Round Table can come at the same time to Camelot and sit around the round table; usually only a small group of the knights isthere, while the rest are busy doing heroic deeds around the country. 

Knights can easily get over-excited during discussions-especially after a couple of drinks. After some unfortunate accidents, King Arthur asked the famous wizard Merlin to make sure that in the future no fights break out between the knights. After studying the problem carefully, Merlin realized that the fights can only be prevented if the knights are seated according to the following two rules:
The knights should be seated such that two knights who hate each other should not be neighbors at the table. (Merlin has a list that says who hates whom.) The knights are sitting around a roundtable, thus every knight has exactly two neighbors.
An odd number of knights should sit around the table. This ensures that if the knights cannot agree on something, then they can settle the issue by voting. (If the number of knights is even, then itcan happen that ``yes" and ``no" have the same number of votes, and the argument goes on.)
Merlin will let the knights sit down only if these two rules are satisfied, otherwise he cancels the meeting. (If only one knight shows up, then the meeting is canceled as well, as one person cannot sit around a table.) Merlin realized that this means that there can be knights who cannot be part of any seating arrangements that respect these rules, and these knights will never be able to sit at the Round Table (one such case is if a knight hates every other knight, but there are many other possible reasons). If a knight cannot sit at the Round Table, then he cannot be a member of the Knights of the Round Table and must be expelled from the order. These knights have to be transferred to a less-prestigious order, such as the Knights of the Square Table, the Knights of the Octagonal Table, or the Knights of the Banana-Shaped Table. To help Merlin, you have to write a program that will determine the number of knights that must be expelled. 

Input
The input contains several blocks of test cases. Each case begins with a line containing two integers 1 ≤ n ≤ 1000 and 1 ≤ m ≤ 1000000 . The number n is the number of knights. The next m lines describe which knight hates which knight. Each of these m lines contains two integers k1 and k2 , which means that knight number k1 and knight number k2 hate each other (the numbers k1 and k2 are between 1 and n ). 

The input is terminated by a block with n = m = 0 . 

Output
For each test case you have to output a single integer on a separate line: the number of knights that have to be expelled. 

Sample Input
5 5
1 4
1 5
2 5
3 4
4 5
0 0
Sample Output
2
*/

//Result:wizmann	2942	Accepted	1372K	1079MS	C++	2422B	2012-09-21 21:13:07
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <bitset>
#include <stack>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 1024
#define EDGE 1024000

struct node
{
	int val,next;
	node(){}
	node(int ival,int inext)
	{
		val=ival;next=inext;
	}
};

int n,m;
int head[SIZE];
int in[SIZE];
int dfn[SIZE],low[SIZE];
int idx,ind;
stack<int> st;
char visit[SIZE];
int block[SIZE];
node g[EDGE<<1];
char color[SIZE];
char oddcir[SIZE];
char cnc[SIZE][SIZE];

void init()
{
	memset(head,-1,sizeof(head));
	memset(dfn,-1,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(in,0,sizeof(in));
	st=stack<int>();
	idx=ind=0;
	memset(oddcir,0,sizeof(oddcir));
	memset(cnc,0,sizeof(cnc));
}

void addEdge(int a,int b)
{
	g[ind]=node(b,head[a]);
	head[a]=ind++;
}
	

bool bio(int x,int c)
{
	color[x]=c;
	for(int i=head[x];i!=-1;i=g[i].next)
	{
		int u=g[i].val;
		if(in[u])
		{
			if(color[u]==color[x]) return false;
			if(color[u]==-1 && !bio(u,1-c)) return false;
		}
	}
	return true;
}

void check_odd_circle(int pos)
{
	memset(color,-1,sizeof(color));
	memset(in,0,sizeof(in));
	for(int i=1;i<=block[0];i++) in[block[i]]=1;
	if(!bio(pos,0))
	{
		for(int i=1;i<=block[0];i++)
		{
			oddcir[block[i]]=1;
		}
	}
}

void tarjan(int x,int pre)
{
	low[x]=dfn[x]=++idx;
	st.push(x);
	for(int i=head[x];i!=-1;i=g[i].next)
	{
		int u=g[i].val;
		if(u==pre) continue;
		if(dfn[u]==-1)
		{
			tarjan(u,x);
			if(low[u]<low[x]) low[x]=low[u];
			if(low[u]>=dfn[x])
			{
				block[0]=0;
				memset(visit,0,sizeof(visit));
				int v;
				do
				{
					v=st.top();
					st.pop();
					visit[v]=1;
					block[++block[0]]=v;
				}while(u!=v);
				block[++block[0]]=x;
				visit[x]=1;
				check_odd_circle(x);
			}
		}
		else low[x]=min(low[x],dfn[u]);
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	int a,b;
	while(input(n>>m) && n+m)
	{
		init();
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&a,&b);
			cnc[a][b]=cnc[b][a]=1;
		}
		for(int i=1;i<=n;i++)
		{
			for(int j=1;j<=n;j++) if(i!=j)
			{
				if(cnc[i][j]==0) addEdge(i,j);
			}
		}
		for(int i=1;i<=n;i++)
		{
			if(dfn[i]==-1) tarjan(i,-1);
		}
		
		int ans=0;
		for(int i=1;i<=n;i++)
		{
			if(oddcir[i]) ans++;
		}
		print(n-ans);
	}
	return 0;
}

