#include <iostream>
#include <queue>

#define MAX_N 10
#define MAX_M 10
#define MAX_K 1001

using namespace std;

struct Counter{
    int id;
    int time;
    int duration;

    bool operator < (Counter c) const {
        if(time == c.time) return id > c.id;
        return time > c.time;
    }
};

struct Customer{
    int id;
    int time;
    int counterA_id;

    bool operator < (Customer c) const {
        if(time == c.time) return counterA_id > c.counterA_id;
        return time > c.time;
    }
};

int N, M, K, A, B;

int main() {
    int T;
    cin >> T;
    for(int t=1;t<=T;t++) {
        cin >> N >> M >> K >> A >> B;

        int DAT[MAX_K] = {0, };
        priority_queue<Counter> qa;
        priority_queue<Counter> qb;
        queue<Customer> qka;
        priority_queue<Customer> qkb;
        
        int tmp;
        for(int i=0;i<N;i++) {
            cin >> tmp;
            qa.push({i+1, 0, tmp});
        }
        for(int i=0;i<M;i++) {
            cin >> tmp;
            qb.push({i+1, 0, tmp});
        }
        for(int i=0;i<K;i++) {
            cin >> tmp;
            qka.push({i+1, tmp, 0});
        }

        int answer = 0;

        while(!qka.empty()) {
            Customer customer = qka.front();qka.pop();
            Counter counter = qa.top(); qa.pop();

            while(customer.time > counter.time) {
                counter.time = customer.time;
                qa.push(counter);
                counter = qa.top(); qa.pop();
            }
            // cout << "[" << customer.id << "] " << " --> [" << counter.id << "]\n";
            // cout << "Started at " << counter.time << '\n';
            counter.time += counter.duration;
            customer.time = counter.time;

            qa.push(counter);
            qkb.push({customer.id, customer.time, counter.id});

            // cout << "Finished at " << counter.time << "\n\n";
        }

        // cout << "\n-------------------------------------\n\n";

        while(!qkb.empty()) {
            Customer customer = qkb.top();qkb.pop();
            Counter counter = qb.top();qb.pop();

            while(customer.time > counter.time) {
                counter.time = customer.time;
                qb.push(counter);
                counter = qb.top(); qb.pop();
            }

            // cout << "[" << customer.id << "] " << " --> [" << counter.id << "]\n";
            // cout << "Started at " << customer.time << '\n';

            counter.time += counter.duration;

            qb.push(counter);

            if(customer.counterA_id == A && counter.id == B) answer += customer.id;
            // cout << "Finished at " << counter.time << "\n\n";
        }

        if(!answer) answer = -1;

        cout << "#" << t << " " << answer << '\n';
    }

    return 0;
}