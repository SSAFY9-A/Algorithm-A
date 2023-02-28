#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<stdio.h>
/*
[문제]
    접수 창구의 우선순위
    -여러 고객이 기다리고 있는 경우 고객번호가 낮은 순서대로 우선 접수한다.
    -빈 창구가 여러 곳인 경우 접수 창구번호가 작은 곳으로 간다.


    정비 창구의 우선순위
    - 먼저 기다리는 고객이 우선한다.
    - 두 명 이상의 고객들이 접수 창구에서 동시에 접수를 완료하고 정비 창구로 이동한 경우, 이용했던 접수 창구번호가 작은 고객이 우선한다.
    - 빈 창구가 여러 곳인 경우 정비 창구번호가 작은 곳으로 간다.

    고객의 도착 시간 tk, 접수 창구의 처리 시간 ai, 정비 창구의 처리 시간 bj가 주어졌을 때,
    지갑을 분실한 고객과 같은 접수 창구와 같은 정비 창구를 이용한 고객의 고객번호들을 찾아
    그 합을 출력하는 프로그램을 작성하라.

    만약, 그런 고객이 없는 경우 -1을 출력한다.

[설계]
고객마다 도착시간이 다르고, 접수 창구마다 처리 시간이 다르다.
->  1분씩 진짜 시뮬레이션 할까.?
waiting에 있는 고객들이 있다. waiting은 두개를 만들어야 함.


//사람의 수는 customer.size()로 구하면 됨.
    //while로 돌리자.
    //1.customer가 순서대로 들어오면 들어가야 할 곳을 찾자
    //   들어갈 곳이 A라면 A의 벡터를 넣음. B도 넣고, 공통인 사람 찾자.
    //2.-> 만약 들어갈 곳이 없다? 기다림.continue. 시간++;
    //3. 시간 플러스 하면서 현재 창구에 있는 사람의 시간 --해줌.
    //사람의 시간이 0이 되는 순간 정비창구로 (1~3) 똑같이 반복.

*/
using namespace std;
struct node
{
    int cusNum;
    int arrive;
    int act;
};
struct Line
{
    int cusNum;
    int Time;
};
vector<int>reception_time; //접수창구
vector<int>reception;
vector<int>reception_wait;

vector<int>repair_time;
vector<int>repair; //정비창구 사람확인
vector<int>repair_wait;

Line Alist[9]; //접수창구 확인
Line Blist[9]; //정비창구 확인

vector<node>customer;
bool cmp(node left, node right) { return left.arrive < right.arrive; }
int N, M, K, A, B;
int MaxArrive;

int FindReception()
{
    int cnt = 0;
    for (int a = 0; a < N; a++)
    {
        if (Alist[a].Time==0||Alist[a].Time == reception_time[a])
        {
            Alist[a].Time = 0;
            return a;
        }
        //크기 만큼 돌고, 만일 큐가 차있으면 기다리고, 아니면 ㄱㄱ    
    }
    return -1;
}


void run()
{
    int Time = customer[0].arrive; //첫 시간은 처음 도착한 사람부터 


    while (1)
    {
        for (int i = 0; i < customer.size(); i++) // 1.customer가 순서대로 들어오면 들어가야 할 곳을 찾자
        {
            //1.이미 뭐 하고 있어?
            //2. 이제 막 도착이야?
            //waiting에 있으면 나오자. 
            //이미 Alist안에 있어?? 시간 증가 해야함. 
            if (customer[i].arrive < Time) continue;
            int next = FindRepair();
            if (next == -1 && customer[i].act == 0)
            {
                customer[i].act = 1;
                Alist[next].cusNum = i + 1;
                Alist[next].Time++;
            }
            else if (next == -1 && customer[i].act == 1) reception_wait.push_back(i + 1);

            if (next == A - 1)reception.push_back(i + 1);
            //대기하자

            //   들어갈 곳이 A라면 A의 벡터를 넣음. B도 넣고, 공통인 사람 찾자.
            //2.-> 만약 들어갈 곳이 없다? 기다림.continue. 시간++;
            //3. 시간 플러스 하면서 현재 창구에 있는 사람의 시간 --해줌.
            //사람의 시간이 0이 되는 순간 정비창구로 (1~3) 똑같이 반복.
        }
        Time++;
    }


}

int main()
{
    freopen("input.txt", "r", stdin);
    int T;
    int input;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        MaxArrive = 0;
        cin >> N >> M >> K >> A >> B;
        for (int i = 0; i < N; i++)
        {
            cin >> input;
            reception_time.push_back(input);
        }
        for (int i = 0; i < M; i++)
        {
            cin >> input;
            repair_time.push_back(input);
        }
        for (int i = 0; i < K; i++)
        {
            cin >> input;
            //순서대로 들어와서 정렬 안해도됨. 
            customer.push_back({ i + 1,input,0 });
            MaxArrive = input;
        }
        run();
    }

}
