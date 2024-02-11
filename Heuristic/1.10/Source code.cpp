#include<iostream>
using namespace std;
int ChonMay(int MC[], int m)
{
	int min = MC[1];
	int vt = 1;
	for (int i = 2; i <= m; i++)
	{
		if (min > MC[i])
		{
			min = MC[i];
			vt = i;
		}
	}
	return vt;
}
void Sapxepmang(int CV[], int id[], int n)
{
	for(int i=1;i<=n-1;i++)
		for (int j = i+1; j <= n; j++)
		{
			if (CV[i] < CV[j])
			{
				swap(CV[i], CV[j]);
				swap(id[i], id[j]);
			}
		}
}
int main()
{
	int n, m, CV[100], MC[100] = { 0 },id[100], record[100];
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		cin >> CV[i];
		id[i] = i;
	}
	Sapxepmang(CV, id, n);
	for (int i = 1; i <= n; i++)
	{
		int may = ChonMay(MC,m);
		record[id[i]] = may;
		MC[may] += CV[i];
	}
	for (int i = 1; i <= n; i++)
	{
		cout << "nhiem vu thu " << i << "duoc giao cho may " << record[i] << endl;
	}
	return 0;
}