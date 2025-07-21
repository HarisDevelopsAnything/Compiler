#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to check if an element exists in an array
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
    char states[n]; // VLA - will work on most compilers but not standard C++
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
    int finstates[fins]; // VLA
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
            // Pass 'i' as the current filled size of finstates for checking duplicates
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
    char inputs[ins]; // Corrected size: should be 'ins' not 'n'
    for (int i = 0; i < ins; i++)
    {
        inputs[i] = (char)(i + 97);
    }
    int trans[n][ins]; // VLA
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
    if (str == NULL)
    { // Check for malloc failure
        fprintf(stderr, "Memory allocation failed for str.\n");
        return 1;
    }

    // Add an exit condition for the main loop
    printf("\nEnter 'exit' as string input to quit.\n");

    while (1)
    {
        while (1)
        {
            printf("Enter the string input for dfa (use only input symbols):");
            scanf("%s", str);

            if (strcmp(str, "exit") == 0)
            {          // Exit condition
                break; // Break inner loop, outer loop will handle exit
            }

            int flag = 1;
            for (int i = 0; i < strlen(str); i++)
            {
                // Better input validation: check against the actual 'inputs' array
                int is_valid_input_char = 0;
                for (int k = 0; k < ins; k++)
                {
                    if (str[i] == inputs[k])
                    {
                        is_valid_input_char = 1;
                        break;
                    }
                }
                if (!is_valid_input_char)
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
        { // Exit outer loop
            break;
        }

        int curst = start; // Initialize with the chosen start state, not hardcoded 0
        // char *curstr = (char *)malloc(sizeof(char) * 100); // This was problematic, removed for proper DFA logic
        // if (curstr == NULL) { /* handle error */ }
        // curstr[0] = '\0'; // Initialize empty string

        printf("Processing string \"%s\":\n", str);
        printf("Current state: %c\n", states[curst]);

        int reached_dead_state = 0; // Flag to track if a dead state is reached

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
            { // Should not happen if input validation is correct
                printf("Error: Invalid input symbol '%c' encountered. Skipping.\n", current_symbol);
                reached_dead_state = 1;
                break;
            }

            int next_state = trans[curst][input_idx];

            if (next_state != -1)
            {
                printf("  Reading '%c': Transition from %c to %c\n", current_symbol, states[curst], states[next_state]);
                curst = next_state;
                // The problematic logic about curstr and resetting was here. Removed it.
                // A DFA processes the entire string, not parts of it.
            }
            else // Reached a dead state
            {
                printf("  Reading '%c': Reached dead state from %c.\n", current_symbol, states[curst]);
                reached_dead_state = 1;
                break; // Stop processing further characters
            }
        }

        printf("End of input\n");

        if (reached_dead_state)
        {
            printf("String \"%s\" is **REJECTED** (reached dead state).\n", str);
        }
        else if (inArray(finstates, fins, curst)) // Check final state after entire string processed
        {
            printf("String \"%s\" is **ACCEPTED** (ends in final state %c).\n", str, states[curst]);
        }
        else
        {
            printf("String \"%s\" is **REJECTED** (ends in non-final state %c).\n", str, states[curst]);
        }
    }

    free(str); // Free allocated memory for 'str'

    return 0;
}