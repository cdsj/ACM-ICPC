/*
Hotel
Time Limit: 5000MS		Memory Limit: 30000KB

Description
The "Informatics" hotel is one of the most luxurious hotels from Galaciuc. A lot of tourists arrive or leave this hotel in one year. So it is pretty difficult to keep the evidence of the occupied rooms. But this year the owner of the hotel decided to do some changes. That's why he engaged you to write an efficient program that should respond to all his needs. 

Write a program that should efficiently respond to these 3 types of instructions: 
type 1: the arrival of a new group of tourists 
A group of M tourists wants to occupy M free consecutive rooms. The program will receive the number i which represents the start room of the sequence of the rooms that the group wants to occupy and the number M representing the number of members of the group. It is guaranteed that all the rooms i,i+1,..,i+M-1 are free at that moment. 
type 2: the departure of a group of tourists 
The tourists leave in groups (not necessarilly those groups in which they came). A group with M members leaves M occupied and consecutive rooms. The program will receive the number i representing the start room of the sequence of the released rooms and the number M representing the number of members of the group. It is guaranteed that all the rooms i,i+1,..,i+M-1 are occupied. 
type 3: the owner's question 
The owner of the hotel may ask from time to time which is the maximal length of a sequence of free consecutive rooms. He needs this number to know which is the maximal number of tourists that could arrive to the hotel. You can assume that each room may be occupied by no more than one tourist.
 
Input
On the first line of input, there will be the numbers N (3 <= N <= 16 000) representing the number of the rooms and P (3 <= P <= 200 000) representing the number of the instructions. 

The next P lines will contain the number c representing the type of the instruction: 
if c is 1 then it will be followed (on the same line) by 2 other numbers, i and M, representing the number of the first room distributed to the group and the number of the members 
if c is 2 then it will be followed (on the same line) by 2 other numbers, i and M, representing the number of the first room that will be released and the number of the members of the group that is leaving 
if c is 3 then it will not be followed by any number on that line, but the program should output in the output file the maximal length of a sequence of free and consecutive rooms

Output
In the output you will print for each instruction of type 3, on separated lines, the maximal length of a sequence of free and consecutive rooms. Before the first instruction all the rooms are free.

Sample Input
12 10
3
1 2 3
1 9 4
3
2 2 1
3
2 9 2
3
2 3 2
3 

Sample Output
12
4
4
6
10
*/


/*
旅馆有三种操作：1入住，同时给你两个数i，M，其中i表示连续房间的起始房号，M表示房间数量；2退房，同时给你两个数i，M，其中i表示连续房间的起始房号；3查询，要求输出整个旅馆中，房号相连的最大空房间数量。
*/

//Result:wizmann	1823	Accepted	1016K	3485MS	C++	2699B	
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <bitset>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 16160

inline int left(int x)
{
	return (x<<1)+1;
}

inline int right(int x)
{
	return (x<<1)+2;
}

struct node
{
	int l,r;
	int now,lson,rson,val;

	node(){}
	node(int il,int ir)
	{
		l=il;r=ir;
		val=0;
		now=lson=rson=this->cover();
	}

	bool equal(int il,int ir)
	{
		return l==il && r==ir;
	}

	int getmid()
	{
		return (l+r)>>1;
	}
	
	bool has_next()
	{
		if(l==r) return false;
		else return true;
	}
	
	int cover()
	{
		return (r-l+1);
	}
};

node stree[SIZE<<2];
const int ROOT=0;
int n,q;

void stree_init(int l,int r,int pos=ROOT)
{
	stree[pos]=node(l,r);
	if(l<r)
	{
		int mid=(l+r)>>1;
		stree_init(l,mid,left(pos));
		stree_init(mid+1,r,right(pos));
	}
}

void stree_cover(int l,int r,int val,int pos=ROOT)
{
	if(stree[pos].equal(l,r))
	{
		stree[pos].val=val;
		if(val==0)
		{
			stree[pos].now=stree[pos].rson=stree[pos].lson=stree[pos].cover();
		}
		else
		{
			stree[pos].now=stree[pos].rson=stree[pos].lson=0;
		}
	}
	else
	{
		if(stree[pos].val!=-1)
		{
			stree_cover(stree[left(pos)].l,stree[left(pos)].r,stree[pos].val,left(pos));
			stree_cover(stree[right(pos)].l,stree[right(pos)].r,stree[pos].val,right(pos));
			stree[pos].val=-1;
		}

		int mid=stree[pos].getmid();
		if(mid>=r) stree_cover(l,r,val,left(pos));
		else if(mid<l) stree_cover(l,r,val,right(pos));
		else
		{
			stree_cover(l,mid,val,left(pos));
			stree_cover(mid+1,r,val,right(pos));
		}
		stree[pos].now=max(max(stree[left(pos)].now,stree[right(pos)].now),stree[left(pos)].rson+stree[right(pos)].lson);
		if(stree[left(pos)].lson==stree[left(pos)].cover())
		{
			stree[pos].lson=stree[left(pos)].lson+stree[right(pos)].lson;
		}
		else stree[pos].lson=stree[left(pos)].lson;

		if(stree[right(pos)].rson==stree[right(pos)].cover())
		{
			stree[pos].rson=stree[right(pos)].rson+stree[left(pos)].rson;
		}
		else stree[pos].rson=stree[right(pos)].rson;
	}
	//printf("L:%d R:%d  VAL:%d  SPACE:%d  LSPA:%d   RSPA:%d\n",stree[pos].l,stree[pos].r,stree[pos].val,stree[pos].now,stree[pos].lson,stree[pos].rson);
}


int main()
{
	freopen("input.txt","r",stdin);
	int cmd,a,b;
	while(input(n>>q))
	{
		stree_init(1,n);
		while(q--)
		{
			scanf("%d",&cmd);
			if(cmd<=2)
			{
				scanf("%d%d",&a,&b);
				//print(">>"<<a<<' '<<a+b-1);
				stree_cover(a,a+b-1,cmd&1);
				//puts("-----------------------------");
			}
			else
			{
				printf("%d\n",stree[ROOT].now);
			}
		}
	}
	return 0;
}
