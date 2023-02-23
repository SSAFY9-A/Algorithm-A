/*
2383. [모의 SW 역량테스트] 점심 식사시간
https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5-BEE6AK0DFAVl&
*/

#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

#define MAX_N 10

using namespace std;

struct Person{
    int id;
    int y, x;
    int cost;

    bool operator < (Person p) const {
        return cost > p.cost;
    }
};

struct Stair{
    int y, x;
    int length;
};

int N;
int arr[MAX_N][MAX_N];
vector<Person> people;
vector<Stair> stairs;
int debug_cnt = 0;

void init() {
    memset(arr, 0, sizeof(arr));
    people.clear();
    stairs.clear();
}

int min(int a, int b) {
    return a<b?a:b;
}

int getDistance(Person p, Stair s) {
    int R = p.y - s.y;
    int C = p.x - s.x;
    if(R<0) R *= -1;
    if(C<0) C *= -1;
    return R+C;
}

int calcAnswer(priority_queue<Person> q0, priority_queue<Person> q1) {
    // cout << "[" << debug_cnt++ << "]\n";
    int answer = 0;

    int DAT0[100] = {0, };
    // cout << '(';
    while(!q0.empty()) {
        Person p0 = q0.top(); q0.pop();
        // cout << p0.id << ' ';
        while(DAT0[++p0.cost] >= 3) {}
        for(int i=0;i<stairs[0].length;i++) DAT0[p0.cost+i]++;
        if(answer < p0.cost+stairs[0].length) answer = p0.cost+stairs[0].length;
    }
    // cout << ")\n";

    // for(int i=0;i<10;i++) cout << i << ' ';
    // cout << '\n';
    // for(int i=0;i<10;i++) cout << DAT0[i] << ' ';
    // cout << '\n';


    // cout << '(';
    int DAT1[100] = {0, };
    while(!q1.empty()) {
        Person p1 = q1.top(); q1.pop();
        // cout << p1.id << ' ';
        while(DAT1[++p1.cost] >= 3) {}
        for(int i=0;i<stairs[1].length;i++) DAT1[p1.cost+i]++;
        if(answer < p1.cost+stairs[1].length) answer = p1.cost+stairs[1].length;
    }
    // cout << ")\n";
    // for(int i=0;i<10;i++) cout << DAT1[i] << ' ';
    // cout << '\n' << '\n';

    // cout << "answer: " << answer << "\n\n";

    return answer;
}

int dfs(int idx, priority_queue<Person> q0, priority_queue<Person> q1) {
    if(idx == people.size()) return calcAnswer(q0, q1);

    priority_queue<Person> new_q = q0;
    people[idx].cost = getDistance(people[idx], stairs[0]);
    new_q.push(people[idx]);
    int answer0 = dfs(idx+1, new_q, q1);

    new_q = q1;
    people[idx].cost = getDistance(people[idx], stairs[1]);
    new_q.push(people[idx]);
    int answer1 = dfs(idx+1, q0, new_q);

    return min(answer0, answer1);
}

int main() {
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        init();
        cin >> N;

        int id = 1;

        for(int i=0;i<N;i++) for(int j=0;j<N;j++) {
            cin >> arr[i][j];
            if(arr[i][j] == 1) people.push_back({id++, i, j, 0});
            if(arr[i][j] > 1) stairs.push_back({i, j, arr[i][j]});
        }

        priority_queue<Person> q0;
        priority_queue<Person> q1;

        // dfs(0, q0, q1);

        cout << '#' << t << ' ' << dfs(0, q0, q1) << '\n';
    }

    return 0;
}