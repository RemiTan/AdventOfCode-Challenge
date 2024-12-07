#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COL 141
#define ROW 140

char GRID[ROW][COL];
const char *pattern_1 = "MAS";
const char *pattern_2 = "SAM";
int count = 0;

void check_valid_x_shape(int i, int j);

int main(int argc, const char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    char line[COL];
    int i_ = 0;
    while(fgets(line,sizeof(line),fp))
    {
        line[strcspn(line, "\n")] = 0;
        if(strcmp(line, "")==0) continue;
        for(int j = 0; line[j] != '\0'; j++)
        {
           GRID[i_][j] = line[j];
        }
        i_++;
    }
    fclose(fp);

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (GRID[i][j] == 'M' || GRID[i][j] == 'S')
            {
                check_valid_x_shape(i, j);
            }
        }
    }

    printf("count: %d\n", count);
}

int check_answer(char *s1, char *s2)
{
    if ((strcmp(s1, pattern_1) == 0 && strcmp(s2, pattern_1) == 0)
    || (strcmp(s1, pattern_2) == 0 && strcmp(s2, pattern_2) == 0)
    || (strcmp(s1, pattern_1) == 0 && strcmp(s2, pattern_2) == 0)
    || (strcmp(s1, pattern_2) == 0 && strcmp(s2, pattern_1) == 0))
    {
        return 1;
    }
    return 0;
}

void check_valid_x_shape(int i, int j)
{
    char *s1 = malloc(4);
    char *s2 = malloc(4);
    for(int k = 0; k < 4; k++)
    {
        s1[k] = GRID[i+k][j+k];
        s2[k] = GRID[i+k][j+2-k];
    }
    s1[3] = '\0';
    s2[3] = '\0';
    if(check_answer(s1, s2))
    {
        count++;
    }
    free(s1);
    free(s2);
}
