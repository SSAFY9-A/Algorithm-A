//각 노드의 자식중에서 입력받은 두 노드를 포함하고 있으면 true를 출력한다 
//dfs 로 하기엔 노드수가 10000개임, BU DP로 자식 -> 부모 방향으로 가면서 DAT index: 부모, value 입력 노드로 저장한다
//두 번째 노드에서 마찬가지로 진행할때 visited 된 첫 부모가 가장 가까운 공통 조상이다.
#include <iostream>
#include <cstring>

using namespace std;
int N;
int parent[10001]; //index : 자식 , value : 부모
int DAT[10001]; //index: 부모, value: 찾는 자식의 부모여부
int ans;
void Find(int now){   
    if(DAT[now]==1){
        ans=now;
        return;
    }
    DAT[now]=1;
    if(parent[now]==0)
        return;
    Find(parent[now]);
}
int main(){
    int T;
    cin>>T;
    for(int t=0;t<T;t++){
        cin>>N;
        ans=0;
        for(int i=0;i<N-1;i++){
            int a,b;
            cin>>a>>b; //a가 b의 부모
            parent[b]=a;
        }
        int target1,target2;
        cin>>target1>>target2;
        Find(target1);
        Find(target2);
        cout<<ans<<'\n';
        memset(parent,0,sizeof(parent));
        memset(DAT,0,sizeof(DAT));
    }

    return 0;
}