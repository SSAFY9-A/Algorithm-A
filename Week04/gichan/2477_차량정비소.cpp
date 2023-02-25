// 2023-02-20
// 시작 : 22:55
// 끝 : 00:22
 
/*
[내용]
 
고객온다 -> 접수창구 -> 정비 창구 -> 고객 만족도
 
* 접수 창구 우선순위
-> 접수 창구 번호가 작은 곳부터 사람 채운다
-> 여러명의 고객이 기다리고 있으면 고객 번호가 낮은 고객 부터 빈 자리에 간다.
 
 
* 정비창구 우선순위
-> 먼저 기다리는 고객이 우선
-> 2명 이상이 접수창구에서 동시에 정비창구로 오면 접수창구번호가 낮은 놈이 우선
-> 빈 창구가 여러곳인 경우 정비 창구번호가 작은 곳으로 간다.
 
 
접수창구 -> 정비창구 이동시간은 고려하지 않음. 즉, 0.
우리는 고객 도착 시간, 접수, 정비처리시간만 본다.
 
"지갑을 분실한 고객과 같은 접수창구와 같은 정비 창구를 이용한
고객번호들을 찾아 그 합을 출력하는 프로그램 작성"
 
즉, 접수,정비 둘다 
 
그런 고객이 없으면 -1 출력
*/
 
// [입력]
/*
 
10          // T : 전체 테스트 케이스
1 1 2 1 1   // N,M,K,A,B
5           // ai
7           // bi
7 10        // tk1, tk2
*/
 
// [출력]
/*
    #1 3    // #tc 같은창구 고객 번호 합
*/
 
// [전략]
/*
    문제가 이해도 안된다;
    15분을 읽었따
 
    시간 t를 기준으로 
    그냥 전부 시뮬레이션을 돌리자
    천천히 하나씩
    길 잃으면 큰일나니깐 메모하면서해
*/
 
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
 
using namespace std;
 
/*
N : 접수창구개수
M : 정비창구개수
K : 고객 수
A : 지갑분실고객 접수창구 이용 번호
B : 지갑분실 고객 정비창구 이용 번호
*/
 
// 접수, 정비 창구의 요소로 활용될 클래스
 
class client {
public:
    int id;
    int arrival_time;
    bool same_reception;
    bool same_repair;
    client(int _id=0, int _at=0) {
        id = _id;
        arrival_time = _at;
        same_reception = false;
        same_repair = false;
    }
};
 
class booth {
public:
    int processing_time;
    int left_time;
    client c;
    booth(int _p, int _l = 0) {
        processing_time = _p;
        left_time = _l;
    }
};
 
 
int N, M, K, A, B;
 
vector<booth> reception_desk;
vector<booth> repair_desk;
vector<client> client_list;
vector<client> candidate_list;
 
queue<client> reception_desk_stand_by;
queue<client> repair_desk_stand_by;
 
int SUM = 0;
 
