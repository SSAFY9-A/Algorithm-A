//미완
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<algorithm>
#include<stdio.h>
/*

[설계]
고객마다 도착시간이 다르고, 접수 창구마다 처리 시간이 다르다.
->  1분씩 진짜 시뮬레이션 할까.?
waiting에 있는 고객들이 있다. waiting은 두개를 만들어야 함.


사람의 수는 customer.size()로 구하면 됨.
 while로 돌리자.
 1.customer가 순서대로 들어오면 들어가야 할 곳을 찾자
 들어갈 곳이 A라면 A의 벡터를 넣음. B도 넣고, 공통인 사람 찾자.
 2.-> 만약 들어갈 곳이 없다? 기다림.continue. 시간++;
 3. 시간 플러스 하면서 현재 창구에 있는 사람의 시간 ++해줌.
   사람의 시간이 저장된 시간이 되는 순간 정비창구로 (1~3) 똑같이 반복.

*/
using namespace std;
struct node
{
    int cusNum;
    int arrive;
    int act;
    int checkA;
};
struct Line
{
    int cusNum;
    int Time;
};
vector<int>reception_time; //접수창구
vector<int>reception;
queue<int>reception_wait;

vector<int>repair_time;
vector<int>repair; //정비창구 사람확인
queue<int>repair_wait;

Line Alist[9]; //접수창구 확인
Line Blist[9]; //정비창구 확인

vector<node>customer;

int SUM;

bool cmp(node left, node right) { return left.arrive < right.arrive; }
int N, M, K, A, B;
int MaxArrive;

int FindReception()
{
    int cnt = 0;
    for (int a = 0; a < N; a++)
    {
        if (Alist[a].Time==0)
        {
            return a;
        }
        //크기 만큼 돌고, 만일 큐가 차있으면 기다리고, 아니면 ㄱㄱ    
    }
    return -1;
}
int FindRepair()
{
    int cnt = 0;
    for (int a = 0; a < N; a++)
    {
        if (Blist[a].Time == 0)
        {
            return a;
        } 
    }
    return -1;
}

void TimePlusA(int now)
{
    for (int i = 0; i < N; i++)
    {
        if (Alist[i].cusNum == i + 1)
        {
            Alist[i].Time++;
            if (Alist[i].Time == reception_time[i] + 1)
            {
                Alist[i].Time = 0;
                //접수가끝났으면 정비 wait로 
                customer[i].act = 2;
                repair_wait.push(i + 1);
            }
        }
    }
}
void TimePlusB(int now)
{
    for (int i = 0; i < N; i++)
    {
        if (Blist[i].cusNum == i + 1)
        {
            Blist[i].Time++;
            if (Blist[i].Time == repair_time[i] + 1)
            {
                Blist[i].Time = 0;
                //접수가끝났으면 정비 wait로 
                customer[i].act = 4;
            }
        }
    }
}

void run()
{
    int Time = customer[0].arrive; //첫 시간은 처음 도착한 사람부터 
    int sz = customer.size();

    while (1)
    {
        if (customer[sz - 1].act == 4) break;
        for (int i = 0; i < customer.size(); i++) // 1.customer가 순서대로 들어오면 들어가야 할 곳을 찾자
        {

            if (customer[i].act == 4) continue;
            //act=0 대기 act1은 접수 act2는 대기 act3 정비 act4완료 
            if (customer[i].act == 0)
            { //이제 막 도착이야?
                int pre = reception_wait.front();
                if (customer[i].arrive < Time) continue;
                
                int next = FindReception(); //들어가야하는 곳을 찾음
                if (next != -1 && pre == i + 1)
                {
                    //웨이트에 있는데 들어갈 수 있다!!
                    Alist[next].cusNum = i + 1;
                    Alist[next].Time = 1;
                    customer[i].act = 1;
                    customer[i].checkA = next+1;
                    reception_wait.pop();
                    if(next+1==A)
                    continue;
                }

                //만약 들어가야하는 곳이 없다면 wait으로   
                if (next == -1) {
                 
                    continue;
                }
               
            }
            else if (customer[i].act == 1)
            { //정비창구에 있어?
                TimePlusA(i);
            }
            else if (customer[i].act == 2)
            { //정비대기에 있음. 
                int pre = repair_wait.front();
      

                int next = FindRepair(); //들어가야하는 곳을 찾음
                if (next != -1 && pre == i + 1)
                {
                    //웨이트에 있는데 들어갈 수 있다!!
                    Blist[next].cusNum = i + 1;
                    Blist[next].Time = 1;
                    customer[i].act = 3;
                    if (customer[i].checkA == A && next + 1 == B) SUM += customer[i].cusNum;
                    repair_wait.pop();
                    continue;
                }

                //만약 들어가야하는 곳이 없다면 wait으로   
                if (next == -1) {
 
                    continue;
                }

            }
            else if (customer[i].act == 3)
            { //정비창구에 있어?
                TimePlusB(i);
            }
        }
        Time++;
    }


}
void init()
{
    MaxArrive = 0;
    SUM = 0;
    reception_time.clear(); 
    reception.clear();
    while(!reception_wait.empty())reception_wait.pop();

    repair_time.clear();;
    repair.clear(); //정비창구 사람확인
    while (!repair_wait.empty())repair_wait.pop();

    for (int i = 0; i < 9; i++)
    {
        Alist[i].Time = 0;
        Alist[i].cusNum = -1;
        Blist[i].Time = -0;
        Blist[i].cusNum = -1;
    }
    
   customer.clear();
}
int main()
{
    //freopen("input.txt", "r", stdin);
    int T;
    int input;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        
        init();
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
            customer.push_back({ i + 1,input,0,-1 });
            reception_wait.push(i + 1);
            MaxArrive = input;
        }
        run();
        cout <<"#"<<tc<<" "<< SUM<<"\n";
    }

}
