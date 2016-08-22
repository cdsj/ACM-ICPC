/*
Palindrome
Time Limit: 15000MS		Memory Limit: 65536KB

Description

Andy the smart computer science student was attending an algorithms class when the professor asked the students a simple question, "Can you propose an efficient algorithm to find the length of the largest palindrome in a string?" 

A string is said to be a palindrome if it reads the same both forwards and backwards, for example "madam" is a palindrome while "acm" is not. 

The students recognized that this is a classical problem but couldn't come up with a solution better than iterating over all substrings and checking whether they are palindrome or not, obviously this algorithm is not efficient at all, after a while Andy raised his hand and said "Okay, I've a better algorithm" and before he starts to explain his idea he stopped for a moment and then said "Well, I've an even better algorithm!". 

If you think you know Andy's final solution then prove it! Given a string of at most 1000000 characters find and print the length of the largest palindrome inside this string.

Input

Your program will be tested on at most 30 test cases, each test case is given as a string of at most 1000000 lowercase characters on a line by itself. The input is terminated by a line that starts with the string "END" (quotes for clarity). 
Output
For each test case in the input print the test case number and the length of the largest palindrome. 

Sample Input

abcbabcbabcba
abacacbaaaab
END

Sample Output

Case 1: 13
Case 2: 6
*/

//Result:wizmann	3974	Accepted	42972K	3297MS	G++	879B
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

#define print(x) cout<<x<<endl
#define input(x) cin>>x
#define SIZE 10000005

int dp[SIZE];

int manacher(string& str)
{
	memset(dp,0,sizeof(dp));
	string s;
	int n=str.size();
	int ans=0;
	for(int i=0;i<n;i++)
	{
		s+='#';
		s+=str[i];
	}
	s+='#';
	n=(n<<1)+1;
	int i=0,j=1,k;
	while(i<n)
	{
		while(i-j>=0 && i+j<n && s[i-j]==s[i+j]) j++;
		dp[i]=j-1;
		k=1;
		while(k<=dp[i] && dp[i]-k!=dp[i-k])
		{
			dp[i+k]=min(dp[i-k],dp[i]-k);
			k++;
		}
		i+=k;
		j=max(j-k,0);
	}
	for(i=0;i<n;i++) ans=max(ans,dp[i]);
	return ans;
}


int main()
{
	int cas=1;
	string str;
	while(input(str))
	{
		if(str=="END") break;
		else
		{
			printf("Case %d: ",cas++);
			print(manacher(str));
		}
	}
	return 0;
}
