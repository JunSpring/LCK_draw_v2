#ifndef RANDOM_H
#define RANDOM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void random_two_teams(int* teams, int team_num)
{
	int num = rand() % team_num;
	teams[0] = num;
	do
	{
		num = rand() % team_num;
	} while (num == teams[0]);
	teams[1] = num;
}

#endif // !RANDOM_H