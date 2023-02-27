// 50개 테케 3초컷 .06초
// 1 ≤ N, M ≤ 9
// 2 ≤ K ≤ 1,000
// 시간이 순서대로 들어오지 않는다.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int N, M, K, A, B;

struct Person
{
	int number;
	int arr_time;
	int timer;
	int ai_num;
	int bj_num;

	bool operator < (Person B) const
	{
		if (arr_time > B.arr_time)
			return true;
		if (arr_time < B.arr_time)
			return false;
		if (number > B.number)
			return true;
		if (number < B.number)
			return false;
		return false;
	}
};

int ai_time[10]; // 접수 창고 i 시간
int bj_time[10]; // 정비 창고 j
vector<Person> ai[10]; // 점유한 손님 표시
vector<Person> bj[10];
vector<Person> costomers;
vector<Person> waiting;

int result;

void init()
{
	result = 0;
	cin >> N >> M >> K >> A >> B;
	for (int i_n = 1; i_n <= N; i_n++)
		cin >> ai_time[i_n];
	for (int i_m = 1; i_m <= M; i_m++)
		cin >> bj_time[i_m];
	Person tmp;
	for (int i_k = 1; i_k <= K; i_k++)
	{
		cin >> tmp.arr_time;
		tmp.number = i_k;
		costomers.push_back(tmp);
	}
	return;
}

int ft_ai_is_empty()
{
	int result = 0;
	for (int i_n = 1; i_n <= N; i_n++)
		result += ai[i_n].size();
	if (result == 0)
		return 1;
	else
		return 0;
}

int find_ai_empty_index()
{
	for (int i_n = 1; i_n <= N; i_n++)
		if (ai[i_n].size() == 0)
			return i_n;
	return -1;
}

int ft_bj_is_empty()
{
	int result = 0;
	for (int i_m = 1; i_m <= M; i_m++)
		result += bj[i_m].size();
	if (result == 0)
		return 1;
	else
		return 0;
}

int find_bj_empty_index()
{
	for (int i_m = 1; i_m <= N; i_m++)
		if (bj[i_m].size() == 0)
			return i_m;
	return -1;
}

bool cmp(Person a, Person b)
{
	if (a.ai_num > b.ai_num)
		return true;
	if (a.ai_num < b.ai_num)
		return false;
	return false;
}

void solution()
{
	// 도착 순으로 정렬 (내림차순)
	sort(costomers.begin(), costomers.end());

	// 시간을 기준으로 돌립니다.
	// 끝나는 타이밍은 접수, 수리, 대기가 모두 없어야 합니다.
	int day = -1;
	while (!costomers.empty() || !waiting.empty() || !ft_ai_is_empty() || !ft_bj_is_empty())
	{
		// 반복문 한 바퀴를 돌련 시간 1이지남
		day++;
		// 대기하는 사람들 중에 동시에 도착한 사람을 찾는다.
		int end;
		Person end_person;
		if (!costomers.empty())
		{
			end_person = costomers[costomers.size() - 1];
			for (end = costomers.size() - 1; end >= 0; end--)
			{
				if (costomers[end].arr_time != end_person.arr_time)
					break;
			}
			// 사람이 아직 도착하지 않았다면 시간을 접수 하지 않습니다. 접수처가 비어있지 않으면 접수 X
			if (end_person.arr_time <= day && find_ai_empty_index() != -1)
			{
				// end전까지 사람은 동시에 들어온다.
				for (int p = costomers.size() - 1; p > end; p--)
				{
					Person now_p = costomers[p];
					// 접수하기
					int submit = find_ai_empty_index();
					if (submit == -1)
						break;

					now_p.timer = ai_time[submit];
					now_p.ai_num = submit;
					ai[submit].push_back(now_p);
					costomers.pop_back();
				}
			}
		}
		// 접수를 진행 시킨다. 
		for (int i_n = 1; i_n <= N; i_n++)
		{
			if (ai[i_n].size())
			{
				ai[i_n][0].timer--;
				if (ai[i_n][0].timer <= 0)
				{
					// 모든 접수 활동이 끝나면 waiting 한다.
					waiting.push_back(ai[i_n][0]);
					ai[i_n].pop_back();
				}
			}
		}
		// 수리하기 waiting 에 있는 사람을 처리한다.
		sort(waiting.begin(), waiting.end(), cmp);
		// 오늘 날짜를 가진 사람들의 수
		while (find_bj_empty_index() != -1 && !waiting.empty())
		{
			Person now_p = waiting[waiting.size() - 1];
			int submit = find_bj_empty_index();
			if (submit == -1)
				break;

			now_p.timer = bj_time[submit];
			now_p.bj_num = submit;
			bj[submit].push_back(now_p);
			waiting.pop_back();
			if (now_p.ai_num == A && now_p.bj_num == B)
				result += now_p.number;
		}
		// 수리를 한다.
		for (int i_m = 1; i_m <= M; i_m++)
		{
			if (bj[i_m].size())
			{
				bj[i_m][0].timer--;
				if (bj[i_m][0].timer <= 0)
					bj[i_m].pop_back();
			}
		}
	}
	return;
}

int main()
{
	int T;
	cin >> T;
	for (int i_t = 0; i_t < T; i_t++)
	{
		init();
		solution();
		// 출력
		if (result == 0)
			cout << "#" << i_t + 1 << " " << -1 << "\n";
		else
			cout << "#" << i_t + 1<< " " << result << "\n";
	}
	return 0;
}
