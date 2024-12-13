#include "../get_next_line.h"

int mandatory_tests()
{
    int fd = open("testfile_basic.txt", O_RDONLY);
    for (int i = 0; i < 4; i++)
        printf("%s\n", get_next_line(fd));
    close(fd);

    fd = open("oneliner.txt", O_RDONLY);
    printf("%s\n", get_next_line(fd));
    close(fd);

    fd = open("testfile_big.txt", O_RDONLY);
    for (int i = 0; i < 80; i++)
        printf("%s\n", get_next_line(fd));
    close(fd);

    fd = open("largefile.txt", O_RDONLY);
    for (int i = 0; i < 100000; i++)
        printf("%s\n", get_next_line(fd));
    close(fd);
    return 0;
}

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        printf("valid exec: name of the program");
        return -1;
    }
    mandatory_tests();
    return 0;
}