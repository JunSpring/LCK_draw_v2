#ifndef TEAM_STRUCT_H
#define TEAM_STRUCT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "random.h"

typedef struct team //Team구조체
{
	char name[30]; // 팀이름

	int pre_GP; // 전체 경기수
	int pre_win; // 이긴 경기수
	double pre_win_rate; // 승률

	int GP; // 이번 시즌 전체 경기수
	int left_games; // 이번 시즌 남은 경기수
	int win; // 이번 시즌 이긴 경기수
	double win_rate; // 이번 시즌 승률
	int rank; // 이번 시즌 순위
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