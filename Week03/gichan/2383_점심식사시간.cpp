// 2023-02-18
// 시작 : 15:29
// 끝 : 16:54

// [내용]

/*
	방 NxN 에 대한 정보 주어짐
	사람위치는 P, 계단 입구는 S

	최대한 빠르 시간 내로 사람들ㄹ이
	다 계단을 통해 내려가는 시간 구해야함

	최단 시간 = 이동시간 + 내려가는 시간
	
	이동시간 : |사람y-계단y| + |사람x - 계단x|
	
	내려가는 시간 : 
	-> 계단 도착후 1분.
	-> 그다음 계단 K길이만큼 소요
	-> 한번에 계단 이용 가능한 사람 3명
	-> 나머지는 그 앞에서 기다려야함.
*/


// [입력]
/*
	10			// T: 테스트 케이스
	5			// N :맵 크기
	0 1 1 0 0	// NxN 맵 정보
	0 0 1 0 3	// 1 -> 사람, 2 이상 -> 계단 입구, K 길이를 의미
	0 1 0 1 0
	0 0 0 0 0
	1 0 5 0 0
*/

// [출력]
/*
	#1 9	// #tc 최소시간	
*/

// [전략]
/*
	모든 사람이 계단 1 또는 계단 2로 내려가는
	모든 경우의 수를 봐야함
	-> DFS 해

	최대 레벨을사람의 수로

	가지는 2개 -> 계단 1, 계단 2,

	가지치기는 아직 생각 안난다
	근데 사람의 수가 10명이라 사실 크게 문제 없을듯

	시간 계선을 어케하지... 어렵다

	1. 일단 이동시간이 짧은 순으로 계단1, 계단 2 입구도착 사람 벡터 만들어
	2. 그다음에 시간 1분씩 증가시키면서 판단하자


	3. 판단 순서
		-> k분에 계단1,계단2 도착사람 있음?
		-> 그 사람들은 대기 벡터에 넣어놓고
		-> 그 다음분에 대기 벡터에 있는 놈들 다 한명씩 계단 내려가기 벡터에 넣고
		-> 만약 계단 내려가기 벡터가 3명으면 계단 벡터에 3명 미만이 될 떄 넣고
		-> 이걸 반복해서
		-> 계단 도착 사람 벡터, 대기 벡터, 계단 내려가기 벡터다 다 비게 되면 종료.
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>

using namespace std;

int N; // 맵 크기

class node {
public:
	int y;
	int x;
	int length;
	int arrive_time;
	node(int _y=0, int _x=0, int _l=0) {
		y = _y;
		x = _x;
		length = _l;
		arrive_time = 0;
	}
};

int number_of_person;
vector<node> person_list;
vector<node> stair_list;

// 계단 입구 선택 경우의 수 리스트
vector<node> s1_person_list;
vector<node> s2_person_list;

int MIN_delay_time = 21e8;


// 각 계단에 도착한 사람들의 리스트를 만들어주는 함수
void makeStairGateArrivalList(vector<node>& s_person_list, node& stair, vector<node>& s_gate_list)
{
	for (int i = 0; i < s_person_list.size(); ++i) { // 계단 1
		node person = s_person_list[i]; // 이놈을 계단 입구 대기열에 푸시할거임.
		int y_diff = s_person_list[i].y - stair.y;
		int x_diff = s_person_list[i].x - stair.x;
		int arrival_time = abs(y_diff) + abs(x_diff); // 절대값으로
		person.arrive_time = arrival_time;
		s_gate_list.push_back(person);
	}

	// arrival_time이 작은 순으로
	sort(s_gate_list.begin(), s_gate_list.end(), [](node a, node b) {
		return a.arrive_time < b.arrive_time;
		});
}

int makeGetOut(vector<int>& go_through_list)
{
	//cout << go_through_list.size() << '\n';
	for (int i = 0; i < go_through_list.size(); ++i) {
		go_through_list[i]--;
	}

	// 통과한놈들 전부 지우기
	int get_out_person_cnt = 0;
	while (1) {
		bool break_flag = true;
		for (int i = 0; i < go_through_list.size(); ++i) {
			if (go_through_list[i] == 0) { // 나간놈 발견
				go_through_list.erase(go_through_list.begin() + i);
				break_flag = false;
				get_out_person_cnt++;
				break;
			}
		}

		if (break_flag) // 더이상 나갈놈이 없다는 뜻
			break;
	}
	return get_out_person_cnt;
}

void makeGetIn(vector<int>& go_through_list, queue<int>& suspend_list, int length)
{
	// 안비어있는한 계단으로 보낼거다
	while (!suspend_list.empty()) {
		// 계단에 3명 이상 있으면 더 못보낸다.
		if (go_through_list.size() >= 3)
			break;

		// 계단에 3명 미만으로 있으면 이제 내려보내라.
		go_through_list.push_back(length); 
		suspend_list.pop();
	}
}

void checkArrivalPerson(vector<node>& s_gate_list, queue<int>& s_suspend_list, int delay_time)
{
	// s_gate의 arrivaltime이 delay_time과 같은 놈들을 s_suspend에 풋한다.
	// 같은 놈들으 지우면서 푸시할수 있겠지만 일단 복잡하니 지우지느 ㄴ않늗나.
	for (int i = 0; i < s_gate_list.size(); ++i) {
		if (s_gate_list[i].arrive_time == delay_time)
			s_suspend_list.push(1);
	}

}

void computeDelayTime(int number_of_person)
{
	// 계단 입구에 도착해서 도착 시간이 빠르순으로 정렬할 리스트
	vector<node> s1_gate_list;
	vector<node> s2_gate_list;

	// 계단도착해서 1분간 기다리는 리스트
	queue<int> s1_suspend_list;
	queue<int> s2_suspend_list;

	// 계단 통과중인 리스트 -> 값은 통과까지 남은 시간.
	vector<int> s1_go_through_list;
	vector<int> s2_go_through_list;

	// 1. 각 계단에 도착한 사람들을 도착시간이 빠른순으로 정렬해서 gate list에 저장
	makeStairGateArrivalList(s1_person_list, stair_list[0], s1_gate_list);
	makeStairGateArrivalList(s2_person_list, stair_list[1], s2_gate_list);

	// 시뮬레이션 시작
	int delay_time = 0; // 경과 시간
	int get_out_person_cnt = 0;
	while (1) {
		
		delay_time++; // 1분 경과
		if (MIN_delay_time <= delay_time)
			return;
		//cout << delay_time << '\n';
		// goThrough에 있는 놈들 시간 1씩 감소하고
		// 남은 시간이 0인 놈들을 지운다.
		get_out_person_cnt += makeGetOut(s1_go_through_list);
		get_out_person_cnt += makeGetOut(s2_go_through_list);

		// 여기서 전체 사람수와 나간놈들의 수가 같으면 종료조건 넣자
		//cout << number_of_person << ", " << get_out_person_cnt << '\n';
		if (number_of_person == get_out_person_cnt)
			break;

		// 1분 대기 리스트에 있는 사람들 전부 goThroughlist에 보내
		// 근데 goThroughlist크기가 3이면 못보내
		makeGetIn(s1_go_through_list, s1_suspend_list, stair_list[0].length);
		makeGetIn(s2_go_through_list, s2_suspend_list, stair_list[1].length);

		// 각 계단 입구에 도착한 사람 있으면 1분 대기 리스트에 1푸시하고
		checkArrivalPerson(s1_gate_list, s1_suspend_list, delay_time);
		checkArrivalPerson(s2_gate_list, s2_suspend_list, delay_time);
		//cout << s1_suspend_list.size() << '\n';
	}

	// 여기서 시간 비교
	if (MIN_delay_time > delay_time)
		MIN_delay_time = delay_time;
}

void recur(int level)
{
	if (level == number_of_person) {
		// 여기서 시뮬레이션 돌려서 최솟값 찾아야함.
		computeDelayTime(number_of_person); //  -> 여기서 백트래킹 해야될듯
		return;
	}

	// 계단 1 선택
	s1_person_list.push_back(person_list[level]);
	recur(level + 1);
	s1_person_list.pop_back();


	// 계단 2 선택
	s2_person_list.push_back(person_list[level]);
	recur(level + 1);
	s2_person_list.pop_back();
}

void init()
{
	person_list.clear();
	stair_list.clear();

	// 계단 입구 선택 경우의 수 리스트
	s1_person_list.clear();
	s2_person_list.clear();
	MIN_delay_time = 21e8;
}
int main()
{
	int tc;
	int T;
	//freopen("input.txt", "r", stdin);
	cin >> T;
	for (tc = 1; tc <= T; ++tc) {
		// reset
		init();

		// input
		cin >> N; // 맵 크기
		for (int i = 0; i < N; ++i) {	// 맵 정보 
			for (int j = 0; j < N; ++j) {
				int n;
				cin >> n; // 1이면 사람, 2이상 계단.
				if (n == 1) // 사람이다
					person_list.push_back(node(i,j)); // 사람추가
				else if (n >= 2) {
					stair_list.push_back(node(i,j,n)); // 계단 추가
				}
			}
		}

		// solve
		number_of_person = person_list.size(); // 이 값이 dfs의 탈출조건이 될 것임.
		recur(0);

		// output
		cout << "#" << tc << " " << MIN_delay_time << '\n';
	}
	return 0;
}
