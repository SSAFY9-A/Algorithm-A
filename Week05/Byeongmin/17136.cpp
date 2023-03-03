#include <iostream>

#define SIZE 10

using namespace std;

int papers[6] = {0, 5, 5, 5, 5, 5};
bool arr[SIZE][SIZE];
int answer = 25;
int total;

bool check(int y, int x, int size) {
    for(int i=0;i<size;i++) for(int j=0;j<size;j++) {
        if(!arr[y+i][x+j]) return false;
    }
    return true;
}

void fill(int y, int x, int size, bool type) {
    for(int i=0;i<size;i++) for(int j=0;j<size;j++) {
        arr[y+i][x+j] = type;
    }
}

void dfs(int y, int x) {
    if(y == SIZE-1 && x == SIZE-1) return;

    
}

int main() {
    for(int i=0;i<SIZE;i++)for(int j=0;j<SIZE;j++) {
        cin >> arr[i][j];
        if(arr[i][j]) total++;
    }

    dfs(0, 0);

    if(answer <= 25) cout << answer;
    else cout << -1;

    return 0;
}