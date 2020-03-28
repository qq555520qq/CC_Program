#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

long fibonacci(int n);
float buffonNeedle(int times);
int inEllipseAreaNum(int times, int a, int b);
double estimatedArea(int hitNum, int times, int a, int b);
double actualArea(int a, int b);
void pinBallAnswer(int bins, int ballNum);
int getBallPos(int bin);
double histogramMultiples(int ballNum, int bins, int *arr);
void printStr(char str[2000]);

int main(int argc, char *argv[])
{
    pid_t pid1, pid2, pid3, pid4;
    int status;
    int n = atoi(argv[1]);
    int r = atoi(argv[2]);
    int a = atoi(argv[3]);
    int b = atoi(argv[4]);
    int s = atoi(argv[5]);
    int x = atoi(argv[6]);
    int y = atoi(argv[7]);
    int hitNum;
    int binArr[x];
    char str[1000];

    printStr("Main Process Started\n");
    sprintf(str, "Fibonacci Input            = %d\n", n);
    printStr(str);
    sprintf(str, "Buffon's Needle Iterations = %d\n", r);
    printStr(str);
    sprintf(str, "Total random Number Pairs  = %d\n", a);
    printStr(str);
    sprintf(str, "Semi-Major Axis Length     = %d\n", b);
    printStr(str);
    sprintf(str, "Semi-Minor Axis Length     = %d\n", s);
    printStr(str);
    sprintf(str, "Number of Bins             = %d\n", x);
    printStr(str);
    sprintf(str, "Number of Ball Droppings   = %d\n\n", y);
    printStr(str);

    if ((pid1 = fork()) == 0)
    {
        printStr("   Fibonacci Process Started\n");
        sprintf(str, "   Input Number %d\n", n);
        printStr(str);
        sprintf(str, "   Fibonacci Number f(%d) is %ld\n", n, fibonacci(n));
        printStr(str);
        printStr("   Fibonacci Process Exits\n");
        exit(0);
    }
    else if (pid1 > 0)
    {
        printStr("Fibonacci Process Created\n");
        if ((pid2 = fork()) == 0)
        {
            printStr("      Buffon's Needle Process Started\n");
            sprintf(str, "      Input Number %d\n", r);
            printStr(str);
            sprintf(str, "      Estimated Probability is %.5f\n", buffonNeedle(r));
            printStr(str);
            printStr("      Buffon's Needle Process Exits\n");
            exit(0);
        }
        else if (pid2 > 0)
        {
            printStr("Buffon's Needle Process Created\n");
            if ((pid3 = fork()) == 0)
            {
                printStr("         Ellipse Area Process Started\n");
                sprintf(str, "         Total random Number Pairs %d\n", s);
                printStr(str);
                sprintf(str, "         Semi-Major Axis Length %d\n", a);
                printStr(str);
                sprintf(str, "         Semi-Minor Axis Length %d\n", b);
                printStr(str);
                hitNum = inEllipseAreaNum(s, a, b);
                sprintf(str, "         Total Hits %d\n", hitNum);
                printStr(str);
                sprintf(str, "         Estimated Area is %f\n", estimatedArea(hitNum, s, a, b));
                printStr(str);
                sprintf(str, "         Actual Area is %f\n", actualArea(a, b));
                printStr(str);
                printStr("         Ellipse Area Process Exits\n");
                exit(0);
            }
            else if (pid3 > 0)
            {
                printStr("Ellipse Area Process Created\n");
                if ((pid4 = fork()) == 0)
                {
                    printStr("Simple Pinball Process Started\n");
                    sprintf(str, "Number of Bins %d\n", x);
                    printStr(str);
                    sprintf(str, "Number of Ball Droppings %7d\n", y);
                    printStr(str);
                    pinBallAnswer(x, y);

                    exit(0);
                }
                else if (pid4 > 0)
                {
                    printStr("Pinball Process Created\n");
                    printStr("Main Process Waits\n");
                    while (wait(&status) > 0)
                    {
                    }
                }
            }
        }
    }
    printStr("Main Process Exits\n");
    return 0;
}

long fibonacci(int n)
{
    if (n >= 2)
    {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
    else
    {
        return n;
    }
}

float buffonNeedle(int times)
{
    int i;
    int L = 1;
    int G = 1;
    float answerTimes = 0L;
    float pi = acos(-1.0);
    float d;
    float a;

    for (i = 0; i < times; i++)
    {
        d = (float)rand() / (RAND_MAX + 1L);
        a = 2L * pi * (float)rand() / (RAND_MAX + 1L);
        float crossAnswer = d + (L * sin(a));
        if (crossAnswer < 0 || crossAnswer > G)
        {
            answerTimes += 1L;
        }
    }

    return answerTimes / times;
}

int inEllipseAreaNum(int times, int a, int b)
{
    int i;
    int answerTimes = 0;
    float x;
    float y;
    for (i = 0; i < times; i++)
    {
        x = a * (float)rand() / (RAND_MAX + 1L);
        y = b * (float)rand() / (RAND_MAX + 1L);
        float inAreaAnswer = (pow(x, 2) / pow(a, 2)) + (pow(y, 2) / pow(b, 2));
        if (inAreaAnswer <= 1)
        {
            answerTimes += 1;
        }
    }

    return answerTimes;
}

double estimatedArea(int hitNum, int times, int a, int b)
{
    return (((double)hitNum / times) * a * b) * 4;
}

double actualArea(int a, int b)
{
    double pi = acos(-1.0);
    return pi * a * b;
}

void pinBallAnswer(int bins, int ballNum)
{
    int i;
    int binArr[bins];
    double multiples;
    char str[1000];

    for (i = 0; i < bins; i++)
    {
        binArr[i] = 0;
    }
    for (i = 0; i < ballNum; i++)
    {
        binArr[getBallPos(bins)] += 1;
    }

    multiples = histogramMultiples(ballNum, bins, binArr);

    for (i = 0; i < bins; i++)
    {
        char star[50] = "";
        float s = multiples * binArr[i] / ballNum * 100;
        memcpy(star, "**************************************************", (int)((multiples * binArr[i] / ballNum * 100) + 0.5));
        sprintf(str, "%3d-(%7d)-( %5.2f%%)|%s\n", i + 1, binArr[i], (double)binArr[i] / ballNum * 100, star);
        printStr(str);
    }
}

int getBallPos(int bin)
{
    double moveNum = (double)rand() / (RAND_MAX + 1.0);
    if (bin == 2)
    {
        if (moveNum <= 0.5)
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (moveNum <= 0.5)
        {
            return getBallPos(bin - 1);
        }
        else
        {
            return getBallPos(bin - 1) + 1;
        }
    }
}

double histogramMultiples(int ballNum, int bins, int *arr)
{
    int max = 0;
    int i;
    double ans;

    for (i = 0; i < bins; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    ans = (double)max / ballNum * 100;
    return 50 / ans;
}

void printStr(char str[2000])
{
    write(1, str, strlen(str));
}