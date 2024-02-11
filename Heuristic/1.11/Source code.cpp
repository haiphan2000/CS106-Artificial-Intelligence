#include <iostream>
#include <utility>
#define MAX_N 100
using namespace std;

void input(int time[][MAX_N], int id[][MAX_N], int &m, int &n);
void arrange(int time[][MAX_N], int id[][MAX_N], int m, int n);
int findMaxTimeOfMachines(int machine[], int m);
void findSolution(int time[][MAX_N], int id[][MAX_N], int machine[], int solution[], int m, int n);
void output(int solution[], int machine[], int m, int n);

int main()
{
    int m;
    int n;
    int time[MAX_N][MAX_N];
    int id[MAX_N][MAX_N];
    int machine[MAX_N];
    int solution[MAX_N];
    
    input(time, id, m, n);
    findSolution(time, id, machine, solution, m, n);
    output(solution, machine, m, n);
    
    return 0;
}

void input(int time[][MAX_N], int id[][MAX_N], int &m, int &n)
{
    cout << "INPUT:" << endl;
    cin >> m >> n;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
        {
            cin >> time[i][j];
            id[i][j] = i;
        }
}

void arrange(int time[][MAX_N], int id[][MAX_N], int m, int n)
{
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j < m; j++)
        {
            for (int k = j + 1; k <= m; k++)
            {
                if (time[j][i] > time[k][i])
                {
                    swap(time[j][i], time[k][i]);
                    swap(id[j][i], id[k][i]);
                }
            }
        }
    }
}

int findMaxTimeOfMachines(int machine[], int m)
{
    int max = 1;
    for (int i = 2; i <= m; i++)
        if (machine[i] >= machine[max])
            max = i;
    return max;
}

void findSolution(int time[][MAX_N], int id[][MAX_N], int machine[], int solution[], int m, int n)
{
    arrange(time, id, m, n);
    for (int i = 1; i <= n; i++)
    {
        if (i == 1 || findMaxTimeOfMachines(machine, m) != id[1][i])
        {
            solution[i] = id[1][i];
            machine[id[1][i]] = machine[id[1][i]] + time[1][i];
        }
        else
        {
            solution[i] = id[2][i];
            machine[id[2][i]] = machine[id[2][i]] + time[2][i];
        }
    }
}

void output(int solution[], int machine[], int m, int n)
{
    cout << "OUTPUT:" << endl;
    for (int i = 1; i <= n; i++)
    {
        cout << i << " -> " << solution[i] << endl;
    }
    cout << machine[findMaxTimeOfMachines(machine, n)];
}