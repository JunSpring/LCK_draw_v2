#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#include "load_csv.h"
#include "team_struct.h"
#include "date_struct.h"
#include "random.h"

#pragma warning(disable:4996) // scanf오류 전처리기

void input_team_num(int* num);
void input_team_name(Team* teams, int num, char team_name[][30]);
void load_data(Team* team);
void set_pre_win_rate(Team* team);
void set_win_rate(Team* team);
void ranking(Team* team, int team_num);
void print_rank(Team team);

int main()
{
	srand((unsigned int)time(NULL));
	
	char team_name[10][30] = {
		"DRX",
		"DWG KIA",
		"Fredit BRION",
		"Gen.G",
		"Hanwha Life Esports",
		"KT Rolster",
		"Kwangdong Freecs",
		"Liiv SANDBOX",
		"Nongshim RedForce",
		"T1"
	};

	int team_num;
	input_team_num(&team_num);

	Team* teams;
	teams = (Team*)malloc(sizeof(Team) * team_num);
	for (int i = 0; i < team_num; i++)
	{
		teams[i].pre_GP = 0;
		teams[i].pre_win = 0;
		teams[i].win = 0;
		teams[i].rank = 0;
		teams[i].left_games = 0;
	}

	input_team_name(teams, team_num, team_name);
	system("pause");
	system("cls");

	for (int i = 0; i < team_num; i++)
	{
		load_data(&teams[i]);
		set_pre_win_rate(&teams[i]);
	}

	Date summer2022;
	set_date_data(&summer2022, 100, (team_num)*(team_num-1)/2);
	print_date(&summer2022, teams, team_num, 6, 8);
	system("pause");
	system("cls");

	for (int i = 0; i < team_num; i++)
	{
		set_win_rate(&teams[i]);
	}

	ranking(teams, team_num);

	for (int i = 0; i < team_num; i++)
	{
		for (int j = 0; j < team_num; j++)
		{
			if (teams[j].rank == i + 1)
			{
				print_rank(teams[j]);
			}
		}
	}

	free(teams);
}

void input_team_num(int* num)
{
	do
	{
		printf("시즌에 경기하는 팀의 수를 입력하시오 >> ");
		scanf("%d", num);
	} while (!(6 <= *num && *num <= 10) && printf("6이상 10이하의 수를 입력해주세요!\n\n"));
	printf("\n");
	getchar();
}

void input_team_name(Team* teams, int num, char team_name[][30])
{
	for (int i = 0; i < num;)
	{
		char temp[50];
		int temp_num = i;
		printf("%d번째 팀의 이름을 입력하시오 >> ", i + 1);
		gets(temp);

		for (int j = 0; j < 10; j++)
		{
			for (int k = 0; k < i; k++)
			{
				if (!strcmp(temp, teams[k].name))
				{
					j = -1;
					break;
				}
			}

			if (j == -1)
			{
				printf("이미 입력된 팀입니다! ");
				break;
			}

			if (!strcmp(temp, team_name[j]))
			{
				printf("성공!\n\n");
				strcpy(teams[i].name, temp);
				i++;
				break;
			}
		}

		if (temp_num == i)
			printf("다시 입력해주세요!\n\n");
	}
}

void load_data(Team* team)
{
	print(team, "data\\01. LCK 2021 Spring\\Team Stats - OraclesElixir.csv");
	print(team, "data\\02. LCK 2021 Spring Playoffs\\Team Stats - OraclesElixir.csv");
	print(team, "data\\03. LCK 2021 Summer\\Team Stats - OraclesElixir.csv");
	print(team, "data\\04. LCK 2021 Summer Playoffs\\Team Stats - OraclesElixir.csv");
	print(team, "data\\05. LCK 2021 Regional Finals\\Team Stats - OraclesElixir.csv");
	print(team, "data\\06. LCK 2022 Spring\\Team Stats - OraclesElixir.csv");
	print(team, "data\\07. LCK 2022 Spring Playoffs\\Team Stats - OraclesElixir.csv");
}

void set_pre_win_rate(Team* team)
{
	team->pre_win_rate = (double)team->pre_win / team->pre_GP * 100;
}

void set_win_rate(Team* team)
{
	team->win_rate = (double)team->win / team->GP * 100;
}

void ranking(Team* team, int team_num)
{
	for (int i = 0; i < team_num; i++)
	{
		for (int j = 0; j < team_num; j++)
		{
			if (team[i].win_rate < team[j].win_rate)
				team[i].rank += 1;
		}
		team[i].rank += 1;
	}
}

void print_rank(Team team)
{
	printf("%d등\n", team.rank);
	printf("이름:\t%s\n", team.name);
	printf("전체 경기수:\t%d판\n", team.GP);
	printf("승:         \t%d승\n", team.win);
	printf("패:         \t%d패\n", team.GP - team.win);
	printf("승률:       \t%f%%\n\n", team.win_rate);
}