/*
Bridge Across Islands
Time Limit: 1000MS		Memory Limit: 65536K

Description

Thousands of thousands years ago there was a small kingdom located in the middle of the Pacific Ocean. The territory of the kingdom consists two separated islands. Due to the impact of the ocean current, the shapes of both the islands became convex polygons. The king of the kingdom wanted to establish a bridge to connect the two islands. To minimize the cost, the king asked you, the bishop, to find the minimal distance between the boundaries of the two islands.


Input

The input consists of several test cases.
Each test case begins with two integers N, M. (3 ≤ N, M ≤ 10000)
Each of the next N lines contains a pair of coordinates, which describes the position of a vertex in one convex polygon.
Each of the next M lines contains a pair of coordinates, which describes the position of a vertex in the other convex polygon.
A line with N = M = 0 indicates the end of input.
The coordinates are within the range [-10000, 10000].

Output

For each test case output the minimal distance. An error within 0.001 is acceptable.

Sample Input

4 4
0.00000 0.00000
0.00000 1.00000
1.00000 1.00000
1.00000 0.00000
2.00000 0.00000
2.00000 1.00000
3.00000 1.00000
3.00000 0.00000
0 0
Sample Output

1.00000

*/


//Result:wizmann	3608	Accepted	1060K	141MS	G++	2735B	2012-09-15 12:47:25
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 10240

const double inf=1e100;
const double eps=1e-8;

inline double mul(double x){return x*x;}
inline double zero(double x)
{
	if(x>eps) return 1;
	else if(x<-eps) return -1;
	else return 0;
}

struct point
{
	double x,y;
	point(){}
	point(double ix,double iy)
	{
		x=ix;y=iy;
	}
};

inline double pntDis(const point &a,const point &b)
{
	return sqrt(mul(a.x-b.x)+mul(a.y-b.y));
}

double xmult(const point &sp,const point &ep,const point &op)
{
	return ((sp.x-op.x)*(ep.y-op.y)-(sp.y-op.y)*(ep.x-op.x));
}

double xmult(const point &a1,const point &a0,const point &b1,const point &b0)
{
	point sp=point(a1.x-a0.x,a1.y-a0.y);
	point ep=point(b1.x-b0.x,b1.y-b0.y);
	return xmult(sp,ep,point(0,0));
}

struct segment
{
	point p1,p2;
	segment(){}
	segment(const point &ip1,const point &ip2)
	{
		p1=ip1;p2=ip2;
	}
	double distopoint(const point &c)
	{
		double x=mul(p1.x-c.x)+mul(p1.y-c.y);
		double y=mul(p2.x-c.x)+mul(p2.y-c.y);
		double z=mul(p1.x-p2.x)+mul(p1.y-p2.y);
		if(x+z-y<0 || y+z-x<0) return sqrt(min(x,y));
		return fabs(xmult(c,p1,p2)/sqrt(z));
	}
};

int n,m;
point p1[SIZE],p2[SIZE];

double slove()
{
	int a=0,b=0;
	double ans=inf;
	if(zero(xmult(p1[1],p1[2],p1[0]))<0) reverse(p1,p1+n);
	if(zero(xmult(p2[1],p2[2],p2[0]))<0) reverse(p2,p2+m);

	for(int i=0;i<n;i++)
	{
		if(p1[i].y<p1[a].y) a=i;
	}
	for(int i=0;i<m;i++)
	{
		if(p2[i].y>p2[b].y) b=i;
	}

	p1[n]=p1[0];p2[m]=p2[0];
	int i=0,j=0;
	double tmp;

	while(i<=n || j<=m)
	{
		if(zero(xmult(p1[a+1],p1[a],p2[b],p2[b+1]))>0)
		{
			tmp=segment(p1[a],p1[a+1]).distopoint(p2[b]);
			a=(a+1)%n;
			i++;
		}
		else
		{
			tmp=segment(p2[b],p2[b+1]).distopoint(p1[a]);
			b=(b+1)%m;
			j++;
		}
		ans=min(ans,tmp);
	}
	return ans;
}


int main()
{
	freopen("input.txt","r",stdin);
	double a,b;
	while(scanf("%d%d",&n,&m)!=EOF && m+n)
	{
		for(int i=0;i<n;i++)
		{
			scanf("%lf%lf",&a,&b);
			p1[i]=point(a,b);
		}
		for(int i=0;i<m;i++)
		{
			scanf("%lf%lf",&a,&b);
			p2[i]=point(a,b);
		}
		printf("%.5f\n",slove());
	}
	return 0;
}
