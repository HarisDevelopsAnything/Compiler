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
    int n, ins, start, fins, cur_start = 0;
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
            if (!inArray(finstates, i, ci) && ci >= 0 && ci < n)
            {
                finstates[i] = ci;
                break;
            }
            printf("Entered state is invalid/already a final state!\n");
        }
    }
    printf("Start state = %c, Final states:\n", states[start]); // Use 'start'
    for (int i = 0; i < fins; i++)
    {
        printf("%c\n", (char)(finstates[i] + 65));
    }
    printf("Enter the no. of inputs: ");
    scanf("%d", &ins);
    char inputs[ins];
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
    printf("\nEnter 'exit' as string input to quit.\n");
    while (1)
    {
        while (1)
        {
            printf("Enter the string input for dfa (use only input symbols):");
            scanf("%s", str);
            if (strcmp(str, "exit") == 0)
            {
                break;
            }
            int flag = 1;
            for (int i = 0; i < strlen(str); i++)
            {
                // Better input validation: check against the actual 'inputs' array
                int inpvalid = 0;
                for (int k = 0; k < ins; k++)
                {
                    if (str[i] == inputs[k])
                    {
                        inpvalid = 1;
                        break;
                    }
                }
                if (!inpvalid)
                {
                    printf("The given input contains invalid characters. Retry\n");
                    flag = 0;
                    break;
                }
            }
            if (flag)
                break;
        }

        if (strcmp(str, "exit") == 0)
        {
            break;
        }

        int curst = start;

        printf("Processing string \"%s\":\n", str);
        printf("Current state: %c\n", states[curst]);

        int reached_dead_state = 0;

        for (int i = 0; i < strlen(str); i++)
        {
            char current_symbol = str[i];
            int input_idx = -1;
            for (int k = 0; k < ins; k++)
            {
                if (inputs[k] == current_symbol)
                {
                    input_idx = k;
                    break;
                }
            }

            if (input_idx == -1)
            {
                printf("Error: Invalid input symbol '%c' encountered. Skipping.\n", current_symbol);
                reached_dead_state = 1;
                break;
            }

            int next_state = trans[curst][input_idx];

            if (next_state != -1)
            {
                if (inArray(finstates, fins, curst) && !inArray(finstates, fins, next_state))
                {
                    printf("Tokenised: ");
                    for (int k = cur_start; k < i; k++)
                    {
                        printf("%c", str[k]);
                    }
                    printf("\n");
                    curst = 0;
                    cur_start = i;
                }
                else
                {
                    printf("  Reading '%c': Transition from %c to %c\n", current_symbol, states[curst], states[next_state]);
                    curst = next_state;
                }
            }
            else
            {
                if (inArray(finstates, fins, curst))
                {
                    printf("Tokenised: ");
                    for (int k = cur_start; k < i; k++)
                    {
                        printf("%c", str[k]);
                    }
                    printf("\n");
                    curst = 0;
                    cur_start = i;
                }
                printf("  Reading '%c': Reached dead state from %c.\n", current_symbol, states[curst]);
                reached_dead_state = 1;
                break;
            }
        }

        printf("End of input\n");
        cur_start = 0;
        if (reached_dead_state)
        {
            printf("String %s is REJECTED (reached dead state).\n", str);
        }
        else if (inArray(finstates, fins, curst))
        {
            printf("String %s is ACCEPTED (ends in final state %c).\n", str, states[curst]);
        }
        else
        {
            printf("String %s is REJECTED (ends in non-final state %c).\n", str, states[curst]);
        }
    }
    return 0;
}