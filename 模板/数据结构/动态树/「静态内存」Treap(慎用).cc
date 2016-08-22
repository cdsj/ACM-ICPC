/*
Data Structure?
Time Limit: 10000/5000 MS (Java/Others)    Memory Limit: 65536/65536 K (Java/Others)
Total Submission(s): 1803    Accepted Submission(s): 561


Problem Description
Data structure is one of the basic skills for Computer Science students, which is a particular way of storing and organizing data in a computer so that it can be used efficiently. Today let me introduce a data-structure-like problem for you.
Original, there are N numbers, namely 1, 2, 3...N. Each round, iSea find out the Ki-th smallest number and take it away, your task is reporting him the total sum of the numbers he has taken away.


Input
The first line contains a single integer T, indicating the number of test cases.
Each test case includes two integers N, K, K indicates the round numbers. Then a line with K numbers following, indicating in i (1-based) round, iSea take away the Ki-th smallest away.

Technical Specification
1. 1 <= T <= 128
2. 1 <= K <= N <= 262 144
3. 1 <= Ki <= N - i + 1


Output
For each test case, output the case number first, then the sum.


Sample Input

2
3 2
1 1

10 3
3 9 1

Sample Output

Case 1: 3
Case 2: 14

*/

/*
区间第K大数,静态Treap
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <ctime>

#pragma comment(linker, "/STACK:1024000000,1024000000")

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x

typedef long long llint;


template<typename T> class Treap
{
private:
	enum{SIZE=300000};

    struct TreapNode
    {
        TreapNode *left,*right;
        T value;
        int fix,size;
        TreapNode()
        {
            size=0;
        }
    };
    TreapNode *root,*null;

    TreapNode pool[SIZE];
    int ptr;

    TreapNode* alloc()
    {
		int t=ptr++;
		return &pool[t];
	}

    /*
    void Right_Rotate(TreapNode *&a);              //右旋              done
    void Left_Rotate(TreapNode *&a);               //左旋              done
    void Insert(TreapNode *&a,T k);                //插入              done
    void Delete(TreapNode *&a,T k);                //删除              done
    void Msize(TreapNode *&a);                     //维护节点的大小    done
    T Rank(TreapNode *&a,int k);                   //取第k小元素       done
    int Get_Rank(TreapNode *&a,int num,T k);       //取x的排名         done
    */

public:
	/*
    Treap<T>();                                     //构造函数          done
    void Insert(T x);                               //插入              done
    void Delete(T x);                               //删除              done
    int Size();                                     //返回树的大小      done
    T Max();                                        //取最大值          done
    T Min();                                        //取最小值          done
    T Rank(int k);                                  //取第k小元素       done
    int Get_Rank(T x);                              //取x的排名，如果不存在返回-1，done
    //当树为空的时候，Max,Min,Rank函数会出错
    */
    /*******************************************************************/

    Treap()
	{
		srand(time(0));
		ptr=0;
		null=alloc();
		root=null;
	}

	void Right_Rotate(TreapNode *&a)
	{
		TreapNode *b=a->left;
		a->left=b->right;
		b->right=a;
		Msize(a);
		Msize(b);
		a=b;
	}

	void Left_Rotate(TreapNode *&a)
	{
		TreapNode *b=a->right;
		a->right=b->left;
		b->left=a;
		Msize(a);
		Msize(b);
		a=b;
	}

	void Insert(TreapNode *&a,T k)
	{
		if(a==null)
		{
			a=alloc();
			a->value=k;
			a->fix=rand();
			a->size=1;
			a->left=a->right=null;
		}
		else if(k<=a->value)
		{
			Insert(a->left,k);
			a->size++;
			if(a->left->fix<a->fix)Right_Rotate(a);
		}
		else
		{
			Insert(a->right,k);
			a->size++;
			if(a->right->fix<a->fix)Left_Rotate(a);
		}
	}
	void Insert(T x)
	{
		Insert(root,x);
	}


	void Msize(TreapNode*& a)
	{
		a->size=1+a->left->size+a->right->size;
	}

	void Delete(TreapNode*& a,T k)
	{
		if(a->value==k)
		{
			if(a->right==null||a->left==null)
			{
				if(a->right==null)a=a->left;
				else a=a->right;
			}
			else
			{
				if(a->left->fix<a->right->fix)
				{
					TreapNode *tmp=a->left;
					Right_Rotate(a);
					Delete(a->right,k);
					Msize(tmp);
				}
				else
				{
					TreapNode *tmp=a->right;
					Left_Rotate(a);
					Delete(a->left,k);
					Msize(tmp);
				}
			}
		}
		else if(k<a->value) Delete(a->left,k),Msize(a);
		else Delete(a->right,k),Msize(a);
	}

	inline void Delete(T x){Delete(root,x);}

	T Max()
	{
		TreapNode *tmp=root;
		while(tmp->right!=null)tmp=tmp->right;
		return tmp->value;
	}

	T Min()
	{
		TreapNode *tmp=root;
		while(tmp->left!=null) tmp=tmp->left;
		return tmp->value;
	}

	int Size()
	{
		return root->size;
	}

	T Rank(TreapNode*& a, int k)
	{
		if(a->left->size+1==k)return a->value;
		else if(a->left->size>=k)return Rank(a->left,k);
		else return Rank(a->right,k-a->left->size-1);
	}

	T Rank(int k)
	{
		return Rank(root,k);
	}

	int Get_Rank(TreapNode*& a, int num, T k)
	{
		if(a==null)return -1;
		if(a->value==k)return num+a->left->size+1;
		if(k<a->value)return Get_Rank(a->left,num,k);
		return Get_Rank(a->right,num+a->left->size+1,k);
	}

	int Get_Rank(T x)
	{
		return Get_Rank(root,0,x);
	}
};

Treap<int> tp;//Tristian Prettyman

int n,k;

int main()
{
	freopen("input.txt","r",stdin);
	int T,tmp,ans,cas=1;
	input(T);
	while(T--)
	{
		tp=Treap<int>();
		input(n>>k);
		while(tp.Size()!=0) tp.Delete(tp.Min());
		llint sum=0;
		for(int i=1;i<=n;i++) tp.Insert(i);
		for(int i=0;i<k;i++)
		{
			scanf("%d",&tmp);
			ans=tp.Rank(tmp);
			tp.Delete(ans);
			sum+=ans;
		}
		printf("Case %d: ",cas++);
		print(sum);
	}
	return 0;
}

