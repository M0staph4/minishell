#include "../inc/header.h"

void    pipeline(t_table *table)
{
	int *end[2];
	while (table)
	{
		pipe(end);
		pid = fork();
		if (pid == 0)
			execute(table);
		// if last command 
		//execute_lastcommand()
	}
}
