#include <stdio.h>
#include <string.h>

struct directory
{
	char name[10];
	char files[10][10];
	int file_count;
};

int main(void)
{
	struct directory directory = {"", {{0}}, 0};
	char file_name[10];
	int choice;
	int index;
	int found;

	printf("Enter name of directory: ");
	scanf("%9s", directory.name);

	while (1)
	{
		printf("\n1. Create File\n");
		printf("2. Delete File\n");
		printf("3. Search File\n");
		printf("4. Display Files\n");
		printf("5. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);

		switch (choice)
		{
		case 1:
			if (directory.file_count == 10)
			{
				printf("Directory is full.\n");
				break;
			}

			printf("Enter the name of the file: ");
			scanf("%9s", directory.files[directory.file_count]);
			directory.file_count++;
			printf("File created successfully.\n");
			break;

		case 2:
			printf("Enter the name of the file: ");
			scanf("%9s", file_name);
			found = 0;

			for (index = 0; index < directory.file_count; index++)
			{
				if (strcmp(file_name, directory.files[index]) == 0)
				{
					found = 1;
					directory.file_count--;
					strcpy(directory.files[index],
						   directory.files[directory.file_count]);
					printf("File %s was deleted.\n", file_name);
					break;
				}
			}

			if (!found)
				printf("File %s was not found.\n", file_name);
			break;

		case 3:
			printf("Enter the name of the file: ");
			scanf("%9s", file_name);

			for (index = 0; index < directory.file_count; index++)
			{
				if (strcmp(file_name, directory.files[index]) == 0)
				{
					printf("File %s was found.\n", file_name);
					break;
				}
			}

			if (index == directory.file_count)
				printf("File %s was not found.\n", file_name);
			break;

		case 4:
			if (directory.file_count == 0)
			{
				printf("Directory is empty.\n");
				break;
			}

			printf("Files in %s: ", directory.name);
			for (index = 0; index < directory.file_count; index++)
				printf("%s ", directory.files[index]);
			printf("\n");
			break;

		case 5:
			return 0;

		default:
			printf("Invalid choice.\n");
		}
	}
}