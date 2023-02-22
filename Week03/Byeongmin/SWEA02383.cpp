#include <iostream>
#include <vector>

#define MAX_N 10

using namespace std;

struct Node{
    int y, x;
    int length;
};

int N;
int arr[MAX_N][MAX_N];
vector<Node> people;
vector<Node> stairs;

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        for(int i=0;i<N;i++) for(int j=0;j<N;j++) cin >> arr[i][j];

        cout << '#' << t << ' ' << '\n';
    }

    return 0;
}