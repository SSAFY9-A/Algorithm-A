/*
주식거래 
초기 시드액 Ms
매달 주기적으로 투자 금액 Ma
과거 데이터 기간 L
과거 데이터 종목 N
종목별 주식 가격

과정 투자액 증가 매도 매수 
최대 수익
*/
#include <iostream>
#include <cstring>
using namespace std;
int Ms, Ma;
int N, L;
int item[15][16];
int dat[15][15];
int MAX;
void select(int money, int level, int i, int sum)
{
	for (int t = i; t < N; t++)
	{
		if (dat[t][level] > 0)
		{
			if (money > item[t][level])
			{
				select(money-item[t][level], level, t, sum + dat[t][level]);
			}
		}
	}
	if (MAX < sum)
		MAX = sum;
	return;
}
int sv(void)
{
	
	int money = Ms;
	for (int t = 0; t < N; t++)
	{
		for (int x = 0; x < L; x++)
		{
			if (item[t][x + 1] - item[t][x] > 0)
				dat[t][x] = item[t][x + 1] - item[t][x];
		}
	}

	for(int t=0; t<L; t++)
	{
		MAX = 0;
		select(money, t, 0, 0);
		money += MAX + Ma;
	}
	return money - (Ms + Ma * L);
}
int main(void)
{	
	int T,i;
	cin >> T;
	for(int tc=1; tc<=T; tc++)
	{
		cin >> Ms >> Ma;
		cin >> N >> L;
		for (int t = 0; t < N; t++)
		{
			for (int x = 0; x <= L; x++)
			{
				cin >> i;
				item[t][x] = i;
			}
		}
		cout << '#' << tc << ' ' << sv()<<'\n';
		memset(dat, 0, sizeof(dat));
	}
}
