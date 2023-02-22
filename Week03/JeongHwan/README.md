# SWEA 2117. 홈 방범 서비스


[SWEA 2117 바로가기](https://swexpertacademy.com/main/code/problem/problemDetail.do?contestProbId=AV5V61LqAf8DFAWu&)

## 문제 요약
N * N 도시, 영역 크기 K, 운영비용 K*K+(k-1)*(k-1),
하나의 집이 이용할 수 있는 비용 M, 손해를 안보고 가장 많은 집에 서비스를 제공하는 영역을 찾고 서비스를 제공받는 집들의 수를 
구하라

## 주요 조건
* 50개 테스트케이스를 합쳐서 C의 경우 3초 / C++의 경우 3초 힙, 정적 메모리 합쳐서 256MB 이내, 스택 메모리 1MB 이내

## 접근
* 홈 방범 서비스의 영역이 flood-fill 알고리즘으로 체우는 방법과 같음
* 모든 영역에서 flood-fill 알고리즘으로 영역 크기를 늘려가며 집의 수와 비용을 계산하여 집의 수의 최댓값을 구함
* 얻을 수있는 최대 이익이 현재 영역의 비용보다 적다면 더이상 영역을 늘릴 필요가 없음(back-tracking)
* cost K당 비용을 미리 계산을 해놓아 계산을 줄임 (DAT)
## 전역변수
type|변수명|의미|
---|---|---|
int|N,M|맵의 너비, 집 1개당 지불 비용|
int[][]|map|맵|
int[]|cost|index의 영역으로 홈 방범 서비스를 하면 지불되는 비용|
int|num_house|맵에 존재하는 집의 수|
int|max_house|보안회사가 손해를 보지 않고 서비스를 제공할 수 있는 집들의 최댓값|


## 함수 프로토 타입
* void init(void) 맵에 존재하는 집의수와 보안회사가 보안회사가 손해를 보지 않고 서비스를 제공할 수 있는 집들의 최댓값을 초기화
* void ff(int y, int x) (y,x)를 시작점으로 flood-fill 알고리즘으로 탐색하면서 max_house를 갱신함
