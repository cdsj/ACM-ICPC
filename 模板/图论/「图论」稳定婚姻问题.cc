//Result:wizmann	3487	Accepted	252K	16MS	C++	1646B	2012-10-03 11:15:17

//稳定婚姻问题：
//有一个社团里有n个女生和n个男生，每位女生按照她的偏爱程度将男生排序，
//同时每位男生也按照自己的偏爱程度将女生排序。然后将这n个女生和n个男生配成完备婚姻。
//如果存在两位女生A和B，两位男生a和b，使得A和a结婚，B和b结婚，
//但是A更偏爱b而不是a，b更偏爱A而不是B，则这个婚姻就是不稳定的，
//A和b可能背着别人相伴而走，因为他俩都认为，与当前配偶比起来他们更偏爱各自的新伴侣。


//输入：
//n个男士姓名(a..z)，n个女士姓名(A..Z)
//n个男士喜欢的女生的优先度排名
//n个女士喜欢的男生的排名

//输出：
//稳定婚姻，按男士名字的字典序排列

//The Stable Marriage Problem
//Time Limit: 1000MS 		Memory Limit: 65536KB
//Description
//
//The stable marriage problem consists of matching members of two different sets
//according to the member’s preferences for the other set’s members. The input 
//for our problem consists of:
//
//    a set M of n males;
//    a set F of n females;
//    for each male and female we have a list of all the members of the opposite 
//    gender in order of preference (from the most preferable to the least).
//
//A marriage is a one-to-one mapping between males and females. A marriage is 
//called stable, if there is no pair (m, f) such that f ∈ F prefers m ∈ M to her
//current partner and m prefers f over his current partner. The stable marriage 
//A is called male-optimal if there is no other stable marriage B, where any male 
//matches a female he prefers more than the one assigned in A.
//
//Given preferable lists of males and females, you must find the male-optimal 
//stable marriage.
//
//Input
//
//The first line gives you the number of tests. The first line of each test case 
//contains integer n (0 < n < 27). Next line describes n male and n female names. 
//Male name is a lowercase letter, female name is an upper-case letter. Then go 
//n lines, that describe preferable lists for males. Next n lines describe 
//preferable lists for females.
//
//Output

//For each test case find and print the pairs of the stable marriage, which is 
//male-optimal. The pairs in each test case must be printed in lexicographical 
//order of their male names as shown in sample output. Output an empty line 
//between test cases.

//Sample Input
//
//2
//3
//a b c A B C
//a:BAC
//b:BAC
//c:ACB
//A:acb
//B:bac
//C:cab
//3
//a b c A B C
//a:ABC
//b:ABC
//c:BCA
//A:bac
//B:acb
//C:abc
//
//Sample Output
//
//a A
//b B
//c C
//
//a B
//b A
//c C

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
#define SIZE 32

int n;
int m_name[SIZE],f_name[SIZE];
int m_like[SIZE][SIZE],f_like[SIZE][SIZE];
int m_visit[SIZE],f_visit[SIZE];

int main()
{
	freopen("input.txt","r",stdin);
	int T;
	char str[36];
	input(T);
	while(T--)
	{
		scanf("%d",&n);
		memset(m_name,0,sizeof(m_name));
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			m_name[i]=*str-'a'+1;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			f_name[i]=*str-'A'+1;
		}
		
		sort(m_name,m_name+n);//重新编号，使字典序小的在先
		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			for(int j=1;j<=n;j++)
			{
				m_like[i][j]=str[j+1]-'A'+1;
			}
		}

		for(int i=1;i<=n;i++)
		{
			scanf("%s",str);
			for(int j=1;j<=n;j++)
			{
				f_like[i][str[j+1]-'a'+1]=n-j+1;
			}
			f_like[i][n+1]=-1;//虚拟人物，所有女生对它的喜爱度为-1
		}

		memset(m_visit,0,sizeof(m_visit));
		memset(f_visit,0,sizeof(f_visit));
		queue<int> q;
		for(int i=1;i<=n;i++) q.push(m_name[i]);
		for(int i=1;i<=n;i++) f_visit[i]=n+1;

		while(!q.empty())
		{
			int male=q.front();
			int female=m_like[male][m_visit[male]];
			if(f_like[female][male]>f_like[female][f_visit[female]])
			{
				q.pop();
				if(f_visit[female]!=n+1)
				{
					q.push(f_visit[female]);
					m_visit[f_visit[female]]++;
				}
				f_visit[female]=male;
			}
			else m_visit[male]++;
		}

		for(int i=1;i<=n;i++)
		{
			printf("%c %c\n",m_name[i]+'a'-1,m_like[m_name[i]][m_visit[i]]+'A'-1);
		}
		if(T) puts("");
	}
	return 0;
}
