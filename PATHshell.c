#include "holberton.h"
int main(void)
{
        char *prompt = "#cisfun$ ", *buffer = NULL, *PATH = NULL;
        char *environvariable = "PATH", *fullpathbuffer;
        ssize_t readcount = 0, writecount = 0;
        size_t n = 0;
        int i = 1, fullpathflag = 0, CWDflag = 0, status;
        char **av, **PATHtokens;
        pid_t pid;
        struct stat h, g, v;

	signal(SIGINT, sigint_handler);
	PATH = _getenv(environvariable);
	PATHtokens = PATHtokenize(PATH);
	/*for (i = 0; PATHtokens[i] != NULL; i++)
	  printf("PATHtokens[%i] %s\n", i, PATHtokens[i]); */
	if (PATH == NULL)
		return(-1);
	while (1)
        {
		fullpathflag = 0;
		CWDflag = 0;
		writecount = write(STDOUT_FILENO, prompt, 9);
		if (writecount == -1)
			return(-1);
		readcount = getline(&buffer, &n, stdin);
		buffer[readcount - 1] = '\0';
		/*printf("%s\n", buffer);*/
		if (readcount == -1)
                {
                        free(buffer);
                        return(0);
                }
		if(*buffer != '\0')
		{
			av = tokenize(buffer);
			/*for (i = 0; av[i] != NULL; i++)
			  printf("av[%i] %s\n", i, av[i]); */
			if (av == NULL)
				return(-1);
			if(PATH[0] == ':')
			{
				status = stat(av[0], &v);
				if (status == 0)
				{
					fullpathbuffer = av[0];
					CWDflag = 1;
				}
			}
			if (!CWDflag)
			{
				for (i = 1; PATHtokens[i] /*&& status != 0*/; i++)
				{
					fullpathbuffer = concat(av[0], PATHtokens[i]);
					status = stat(fullpathbuffer, &h);
/*					printf("%s status: %i\n", fullpathbuffer, status); */
					if (!status)
					{
						fullpathflag = 1;
						break;
					}
				}
				if (stat(av[0], &g) == 0 && !fullpathflag)
				{
					fullpathbuffer = av[0];
/*			printf("full path string to enter execve: %s\n", fullpathbuffer);*/
				}
			}
			pid = fork();
			if (pid == -1)
			{
				perror("Error:");
				return(1);
			}
			if (pid == 0)
			{
				{
					/*printf("Command executed: %s\n", fullpathbuffer);*/
					if (execve(fullpathbuffer, av, NULL) == -1)
					{
						perror("Error");
						free(av);
						free(buffer);
						return(-1);
					}
				}
				/*		else
						execve(av[0], av , NULL); */
			}
			wait(&status);
			free(av);
		}
	}
/*	printf("!%s\n", fullpathbuffer);*/
	free(fullpathbuffer);
	free(buffer);
	return(0);
}
