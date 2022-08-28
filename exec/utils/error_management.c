#include "../../inc/header.h"

void print_error(char *error, char *ar, int ex_code)
{
    ft_putstr_fd(ar, 2);
	ft_putstr_fd(error, 2);
    exit_status = ex_code;
}

void print_error2(char *error, char *ar, int ex_code)
{
    ft_putstr_fd(ar, 2);
	ft_putendl_fd(error, 2);
    exit_status = ex_code;
}