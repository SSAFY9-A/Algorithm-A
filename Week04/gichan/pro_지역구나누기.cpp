// 2023-02-27
// 시작 : 23:13
// 끝 : 23:48

// [내용]
/*
	N개의 마을을 A,B 지역구로 나눌려고 한다

	각 마을은 각자의 유권자수가 있는데

	이것을 최소가 되도록 하게 하여 나눌려고 한다

	그리고 각 지역구는 서로 연결되어 있어야 한다.
*/

// [입력]
/*
2			//  T: 테스트케이스
4			//  N : 마을 수
0 0 1 0		// 인접행렬 연결 정보
0 0 1 0
1 1 0 1
0 0 1 0
6 7 4 8		// N개의 마을의 유권자 수
*/

// [출력]
/*
#1 9		// #tc A,B 지역 유권자수차이최소
*/

// [전략]
/*
	각 마을을 dfs로 2개로 나누고
	그걸 A,B로 표시하고
	bfs돌려서 각 지연구가 서로 연결되어있는지 확인하고

	bfs말고 유니온 파인드로도 될거 같기도 이거로 되면 유니온파인드로하자

	다 연결되어있으면
	유권자수 더해서 차이 -> 최소 값 업데이트

	----------------------
	실제로 구현한 방식
	1. dfs로 각 마을의 번호를 2개의 그룹으로 나눔
	2. 각 그룹별로 서로 전부 연결되어 있는지 검사 -> Union Find
	3. 연결되어 있다면 각 A,B 지역구의 유권자수의 차이를 구하고
	4. 최소차이값이라면 업데이트
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int N;
int ar[8][8] = { 0, };
int voters[8] = { 0, };

vector<int> A_list; // A 지역구 마을 번호
vector<int> B_list;	// B 지역구 마을 번호
int parent[8] = { 0, };
int MIN_diff = 21e8;


void init()
{
	A_list.clear(); // A 지역구 마을 번호
	B_list.clear();	// B 지역구 마을 번호
	MIN_diff = 21e8;
}

int Find(int now)
{
	if (now == parent[now])
		return now;

	return parent[now] = Find(parent[now]);
}

void Union(int P, int C)
{
	int pp = Find(P);
	int cp = Find(C);

	if (pp == cp)
		return;

	parent[cp] = pp;
}

bool isAllConnected(vector<int>& vil_list) {
	// parent 배열 초기화
	for (int i = 0; i < 8; ++i) {
		parent[i] = i;
	}

	// 마을을 전부 연결해 본다
	for (int i = 0; i < vil_list.size() - 1; ++i) {
		for (int j = 0; j < vil_list.size(); ++j) {
			int v1 = vil_list[i];
			int v2 = vil_list[j];

			// v1과 v2가 연결될 수 있다면 유니온 해준다 안되면? 말고
			if (ar[v1][v2] == 1) {
				Union(v1,v2);
			}
		}
	}

	// 서로 다 연결되었는지 확인
	bool flag = true;
	int P = Find(vil_list[0]); // 초기
	for (int i = 1; i < vil_list.size(); ++i) {
		if (P != Find(vil_list[i])) { // 연결 안되어있다 -> 불가능한 케이스
			flag = false;
			break;
		}
	}
	return flag;
}

int getVoters(vector<int>& vil_list)
{
	int sum = 0;// 각 마을의 유권자수를 누적해서 더할 변수
	for (int i = 0; i < vil_list.size(); ++i) {
		sum += voters[vil_list[i]];
	}
	return sum;
}

void recur(int level)
{
	if (level == N) {
		// 여기서 검사해야함.
		bool flag_A = isAllConnected(A_list);
		bool flag_B = isAllConnected(B_list);


		if (flag_A == true && flag_B == true) { 
			// 나눌수있다면 최소 차이 구하자
			// getVoters는 각 지역구의 유권자수를 더해서 넘겨줌.
			int A_voters = getVoters(A_list);
			int B_voters = getVoters(B_list);
			int cur_diff = abs(A_voters - B_voters);

			if (cur_diff < MIN_diff)
				MIN_diff = cur_diff; // 최솟값 업데이트.
		}




		return;
	}

	// [level 인덱스]의 마을이 A로 간다
	if (A_list.size() < N - 1) { // A,B 에 적어도 1개의 마을은 속하도록 만들기 위함이다.
		A_list.push_back(level);
		recur(level + 1);
		A_list.pop_back();
	}


	// [level 인덱스]의 마을이 B로 간다
	if (B_list.size() < N - 1) {
		B_list.push_back(level);
		recur(level + 1);
		B_list.pop_back();
	}
}

void solve()
{
	// 1. 일단 dfs로 마을을 A,B 지역구로 나눠

	recur(0);
}


void input()
{
	cin >> N; // 마을 수
	for (int i = 0; i < N; ++i) { // 인접행렬
		for (int j = 0; j < N; ++j) {
			cin >> ar[i][j];
		}
	}
	for (int i = 0; i < N; ++i) { // 유권자수
		cin >> voters[i];
	}
}

int main()
{
	int tc;
	int T;
	cin >> T;
	//T = 1;
	for (tc = 1; tc <= T; ++tc) {
		// reset
		init();

		// input
		input();
		// solve
		solve();

		// output
		cout << "#" << tc << " " << MIN_diff << '\n';
	}
	return 0;
}
