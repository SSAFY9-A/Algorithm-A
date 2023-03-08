// 2023-03-08


// [내용]
/*
	공통조상
	두 노드의 가장 가까운 공통 조상을 찾아라
*/

// [입력]
/*
1		// T : 테스트 케이스
16		// N : 노드 수
1 14	// N-1 개의 간선 정보 먼저 나온 수가 부모, 그 다음이 자식
8 5
10 16
5 9
4 6
8 4
4 10
1 13
6 15
10 11
6 7
10 2
16 3
8 1
16 12
16 7	// 가장 가까운 부모 노드를 구하 노드 2개
*/

// [출력]
/*
4	: 가장 가까운 부모노드 번호
*/

// [전략]
/*
	Union Find 쓰면 될듯
	대신 Find에서 parent 배열 업데이트할 때,
	다른 거 업데이트 하지말고 그냥 자기 부모만 가리키도록 설정
*/

#include <iostream>
#include <vector>

using namespace std;

int N;
int parent[10001] = { 0, };
int node_1, node_2;
int closest_parent = 0;
void init()
{
	for (int i = 0; i < 10001; ++i) {
		parent[i] = i;
	}
	closest_parent = 0;
}

void input()
{
	cin >> N;
	for (int i = 0; i < N-1; ++i) {
		int P, C;
		cin >> P >> C;
		parent[C] = P; // 부모 바꿔주기
	}

	cin >> node_1 >> node_2; // 공통 부모 찾을 노드 2개.
}

void findParentList(int node, vector<int>& node_1_parent_list)
{
	int idx = node;
	while (idx != parent[idx]) {
		// 내 부모
		int P = parent[idx];
		node_1_parent_list.push_back(P); // 부모 추가하고
		idx = parent[idx]; // 위로 올라가자
	}
}

bool isSameParent(int p, vector<int>& node_1_parent_list)
{
	for (int i = 0; i < node_1_parent_list.size(); ++i) {
		if (node_1_parent_list[i] == p)
			return true;
	}
	return false;
}

int findClosestParent(int node , vector<int>& node_1_parent_list)
{
	int idx = node;
	while (idx != parent[idx]) {

		int P = parent[idx];

		if (isSameParent(P, node_1_parent_list)) {
			return P;
		}
		idx = parent[idx];
	}
	return parent[idx];
}

void solve()
{
	// 노드 1의 부모 노드 리스트가 들어가 벡터
	vector<int> node_1_parent_list;
	//vector<int> node_2_parent_list;
	node_1_parent_list.push_back(node_1);
	// 각 노드의 부모 노드를 전부 찾아 준다.
	findParentList(node_1, node_1_parent_list);
	
	closest_parent = findClosestParent(node_2, node_1_parent_list);

}

int main()
{
	int tc;
	int T;
	cin >> T;
	for (tc = 1; tc <= T; ++tc) {
		// reset
		init();

		// input
		input();

		// solve
		solve();

		// output
		cout << closest_parent << '\n';
	}
	return 0;
}
