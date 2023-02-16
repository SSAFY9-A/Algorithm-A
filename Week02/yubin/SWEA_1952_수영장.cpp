#include<iostream>

using namespace std;

int D, M, M3, Y; //1일,한달,세달,일년 이용권
int arr[12]; 
int SUM;
int MIN;

void run(int now)
{
	if (now >= 12)
	{
		if (MIN > SUM)
			MIN = SUM;
		return;
	}
	if (SUM > MIN)
		return;

	//1일요금
	SUM += arr[now] * D;
	run(now + 1);
	SUM -= arr[now] * D;

	//한달요금
	if (arr[now] != 0) SUM += M;
	run(now + 1);
	if (arr[now] != 0) SUM -= M;
	
	//세달요금 
	SUM += M3;
	run(now + 3);
	SUM -= M3;

}

int main()
{
	int TC;
	cin >> TC;
	for (int tc = 0; tc < TC; tc++)
	{
		SUM=0;
		MIN = 21e8;

		cin >> D >> M >> M3 >> Y;
		for (int i = 0; i < 12; i++)
			cin >> arr[i];

		run(0);
		if (MIN > Y)
			MIN = Y;
		cout << "#" << tc + 1 << " " << MIN << '\n';
	}
}
