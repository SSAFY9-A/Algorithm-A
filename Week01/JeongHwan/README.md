# SWEA 1767.프로세서 연결하기


[SWEA 1767 바로가기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV4suNtaXFEDFAUf)

## 문제 요약
![1PNG](https://user-images.githubusercontent.com/99806622/217823257-a0bc65c9-404d-47fb-80bb-3fbcf349cac2.PNG)![2](https://user-images.githubusercontent.com/99806622/217823541-6b5c5204-099b-417a-9e90-c94eacff85b2.PNG)

멕시노스의 cell에는 core 혹은 전신이 올 수 있다. 최대한 많은 core에 전원을 연결하였을 경우, 전선의 길이의 합을 구하라(단, 여러 방법이 있을 경우, 전선 길이의 합이 최소가 되는 값을 구하라.)

## 주요 조건
* 50개 테스트케이스를 합쳐서 C++의 경우 2초, 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내
* 멕시노스의 가장자리에 위치한 Core는 이미 전원이 연결된 것으로 간주함.

## 접근
* 최대한 많은 Core에 연결해야 하므로 완전탐색으로 접근함
* 코어 하나당  연결x, 위쪽연결, 아래쪽연결, 왼쪽연결, 오른쪽연결 다섯가지의 경우가 존재함
* 시간 복잡도 5^12 = 244,140,625(c++ 기준 약 2.5초) 백트랙킹 필수임

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
