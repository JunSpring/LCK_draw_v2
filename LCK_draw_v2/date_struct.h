#ifndef DATE_STRUCT_H
#define DATR_STRUCT_H

#include <stdio.h>
#include <stdlib.h>

#include "team_struct.h"
#include "random.h"

typedef struct date
{
	int left_games;
	int cycle;
}Date;

void set_date_data(Date* date, int left_games, int cycle)
{
	date->left_games = left_games;
	date->cycle = cycle;
}

void print_fight(Team team1, Team team2, int result, int month, int day)
{
	printf("%d¿ù %dÀÏ\n", month, day);
	printf("%s\t:\t%s\n", team1.name, team2.name);
	
	if (result)
		printf("½Â\t:\tÆÐ\n\n");
	else
		printf("ÆÐ\t:\t½Â\n\n");
}

void print_date(Date* season, Team* teams, int team_num, int month, int day)
{
	int day_count = 0;
	
	for (int i = 0; i < season->left_games * 2; i++)
	{
		teams[i % team_num].left_games += 1;
	}

	for (int i = 0; i < team_num; i++)
	{
		teams[i].GP = teams[i].left_games;
	}

	while (season->left_games)
	{
		int team[2];
		int i;

		do
		{
			random_two_teams(team, team_num);
		} while (teams[team[0]].left_games == 0 || teams[team[1]].left_games == 0);
		print_fight(teams[team[0]], teams[team[1]], team_fight(&teams[team[0]], &teams[team[1]]), month, day);
		
		do
		{
			random_two_teams(team, team_num);
		} while (teams[team[0]].left_games == 0 || teams[team[1]].left_games == 0);
		print_fight(teams[team[0]], teams[team[1]], team_fight(&teams[team[0]], &teams[team[1]]), month, day);

		season->left_games -= 2;

		day_count += 1;
		if (day_count == 5)
		{
			day += 3;
			day_count = 0;
		}
		else
		{
			day += 1;
		}

		if (month == 6 && day > 30)
		{
			month = 7;
			day -= 30;
		}
		else if (month == 7 && day > 31)
		{
			month = 8;
			day -= 31;
		}
	}
}

#endif // !DATE_STRUCT_H