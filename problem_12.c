/* Program to simulate a two-level directory file organization */
#include <stdio.h>
#include <string.h>

#define MAX_USERS 10
#define MAX_FILES 10
#define NAME_LENGTH 30
#define INPUT_LENGTH 128

struct user_directory
{
    char name[NAME_LENGTH];
    char files[MAX_FILES][NAME_LENGTH];
    int file_count;
};

static int read_line(const char *prompt, char *text, size_t size)
{
    char input[INPUT_LENGTH];
    size_t length;
    int ch;

    for (;;)
    {
        printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL)
            return 0;

        length = strlen(input);
        if (length > 0 && input[length - 1] == '\n')
            input[--length] = '\0';
        else if (!feof(stdin))
        {
            while ((ch = getchar()) != '\n' && ch != EOF)
                ;
            printf("Input is too long. Try again.\n");
            continue;
        }

        if (length == 0)
        {
            printf("Name cannot be empty. Try again.\n");
            continue;
        }

        if (length >= size)
        {
            printf("Name must be shorter than %zu characters. Try again.\n",
                   size);
            continue;
        }

        strcpy(text, input);
        return 1;
    }
}

static int read_choice(int *choice)
{
    char input[INPUT_LENGTH];
    char extra;

    for (;;)
    {
        printf("Enter your choice: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
            return 0;

        if (sscanf(input, "%d %c", choice, &extra) == 1)
            return 1;

        printf("Invalid choice. Enter a number.\n");
    }
}

static int find_user(const struct user_directory users[], int user_count,
                     const char *name)
{
    int index;

    for (index = 0; index < user_count; index++)
    {
        if (strcmp(users[index].name, name) == 0)
            return index;
    }

    return -1;
}

static int find_file(const struct user_directory *user, const char *name)
{
    int index;

    for (index = 0; index < user->file_count; index++)
    {
        if (strcmp(user->files[index], name) == 0)
            return index;
    }

    return -1;
}

int main(void)
{
    struct user_directory users[MAX_USERS] = {0};
    char user_name[NAME_LENGTH];
    char file_name[NAME_LENGTH];
    int user_count = 0;
    int user_index;
    int file_index;
    int choice;
    int index;

    for (;;)
    {
        printf("\nTwo-Level Directory\n");
        printf("1. Create User Directory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display Files in a User Directory\n");
        printf("6. Display User Directories\n");
        printf("7. Exit\n");

        if (!read_choice(&choice))
            break;

        switch (choice)
        {
        case 1:
            if (user_count == MAX_USERS)
            {
                printf("Maximum number of user directories reached.\n");
                break;
            }

            if (!read_line("Enter user directory name: ", user_name,
                           sizeof(user_name)))
                return 0;

            if (find_user(users, user_count, user_name) != -1)
            {
                printf("User directory %s already exists.\n", user_name);
                break;
            }

            strcpy(users[user_count].name, user_name);
            users[user_count].file_count = 0;
            user_count++;
            printf("User directory %s created successfully.\n", user_name);
            break;

        case 2:
        case 3:
        case 4:
        case 5:
            if (user_count == 0)
            {
                printf("No user directories exist. Create one first.\n");
                break;
            }

            if (!read_line("Enter user directory name: ", user_name,
                           sizeof(user_name)))
                return 0;

            user_index = find_user(users, user_count, user_name);
            if (user_index == -1)
            {
                printf("User directory %s was not found.\n", user_name);
                break;
            }

            if (choice == 5)
            {
                if (users[user_index].file_count == 0)
                {
                    printf("Directory %s is empty.\n", user_name);
                    break;
                }

                printf("Files in %s:\n", user_name);
                for (index = 0; index < users[user_index].file_count; index++)
                    printf("%s\n", users[user_index].files[index]);
                break;
            }

            if (!read_line("Enter file name: ", file_name,
                           sizeof(file_name)))
                return 0;

            file_index = find_file(&users[user_index], file_name);

            if (choice == 2)
            {
                if (file_index != -1)
                {
                    printf("File %s already exists in %s.\n", file_name,
                           user_name);
                    break;
                }

                if (users[user_index].file_count == MAX_FILES)
                {
                    printf("Directory %s is full.\n", user_name);
                    break;
                }

                strcpy(users[user_index].files[users[user_index].file_count],
                       file_name);
                users[user_index].file_count++;
                printf("File %s created in %s.\n", file_name, user_name);
            }
            else if (choice == 3)
            {
                if (file_index == -1)
                {
                    printf("File %s was not found in %s.\n", file_name,
                           user_name);
                    break;
                }

                for (index = file_index;
                     index < users[user_index].file_count - 1; index++)
                {
                    strcpy(users[user_index].files[index],
                           users[user_index].files[index + 1]);
                }
                users[user_index].file_count--;
                printf("File %s deleted from %s.\n", file_name, user_name);
            }
            else
            {
                if (file_index == -1)
                    printf("File %s was not found in %s.\n", file_name,
                           user_name);
                else
                    printf("File %s was found in %s.\n", file_name, user_name);
            }
            break;

        case 6:
            if (user_count == 0)
            {
                printf("No user directories exist.\n");
                break;
            }

            printf("User directories:\n");
            for (index = 0; index < user_count; index++)
                printf("%s\n", users[index].name);
            break;

        case 7:
            return 0;

        default:
            printf("Invalid choice.\n");
        }
    }

    return 0;
}