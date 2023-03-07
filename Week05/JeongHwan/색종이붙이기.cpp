/*
색종이 붙이기

색종이 1,2,3,4,5

*/
#include <iostream>
using namespace std;
int map[10][10];
int Min = 21e8;
int cnt;
int dat[6];
int num;
int sum;
bool isValid(int sy, int sx, int t)
{
	if (dat[t] >= 5) return false;
	for (int y = sy; y < sy + t; y++)
	{
		for (int x = sx; x < sx + t; x++)
		{
			if (y < 0 || x < 0 || y >= 10 || x >= 10)  return false;
			if (map[y][x] == 0) return false;
		}
	}
	return true;
}



void sv(int level)
{


	for (int y = level / 10; y < 10; y++)
		for (int x = level % 10; x < 10; x++)
		{
			if (map[y][x] == 1)
			{
				bool a = false;
				for (int t = 1; t <= 5; t++)
				{
					if (isValid(y, x, t))
					{
						a = true;
						dat[t]++;
						sum += t * t;
						cnt++;
						for (int q = y; q < y + t; q++)
							for (int w = x; w < x + t; w++)
								map[q][w] = 0;

						sv(y * 10 + x + 1);

						for (int q = y; q < y + t; q++)
							for (int w = x; w < x + t; w++)
								map[q][w] = 1;
						dat[t]--;
						cnt--;
						sum -= t * t;
					}
				}
				if (!a) return;
			}
		}

	if (sum == num && Min > cnt) Min = cnt;
	
}


int main(void)
{
	for (int y = 0; y < 10; y++)
		for (int x = 0; x < 10; x++)
		{
			cin >> map[y][x];
			if (map[y][x] == 1)
				num++;
		}
	sv(0);
	if (Min == 21e8) Min = -1;
	cout << Min;
}
