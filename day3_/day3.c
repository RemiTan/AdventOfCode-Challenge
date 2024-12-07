#include <regex.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 100000

int extractNumberFromMatches(regmatch_t match, char input[]);
void get_expression(char* line, char* expression);

int main(int argc, const char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    int count_1 = 0;
    int count_2 = 0;
    int DO = 1;

    regex_t regex_mul;
    regmatch_t matches[3];
    int reti_mul;

    reti_mul = regcomp(&regex_mul,"^mul\\(([0-9]+),([0-9]+)\\)$", REG_EXTENDED);

    regex_t regex_do;
    int reti_do;

    reti_do = regcomp(&regex_do,"^do\\(\\)$", REG_EXTENDED);

    regex_t regex_dont;
    int reti_dont;

    reti_dont = regcomp(&regex_dont,"^don't\\(\\)$", REG_EXTENDED);

    if (reti_mul | reti_do | reti_dont)
    {
        printf("Error regex\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char expression[MAX_LINE_LENGTH];

    while(fgets(line, sizeof(line), fp))
    {
        for(int i = 0; line[i]!='\0'; i++)
        {
            if (line[i] == 'm')
            {
                get_expression(&line[i], expression);
                reti_mul = regexec(&regex_mul, expression, 3, matches, 0);
                if (!reti_mul)
                {
                    int number1 = extractNumberFromMatches(matches[1], expression);
                    int number2 = extractNumberFromMatches(matches[2], expression);
                    count_1 += number1 * number2;
                    if (DO){
                        count_2 += number1 * number2;
                    }
                }
            }
            else if (line[i] == 'd')
            {
                get_expression(&line[i], expression);
                reti_do = regexec(&regex_do, expression, 0, NULL, 0);
                if (!reti_do){
                    DO = 1;
                }
                reti_dont = regexec(&regex_dont, expression, 0, NULL, 0);
                if (!reti_dont){
                    DO = 0;
                }
            }
        }
    }
    printf("----PART1-----\n");
    printf("count: %d\n", count_1);
    printf("----PART2-----\n");
    printf("count: %d\n", count_2);
}

int extractNumberFromMatches(regmatch_t match, char input[])
{
    int number = 0;
    if (match.rm_so != -1)
    {
        int length = match.rm_eo - match.rm_so;
        char *str_number = malloc(length + 1);
        if(str_number){
            strncpy(str_number, input + match.rm_so, length);
            str_number[length] = '\0';
            number = atoi(str_number);
            free(str_number);
        }
    }
    return number;
}

void get_expression(char* line, char* expression)
{
    int k = 0;
    int j = 0;
    while (line[k] != '\0' && line[k] != ')')
    {
        expression[j] = line[k];
        j++;
        k++;
    }
    expression[j] = ')';
    expression[j + 1] = '\0';
}
