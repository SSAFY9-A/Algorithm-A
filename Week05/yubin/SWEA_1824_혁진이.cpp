#include<iostream>
#include<vector>
#include<cstring>
using namespace std;
int R, C;
vector<char>v[20];

int viaQ[20][20][4];
int checkloop[20][20][4][16];

int dy[4] = { -1,1,0,0 };//상하좌우
int dx[4] = { 0,0,-1,1 };

int Memory = 0;
int flag = 0;

void dfs(int cy, int cx, int d)
{
    if (flag == 2 )
        return;
    
    checkloop[cy][cx][d][Memory]++;
    //cout << cy << "," << cx << " d= " << d <<" flag="<<flag <<" memory= "<<Memory << '\n';
    if (checkloop[cy][cx][d][Memory] > 2)
    {
        flag = 1;
        return;
    }
    if (v[cy][cx] == '@') {
        flag = 2;
        return;
    }

    //cout << cy << "," << cy << " d= " << d << '\n';
    if (v[cy][cx] >= '0' && v[cy][cx] <= '9')
        Memory = v[cy][cx] - '0';
    else if (v[cy][cx] == '-')
    {
        if (Memory == 0)
            Memory = 15;
        else Memory--;
    }
    else if (v[cy][cx] == '+')
    {
        if (Memory == 15)
            Memory = 0;
        else Memory++;
    }
    else if (v[cy][cx] == '<') d = 2;
    else if (v[cy][cx] == '>') d = 3;
    else if (v[cy][cx] == '^') d = 0;
    else if (v[cy][cx] == 'v') d = 1;

    else if (v[cy][cx] == '_')
    {
        if (Memory == 0) d = 3;
        else d = 2;
    }
    else if (v[cy][cx] == '|')
    {
        if (Memory == 0) d = 1;
        else d = 0;
    }
    //?가 나오면 4방향 설정 해줘야함. ->visited로..?
    else if (v[cy][cx] == '?')
    {
        int saveX, saveY;
        //for문으로 dfs돌려야함. 
        for (int i = 0; i < 4; i++)
        {
            if (viaQ[cy][cx][i] == 1) continue;
            viaQ[cy][cx][i] = 1;
            d = i;
            saveX = cx;
            saveY = cy;
            saveX += dx[d];
            saveY += dy[d];
            if (saveX < 0 || saveX >= C)
                saveX = (saveX + C) % C;
            if (saveY < 0 || saveY >= R)
                saveY = (saveY + R) % R;

            dfs(saveY, saveX, d);
            
            
        }

    }
    if (v[cy][cx] != '?')
    {
        cy += dy[d];
        cx += dx[d];
        if (cx < 0 || cx >= C)
            cx = (cx + C) % C;
        if (cy < 0 || cy >= R)
            cy = (cy + R) % R;

        dfs(cy, cx, d);
    }
}
int isCheck()
{
    for (int i = 0; i < R; i++)
    {
        for (int j = 0; j < C; j++)
        {
            if (v[i][j] == '@')
                return 1;
        }
    }
    return 0;
}
int main()
{
    int T;
    char input;
    cin >> T;
    for (int tc = 1; tc <= T; tc++)
    {
        cin >> R >> C;
        Memory = 0;
        memset(viaQ, 0, sizeof(viaQ));
        memset(checkloop, 0, sizeof(checkloop));
        flag = 0;
        for (int i = 0; i < R; i++)
        {
            for (int j = 0; j < C; j++)
            {
                cin >> input;
                v[i].push_back(input);
            }
        }

        //일단 @이 있는지만 확인
        if(isCheck()==0)
            cout << "#" << tc << " NO\n";
        else {
            dfs(0, 0, 3);

            if (flag == 1)
                cout << "#" << tc << " NO\n";
            else
                cout << "#" << tc << " YES\n";
        }
        for (int i = 0; i < R; i++)
            v[i].clear();

    }
}
