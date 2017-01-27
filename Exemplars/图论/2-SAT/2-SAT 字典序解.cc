/*
Peaceful Commission
Time Limit:5000MS     Memory Limit:32768KB

Description
The Public Peace Commission should be legislated in Parliament of The Democratic Republic of Byteland according to The Very Important Law. Unfortunately one of the obstacles is the fact that some deputies do not get on with some others. 

The Commission has to fulfill the following conditions: 
1.Each party has exactly one representative in the Commission, 
2.If two deputies do not like each other, they cannot both belong to the Commission. 

Each party has exactly two deputies in the Parliament. All of them are numbered from 1 to 2n. Deputies with numbers 2i-1 and 2i belong to the i-th party . 

Task 
Write a program, which: 
1.reads from the text file SPO.IN the number of parties and the pairs of deputies that are not on friendly terms, 
2.decides whether it is possible to establish the Commission, and if so, proposes the list of members, 
3.writes the result in the text file SPO.OUT. 
 
Input
In the first line of the text file SPO.IN there are two non-negative integers n and m. They denote respectively: the number of parties, 1 <= n <= 8000, and the number of pairs of deputies, who do not like each other, 0 <= m <=2 0000. In each of the following m lines there is written one pair of integers a and b, 1 <= a < b <= 2n, separated by a single space. It means that the deputies a and b do not like each other. 
There are multiple test cases. Process to end of file. 
 
Output
The text file SPO.OUT should contain one word NIE (means NO in Polish), if the setting up of the Commission is impossible. In case when setting up of the Commission is possible the file SPO.OUT should contain n integers from the interval from 1 to 2n, written in the ascending order, indicating numbers of deputies who can form the Commission. Each of these numbers should be written in a separate line. If the Commission can be formed in various ways, your program may write mininum number sequence. 
 
Sample Input
3 2
1 3
2 4
 
Sample Output
1
4
5
*/

/*
和平委员会

根据宪法，Byteland民主共和国的公众和平委员会应该在国会中通过立法程序来创立。 不幸的是，由于某些党派代表之间的不和睦而使得这件事存在障碍。

此委员会必须满足下列条件：

    每个党派都在委员会中恰有1个代表，
    如果2个代表彼此厌恶，则他们不能都属于委员会。

每个党在议会中有2个代表。代表从1编号到2n。 编号为2i-1和2i的代表属于第I个党派。

任务

写一程序：

    从文本文件读入党派的数量和关系不友好的代表对，
    计算决定建立和平委员会是否可能，若行，则列出委员会的成员表，
    结果写入文本文件。
*/


//Result:2012-10-15 22:40:58	Accepted	1814	406MS	764K	1544 B	C++	Wizmann
#include <cstdio>
#include <cstring>

using namespace std;

const int NODE=16000+123;
const int EDGE=100000+123;

const int RED=1;
const int BLACK=2;
const int WHITE=0;

struct edge
{
	int v,next;
	edge(){}
	edge(int iv,int inext)
	{
		v=iv;next=inext;
	}
};

edge g[EDGE];
int head[NODE],ind;
int color[NODE];
int scc[NODE],sccnr,limit;

inline void _addedge(int a, int b)
{
	g[ind]=edge(b,head[a]);
	head[a]=ind++;
}

inline void addedge(int a, int b)
{
	_addedge(a,b^1);
	_addedge(b,a^1);
}

void init()
{
	memset(head,-1,sizeof(head));
	ind=0;
}

bool dfs(int now)
{
	if(color[now]==BLACK) return false;
	else if(color[now]==RED) return true;
	else
	{
		color[now]=RED;
		color[now^1]=BLACK;
		scc[sccnr++]=now;
		for(int p=head[now];p!=-1;p=g[p].next)
		{
			if(!dfs(g[p].v)) return false;//有矛盾
		}
		return true;
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	int a,b,n,m;
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		limit=n*2;
		init();
		for(int i=0;i<m;i++)
		{
			scanf("%d%d",&a,&b);
			addedge(--a,--b);
		}
		memset(color,0,sizeof(color));
		bool ok=true;
		for(int i=0;i<n;i++)
		{
			if(color[i<<1] || color[i<<1|1]) continue;
			sccnr=0;
			if(!dfs(i<<1))//如果失败，回溯遍历此连通分量之前的状态
			{
				for(int j=0;j<sccnr;j++)
				{
					color[scc[j]]=color[scc[j]^1]=WHITE;
				}
				if(!dfs(i<<1|1)) ok=false;
			}
		}
		if(ok)
		{   
			for(int i=0;i<n*2;i++)
			{
				if(color[i]==RED) printf("%d\n",i+1);
			}
		}
		else puts("NIE");
	}
	return 0;
}
