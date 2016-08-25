/*
Nubulsa Expo
Time Limit: 3000MS 		Memory Limit: 32768KB

Description
You may not hear about Nubulsa, an island country on the Pacific Ocean. Nubulsa is an undeveloped country and it is threatened by the rising of sea level. Scientists predict that Nubulsa will disappear by the year of 2012. Nubulsa government wants to host the 2011 Expo in their country so that even in the future, all the people in the world will remember that there was a country named “Nubulsa”.

As you know, the Expo garden is made up of many museums of different countries. In the Expo garden, there are a lot of bi-directional roads connecting those museums, and all museums are directly or indirectly connected with others. Each road has a tourist capacity which means the maximum number of people who can pass the road per second.

Because Nubulsa is not a rich country and the ticket checking machine is very expensive, the government decides that there must be only one entrance and one exit. The president has already chosen a museum as the entrance of the whole Expo garden, and it’s the Expo chief directory Wuzula’s job to choose a museum as the exit.

Wuzula has been to the Shanghai Expo, and he was frightened by the tremendous “people mountain people sea” there. He wants to control the number of people in his Expo garden. So Wuzula wants to find a suitable museum as the exit so that the “max tourists flow” of the Expo garden is the minimum. If the “max tourist flow” is W, it means that when the Expo garden comes to “stable status”, the number of tourists who enter the entrance per second is at most W. When the Expo garden is in “stable status”, it means that the number of people in the Expo garden remains unchanged.

Because there are only some posters in every museum, so Wuzula assume that all tourists just keep walking and even when they come to a museum, they just walk through, never stay.
 

Input
There are several test cases, and the input ends with a line of “0 0 0”.

For each test case:

The first line contains three integers N, M and S, representing the number of the museums, the number of roads and the No. of the museum which is chosen as the entrance (all museums are numbered from 1 to N). For example, 5 5 1 means that there are 5 museums and 5 roads connecting them, and the No. 1 museum is the entrance.

The next M lines describe the roads. Each line contains three integers X, Y and K, representing the road connects museum X with museum Y directly and its tourist capacity is K.

Please note:

1<N<=300, 0<M<=50000, 0<S,X,Y<=N, 0<K<=1000000

Output
For each test case, print a line with only an integer W, representing the “max tourist flow” of the Expo garden if Wuzula makes the right choice.

Sample Input

5 5 1
1 2 5 
2 4 6 
1 3 7 
3 4 3 
5 1 10 
0 0 0

Sample Output

8

【题目大意】

给定一个无向连通图和一个源点，让你选一个汇点，使得源点到汇点的最大流最小。输出这时的最大流流量。

【算法分析】

实际上就是求全局最小割。给的那个源点是废的，因为如果图被分割开了，无论当前这个源点在那一块，总有一个汇点在另外一块。所以可以无视他给的源点。

*/
 


//Stoer-Wagner算法，求全局最大流/最小割
//图中点的编号从0开始

//Result:2012-09-07 16:21:35	Accepted	3691	703MS	700K	1339 B	C++	Wizmann
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 320
#define INF 1<<28

int mp[SIZE][SIZE],w[SIZE],c[SIZE];
int n,sx,tx;

void contract(int x,int y)
{
	for(int i=0;i<n;i++)
	{
		if (i!=x)
		{
			mp[x][i]+=mp[y][i];
			mp[i][x]+=mp[i][y];
		}
	}
	for(int i=y+1;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			mp[i-1][j]=mp[i][j];
			mp[j][i-1]=mp[j][i];
		}
	}
	n--;
}

int mincut()
{
	memset(c,0,sizeof(c));
	c[0]=1;
	for(int i=0;i<n;i++) w[i]=mp[0][i];
	for(int i=1;i+1<n;i++)
	{
		int t=-1,k=-1;
		for(int j=0;j<n;j++)
		{
			if(c[j]==0&&w[j]>k)
			{
				t=j;
				k=w[t];
			}
		}
		sx=t;
		c[sx]=1;
		for(int j=0;j<n;j++) w[j]+=mp[t][j];
	}
	for(int i=0;i<n;i++)
	{
		if(c[i]==0)
		{
			tx=i;
			return w[tx];
		}
	}
	return -1;
}

int SW()
{
	int ans=INF;
	while(n>1)
	{
		int mc=mincut();
		ans=min(ans,mc);
		contract(sx,tx);
	}
	return ans;
}


int main()
{
	freopen("input.txt","r",stdin);
	int m,st;
	int a,b,c;
	while(input(n>>m>>st) && n+m+st)
	{
		memset(mp,0,sizeof(mp));
		for(int i=0;i<m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			mp[a-1][b-1]+=c;
			mp[b-1][a-1]+=c;
		}
		printf("%d\n",SW());
	}
	return 0;
}
