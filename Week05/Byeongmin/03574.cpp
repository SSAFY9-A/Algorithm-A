#include <iostream>
#include <cstring>

#define MAX_N 10000

using namespace std;

int N;
int parent[MAX_N+1];
int depth[MAX_N+1];

void init() {
    for(int i=1;i<=N;i++) parent[i] = i;
    memset(depth, -1, sizeof(depth));
}

int Find(int a) {
    if(parent[a] == a) {
        depth[a] = 0;
        return a;
    } else {
        int pa = Find(parent[a]);
        depth[a] = depth[parent[a]] + 1;
        return pa;
    }
}

int LCA(int A, int B) { // Lowest Common Ancestor
    Find(A);
    Find(B);

    while(depth[A] != depth[B]) {
        // cout << "A: " << A << "\nB: " << B << '\n';
        // cout << "depth[A] " << depth[A] << "\ndepth[B] " << depth[B] << '\n';
        if(depth[A] > depth[B]) A = parent[A];
        else B = parent[B];
    }

    // cout << "Now, A: " << A << " B: " << B << '\n';

    while(A != B) {
        // cout << "A: " << A << "\nB: " << B << '\n';
        A = parent[A];
        B = parent[B];
    }

    return A;
}

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        cin >> N;

        init();

        int A, B;
        for(int i=1;i<N;i++) {
            cin >> A >> B;
            parent[B] = A;
        }

        cin >> A >> B;

        // Find(A);
        // Find(B);
        // for(int i=1;i<=N;i++) cout << i << '\t';
        // cout << '\n';
        // for(int i=1;i<=N;i++) cout << parent[i] << '\t';
        // cout << '\n';
        // for(int i=1;i<=N;i++) cout << depth[i] << '\t';

        cout << LCA(A, B) << '\n';
    }

    return 0;
}