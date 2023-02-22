//DFS
// level 각 월
//브랜치: 이용권 종류
// 이용권에 따라 계산된 월은 0일로

//백트랙킹
//가격이 이미 최소비용을 넘었으면 return
//0일이면 바로 넘어가

#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;
int prices[4]; // 1일, 1달, 3달, 1년
int Days[20]; // DAT index: month, value: days
int sum;
int Min;
void input() {
    for (int i = 0; i < 4; i++) {
        cin >> prices[i];
    }
    for (int i = 1; i < 13; i++) {
        cin >> Days[i];
    }
    sum = 0;
    Min = prices[3]; //1년가격을 초기화로 주고 브랜치에서 제외
}
void dfs(int month) {
    if (Min <= sum) {
        return;
    }
    if (month > 12) {
        if (Min > sum)
            Min = sum;
    }
    
    int next = month + 1;
    while (Days[next] == 0&&next<=12) {
        next += 1;
    }
    
    //1일
    sum += prices[0] * Days[month];
    dfs(next);
    sum -= prices[0] * Days[month];
    //한달
    sum += prices[1];
    dfs(next);
    sum -= prices[1];
    //세달
    sum += prices[2];
    if (next < month + 3) {
        next = month + 3;
    }
    dfs(next);
    sum -= prices[2];
}
int main() {
    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        input();
        dfs(1);
        cout << '#' << t + 1 << ' ' << Min << '\n';
    }
    return 0;
}

