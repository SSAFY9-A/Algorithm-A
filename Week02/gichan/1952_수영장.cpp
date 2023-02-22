// 2023-02-08
// 1일, 1달, 3달, 1년 이용권 가지고
// 사용자가 수영하려고 하는 날들을 고려해서
// 가장 적은 금액으로 이용할 수 있게
// 이용권 조합을 선택해라.

// [입력]
/*
	T ( 테스트 케이스 )
	1일요금, 1달요금, 3달요금, 1년요금 (4개 숫자)
	0 0 2 8 1 .... ( 각 달의 이용 일수 )

*/

// [출력]
/*
	#test_case 최소이용가능금액
*/

// [전략]
/*
	일단 다 입력받고
	dfs로 풀 것 (연습)
	1~12월 까지 요금제를 선택하는 방시긍로 => level이 달을 의미
	대신 3달, 1년치 선택하면 그만큼 level을 건너 뛰어야됨
	그리고 최솟값 구하는 문제니깐 현재 구하고 있는 가격이
	최솟값보다 커지면 그냥 리턴떄리고 나오기
*/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>

using namespace std;

int ticket_price[4] = { 0, }; // 1일, 1달, 3달, 1년 순서
int month_use[12] = { 0, };
int MIN_price = 21e8;
int cur_price = 0;

void recur(int level)
{
	if (level >= 12) {
		if (cur_price < MIN_price) {
			MIN_price = cur_price;
		}
		return; // 12월 까지 조사한 상태.
	}

	if (MIN_price <= cur_price) return; // 더 이상 볼 필요 없음.

	// level 월별로 어떤 이용권으로 이용할지
	
	// 만약 현재 달의 이용일 수가 0 이면 그냥 다음달로 넘어가
	if (month_use[level] == 0) {
		recur(level + 1);
	}
	else { // 이용일 수 있으면 계산 시작

		// 1일 * 이용일수
		cur_price += ticket_price[0] * month_use[level];
		recur(level + 1);
		cur_price -= ticket_price[0] * month_use[level];

		// 1달
		cur_price += ticket_price[1];
		recur(level + 1);
		cur_price -= ticket_price[1];

		// 3달
		cur_price += ticket_price[2];
		recur(level + 3);
		cur_price -= ticket_price[2];

		// 1년
		cur_price += ticket_price[3];
		recur(level + 12);
		cur_price -= ticket_price[3];
	}
}

void init()
{
	memset(ticket_price, 0, sizeof(ticket_price));
	memset(month_use, 0, sizeof(month_use));
	MIN_price = 21e8;
	cur_price = 0;
}

int main()
{
	int T;
	// 문제 인풋
	//freopen("input.txt", "r", stdin);
	cin >> T;
	for (int test_case = 1; test_case <= T; ++test_case) {
		// reset =============
		init();

		// input =============
		// 티켓 가격 입력
		for (int i = 0; i < 4; ++i) {
			cin >> ticket_price[i];
		}

		// 월별 이용수 입력
		for (int i = 0; i < 12; ++i) {
			cin >> month_use[i];
		}

		// solve ==================
		recur(0);

		// output =============
		cout << "#" << test_case << " "<< MIN_price << '\n';
	}
	return 0;
}