void simulate()
{
    int time = 0;
    int client_s_idx = 0;
    int complete_client_cnt = 0;
 
    // 시뮬레이션 부분
    while (1) {
        // 1. time 시간대에 처리가 끝난 고객들을 뒤로 보낸다
        // 접수 창구 -> 정비창구대기줄
        // 정비 창구 손님빼 -> 그냥 끝.
        // 정비창구 대기줄 -> 빈 정비창구에
        // 지금 시간대에 온 애들 reception_desk_stand_by 에 일단 다 넣어.
        // reception_desK_stand_by -> reception_desk에 빈자리로 가자
 
        //접수창구 -> 정비창구 대기줄로
        for (int i = 0; i < N; ++i) { // 접수창구 처리 시간 감소하고 0 인놈들은 빼.
            if (reception_desk[i].c.id != 0) { // 손님이 있는 창구다.
                // 그럼 남은 처리시간 감소
                reception_desk[i].left_time--;
                // 근데 남으 처리시간이 0이다? -> 그럼 정비창구 대기줄로 뺴
                if (reception_desk[i].left_time == 0) {
                    repair_desk_stand_by.push(reception_desk[i].c); // 대기줄로 뺴고
                    reception_desk[i].c = client(); // 고객이 없다고 표시해 주고.
                }
            }
        }
        //정비 창구 손님빼 -> 그냥 끝.
        for (int i = 0; i < M; ++i) {
            // 해당 창구에 손님이 있으면 시간 감소
            if (repair_desk[i].c.id != 0) {
                repair_desk[i].left_time--;
                // 감소하고 보니 0이다? -> 그럼 처리 완료
                if (repair_desk[i].left_time == 0) {
                    // 여기서 
                    //same_reception = true;
                    //same_repair = true;
                    // 이면 이 클라이언트 정보 벡터에 추가하자
                    if (repair_desk[i].c.same_reception == true && repair_desk[i].c.same_repair == true) {
                        candidate_list.push_back(repair_desk[i].c);
                    }
                    //cout << repair_desk[i].c.id << '\n';
                    repair_desk[i].c = client(); // 자리 비워 주자.
 
                    complete_client_cnt++; // 손님 처리 완료니까 여기에서 나간 손님 세어 주자.
                }
            }
        }
         
        // 여기서 나간손님이 전체 손님수와 같다면 break;
        //cout << complete_client_cnt << '\n';
        if (complete_client_cnt == K)
            break;
         
        // 정비창구 대기줄이 있다면 -> 빈 정비창구에 넣어
        int repair_idx = 0;
        while (!repair_desk_stand_by.empty() && repair_idx < M) { // 댇기줄이 없거나 빈자리가 없을때까지
            // 비어있다면
            if (repair_desk[repair_idx].c.id == 0) {
                // 이 자리에 바로 넣어
                client c = repair_desk_stand_by.front(); // 대기줄에서 뽑고
                repair_desk_stand_by.pop();
 
                // 지갑분실놈이랑 같은 자리냐?
                if (repair_idx == B) {
                    c.same_repair = true;
                }
 
                repair_desk[repair_idx].c = c; // 손님 넣고
                repair_desk[repair_idx].left_time = repair_desk[repair_idx].processing_time; // 남은 시간 업뎃하고
            }
            repair_idx++;
        }
 
        // 지금 시간대에 온 애들 reception_desk_stand_by 에 일단 다 넣어.
        for (int i = client_s_idx; i < K; ++i) {
            if (client_list[i].arrival_time == time) {
                reception_desk_stand_by.push(client_list[i]);
            }
            else {
                client_s_idx = i;
                break;
            }
        }
 
        // reception_desK_stand_by -> reception_desk에 빈자리로 가자
        int reception_idx = 0;
        while (!reception_desk_stand_by.empty() && reception_idx < N) {
            // 빈자리냐
            if (reception_desk[reception_idx].c.id == 0) {
                // 대기줄에 뽑고
                client c = reception_desk_stand_by.front();
                reception_desk_stand_by.pop();
                 
                // 지갑 분실놈이랑 같은 자리냐?
                if (reception_idx == A) {
                    c.same_reception = true;
                }
 
                // 손님 넣고
                reception_desk[reception_idx].c = c;
 
                // 시간 업데이트하고
                reception_desk[reception_idx].left_time = reception_desk[reception_idx].processing_time;
            }
            reception_idx++;
        }
 
        time++; // 시간 증가?
    }
 
    // 검증 완료
    for (int i = 0; i < candidate_list.size(); ++i) {
        SUM += candidate_list[i].id;
    }
}
 
void init()
{
    reception_desk.clear();
    repair_desk.clear();
    client_list.clear();
    candidate_list.clear();
 
    while (!reception_desk_stand_by.empty())
        reception_desk_stand_by.pop();
 
    while (!repair_desk_stand_by.empty())
        repair_desk_stand_by.pop();
 
    SUM = 0;
}
 
int main()
{
    int tc;
    int T;
    //freopen("input.txt", "r", stdin);
    cin >> T;
    //T = 1;
    for (tc = 1; tc <= T; ++tc) {
        // reset
        init();
 
        // input
        cin >> N >> M >> K >> A >> B;
        A--; B--; // 얘네는 인덱스화를 시키자
        // 접수창구 부스별 지연시간 받기
        for (int i = 0; i < N; ++i) {
            int t;
            cin >> t;
            reception_desk.push_back(booth(t));
        }
        // 정비창구 부스별 지연시간 받기
        for (int i = 0; i < M; ++i) {
            int t;
            cin >> t;
            repair_desk.push_back(booth(t));
        }
        // 손님 도착 시간 정보 받기
        for (int i = 0; i < K; ++i) {
            int t;
            cin >> t;
            //cout << "입력? : " << t << '\n';
            client_list.push_back(client(i+1, t)); // 손님 아이디는 1부터 시작
        }
 
        // solve
        simulate(); // 시뮬레이션 돌려
 
        // output
        if (SUM == 0)
            SUM = -1;
        cout << "#" << tc << " " << SUM << '\n';
 
    }
 
 
 
    return 0;
}
