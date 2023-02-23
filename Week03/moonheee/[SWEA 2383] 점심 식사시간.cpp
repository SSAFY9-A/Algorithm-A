// 최소 시간을 결정하는 경우의 수는 단 한개인가를 생각하면 알고리즘 유무가 나온다.
// 도착시간이 매우 빠른 친구를 먼저 보냅니다.
// 모든 친구는 분신술을 할 수 있습니다.
// 나보다 계단에 먼저 도착하는 친구들이 많을 수록 많이 기다려야 한다.
// 누구보다 계단에 먼저 도착한다면 내가 먼저 계단을 타야 한다.
// 제일 처음 계단을 빠져나갈 사람은 무조건 고를 수 없다.
// 예외 케이스 : 내가 계단에 가깝지만 내가 빨라서 다른 친구에게 양보하고
// 다른 계단으로 가는 착한 친구가 있을 수 있을까?

// 조합을 비트연산으로 하면 좋겠다
#include <iostream>
#include <vector>
#include <algorithm>

int min_time;
using namespace std;
int N;

struct Person
{
	int y;
	int x;
	int dis0;
	int dis1;
};

bool cmp0 (Person A, Person B)
{
	if (A.dis0 < B.dis0)
		return true;
	if (A.dis0 > B.dis0)
		return false;
	return false;
}

bool cmp1(Person A, Person B)
{
	if (A.dis1 < B.dis1)
		return true;
	if (A.dis1 > B.dis1)
		return false;
	return false;
}

struct Step
{
	int y;
	int x;
	int time;
};

vector<Step> down_time;    // 계단을 내려가는 시간
vector<Person> people;    // 사람 정보 ( 0 ~ 9 )
vector<Person> select0;		// 0번 계단을 골른 사람들
vector<Person> select1;		// 1번 계단을 고른 사람들

void init()
{
	cin >> N;
	int tmp;
	int t = 0;
	people.clear();
	select0.clear();
	select1.clear();
	down_time.clear();
	min_time = 21e8;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
		{
			cin >> tmp;
			if (tmp == 1)
				people.push_back({ y, x, 0 });
			else if (tmp > 1)
				down_time.push_back({ y, x, tmp });
		}

	// 각 계단에 대한 시간 입력
	for (int idx = 0; idx < people.size(); idx++)
	{
		people[idx].dis0 = abs(down_time[0].x - people[idx].x) + abs(down_time[0].y - people[idx].y) + 1;
		people[idx].dis1 = abs(down_time[1].x - people[idx].x) + abs(down_time[1].y - people[idx].y) + 1;
	}
	return;
}

void cal()
{
	// 계단 0이 끝나는 시간 구하기 (이미 정렬되어 있음)
	sort(select0.begin(), select0.end(), cmp0);
	int time0 = 0;
	if (!select0.empty())
	{
		time0 = select0[(select0.size() - 1) % 3].dis0 + down_time[0].time;
		for (int i = (select0.size() - 1) % 3 + 3; i < select0.size(); i += 3)
		{
			int wait_time;
			if (select0[i].dis0 >= time0)
				wait_time = 0;
			else
				wait_time = time0 - select0[i].dis0;
			time0 = select0[i].dis0 + down_time[0].time + wait_time;
		}
	}
	// 계단 1이 끝나는 시간 구하기
	sort(select1.begin(), select1.end(), cmp1);
	int time1 = 0;
	if (!select1.empty())
	{
		time1 = select1[(select1.size() - 1) % 3].dis1 + down_time[1].time;
		for (int i = (select1.size() - 1) % 3 + 3; i < select1.size(); i += 3)
		{
			int wait_time;
			if (select1[i].dis1 >= time1)
				wait_time = 0;
			else
				wait_time = time1 - select1[i].dis1;
			time1 = select1[i].dis1 + down_time[1].time + wait_time;
		}
	}
	// 최소 시간인지 확인하기
	if (time0 > time1)
	{
		if (time0 < min_time)
			min_time = time0;
	}
	else
	{
		if (time1 < min_time)
			min_time = time1;
	}
	return;
}

void dfs(int level)
{
	if (level >= people.size())
	{
		cal();
		return;
	}
	// 계단 0
	select0.push_back(people[level]);
	dfs(level + 1);
	select0.pop_back();
	// 계단 1
	select1.push_back(people[level]);
	dfs(level + 1);
	select1.pop_back();
	return;
}

int main()
{
	int T;
	cin >> T;

	for (int i_t = 0; i_t < T; i_t++)
	{
		init();
		sort(people.begin(), people.end(), cmp0);	// 계단 0번을 기준을 정렬되어 있다.
		dfs(0);
		cout << "#" << i_t + 1 << " " << min_time << "\n";
	}
	return 0;
}