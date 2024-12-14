#include "../get_next_line_bonus.h"

void bonus_tests()
{
    int fd1 = open("testfiles/testfile_basic.txt", O_RDONLY);
    int fd2 = open("testfiles/testfile_big.txt", O_RDONLY);
    int fd3 = open("testfiles/generated_file.txt", O_RDONLY);
    int fd4 = open("testfiles/gen_file2.txt", O_RDONLY);
    int fd5 = open("testfiles/genfile3.txt", O_RDONLY);
    int fd6 = open("testfiles/genfile4.txt", O_RDONLY);
    int fd7 = open("testfiles/largefile.txt", O_RDONLY);
    int fd8 = open("testfiles/oneliner.txt", O_RDONLY);
    for (int i = 0; i < 100000; i++)
    {
        if (!i)
            printf("%s\n", get_next_line(fd8));
        if (i < 4)
            printf("%s\n", get_next_line(fd1));
        if (i < 82)
            printf("%s\n", get_next_line(fd2));
        if (i < 4)
            printf("%s\n", get_next_line(fd3));
        if (i < 4)
            printf("%s\n", get_next_line(fd4));
        if (i < 12)
            printf("%s\n", get_next_line(fd5));
        if (i < 20)
            printf("%s\n", get_next_line(fd6));
        printf("%s\n", get_next_line(fd7));
    }
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);
    close(fd5);
    close(fd6);
    close(fd7);
    close(fd8);
}

int main(int argc, char **argv)
{
    (void)argv;
    if (argc != 1)
    {
        printf("valid exec: name of the program");
        return -1;
    }
    bonus_tests();
    return 0;
}