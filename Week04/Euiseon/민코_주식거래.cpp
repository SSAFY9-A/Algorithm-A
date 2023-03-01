
//Ms 초기 시드액, Ma 매달 추가 금액
// 기간 L(8~15), 종목 수 N(3~15), 가격 (100~2000)

//해당 월에서 만들 수 있는 가장 많은 수익은?
// (잔고/가격) * 수익 -> 높은 순서대로? ... 남은 잔고는 어떻게 처리
// 두번째부터 다시 계산해서 sort N*N 해서 가장 높은 수익 고르기
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
int Ms, Ma; // 초기 시드, 월 추가금액
int N, L; // 종목 수, 투자 기간
struct Stock {
    int price;
    int p;
};
vector<Stock>v[15];
int Min[16]; //월별로 최저 가격
int Max;
int getMaxProfit(int m, int left, int sum) { // 월, 잔고, 총 수익
    if (left < Min[m - 1]) { //최저 가격보다 잔고가 없다면
        return sum;
    }

    for (int i = 0; i < N; i++) {
        //최대 수익은 시드/가격 * 수익
        if (left < v[i][m - 1].price) // 남은 잔고보다 비싸다면
            continue;
        if (v[i][m].p < 0) continue; //수익이 - 라면
        int profit = (left / v[i][m - 1].price) * v[i][m].p; //살 수 있는 개수 * 수익
        int ret = getMaxProfit(m, left % v[i][m - 1].price, sum + profit);
        if (Max < ret) Max = ret;
    }
    return Max;
}
int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        cin >> Ms >> Ma >> N >> L;
        
        for (int i = 0; i < N; i++) {
            for (int j = 0; j <= L; j++) {
                int price;
                cin >> price;
                int p = 0;
                if (j != 0) {
                    p = price - v[i][j - 1].price;
                }
                Stock s = { price,p };
                v[i].push_back(s);
            }
        }
        for (int m = 0; m <= L; m++) {
            Min[m] = 21e8;
            for (int i = 0; i < N; i++) {
                if (Min[m] > v[i][m].price) {
                    Min[m] = v[i][m].price; //각 월마다 최저값 저장
                }
            }
        }
        int ans = 0;
        for (int m = 1; m <= L; m++) {
            Max = 0;
            int ret = getMaxProfit(m, Ms, 0); // m개월에 최대수익
            //cout << m << "개월 수익" << ret << '\n';
            Ms += (ret + Ma);                 // 잔고 늘어남, 전달 최대수익+이번달 투자금
            ans += ret;
        }
        cout << '#'<<t+1<<' '<<ans<<'\n';
        for (int i = 0; i < N; i++) {
            v[i].clear();
        }
    }
}
