// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>

extern void init(int, int);
extern int Add(int, int, int, int);
extern int Get(int, int);

static unsigned int seed = 5;
static int pseudo_rand(void)
{
	seed = seed * 214013 + 2531011;
	return (seed >> 16) & 0x7FFF;
}

static int board_size, area_size, query_cnt;

static int run(int score)
{
	scanf("%d%d%d%d", &seed, &board_size, &area_size, &query_cnt);
	init(board_size, area_size);

	for (int q = 0; q < query_cnt; q++)
	{
		int r, c, size, user_ans, correct_ans;
		for (int i = 1; i <= 2; i++)
		{
			size = (pseudo_rand() * pseudo_rand()) % area_size + 1;
			r = (pseudo_rand() * pseudo_rand()) % (board_size - size + 1);
			c = (pseudo_rand() * pseudo_rand()) % (board_size - size + 1);

			user_ans = Add(r, c, size, i);
			scanf("%d", &correct_ans);

			if (user_ans != correct_ans) {
				score = 0;
			}
		}

		r = (pseudo_rand() * pseudo_rand()) % (board_size);
		c = (pseudo_rand() * pseudo_rand()) % (board_size);
		user_ans = Get(r, c);
		scanf("%d", &correct_ans);

		if (user_ans != correct_ans) {
			score = 0;
		}
	}

	return score;
}

int main()
{
	setbuf(stdout, NULL);
	//freopen("input.txt", "r", stdin);

	int tc, score;
	scanf("%d%d", &tc, &score);

	for (int t = 1; t <= tc; t++)
	{
		int t_score = run(score);

		printf("#%d %d\n", t, t_score);
	}

	return 0;
}