#ifndef TEAM_STRUCT_H
#define TEAM_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "random.h"

typedef struct team //Team����ü
{
	char name[30]; // ���̸�

	int pre_GP; // ��ü ����
	int pre_win; // �̱� ����
	double pre_win_rate; // �·�

	int GP; // �̹� ���� ��ü ����
	int left_games; // �̹� ���� ���� ����
	int win; // �̹� ���� �̱� ����
	double win_rate; // �̹� ���� �·�
	int rank; // �̹� ���� ����
}Team;

int team_fight(Team* team1, Team* team2)
{
	int result = rand() % (int)(team1->pre_win_rate + team2->pre_win_rate) - team1->pre_win_rate;

	team1->left_games -= 1;
	team2->left_games -= 1;

	if (result < 0)
	{
		team1->win += 1;
		return 1;
	}
	else
	{
		team2->win += 1;
		return 0;
	}
}
#endif // !TEAM_STRUCT_H