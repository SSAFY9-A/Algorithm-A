#define SZ 10
#include <iostream>
#include <vector>

using namespace std;

class node {
public:
    int y;
    int x;
    node(int _y, int _x) {
        y = _y;
        x = _x;
    }
};

vector<vector<int>> map;
vector<int> papers_cnt;
int MIN_paper_cnt = 21e8;
int using_paper = 0;

void input()
{
    papers_cnt = vector<int>(5, 5);
    map = vector<vector<int>>(SZ, vector<int>(SZ, 0));
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            cin >> map[i][j];
        }
    }
}

bool canPutPaper(node start, int n)
{
    int cnt = 0;
    bool break_flag = false;
    for (int i = start.y; i <= start.y + n; ++i) {

        for (int j = start.x; j <= start.x + n; ++j) {

            // 범위 내인가
            if (i >= 0 && i < SZ && j >= 0 && j < SZ) {
                if (map[i][j] == 1) {
                    map[i][j] = 0; // 0으로 붙히는거
                    cnt++;
                }
                else if (map[i][j] == 0)
                    return false;
                else {
                    break_flag = true;
                    break;
                }
            }
            else {
                return false;
            }



        }
        if (break_flag)
            break;
    }

    if (cnt == (n + 1) * (n + 1))
        return true;
    else
        return false;
}

bool checkCover()
{
    for (int i = 0; i < SZ; ++i) {
        for (int j = 0; j < SZ; ++j) {
            if (map[i][j] == 1) {
                return false;
            }
        }
    }
    return true;
}

int getUsedPaperNum()
{
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += 5 - papers_cnt[i];
    }
    return sum;
}

void recur(node start)
{
    if (using_paper > MIN_paper_cnt) {
        //cout << "이거아냐?";
        //cout << MIN_paper_cnt;
        return;
    }

    // 만약 모든 칸이 덮혔으면 사용한 색종이수 업데이트
    if (checkCover()) {
        if (MIN_paper_cnt > using_paper) {
            MIN_paper_cnt = using_paper;
        }
        return;
    }

    int j = start.x + 1;
    for (int i = start.y; i < SZ; ++i) {
        while (j < SZ) {
            if (map[i][j] == 1) {
                // 여기부터 재귀 시작
                vector<vector<int>> map_copy = map;
                for (int s = 4; s >= 0; --s) {

                    if (canPutPaper(node(i, j), s)) { // 가능하면 그걸로 재귀 시작해봐
                        // 가능하다?
                        // 근데 종이가 남아있니?
                        if (papers_cnt[s] > 0) {
                            int de = 1;
                            papers_cnt[s]--;
                            using_paper++;

                            recur(node(i, j + s));

                            using_paper--;
                            papers_cnt[s]++; // 복구
                            map = map_copy; // 맵 복구
                        }
                    }
                    else {
                        map = map_copy; // 맵 복구
                        //break;
                    }
                }

                // 이게 존나 중요한
                // 잘 생각해야되는게 모든 "시작"위치에서 부르트 포스처럼 재귀함수를 돌릴필요없이 그냥
                // 처음 만나는 1에서만 돌리면됨. 그니깐 위 반복문이 끝나면 그냥 답이 나온거임. ㅇㅋ?
                return;

            }

            j++;
        }
        j = 0;
    }
}

int main()
{
    // input
    input();

    // solve
    recur(node(0, -1));

    // output
    if (MIN_paper_cnt == 21e8) {
        cout << -1;
    }
    else {
        cout << MIN_paper_cnt;
    }

    return 0;
}
