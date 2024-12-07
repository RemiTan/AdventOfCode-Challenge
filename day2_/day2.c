#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 30

void printArray(int arr[], int length)
{
    printf("array: ");
    for (int i = 0; i < length; i++)
    {
        printf(" %d", arr[i]);
    }
    printf("\n");
}

int valid_list(int arr[], int length);
int* remove_nth_number(int arr[], int n, int length);

int main(int argc, const char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    int count_1 = 0;
    int count_2 = 0;
    char line[MAX_LINE_LENGTH];
    int numbers[MAX_LINE_LENGTH];

    while(fgets(line, sizeof(line), fp))
    {
        line[strcspn(line, "\n")] = 0;
        char *token = strtok(line, " ");

        int i = 0;

        while(token != NULL)
        {
            numbers[i] = atoi(token);
            i++;
            token = strtok(NULL, " ");
        }

        int length = i;
        if(valid_list(numbers, length))
        {
            count_1++;
            count_2++;
        }
        else
        {
            for(int j = 0; j < length; j++)
            {
                if (valid_list(remove_nth_number(numbers, j, length), length - 1))
                {
                    count_2++;
                    break;
                }
            }
        }
    }

    fclose(fp);

    printf("----PART 1-----\n");
    printf("Answer: %d\n", count_1);
    printf("----PART 2-----\n");
    printf("Answer: %d\n", count_2);
}


int valid_list(int arr[], int length)
{
    int diff = arr[1] - arr[0];
    for(int i = 0; i < length - 1; i++ )
    {
        int prev = arr[i];
        int next = arr[i+1];
        if (!(diff > 0 && next - prev > 0 && next - prev <= 3) &&
            !(diff < 0 && next - prev < 0 && next - prev >= -3))
        {
            return false;
        }
    }
    return true;
}

int* remove_nth_number(int arr[], int n, int length)
{
    int *new_numbers = malloc((length - 1) * sizeof(int));
    int j = 0;
    for (int i = 0; i < length; i++)
    {
        if(i==n) continue;

        new_numbers[j] = arr[i];
        j++;
    }
    return new_numbers;
}

