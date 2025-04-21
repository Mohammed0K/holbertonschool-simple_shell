#include "shell.h"
int _atoi(char *str)
{
	int result = 0, sign = 1, i = 0;

	if (str[0] == '-')
	{
		sign = -1;
		i++;
	}

	for (; str[i] != '\0'; ++i)
	{
		if (str[i] < '0' || str[i] > '9')
			break;
		result = result * 10 + (str[i] - '0');
	}

	return sign * result;
}

