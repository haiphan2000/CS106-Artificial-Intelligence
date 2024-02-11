#include<iostream>
#include <string>
#include <fstream>
using namespace std;
typedef char TAB[3][3];
TAB S0, G; int n;
struct info {
	TAB S;
	unsigned int g, h, f;
	int d;
	void Xuat()
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
				cout << S[i][j] << " ";
			cout << endl;
		}
 	}
};
typedef struct List
{
	int n = 0;
	info e[500];
	void Add(info X)
	{
		e[n] = X;
		n++;
	}
	void Del(info X)
	{
		for (int i = 0; i < n; i++)
		{
			if (SoSanh(e[i].S, X.S) == 1)
			{
				for (int j = i; j < n; j++)
					e[j] = e[j + 1];
				n -= 1;
			}
		}
	}
	info Searchfmin()
	{
		int vitri = 0;
		info min = e[0];
		for (int i = 1; i < n; i++)
		{
			if (e[i].f < min.f)
			{
				min.f = e[i].f;
				vitri = i;
			}
		}
		return e[vitri];
	}
	void ListOut()
	{
		for (int i = 0; i < n; i++)
		{
			e[i].Xuat();
			cout << endl;
		}
	}
	int SoSanh(TAB S1, TAB S2)
	{
		int temp = 0;
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
			{
				if (S1[i][j] == S2[i][j]) temp += 1;
			}
		if (temp == 9) return 1;
		return 0;
	}
	int Position(TAB X)
	{
		for (int i = 0; i < n; i++)
		{
			if (SoSanh(e[i].S, X) == 1) return i;
		}
		return -1;
	}
	
};
List O, C, KQ;
void Input(TAB X,TAB Y)
{
	fstream f;
	f.open("Input.txt", ios::in);
	f >> n;
	for(int i=0;i<6;i++)
		for (int j = 0; j < 3; j++)
		{
 			if (i < 3) f >> X[i][j];
			else f >> Y[i%3][j];
		}
	f.close();
}
unsigned int count(TAB S)
{
	int temp = 0;
	for(int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
		{
			if (S[i][j] != G[i][j]) temp += 1;
		}
	return temp;
}
int sobang(TAB S1, TAB S2)
{
	int temp = 0;
    for(int i=0;i<3;i++)
		for (int j = 0; j < 3; j++)
		{
			if (S1[i][j] == S2[i][j]) temp += 1;
		}
	if (temp == 9) return 1;
	return 0;
}
void ganbang(TAB S1, TAB S2)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
		{
			S1[i][j] = S2[i][j];
		}
}
void timotrong(TAB S, int& k, int& l)
{
	bool findout = false;
	for (int i = 0; i < 3; i++)
	{
		if (findout == true) break;
		for (int j = 0; j < 3; j++)
			if (S[i][j] ==*"0")
			{
				k = i; l = j;
				findout = true;
			}
	}
}
void bangke(TAB N,int d,TAB S, int k, int l)
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			S[i][j] = N[i][j];
	if (d == 1)
	{
		if (k + 1 <= 2) swap(S[k + 1][l], S[k][l]);
	}
	else
		if (d == 2)
		{
			if (k - 1 >= 0) swap(S[k - 1][l], S[k][l]);
		}
		else if (d == 3)
		{
			if (l + 1 <= 2) swap(S[k][l], S[k][l + 1]);
		}
		else
			if (l - 1 >= 0) swap(S[k][l], S[k][l - 1]);
}
void xulyke(info X, int d, TAB S)
{
	info Y;
	int k;
	if (C.Position(S) != -1) return;
	if (k = O.Position(S) == -1)
	{
		ganbang(Y.S, S);
		Y.g = X.g + 1;
		Y.h = count(S);
		Y.f = Y.g + Y.h;
		Y.d = d;
		O.Add(Y);
	}
	else if (X.g + 1 < O.e[k].g)
	{
		O.e[k].g = X.g + 1;
		O.e[k].f = O.e[k].g + O.e[k].h;
		O.e[k].d = d;
	}

}
int main()
{
   Input(S0,G);
   info X;
   ganbang(X.S, S0);
   X.g = 0;
   X.h = count(S0);
   X.f = X.h;
   X.d = 0;
   O.Add(X);
   while (O.n > 0)
   {
	   int k = 0, l = 0, d = 0;
	   TAB BK;
	   info X = O.Searchfmin();
	   C.Add(X);
	   if (sobang(X.S, G) == 1) break;
	   timotrong(X.S,k, l);
	   if (k >= 0)
	   {
		   d = 1;
		   bangke(X.S, 1, BK, k, l);
           if (sobang(X.S,BK)==0) xulyke(X, d, BK);
	   }
	   if (k <= 2)
	   {
		   d = 2;
		   bangke(X.S, 2, BK, k, l);
		   if (sobang(X.S, BK) == 0) xulyke(X, d, BK);
	   }
	   if (l >= 0)
	   {
		   d = 3;
		   bangke(X.S, 3, BK, k, l);
		   if (sobang(X.S, BK) == 0) xulyke(X, d, BK);
	   }
	   if (l <= 2)
	   {
		   d = 4;
		   bangke(X.S, 4, BK, k, l);
		   if (sobang(X.S, BK) == 0) xulyke(X, d, BK);
	   }
	   O.Del(X);
   }
   C.ListOut();
}
