/*
공통조상
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <cstring>
using namespace std;
#define v_max 10001

struct Node {
	int parent;
};

Node node[v_max];//120KB
bool check[v_max];

void init(void)
{
	for (int t = 0; t < v_max; t++)
	{
		node[t].parent = 0;
	}
	memset(check, 0, sizeof(check));
}

int LCA(int s, int e)
{
	int start = s;
	check[start] = true;
	while (node[start].parent != 0)
	{
		start = node[start].parent;
		check[start] = true;
	}
	start = e;
	while (!check[start])
	{
		start = node[start].parent;
	}
	return start;
}


int main(void)
{
	//freopen("input.txt", "r", stdin);
	int T,V,s,e;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++)
	{
		init();
		scanf("%d", &V);
		for (int t = 0; t < V-1; t++)
		{
			int p,c;
			scanf("%d%d", &p, &c);
			node[c].parent = p;
		}
		scanf("%d%d", &s, &e);
		int ans1 = LCA(s, e);
		printf("%d\n", ans1);
	}
}
