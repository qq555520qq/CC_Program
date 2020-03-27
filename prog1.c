#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>

void A(void);
void B(void);
void C(void);
void D(void);
void father(void);
void printStr(char str[2000]);

void main(void)
{
    pid_t pid1, pid2, pid3, pid4;
    int status;

    printStr("Main Process Started\n");

    if ((pid1 = fork()) == 0)
    {
        A();
        exit(0);
    }
    else if (pid1 > 0)
    {
        printStr("Fibonacci Process Created\n");
        father();
        if ((pid2 = fork()) == 0)
        {
            B();
            exit(0);
        }
        else if (pid2 > 0)
        {
            printStr("Buffon's Needle Process Created\n");
            father();
            if ((pid3 = fork()) == 0)
            {
                C();
                exit(0);
            }
            else if (pid3 > 0)
            {
                printStr("Ellipse Area Process Created\n");
                father();
                if ((pid4 = fork()) == 0)
                {
                    D();
                    exit(0);
                }
                else if (pid4 > 0)
                {
                    printStr("Pinball Process Created\n");
                    father();
                    printStr("Main Process Waits\n");
                    while (wait(&status) > 0)
                    {
                    }
                }
            }
        }
    }
    printStr("Main Process Exits\n");
}

void father(void)
{
    printStr("I am father\n");
}

void A(void)
{
    printStr("  This is A\n");
}

void B(void)
{
    printStr("  This is B\n");
}

void C(void)
{
    printStr("  This is C\n");
}

void D(void)
{
    printStr("  This is D\n");
}

void printStr(char str[2000])
{
    char tempStr[strlen(str)];
    sprintf(tempStr, "%s", str);
    write(1, str, strlen(str));
}