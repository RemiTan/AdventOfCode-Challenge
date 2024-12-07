#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define COL 141
#define ROW 140
#define MAX_LIST_PAIR 10000

typedef struct
{
    int x;
    int y;
}
point;

typedef struct
{
    point first;
    point second;
}
pair;

char GRID[ROW][COL];
pair COMBINAISON[MAX_LIST_PAIR];
int number_of_pair = 0;
const char *pattern_1 = "XMAS";
const char *pattern_2 = "SAMX";

void check_right(int i, int j);
void check_down(int i, int j);
void check_right_diag(int i, int j);
void check_left_diag(int i, int j);
void createPairsAndDoSomeStuff(int x1, int y1, int x2, int y2);

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
            if (GRID[i][j] == 'X' || GRID[i][j] == 'S')
            {
                check_right(i, j);
                check_down(i, j);
                check_right_diag(i,j);
                check_left_diag(i,j);
            }
        }
    }

    printf("count: %d\n", number_of_pair);
}

int check_answer(char *s)
{
    if ((strcmp(s, pattern_1) == 0) | (strcmp(s, pattern_2) == 0))
    {
        return 1;
    }
    return 0;
}

void check_right(int i, int j)
{
    char *s = malloc(5);
    for(int k = 0; k < 4; k++)
    {
        s[k] = GRID[i][j+k];
    }
    s[4] = '\0';
    if(check_answer(s))
    {
        createPairsAndDoSomeStuff(j, i, j+3, i);
    }
    free(s);
}

void check_down(int i, int j)
{
    char *s = malloc(5);
    for(int k = 0; k < 4; k++)
    {
        s[k] = GRID[i+k][j];
    }
    s[4] = '\0';
    if(check_answer(s))
    {
        createPairsAndDoSomeStuff(j, i, j, i+3);
    }
    free(s);
}

void check_right_diag(int i, int j)
{
    char *s = malloc(5);
    for(int k = 0; k < 4; k++)
    {
        s[k] = GRID[i+k][j+k];
    }
    s[4] = '\0';
    if(check_answer(s))
    {
        createPairsAndDoSomeStuff(j, i, j+3, i+3);
    }
    free(s);
}

void check_left_diag(int i, int j)
{
    char *s = malloc(5);
    for(int k = 0; k < 4; k++)
    {
        s[k] = GRID[i+k][j-k];
    }
    s[4] = '\0';
    if(check_answer(s))
    {
        createPairsAndDoSomeStuff(j, i, j-3, i+3);
    }
    free(s);
}

int IsEqualPoint(point *a, point *b)
{
    if(a->x == b->x && a->y == b->y) return 1;
    return 0;
}

int IsEqualPair(pair *a, pair *b)
{
    if((IsEqualPoint(&a->first, &b->first) && (IsEqualPoint(&a->second, &b->second)))) return 1;

    return 0;
}

int checkIfCombinationExists(pair input_pair)
{
    if(!number_of_pair) return 0;
    for (int i = 0; i < number_of_pair; i++)
    {
        if (IsEqualPair(&input_pair, &COMBINAISON[i])) return 1;
    }
    return 0;
}

void createPairsAndDoSomeStuff(int x1, int y1, int x2, int y2)
{
        point point1;
        point1.x = x1;
        point1.y = y1;

        point point2;
        point2.x = x2;
        point2.y = y2;

        pair new_pair;
        new_pair.first = point1;
        new_pair.second = point2;
        if (!checkIfCombinationExists(new_pair))
        {
            COMBINAISON[number_of_pair] = new_pair;
            number_of_pair++;
        }
}
