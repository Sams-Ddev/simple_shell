#include "main.h"

/**
 * main - entry point of my shell program
 * @argc: arguments counts
 * @argv: argument vector
 *
 * Return: 0 (on success),however  1 on error
 */
int main(int argc, char **argv)
{
	info_r info[] = { INFO_INITIATE };
	int fd = 2;

	fd += 3;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				char error_msg[] = ": Can't open ";
				write(STDERR_FILENO, argv[0], strlen(argv[0]));
				write(STDERR_FILENO, error_msg, strlen(error_msg));
				write(STDERR_FILENO, argv[1], strlen(argv[1]));
				write(STDERR_FILENO, "\n", 1);
				printChar_stderr(BUFFER_FLUSH);

				exit(127);
			}

			return (EXIT_FAILURE);
		}
		info->readInput_fd = fd;
	}
	populate_envList(info);
	readHistoryFile(info);
	h_sh(info, argv);
	return (EXIT_SUCCESS);
}

