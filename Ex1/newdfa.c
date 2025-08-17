#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int inArray(int *arr, int n, int ele)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == ele)
            return 1;
    }
    return 0;
}
int main()
{
    int n, ins, start, fins;
    printf("Enter the no. of states: ");
    scanf("%d", &n);
    char states[n];
    for (int i = 0; i < n; i++)
    {
        states[i] = (char)(i + 65);
        printf("%c - %d\n", states[i], i);
    }
    printf("Select start state:\n ");
    while (1)
    {
        scanf("%d", &start);
        if (start < n && start >= 0)
        {
            break;
        }
        printf("Enter a valid state!\n");
    }
    printf("Enter the no. of final states: ");
    while (1)
    {
        scanf("%d", &fins);
        if (fins > 0 && fins <= n)
            break;
        printf("Enter valid number.\n");
    }
    int finstates[fins];
    printf("Enter final states: ");
    for (int i = 0; i < n; i++)
    {
        printf("%c - %d\n", states[i], i);
    }
    for (int i = 0; i < fins; i++)
    {
        while (1)
        {
            int ci;
            scanf("%d", &ci);
            if (!inArray(finstates, fins, ci) && ci >= 0 && ci < n)
            {
                finstates[i] = ci;
                break;
            }
            printf("Entered state is invalid/already a final state!\n");
        }
    }
    printf("Start state = %c, Final states:\n", states[0]);
    for (int i = 0; i < fins; i++)
    {
        printf("%c\n", (char)(finstates[i] + 65));
    }
    printf("Enter the no. of inputs: ");
    scanf("%d", &ins);
    char inputs[n];
    for (int i = 0; i < ins; i++)
    {
        inputs[i] = (char)(i + 97);
    }
    int trans[n][ins];
    printf("Enter the transitions (-1 for null state): \n");
    for (int i = 0; i < n; i++)
    {
        printf("%c - %d\n", states[i], i);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < ins; j++)
        {
            while (1)
            {
                printf("%c,%c: ", states[i], inputs[j]);
                int in;
                scanf("%d", &in);
                if (in >= -1 && in < n)
                {
                    trans[i][j] = in;
                    break;
                }
                else
                {
                    printf("Invalid state. Retry.\n");
                }
            }
        }
    }
    printf("Final transition table:\n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < ins; j++)
        {
            printf("%c, %c -> %c\n", states[i], inputs[j], (char)(trans[i][j] != -1 ? trans[i][j] + 65 : '-'));
        }
    }
    char *str = (char *)malloc(sizeof(char) * 100);
    while (1)
    {
        while (1)
        {
            printf("Enter the string input for dfa (use only input symbols):");
            scanf("%s", str);
            int flag = 1;
            for (int i = 0; i < strlen(str); i++)
            {
                if (str[i] < (char)inputs[0] || str[i] > (char)inputs[ins - 1])
                {
                    printf("The given input contains invalid characters. Retry\n");
                    flag = 0;
                    break;
                }
            }
            if (flag)
                break;
        }
        int curst = 0;
        char *curstr = (char *)malloc(sizeof(char) * 100);
        for (int i = 0; i < strlen(str); i++)
        {
            int newst = trans[curst][(int)str[i] - 97];
            if (newst != -1)
            {
                int prest = curst;
                curst = newst;
                strncat(curstr, &str[i], 1);
                if (!inArray(finstates, fins, curst) && inArray(finstates, fins, prest))
                {
                    printf("%s\n", curstr);
                    curstr = (char *)malloc(sizeof(char) * 100);
                    curst = 0;
                }
            }
            else
            {
                printf("Reached dead state.\n");
                printf("%s\n", curstr);
                break;
            }
        }
        printf("End of input\n");
    }
}
