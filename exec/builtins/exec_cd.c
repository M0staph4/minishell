#include "../../inc/header.h"

void    exec_cd(char *path)
{
	
    if (path == NULL || !ft_strncmp(path, "~", 2))
	{
        if(!chdir(getenv("HOME")))
			printf("cd: HOME not set\n");
	}
	else
		chdir(path);
		//another case missing
}
