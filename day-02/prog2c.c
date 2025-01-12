// for file control operations
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void main(char *argv[])
{
	// O_RDONLY for read only
	int src = open(argv[1], O_RDONLY);

	if (src == -1)
	{
		printf("Error opening source file\n");
		return;
	}

	// argv is array of args passed
	// O_WRONLY for write only
	// O_CREAT for create if not exists
	// O_TRUNC for truncate contents if exists
	// 0644 for permission
	int dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

	if (dest == -1)
	{
		printf("Error opening destination file\n");
		close(src);
		return;
	}

	// buffer to hold data during copy
	char buffer[1024];
	// ssize_t is signed size type for bytes read & written
	ssize_t bread, bwrtn;

	while ((bread = read(src, buffer, 1024)) > 0)
	{
		bwrtn = write(dest, buffer, bread);
	}

	close(src);
	close(dest);
	printf("File copied successfully.\n");
}
