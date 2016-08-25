/*
HDU - 3685
Rotational Painting
Time Limit: 1000MS		Memory Limit: 32768KB

Description
给出一个多边形，判断有多少种稳定的摆放方法。

[分析]：从物理角度分析，多边形的稳定方法就是重心的垂足落在支撑边以内（不含顶点），而因为有可能会有凹多边形出现所以支撑边一定是所有点的凸包的边。现在问题转化成了：

（1）、求凸包：可以用Graham_Scan搞定

（2）、求重心：这个比较麻烦，有一堆的公式我也不会证明记住就行，真要想弄明白还是自己找计算几何的书看吧（谁搞懂了可以告诉我一声）。首先对多边形进行三角剖分（从0号点到i和i+1构成三角形），每个三角形的重心坐标就是xi=(x0+xi+xi+1)/3，yi=(y0+yi+yi+1)/3，然后三角形的有向面积G(i)就是它的两条边（0，i）和（0，i+1）的叉积。整个多边形的重心坐标就是

x0=ΣxiG(i)/ΣG(i)，y0=ΣyiG(i)/ΣG(i)。

（3）、枚举支撑边，判断重心的垂足是否在边上：从重心到支撑边的两顶点连边和支撑边构成的角应该都是锐角——这两条边和支撑边的点积应该都大于0

Input
The input file contains several test cases. The first line of the file contains an integer T representing the number of test cases. 

For each test case, the first line is an integer n representing the number of lines of the polygon. (3<=n<=50000). Then n lines follow. The ith line contains two real number xi and yi representing a point of the polygon. (xi, yi) to (xi+1, yi+1) represents a edge of the polygon (1<=i<n), and (xn,yn) to (x1, y1) also represents a edge of the polygon. The input data insures that the polygon is not self-crossed.
 
Output
For each test case, output a single integer number in a line representing the number of ways to put the polygonal glass stably on the table.
 
Sample Input
2
4
0 0
100 0
99 1
1 1
6
0 0
0 10
1 10
1 1
10 1
10 0
 
Sample Output
2
3
Hint
The sample test cases can be demonstrated by Figure 1 and Figure 2 in Description part.  
*/


//Result:2012-09-05 11:38:42	Accepted	3685	281MS	2784K	4350 B	C++	Wizmann
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define pb push_back
#define SIZE 50100

const double eps=1e-8;
const double inf=1e10;

inline int zero(double x)
{
	if(x>eps) return 1;
	else if(x<-eps) return -1;
	else return 0;
}

struct point
{
	double x,y;
	point(){x=y=-1;}
	point(double ix,double iy)
	{
		x=ix;y=iy;
	}
	friend bool operator == (const point &a,const point &b)
	{
		return zero(a.x-b.x)==0 && zero(a.y-b.y)==0;
	}
};

struct segment
{
	point p1,p2;
	segment(){}
	segment(const point& ip1,const point& ip2)
	{
		p1=ip1;p2=ip2;
	}
};

struct line
{
	double a,b,c;
	line(){}
	line(double ia,double ib,double ic)
	{
		a=ia;b=ib;c=ic;
	}
	line make_vertical(const point &p)
	{
		line res=(*this);
		swap(res.a,res.b);
		res.b*=-1;
		res.c=-(res.a*p.x+res.b*p.y);
		return res;
	}
};

double pntDis(const point &p1,const point &p2)
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

inline double xmult(point p1,point p2,point p0)
{
	return (p1.x-p0.x)*(p2.y-p0.y)-(p2.x-p0.x)*(p1.y-p0.y);
}

bool lineIntersect(line l1,line l2,point &p)
{
	double d=l1.a*l2.b-l2.a*l1.b;
	if(zero(d)==0) return false;
	else
	{
		p.x=(l2.c*l1.b-l1.c*l2.b)/d;
		p.y=(l2.a*l1.c-l1.a*l2.c)/d;
		return true;
	}
}

line makeLine(point p1,point p2)
{
	line res;
	int sig=1;
	res.a=p2.y-p1.y;
	if(zero(res.a)<0)
	{
		sig=-1;
		res.a=sig*res.a;
	}
	res.b=sig*(p1.x-p2.x);
	res.c=sig*(p1.y*p2.x-p2.y*p1.x);
	return res;
}

