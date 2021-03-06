//Result: wizmann	3294	Accepted	3844K	2875MS	G++	4608B
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <climits>
#include <iostream>
#include <bitset>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define llint long long
#define uint unsigned int
#define input(x) cin>>x
#define print(x) cout<<x<<endl
#define elif else if
#define INF 1<<25
#define eps 1e-5
#define pq priority_queue
#define pb push_back
#define mp make_pair
#define np next_permutation

#define SIZE 100200
#define N 256

int n;
int pad,spow;
int memo[SIZE];//拼接出的长字符串
int nr[SIZE];//字符串编号
int rank[SIZE];
int sarray[SIZE];//后辍数组
int mark[SIZE];
int height[SIZE];
//height 数组:定义 height[i]=suffix(sa[i-1])和 suffix(sa[i])的最长公
//共前缀,也就是排名相邻的两个后缀的最长公共前缀。

int cmpSuffix(const void *a,const void *b)
{
	int ta=*(int*)a,tb=*(int*)b;
	return memo[ta]-memo[tb];
}

int cmp(const void *a,const void *b)
{
	int x=*(int*)a;
	int y=*(int*)b;
	if(rank[x]!=rank[y]) return 1;
	else
	{
		if(rank[x+spow]!=rank[y+spow]) return 1;
		else return 0;
	}
}

void creatSuffixArray()
{
	for(int i=0;i<pad;i++) sarray[i]=i;
	qsort(sarray,pad,sizeof(int),cmpSuffix);//后辍排序
	
	for(int i=0,j=0;i<pad;i++)
	{
		if(i>0 && memo[sarray[i]]!=memo[sarray[i-1]]) j++;
		rank[sarray[i]]=j;//后辍排名
	}
	
	int tmpstr[SIZE];
	int nextRank[SIZE];
	for(spow=1;spow<pad;spow<<=1)//2倍增算法
	{
		memset(tmpstr,0,sizeof(tmpstr));
		for(int i=0;i<pad;i++)
		{
			if(sarray[i]+spow<pad) tmpstr[rank[sarray[i]+spow]]++;
			else tmpstr[rank[sarray[i]]]++;
		}
		for(int i=1;i<pad;i++) tmpstr[i]+=tmpstr[i-1];
		for(int i=pad-1;i>=0;i--)
		{
			if(sarray[i]+spow<pad) mark[--tmpstr[rank[sarray[i]+spow]]]=sarray[i];
			else mark[--tmpstr[rank[sarray[i]]]]=sarray[i];
		}
		memset(tmpstr,0,sizeof(tmpstr));
		for(int i=0;i<pad;i++) tmpstr[rank[mark[i]]]++;
		for(int i=1;i<pad;i++) tmpstr[i]+=tmpstr[i-1];
		for(int i=pad-1;i>=0;i--) sarray[--tmpstr[rank[mark[i]]]]=mark[i];
		for(int i=0,j=0;i<pad;i++)
		{
			if(i>0&&cmp(&sarray[i],&sarray[i-1])!=0) j++;
			nextRank[sarray[i]]=j;
		}
		memcpy(rank,nextRank,sizeof(rank));
		//更新排名，要求严格的字典序
	}
}

void creatHeight()
{
	int k=0;
	for(int i=0,j=0;i<pad;i++)
	{
		if(rank[i]==0) height[rank[i]]=k=0;
		else
		{
			if(k>0) k--;
			j=sarray[rank[i]-1];
			while(memo[i+k]==memo[j+k]) k++;
			height[rank[i]]=k;
		}
	}
}


int judge(int len)
{
	int sum=0;
	int v[128]={0};
	for(int i=1;i<pad;i++)
	{
		if(height[i]>=len)
		{
			if(nr[sarray[i-1]]!=0 && v[nr[sarray[i-1]]]==0)
			{
				sum++;
				if(sum>n/2) return 1;
				v[nr[sarray[i-1]]]=1;
			}
			if(nr[sarray[i]]!=0 && v[nr[sarray[i]]]==0)
			{
				sum++;
				if(sum>n/2) return 1;
				v[nr[sarray[i]]]=1;
			}
		}
		else
		{
			memset(v,0,sizeof(v));
			sum=0;
		}
	}
	return 0;
}

void printAns(int len)
{
	int sum=0;
	int find=0;
	int v[128]={0};
	for(int i=1;i<pad;i++)
	{
		if(height[i]>=len && !find)
		{
			if(nr[sarray[i-1]]!=0 && v[nr[sarray[i-1]]]==0)
			{
				sum++;
				if(sum>n/2)
				{
					find=1;
					for(int j=sarray[i-1];j<sarray[i-1]+len;j++)
					{
						printf("%c",char(memo[j]-N));
					}
					print("");
				}
				v[nr[sarray[i-1]]]=1;
			}
			if(nr[sarray[i]]!=0 && v[nr[sarray[i]]]==0 && !find)
			{
				sum++;
				if(sum>n/2)
				{
					find=1;
					for(int j=sarray[i];j<sarray[i]+len;j++)
					{
						printf("%c",char(memo[j]-N));
					}
					print("");
				}
				v[nr[sarray[i]]]=1;
			}
		}
		if(height[i]<len)
		{
			memset(v,0,sizeof(v));
			sum=0;
			find=0;
		}
	}
}

int main()
{
	freopen("input.txt","r",stdin);
	char instr[1024];
	while(input(n) && n)
	{
		if(n==1)
		{
			input(instr);
			print(instr<<endl);
			continue;
		}
		
		pad=0;
		for(int i=1;i<=n;i++)
		{
			input(instr);
			int sz=strlen(instr);
			for(int j=0;j<sz;j++)
			{
				memo[pad]=instr[j]+N;
				//将n个字符串连起来，中间用不相同的且没有出现在字符串中的字符隔开
				nr[pad]=i;
				pad++;
			}
			memo[pad]=i;
			nr[pad]=0;
			pad++;
		}
		creatSuffixArray();
		creatHeight();		
		int i=0,j=pad;
		while(i<=j)
		{
			int mid=(i+j)/2;
			if(judge(mid)) i=mid+1;
			else j=mid-1;
		}
		if(j==0) print("?");
		else printAns(j);
		
		print("");
	}
	return 0;
}	
