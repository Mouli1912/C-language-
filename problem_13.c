#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_FILES 20
#define NAME_LENGTH 30

struct file_allocation
{
    char name[NAME_LENGTH];
    int start_block;
    int length;
    int allocated;
};

int main(void)
{
    int disk[MAX_BLOCKS] = {0};
    struct file_allocation files[MAX_FILES];
    int total_blocks;
    int file_count;
    int file_index;
    int block;
    int available;

    printf("Enter the total number of disk blocks (1-%d): ", MAX_BLOCKS);
    if (scanf("%d", &total_blocks) != 1 ||
        total_blocks < 1 || total_blocks > MAX_BLOCKS)
    {
        printf("Invalid number of disk blocks.\n");
        return 1;
    }

    printf("Enter the number of files (1-%d): ", MAX_FILES);
    if (scanf("%d", &file_count) != 1 ||
        file_count < 1 || file_count > MAX_FILES)
    {
        printf("Invalid number of files.\n");
        return 1;
    }

    for (file_index = 0; file_index < file_count; file_index++)
    {
        printf("\nEnter file name, starting block (0-%d), and length: ",
               total_blocks - 1);
        if (scanf("%29s %d %d", files[file_index].name,
                  &files[file_index].start_block,
                  &files[file_index].length) != 3)
        {
            printf("Invalid file allocation input.\n");
            return 1;
        }

        files[file_index].allocated = 0;

        if (files[file_index].start_block < 0 ||
            files[file_index].length <= 0 ||
            files[file_index].start_block >= total_blocks ||
            files[file_index].length >
                total_blocks - files[file_index].start_block)
        {
            printf("Cannot allocate %s: the requested blocks are outside "
                   "the disk.\n",
                   files[file_index].name);
            continue;
        }

        available = 1;
        for (block = files[file_index].start_block;
             block < files[file_index].start_block + files[file_index].length;
             block++)
        {
            if (disk[block] != 0)
            {
                available = 0;
                break;
            }
        }

        if (!available)
        {
            printf("Cannot allocate %s: one or more requested blocks are "
                   "already occupied.\n",
                   files[file_index].name);
            continue;
        }

        for (block = files[file_index].start_block;
             block < files[file_index].start_block + files[file_index].length;
             block++)
        {
            disk[block] = 1;
        }

        files[file_index].allocated = 1;
        printf("File %s allocated successfully.\n", files[file_index].name);
    }

    printf("\nSequential File Allocation Table\n");
    printf("File Name\tStarting Block\tLength\tAllocated Blocks\n");
    for (file_index = 0; file_index < file_count; file_index++)
    {
        if (!files[file_index].allocated)
            continue;

        printf("%s\t\t%d\t\t%d\t",
               files[file_index].name,
               files[file_index].start_block,
               files[file_index].length);

        for (block = files[file_index].start_block;
             block < files[file_index].start_block + files[file_index].length;
             block++)
        {
            printf("%d ", block);
        }
        printf("\n");
    }

    return 0;
}