// *** user.cpp ***

/*==== Union Find code ====*/
const int LM = 20003;
int PARENT[LM];

int Find(int x) {
	if (PARENT[x] == x) return x;
	return PARENT[x] = Find(PARENT[x]);
}

void Union(int x, int y, int pid) {
	x = Find(x), y = Find(y);
	if (x == y) return;
	PARENT[x] = y;
}
/*===========================*/
void init(int N, int M)
{
    
}
 
int Add(int row, int col, int size, int pid)
{
    return 0;
}
 
int Get(int row, int col)
{
    return 0;
}