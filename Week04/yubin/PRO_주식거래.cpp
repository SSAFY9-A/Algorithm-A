#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
int Ms, Ma;//첫 시드액과 월별 투자금액
int N, L;//종목 수와 데이터 기간. 종목수와 기간은 15이하. 

vector<int>v[15];

int buy[15];
int Max;
int now;

struct node
{
	int me; 
	int ori; //현재의 가격
	int plus; //가능한 이득
};

//차이는 커야 하고, 현재 가격은 작아야함!
bool cmp(node right, node left)
{
	if (right.plus > left.plus)
		return true;
	else if (right.plus < left.plus)
		return false;
	else if (right.ori < left.ori)
		return true;
	else if (right.ori > left.ori)
		return false;
	return false;
}
void run()
{
	int M = 0;
	int minus;
	int plus;

	//일단 저장하고 
	for (int k = 0; k < L; k++)
	{
		vector<node>Sort_List;
		M = 0;
		//k가 0개월이 아니라면 월별 투자금액 증가. 
		if (k != 0)
			now = now + Ma;

		//전 달에 매수항목이 있다면 매도.
		for (int i = 0; i < N; i++)
		{
			if (buy[i] > 0)
			{
				//i종목을 buy[i]만큼 샀다는 말. 
				now += v[i][k] * buy[i];
				buy[i] = 0;
			}
		}
		//다음달과 차이 확인
		for (int i = 0; i < N; i++)
		{
			minus = v[i][k + 1] - v[i][k];

			if (minus > 0)
			{
				plus = now / v[i][k];
				Sort_List.push_back({ i,v[i][k],plus*minus });
			}
			if (M < minus)
				M = minus;
		}
		//만일 다 마이너스다? 그러면 살 필요가 없지 
		if (M == 0)
		{
			continue;
		}
		//만일? 플러스가 있다? 일단 정렬!
		sort(Sort_List.begin(), Sort_List.end(), cmp);

		for (int i = 0; i < Sort_List.size(); i++)
		{
			//구매하자.
			if (now < v[Sort_List[i].me][k]) continue;
			int num = now / v[Sort_List[i].me][k]; //몫은 살 수 있는 수 
			int rest = now % v[Sort_List[i].me][k]; //나머지는 now값. 
			buy[Sort_List[i].me] = num;
			//cout << "원래는 " << now;
			now = rest;
		}
	}

	//마지막달! 사는거 없이 매수한게 있다면 매도!
	now = now + Ma;
	for (int i = 0; i < N; i++)
	{

		if (buy[i] > 0)
		{
			//i종목을 buy[i]만큼 샀다는 말. 
			now += v[i][L] * buy[i];
			buy[i] = 0;
		}
	}
}

int main()
{
	int T;
	int origin;
	int input;
	cin >> T;
	for (int tc = 1; tc <= T; tc++)
	{
		cin >> Ms >> Ma;
		cin >> N >> L;
		Max = 0;
		now = 0;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j <= L; j++)
			{
				cin >> input;
				v[i].push_back(input);
			}
		}
		now = Ms;
		run();
		origin = Ms + Ma * L; //구한 수익을 이거에 빼야한다. 
		cout << "#" << tc << " " << now - origin << "\n";
		for (int i = 0; i < 15; i++)
			v[i].clear();

	}
}
