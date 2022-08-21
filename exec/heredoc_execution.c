#include "../inc/header.h"

// int random_file()
// {
//     static int file;

//     file += 1;
//     return (file); 
// }
// void    heredoc()
// {
//     int file = random_file();
//     int tmp_file;
//     char *buff;

//     tmp_file = open("tmp/file", O_WRONLY | O_CREAT | O_TRUNC, 0777);
//     while(1)
//     {
//         buff = readline("heredoc> ");
// 		add_history(buff);
//     }
// }