line makeLine(segment s)
{
	return makeLine(s.p1,s.p2);
}

bool onSegment(segment s,point p)
{
	return zero(xmult(s.p2,p,s.p1))==0 &&
			zero((p.x-s.p1.x)*(p.x-s.p2.x))<=0 &&
			zero((p.y-s.p1.y)*(p.y-s.p2.y))<=0;
}

vector<point> poly;

point getBaryCenter(point a,point b,point c)
{
	segment u,v;
	point p;
	u.p1.x=(a.x+b.x)/2;
	u.p1.y=(a.y+b.y)/2;
	u.p2=c;
	v.p1.x=(a.x+c.x)/2;
	v.p1.y=(a.y+c.y)/2;
	v.p2=b;
	lineIntersect(makeLine(u),makeLine(v),p);
	return p;
}

void getBaryCenter(point &p)//求多边形重心
{
	int sz=poly.size();
	point t;
	double t1=0,t2;
	p.x=p.y=0;
	for(int i=1;i<sz-1;i++)
	{
		t2=xmult(poly[0],poly[i],poly[i+1]);
		if(zero(t2)!=0)
		{
			t=getBaryCenter(poly[0],poly[i],poly[i+1]);
			p.x+=t.x*t2;
			p.y+=t.y*t2;
			t1+=t2;
		}
	}
	if(zero(t1)!=0)
	{
		p.x/=t1;
		p.y/=t1;
	}
}

namespace ConvexHull//一定要多于三个点
{
	int sz;
	point array[SIZE];
	point stack[SIZE];
	point *p;
	inline void push(point n){*p=n;	p++;}
	inline void pop(){p--;}
	inline void init(int isz)
	{
		sz=isz;
		memset(stack,0,sizeof(stack));
		p=stack;
	}

	int cmp(point p1,point p2)
	{
		if(xmult(p1,p2,array[0])>0) return 1;
		else if(xmult(p1,p2,array[0])==0 && pntDis(p1,array[0])<pntDis(p2,array[0])) return 1;
		else return 0;
	}
	int findtop()
	{
		int res=0;
		for(int i=1;i<sz;i++)
		{
			if(array[i].y<array[res].y) res=i;
			else if(array[i].y==array[res].y && array[i].x<array[res].x) res=i;
		}
		return res;
	}

	int graham()
	{
		int top=findtop();
		push(array[top]);
		swap(array[0],array[top]);
		sort(array+1,array+sz,cmp);
		
		push(array[1]);
		push(array[2]);
		for(int i=3;i<sz;i++)
		{
			while(xmult(array[i],*(p-1),*(p-2))>0) pop();//有等号时，不包括点都在一条直线的情况
			push(array[i]);
		}
		return p-stack;
	}
};


bool stable(point a,point b,point bc)//判断重心bc的垂足是否在边ab上
{
	segment seg(a,b);
	line l=makeLine(a,b);
	line v=l.make_vertical(bc);
	point p;
	lineIntersect(l,v,p);
	if(onSegment(seg,p))
	{
		if(p==a || p==b) return false;
		else return true;
	}
	return false;
}

int main()
{
	freopen("input.txt","r",stdin);
	int T,n;
	double a,b;
	input(T);
	while(T--)
	{
		int ans=0;
		poly.clear();
		input(n);
		ConvexHull::init(n);
		for(int i=0;i<n;i++)
		{
			scanf("%lf%lf",&a,&b);
			poly.pb(point(a,b));
		}
		point bc;
		getBaryCenter(bc);
		//print(bc.x<<' '<<bc.y);
		for(int i=0;i<n;i++)
		{
			ConvexHull::array[i]=poly[i];
		}
		int m=ConvexHull::graham();
		for(int i=0;i<m;i++)
		{
			int j=(i+1)%m;
			if(stable(ConvexHull::stack[i],ConvexHull::stack[j],bc))
			{
				ans++;
			}
		}
		print(ans);
	}
	return 0;
}
