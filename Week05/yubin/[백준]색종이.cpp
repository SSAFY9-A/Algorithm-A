#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int map[10][10];
int via[10][10];
int CNT;
int dat[5];
//2,3,4,5,6으로 확인

int findMax(int y, int x)
{
	int flag = 0;
	int k = 0;
	//중복 체크를 어떻게 할까,,
	for (k = 1; k <5; k++)
	{
		flag = 0;
		for (int i = y; i < y + k; i++)
		{
			for (int j = x; j < x + k; j++)
			{
				if (map[i][j] == 0)
				{
					flag = 1;
					break;
				}
				
			}
			if (flag == 1)
				break;
		}
		if (flag == 1)
			break;
	}
	if (flag == 1)
	{
		k--;
		for (int i = y; i < y + k; i++)
		{
			for (int j = x; j < x + k; j++)
			{
				map[i][j] = 0;
			}
		}
		return k - 1;
	}
	for (int i = y; i < y + k; i++)
	{
		for (int j = x; j < x + k; j++)
		{
			map[i][j] = 0;
		}
	}
	return k;
}
void run()
{
	int result = 0;
	int pre_sum = 0;
	int flag = 0;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (map[i][j] == 1)
			{
				result=findMax(i, j);
				cout << result << " ";
				dat[result]++;
				if (dat[result] > 5)
				{
					flag = 1;
					break;
				}
			}
		}
		if (flag == 1)
			break;
	}
	if (flag == 1)
		cout << "-1";
	else {
		for (int i = 0; i < 5; i++)
			pre_sum += dat[i];
		cout << pre_sum;
	}
}
int  main()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			cin >> map[i][j];
	run();
}
