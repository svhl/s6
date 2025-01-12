#include <stdio.h>
#include <stdlib.h>
// for directory handling
#include <dirent.h>
#include <string.h>

void main()
{
	const char *dir_path = ".";
	DIR *dir = opendir(dir_path);

	if (dir == NULL)
	{
		printf("Failed to open directory\n");
		return;
	}

	// no need to define struct as already provided by dirent header
	struct dirent *entry;
	printf("Directory contents of '%s':\n", dir_path);

	while ((entry = readdir(dir)) != NULL)
	{
		printf("%s\n", entry->d_name);
	}

	closedir(dir);
}
