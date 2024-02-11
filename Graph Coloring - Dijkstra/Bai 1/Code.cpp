#include <iostream>
#include<fstream>
using namespace std;

struct dinh
{
	int name;
	int g;
	int prev;
};

int DT[50][50];
int n;

dinh open[50];
int nO = 0;
dinh close[50];
int nC = 0;

void Docfile()
{
	fstream f;
	f.open("C:/Users/lecao/Desktop/dothi.txt", ios::in);
	f >> n;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			f >> DT[i][j];
		}
}
void add(dinh N, dinh Set[], int& nS)
{
	Set[nS] = N;
	nS++;
}
void del(int vt, dinh open[], int& nO)
{
	for (int i = vt; i < nO - 1; i++)
		open[i] = open[i + 1];
	nO--;
}
int min(dinh open[], int nO)
{
	int min = open[0].g;
	int vt = 0;
	for (int i = 0; i < nO; i++)
	{
		if (min > open[i].g)
		{
			min = open[i].g;
			vt = i;
		}
		if (min == open[i].g)
		{
			if (open[vt].name > open[i].name)
			{
				min = open[i].name;
				vt = i;
			}
		}
	}
	return vt;
}
int check(int node, dinh Set[], int nS)
{
	for (int i = 0; i < nS; i++)
	{
		if (Set[i].name == node)
		{
			return i;
		}
	}
	return -1;
}
void Dijkstra(int S, int G)
{
	int node;
	dinh N;
	N.name = S;
	N.g = 0;
	N.prev = 0;
	add(N, open, nO);

	while (nO != 0)
	{
		int vt = min(open, nO);
		dinh N = open[vt];
		if (N.name == G)
		{
			add(N, close, nC);
			break;
		}
		else
		{
			add(N, close, nC);
			for (node = 0; node < n; node++)
			{
				int belong = check(node, close, nC);
				if (belong == -1 && DT[N.name][node] > 0)
				{
					int k = check(node, open, nO);
					if (k >= 0)
					{
						dinh Q;
						Q = open[k];
						if (N.g + DT[N.name][Q.name] < Q.g)
						{
							open[k].g = N.g + DT[N.name][Q.name];
							open[k].prev = N.name;
						}
					}
					else
					{
						dinh Q;
						Q.name = node;
						Q.g = N.g + DT[N.name][Q.name];
						Q.prev = N.name;
						add(Q, open, nO);
					}
				}
			}
			del(vt, open, nO);
		}

	}
}
int main()
{

	Docfile();
	int S, G;

	cout <<"\nDinh bat dau : ";
	cin >> S;
	cout << "\nDinh ket thuc : ";
	cin >> G;
	Dijkstra(S, G);
	int vtG = check(G, close, nC);
	if (vtG >= 0)
	{
		cout << "\nDuong di tu " << S <<" den " << G << " la : " << close[vtG].g;
		cout << "\nDuong di la : " << G;
		int k = vtG;
		while (close[k].prev != S)
		{
			cout << " <- " << close[k].prev;
			k = check(close[k].prev, close, nC);
		}
		cout << " <- " << S;
	}
	else
	{
		cout << "\nKhong co duong di tu "<<S << " den "<< G;
	}
	
	return 0;
}
