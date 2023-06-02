#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int global_var = 1;

int main()
{
    int local_var = 2;

    printf("global_var address: %p, value: %d\n", &global_var, global_var);
    printf("local_var address: %p, value: %d\n", &local_var, local_var);
    printf("pid: %d\n", getpid());

    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        printf("child pid: %d, parent pid: %d\n", getpid(), getppid());
        printf("global_var address: %p, value: %d\n", &global_var, global_var);
        printf("local_var address: %p, value: %d\n", &local_var, local_var);

        global_var = 10;
        local_var = 20;
        printf("child global_var: %d, local_var: %d\n", global_var, local_var);
        exit(5);
    }
    else
    {
        printf("parent pid: %d\n", getpid());
        printf("global_var address: %p, value: %d\n", &global_var, global_var);
        printf("local_var address: %p, value: %d\n", &local_var, local_var);

        sleep(30);

        int status;
        pid_t wpid = waitpid(pid, &status, 0);

        if (wpid == -1)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status))
        {
            printf("child exit status: %d\n", WEXITSTATUS(status));
        }
        else if (WIFSIGNALED(status))
        {
            printf("child was terminated by signal %d\n", WTERMSIG(status));
        }
    }

    return 0;
}
