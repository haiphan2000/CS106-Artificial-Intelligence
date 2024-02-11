#include<iostream>
#include<stack>
using namespace std;
string s[10] = { "Arad","Zerind","Orades","Timisoara","Craiova","Sibiu","R.Vilcea","Pitesti","Fagaras","Bucharest" };
int cost[10][10] ={
					  {0,75,0,118,0,140,0,0,0,0},
					  {75,0,71,0,0,0,0,0,0,0},
					  {0,71,0,0,0,151,0,0,0,0},
					  {118,0,0,0,376,0,0,0,0,0},
					  {0,0,0,376,0,0,146,124,0,0},
					  {140,0,151,0,0,0,80,0,99,0},
	                  {0,0,0,0,146,80,0,97,0,0},
					  {0,0,0,0,124,0,97,0,0,100},
					  {0,0,0,0,0,99,0,0,0,211},
					  {0,0,0,0,0,0,0,100,211,0},
                    };
int Prev[10], g[10] = { 0 }; int f[10] = { 0 };
bool Open[10] = { false }, Close[10] = { false };
int BirdFly[10] = { 366,374,380,329,160,253,193,98,178,0 };
stack<int> myStack;
int Min()
{
	int min, vt;
	for (int i = 1; i < 10; i++)
	{
		if (Open[i] == true) 
		{
			min = f[i];
			vt = i;
			break;
		}
	}
	for (int i = vt; i < 10; i++)
	{
		if ((Open[i] == true) && (f[i] <= min) && (f[i] != 0))
		{
			min = f[i];
			vt = i;
		}
	}
	return vt;
}
void TinhF(int i, int n)
{
	int temp = g[n] + cost[n][i];
	if ((g[i] == 0) || (temp < g[i]))
	{
		g[i] = temp;
		Prev[i] = n;
		f[i] = g[i] + BirdFly[i];
	}
}
void Order(int n)
{
	if (n == 0)
	{
		myStack.push(n);
		return;
	}
	myStack.push(n);
	Order(Prev[n]);
}
void Select(int n) //n là đỉnh được chọn
{
	Close[n] = true; Open[n] = false;
	for (int i = 0; i < 10; i++)
	{
		if (cost[n][i]!=0&&Close[i]==false)
		{
			 //i là đỉnh kề n
			Open[i] = true;
			TinhF(i,n);
		}
	} 
	int temp= Min();
	if (temp!=9) Select(temp);
	else
	{
		myStack.push(9);
		Order(n);
		return;
	}
}	
int main()
{
	g[0] = 0; Open[0] = true;
    	f[0]= BirdFly[0];
	Select(0);
	while (!myStack.empty())
	{
		if (myStack.size() != 1) cout << s[myStack.top()] << "->";
		else cout << s[myStack.top()];
		myStack.pop();
	}
}
