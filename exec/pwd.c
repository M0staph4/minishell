#include "../header.h"
// void    signal_handler(int sig)
// {
//     if (sig == SIGINT)
//     {
//         printf("\n");
//         rl_on_new_line();
//         rl_replace_line("", 0);
//         rl_redisplay();
//     }
// }
int main()
{
    char *read;
    // char buf[250];

    // getcwd(buf, sizeof(buf));
    // printf("%s\n", buf);
    // chdir("..");
    // getcwd(buf, sizeof(buf));
    // printf("%s\n", buf);
    // printf("PATH: %s\n", getenv("PATH"));
    while(1)
    {
        // signal(SIGINT, signal_handler);
        //termination signal
        // signal(SIGQUIT, SIG_IGN);
        // printf("");
        read = readline("minishell>>");
        add_history(read);
        // printf("%s\n", read);
    }

}