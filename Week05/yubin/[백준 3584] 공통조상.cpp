#include<iostream>
#include<cstring>

using namespace std;

int N; //N은 10,000 이하
int parent[10001];
int checkParent[10001];

void Union(int a, int b)
{
	parent[b] = a;
}
int SameParent(int a, int b)
{
	int flag = 0;
	while (1)
	{
		//cout << a << " ";
		checkParent[a]++;
		if (parent[a] == a)
			break;
		a = parent[a];
		//cout << a << " ";
	}
	//cout << "\n--------\n";
	while (1)
	{
		checkParent[b]++;
		//cout << b << ", ";
		if (checkParent[b] > 1)
		{
			flag = b;
			//cout << "!";
			break;
		}
		if (parent[b] == b)
		{
			//cout << "!!";
			break;
		}
		b = parent[b];
		//cout << b << " ";
	}
	return flag;
}
int main()
{
	int T;
	int input1, input2;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> N;
		memset(checkParent, 0, sizeof(checkParent));
		for (int i = 0; i <= N; i++)
			parent[i] = i;
		for (int i = 0; i < N - 1; i++)
		{
			cin >> input1 >> input2;
			Union(input1, input2);
		}
		cin >> input1 >> input2;
		int result = SameParent(input1, input2);
		cout << result << '\n';
	}
	return 0;
}
