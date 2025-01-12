#include <stdio.h>
#include <stdlib.h>
// for system calls
#include <unistd.h>
// for data types like pid_t
#include <sys/types.h>
#include <sys/wait.h>

void main()
{
	char cwd[1024];
	getcwd(cwd, sizeof(cwd));
	printf("Current directory: %s\n", cwd);
	pid_t ppid = getpid();
	printf("Parent process PID: %d\n", ppid);
	pid_t pid = fork();

	if (pid < 0)
	{
		printf("Fork failed");
	}

	else if (pid == 0)
	{
		pid_t cpid = getpid();
		printf("Child process PID: %d\n", cpid);
	}

	else
	{
		// wait for child to finish
		wait(NULL);
	}
}
