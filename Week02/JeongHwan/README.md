# SWEA 1952.수영장


[SWEA 1952 바로가기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PpFQaAQMDFAUq)

## 문제 요약
수영장의 이용권 4종류가 있다. 각 달의 계획을 입력받아 가장 적은 비용으로 수영장을 이용하는 방법을 찾고 그 비용을 출력하라

## 주요 조건
* 50개 테스트케이스를 합쳐서 C의 경우 3초 / C++의 경우 3초 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내

## 접근
![g](https://user-images.githubusercontent.com/99806622/217833890-67722c8e-69a1-4ee9-afc8-3b71060b1267.jpg)
* 이용 계획은 1월 부터 12월까지이므로 수가 적음 따라서 완전 탐색으로 접근함.
* 월당 1일 이용권, 1달 이용권, 3달 이용권, 1년 이용권 총 4가지 경우가 있음.
* 어떤 이용권을 사용하냐에 따라 다음달을 스킵할 수 있음

## 전역변수
type|변수명|의미|
---|---|---|
int|N|멕시노스의 너비|
int[][]|map|멕시노스 이차원배열|
int|min_length|전선길이의 최솟값|
int|acc_length|전선길이의 누적값|
int|max_core|연결된 코어수 최댓값|
int|acc_core|연결된 코어수 누적값|
struct node[]|cord_core|코어의 좌표를 저장하는 구조체 배열|
int|len_core_arr|코어의 좌표 개수(cord_core의 인덱스 범위다|

## 함수 프로토 타입
* int isValid(node n, int dir) 코어의 좌표 n과 연결할 방향 dir을 입력받아 전선을 연결할 수 있으면 1을 없으면 0을 리턴함.
* int connect(node n, int dir) 코어의 좌표 n과 연결할 방향 dir을 입력받아 전선을 연결하고(map변수를 수정하고) 연결한 전선 수를 리턴함.
* void dfs(int level) 코어의 index(0)을 코어를 연결가능한 모든 경우의 수를 완전탐색하는 함수. 

## 기억해야할 점
* 최대값을 구하는 문제에서 완전탐색을 할 경우 재귀호출 마다 그 상황에서 가질 수 있는 최대값이 이미 구해진 최댓값보다 작다면 더이상 재귀호출하지 말고 리턴하면 경우의수를 많이 줄일 수 있다.


# SWEA 1949.등산로 조성


[SWEA 1949 바로가기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5PoOKKAPIDFAUq)

## 문제 요약
등산로를 만드려고 한다. 가장 높이가 높은곳에서 시작한다. 등산로는 높은 지형에서 낮은지형으로 가로 세로 방향으로만 연결된다. 가장 긴 등산로의 길이를 출력해라\

## 주요 조건
* 51개 테스트케이스를 합쳐서 C++의 경우 3초, 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내
* 긴 등산로를 만들기 위해 딱 한 곳을 정해서 최대 K 깊이만큼 지형을 깎는 공사를 할 수 있다.
* 최대 공사 가능 깊이 K는 1 이상 5 이하의 정수이다.
* 필요한 경우 지형을 깎아 높이를 1보다 작게 만드는 것도 가능하다.

## 접근
![g (1)](https://user-images.githubusercontent.com/99806622/217843218-d55c5567-33e0-4cc5-a693-3a6ca422640c.jpg)
* 가장 긴 등산로를 만들어야 하므로 최댓값을 구하는 완전탐색으로 접근
* 상하좌우 * 땅파기 안파기 8가지 경우가 존재함.
* 시간복잡도 8^64

## 전역변수
type|변수명|의미|
---|---|---|
int|N|지도 너비|
int|K|최대 공사 가능 깊이|
int[][]|map|등산지도 이차원 배열|
int[][]|initial_max|높이가 가장 높은 곳의 좌표|
int|initial_MAX| 높이가 가장 높은곳의 높이|
int|initial_len|initial_max의 길이|
int[][]|visited|방문좌표를 체크하기 위한 이차원 배열|
int[][]|direct|상하좌우 방향좌 이차원배열|
int|dig_flag|땅을 팠는지 기록하는 flag|
int|MAX|등산로 길이 최댓값|
int|length|등산로 길이|

## 함수 프로토 타입
void dfs(int y, int x) 시작 좌표 y와 x를 입력받아 모든 경우의 수를 탐색하여 등산로의 최대 길이를 구하는 함수

## 기억해야할 점
* 변수들이 어느 시점에서 리셋되어야 하는지를 분명히 알고 있어야 함.
* 숨겨진 조건을 찾아야 함(높이를 깎을려면 현재 높이에서 1작은 높이로 깍아야 최대값을 찾을 수 있음)
