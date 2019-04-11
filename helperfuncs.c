#include "holberton.h"
char *_getenv(const char *name)
{
        extern char **environ;
        int i, result;

        for (i = 0; environ[i]; i++)
        {
		result = _strcmp(name, environ[i]);
                if (result == 0)
                        return(environ[i]);
        }
        return(NULL);
}
char **tokenize(char* buffer)
{
        char *token;
        char **av = malloc(100*sizeof(token));
        int i = 0;
        char *delimiter = " \n";

        if (av == NULL)
                return(NULL);
        token = strtok(buffer, delimiter);
        while (token != NULL)
        {
                av[i] = token;
                token = strtok(NULL, delimiter);
                i++;
        }
        av[i] = NULL;
        return(av);
}
char **PATHtokenize(char* buffer)
{
        char *token;
        char **av = malloc(100*sizeof(token));
        int i = 0;
        char *delimiter = "= :";
/*	printf("PATH to be tokenized: %s. AV to store it %s\n", buffer, av[0]); */
        if (av == NULL)
                return(NULL);
        token = strtok(buffer, delimiter);
        while (token != NULL)
        {
                av[i] = token;
/*		printf("%s -> av[%i] %s\n", token, i, av[i]); */
                token = strtok(NULL, delimiter);
		i++;
        }
        av[i] = NULL;
        return(av);
}
int _strcmp(const char *s1, const char *s2)
{
        int i;

        for (i = 0; s2[i] != '='; i++)
        {
                if (s1[i] != s2[i])
                {
                        return(-1);
		}
        }
	return(0);
}

char *concat(char *command, char *PATHtoken)
{
        char *concatbuffer;
        int j, k, z, p;

        k = 0;
        while (command[k] != '\0')
                k++;
	j = 0;
	while(PATHtoken[j] != '\0')
		j++;
	concatbuffer = malloc((j + k) + 2);
	if (concatbuffer == NULL)
		return(NULL);
                z = 0;
                while (z < j)
                {
                        concatbuffer[z] = PATHtoken[z];
                        z++;
                }
                concatbuffer[z] = '/';
                z++;
                p = 0;
                while (p < k)
		{
                        concatbuffer[z] = command[p];
                        z++;
			p++;
		}
		return(concatbuffer);
}

void sigint_handler(__attribute__ ((unused))int sig)
{
	printf("\n");
        exit(-1);
}
