#include <iostream>
#include <cstring>

using namespace std;

int months[25];
int d1, m1, m3, y1;
int min_fee;

void init() {
    memset(months, 0, sizeof(months));
    min_fee = 2147483647;
}

void dfs(int month, int fee) {
    if(month > 12) {
        if(min_fee > fee) min_fee = fee;
    }

    if(fee > min_fee) return;

    dfs(month+1, fee+d1*months[month]);
    dfs(month+1, fee+m1);
    dfs(month+3, fee+m3);
    dfs(month+12, fee+y1);
}

int main() {
    int T;
    cin >> T;

    for(int t=1;t<=T;t++) {
        init();

        cin >> d1 >> m1 >> m3 >> y1;
        
        for(int i=1;i<=12;i++) cin >> months[i];

        dfs(1, 0);

        cout << min_fee << '\n';
    }

    return 0;
}