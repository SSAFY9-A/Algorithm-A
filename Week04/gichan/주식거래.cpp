// 2023-02-24
// 시작 : 20:28
// 끝 : 21:32

// [내용]
/*
	과거 주식 데이터 가지고
	최대 수익 구해라

	매워 보유한 쥬식 전부 매도
*/

// [입력]
/*
2										// T : 전체 테스트케이스
300 60									// Ms : 초기 시드, Ma : 매월 추가금액
3 8										// N : 종목 수, L : 기간
135 120 111 144 170 170 171 173 169		
156 150 144 144 144 150 150 150 147
195 180 165 150 141 172 185 190 159
*/

// [출력]
/*

*/

// [전략]
/*

*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>

using namespace std;

// N : 종목수
// L : 기간
int N, L;
int Ms, Ma;  // Ms : 시드, Ma : 월별추가투자
vector<vector<int>> N_list; // 인덱스 : 종목 번호, 값 : 월별 가격
int total_money = 0; // 마지막 월까지 가지고 있을 총 돈.
vector<int> up_N_list; // 현재 월 -> 다음월 갈 떄, 시세가 오르는 종목 번호 리스트
vector<int> can_buy_list; // 각 월에서 살수 있는 주식들의 경우의 수를 저장하는 벡터.
vector<int> prev_buy_list; // 전달에 산 주식 정보

int MAX_profit = 0;
int result_profit = 0;

void input()
{
	cin >> Ms >> Ma;
	cin >> N >> L;
	N_list = vector<vector<int>>(N, vector<int>());
	can_buy_list = vector<int>(N,0);
	total_money = Ms;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j <= L; ++j) { // 0월 부터 L월 총 L+1월
			int price;
			cin >> price;
			N_list[i].push_back(price);
		}
	}
}



void recur(int level, int& max_level, int& buy_range, int& month)
{
	if (level == max_level) {
		// 지금 저장된 조합을 total money로 살 수 있니?
		// 그럼 지금 저장된 조합이 최대의 수익이니?
		// 그러면 지금 저장된 조합을 따로 저장.
		int my_money = total_money;
		int stock_sum = 0;
		int cur_profit = 0;
		for (int i = 0; i < can_buy_list.size(); ++i) {
			cur_profit += (N_list[i][month + 1] - N_list[i][month]) * can_buy_list[i];
			stock_sum += N_list[i][month] * can_buy_list[i];
			if (stock_sum > my_money) {
				return; //이 경우에는 안봐도 됨. -> 아예 불가능한 경우
			}
		}

		// 여기까지 오면 현재 조합ㅇ로 주식 사기 가능하다
		if (MAX_profit < cur_profit) {
			MAX_profit = cur_profit;
			prev_buy_list = can_buy_list;
		}
		return;
	}

	// up_N_list에 있는 값들이 종목 번호

	for (int j = 0; j <= buy_range; ++j) {
		can_buy_list[up_N_list[level]] = j;
		recur(level + 1, max_level, buy_range, month);
		//can_buy_list[up_N_list[level]] = 0;
	}
}


void simulate(int month, int ma)
{
	// 가지고 있는거 다 매도
	for (int i = 0; i < prev_buy_list.size(); ++i) {
		total_money += N_list[i][month] * prev_buy_list[i];
	}
	prev_buy_list.clear();


	total_money += ma; // 월별 추가 투가 금액



	if (month == L) {
		// 수익
		result_profit = total_money - (Ms + (Ma * L));
		//cout << total_money << '\n';
		return;
	}
	
	// 현재 월에서 다음달로 갈 떄,
	// 무조건 오르는 애들의 주식 번호만 따로 픽

	int can_buy_amount = 0; // 다음달에 오를 하나의 주식을 최대로 살 수 있는 갯수
	for (int i = 0; i < N; ++i) {
		if (N_list[i][month] < N_list[i][month + 1]) {
			up_N_list.push_back(i); // i가 종목 번호
			int cur_buy_amount = total_money / N_list[i][month];
			if (cur_buy_amount > can_buy_amount) {
				can_buy_amount = cur_buy_amount;
			}
		}
	}
	// up_N_list에는 다음달에 오를 종목 번호가 저장되어 있따.
	// up_N_list에 저장된 놈들을 0개부터 can_buy_amount까지 모든 조합으로 사보면서
	// 살수 있는 한 최대로 이익이 발생하는 조합을 저장.
	int max_level = up_N_list.size();
	recur(0, max_level, can_buy_amount, month);

	// 여기서 prev_buy_list에 산거 나와있음
	// index 종목 번호, 값 산 갯수
	for (int i = 0; i < prev_buy_list.size(); ++i) {
		total_money -= N_list[i][month] * prev_buy_list[i];
	}

	int de = 1;

	up_N_list.clear();
	can_buy_list = vector<int>(N, 0);
	MAX_profit = 0;

	simulate(month + 1, Ma);
}

void init()
{
	result_profit = 0;
	N_list.clear();
	total_money = 0;
	up_N_list.clear(); // 현재 월 -> 다음월 갈 떄, 시세가 오르는 종목 번호 리스트
	can_buy_list.clear(); // 각 월에서 살수 있는 주식들의 경우의 수를 저장하는 벡터.
	prev_buy_list.clear(); // 전달에 산 주식 정보
}

int main()
{
	int tc;
	int T;
	//reopen("input.txt", "r", stdin);
	cin >> T;
	//T = 1;
	for (tc = 1; tc <= T; ++tc) {
		// reset
		init();

		// input
		input();

		// solve
		simulate(0, 0);


		// output
		cout << "#" << tc << " " << result_profit << '\n';
	}

	return 0;
}
