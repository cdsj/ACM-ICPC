/*
Boring counting
Time Limit: 6000/3000 MS (Java/Others)    Memory Limit: 98304/98304 K (Java/Others)

Problem Description
In this problem we consider a rooted tree with N vertices. The vertices are numbered from 1 to N, and vertex 1 represents the root. There are integer weights on each vectice. Your task is to answer a list of queries, for each query, please tell us among all the vertices in the subtree rooted at vertice u, how many different kinds of weights appear exactly K times?

Input
The first line of the input contains an integer T( T<= 5 ), indicating the number of test cases.
For each test case, the first line contains two integers N and K, as described above. ( 1<= N <= 105, 1 <= K <= N )
Then come N integers in the second line, they are the weights of vertice 1 to N. ( 0 <= weight <= 109 )
For next N-1 lines, each line contains two vertices u and v, which is connected in the tree.
Next line is a integer Q, representing the number of queries. (1 <= Q <= 105)
For next Q lines, each with an integer u, as the root of the subtree described above.

Output
For each test case, output "Case #X:" first, X is the test number. Then output Q lines, each with a number -- the answer to each query.

Seperate each test case with an empty line.
 
Sample Input
1
3 1
1 2 2
1 2
1 3
3
2
1
3
 
Sample Output
Case #1:
1
1
1
*/


/*
题目大意：给定一棵有根树，树上每个节点都有一个固定的权值，对于每次询问，返回某棵子树中出现k次的权值有多少种。

解题思路：树其实只是一个幌子，用括号序列就能搞成线性结构，题目就转变成询问一段区间里面出现k次的权值有多少种。又是一个树状数组的神奇使用方法。先读取所有询问进行离线处理。把询问的子树转化成区间，按区间的右端点从小到大排序。然后从左到右循环整个区间每个值。假设当前循环到了第i个位置，这个位置的值为v，维护一个树状数组，树状数组中d位置的值就是区间[d,i]中出现k次的权值的种类，考虑到价值v的维护，记录一个数组lst[v][p]表示第p个v值出现的位置，那么可以想到，从i往前推k个v值的地方和往前推k+1个v值的地方之间的权值种类可以+1，所以整个过程的复杂度在O（(n+q)log(n)）。
*/
//Result:2012-08-12 21:45:18	Accepted	4358	1140MS	15408K	3419 B	C++	Wizmann
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>
#include <deque>
#include <map>

//HDU开栈外挂
#pragma comment(linker, "/STACK:102400000,102400000")

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 100100

struct BIT
{
	int baum[SIZE];
	void init()
	{
		memset(baum,0,sizeof(baum));
	}
	inline int lowbit(int x)
	{
		return x&(-x);
	}
	
	void add(int x,int val)
	{
		while(x<SIZE)
		{
			baum[x]+=val;
			x+=lowbit(x);
		}
	}
	int sum(int x)
	{
		int res=0;
		while(x>0)
		{
			res+=baum[x];
			x-=lowbit(x);
		}
		return res;
	}
	int sum(int l,int r)
	{
		return sum(r)-sum(l-1);
	}
};

struct query
{
	int l,r,id;
	query(){}
	query(int il,int ir,int iid)
	{
		l=il;r=ir;id=iid;
	}
	friend bool operator < (const query& a,const query& b)
	{
		return a.r<b.r;
	}
};

int n,k,q;
int w[SIZE];
vector<int> pl[SIZE];
vector<int> g[SIZE];
int lson[SIZE],rson[SIZE],val[SIZE];
int cnt,ind;


//重要：将树转化为线性数组
void dfs(int now,int father)
{
	lson[now]=rson[now]=++ind;
	val[now]=w[now];
	for(int i=0;i<(int)g[now].size();i++)
	{
		int next=g[now][i];
		if(next!=father)
		{
			dfs(next,now);
			rson[now]=rson[next];
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	//freopen("temp.ans","w",stdout);
	int T,a,b;
	BIT bit;
	query ask[SIZE];
	int ans[SIZE];
	map<int,int> mp;
	input(T);
	int cas=1;
	while(T--)
	{
		bit.init();//树状数组初始化
		cnt=ind=0;
		mp.clear();
		memset(ans,0,sizeof(ans));
		for(int i=0;i<SIZE;i++) g[i].clear();
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&w[i]);
			if(!mp[w[i]])
			{
				mp[w[i]]=++cnt;
				pl[cnt].clear();
			}
			w[i]=mp[w[i]];
			//离散化，权值的具体值在本题并没有意义
			//所以只需要区分开
		}
		for(int i=1;i<n;i++)
		{
			//建树
			scanf("%d%d",&a,&b);
			g[a].push_back(b);
			g[b].push_back(a);
		}
		//使用DFS对树进行重编号，将树转化为线性数组
		//使任一非叶子节点的lson,rson值为一个连续区间
		dfs(1,-1);
		scanf("%d",&q);
		for(int i=0;i<q;i++)
		{
			scanf("%d",&a);
			ask[i]=query(lson[a],rson[a],i);
			//离线处理，对query排序
		}
		sort(ask,ask+q);
		int ptr=0;
		for(int i=1;i<=n;i++)
		{
			//val[i]代表对于重编号后的i点代表的权值
			int v=val[i];
			pl[v].push_back(i);
			int sz=pl[v].size();//已经遍历了多少个v值
			if(sz>=k)//如果已经遍历了多于/等于k个v
			{
				if(sz==k)
				{
					//特殊情况，特判
					bit.add(pl[v][sz-k],1);//对于满足条件的右区间进行＋1操作
				}
				if(sz>k)
				{
					//我们现在只考虑一个v值的情况
					//若区间[a+1...i][a+2...i]...[b...i]符合sum(v,[x...i])==k的条件
					//则从i点向左查找，如果包含b,不包含a，说明有k个v点.
					//如果不包含a,b，则说明有不到k个点，不计入答案
					//如果同时包含a,b，则说明超过k个点，也不计入答案
	
					//于是将点(a)标记为-1,将点(b)标记为1，
					//所以对于一个区间[x...i]，如果sum([x...i])==1，则说明有k个v值
					//将此推广到多个v值同样成立
					bit.add(pl[v][sz-k-1],-2);//-1是将上一次的增加恢复原状，再-1是维护下一次的状态
					bit.add(pl[v][sz-k],1);
				}
			}

			while(ask[ptr].r==i)
			{
				int id=ask[ptr].id;
				//使用数状数组求区间和
				ans[id]=bit.sum(ask[ptr].l,ask[ptr].r);
				ptr++;
			}
		}
		printf("Case #%d:\n",cas++);
		for(int i=0;i<q;i++)
		{
			printf("%d\n",ans[i]);
		}
		if(T) puts("");
	}
	return 0;
}

