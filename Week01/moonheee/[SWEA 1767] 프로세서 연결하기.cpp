#include <iostream>
#include <vector>
#include <limits>
using namespace std;
int map[12][12]; // 0: ���ִ� ���� / 1: core / 2: ����
int count_core[13]; // index : ����� core �� / value : core���� �ش�Ǵ� �ּ� ���� ����
int count2; // ���� ����� ������ ����
int min_count; // max core�� ����� �ּ� ���� ���� (���� ġ��)
int max_core; // �ִ� core (���� ġ��)
int core; // ���� ����� core�� ��
int N; // ���� ����, ����
vector<pair<int, int>> v; // dfs�� node
// dfs�� ���� �迭
int direct[4][2] =
{
	1, 0, // �Ʒ����� ����
	-1, 0, // ���ʺ��� ����
	0, 1, // �����ʺ��� ����
	0, -1 // ���� ���� ����
};

// 1. map �ʱ�ȭ
// 2. dfs node ���� �ʱ�ȭ (���� �ִ� core�� ���� �ʴ´�)
void input()
{
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
			cin >> map[y][x];
	int flag;
	for (int y = 0; y < N; y++)
		for (int x = 0; x < N; x++)
		{
			if (map[y][x] && y != 0 && x != 0)
			{
				flag = 0;
				for (int idx = 0; idx < 4; idx++)
				{
					int dy = y + direct[idx][0];
					int dx = x + direct[idx][1];
					if (dy >= 0 && dx >= 0 && dy < N && dx < N)
						if (map[dy][dx] != 1)
							flag = 1;
				}
				if (flag)
					v.push_back(make_pair(y, x));
			}
		}
	return;
}

// node(������ now��°)���� direct_idx�� ����Ű�� ������ ������ �������� üũ
// ��ȯ�� 0 , 1
int is_valid(int now, int direct_idx)
{
	int dy = v[now].first + direct[direct_idx][0];
	int dx = v[now].second + direct[direct_idx][1];
	while (dy >= 0 && dx >= 0 && dy < N && dx < N)
	{
		// ����(3)�� node(1)�� �����ٸ� 0 ��ȯ
		if (map[dy][dx])
			return 0;
		dy += direct[direct_idx][0];
		dx += direct[direct_idx][1];
	}
	return 1;
}

// node(������ now��°)���� direct_idx�� ����Ű�� ������ ���� ����
// map�� ����(3)�� ä������
int set_map(int now, int direct_idx)
{
	int result = 0;
	int dy = v[now].first + direct[direct_idx][0];
	int dx = v[now].second + direct[direct_idx][1];
	while (dy >= 0 && dx >= 0 && dy < N && dx < N)
	{
		map[dy][dx] = 3;
		result++;
		dy += direct[direct_idx][0];
		dx += direct[direct_idx][1];
	}
	return result;
}

// node(������ now��°)���� direct_idx�� ����Ű�� ������ ���� ����
// map�� ������ ���� ������ 0���� ä������
int reset_map(int now, int direct_idx)
{
	int result = 0;
	int dy = v[now].first + direct[direct_idx][0];
	int dx = v[now].second + direct[direct_idx][1];
	while (dy >= 0 && dx >= 0 && dy < N && dx < N)
	{
		map[dy][dx] = 0;
		result++;
		dy += direct[direct_idx][0];
		dx += direct[direct_idx][1];
	}
	return result;
}

void dfs(int now)
{
	// ���� ����
	if (now >= v.size())
	{
		// �ִ� core��ŭ ã�ų� �� ���� core�� ã���� ��
		if (core >= max_core)
		{
			// �� ���� core�� ã���� ��
			if (core != max_core)
			{
				// max_core ����
				max_core = core;
				// max_core�� ����� �ּ� ���� ���� ����
				min_count = count_core[max_core];
			}
			// ���� core�� �����ϰ� �� ���� ���� ���̸� ã���� ��
			if (count2 < count_core[core])
			{
				count_core[core] = count2;
				min_count = count2;
			}
		}
		return;
	}

	// �б��� (4���� ������)
	for (int idx = 0; idx < 4; idx++)
	{
		if (is_valid(now, idx))
		{
			// ���� ����
			core++;
			count2 += set_map(now, idx);
			// ���� ġ�� (�̹� ������ �ʹ� ���� ����� ��� �б� ���� ����)
			// ���� return���� Ž�� ����
			if (count2 < min_count)
				dfs(now + 1);
			// ���� �ʱ�ȭ
			core--;
			count2 -= reset_map(now, idx);
		}
	}
	// core�� ������ �������� �ʴ� �б���
	// ���� ġ�� (���� �ʹ� ���� core�� ������� �ʾƼ� ������ �� �����ص�
	// max_core�� ���� �ʴ� ���)
	if (max_core && now - core + 1 < v.size() - max_core)
		dfs(now + 1);
	return;
}

int main()
{
	int T;
	cin >> T;

	for (int i_t = 0; i_t < T; i_t++)
	{
		// �׽�Ʈ�� �ʱ�ȭ
		cin >> N;
		count2 = 0;
		core = 0;
		max_core = 0;
		min_count = numeric_limits<int>::max();
		v.clear();
		for (int idx = 0; idx < 13; idx++)
			count_core[idx] = numeric_limits<int>::max();
		input();
		// ���� ���� ��尡 ������?
		dfs(0);
		cout << "#" << i_t + 1 << " " << count_core[max_core] << "\n";
	}
	return 0;
}

// 1�� 49/50
// 2�� 49/50