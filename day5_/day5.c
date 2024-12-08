#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 1000
#define MAX_LINE 1000
#define MAX_VALUE_LIST 100

void printArray(int array[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d, ", array[i]);
    }
    printf("\n");
}


typedef struct
{
    int key;
    int value[MAX_VALUE_LIST];
    int n;
} KeyValue;

KeyValue DICT[MAX_ITEMS];
int number_of_items = 0;

int checkIfKeyExists(int key);
void printKeyValue(void);
int checkIfInValueList(int value, int key);

int main(int argc, const char *argv[])
{
    FILE *fp = fopen(argv[1], "r");
    char line[MAX_LINE];
    int key;
    int value;
    int count_1 = 0;
    int count_2 = 0;

    while (fscanf(fp, "%d|%d", &value, &key) == 2)
    {
        printf("%d|%d\n", key, value);
        int key_index = checkIfKeyExists(key);
        if (key_index >= 0)
        {
            KeyValue *key_value = &DICT[key_index];
            key_value->value[key_value->n] = value;
            key_value->n = key_value->n + 1;
        }
        else
        {
            KeyValue new_item;
            new_item.key = key;
            new_item.value[0] = value;
            new_item.n = 1;

            DICT[number_of_items] = new_item;
            number_of_items++;
        }
    }
    printKeyValue();

    while(fgets(line,sizeof(line),fp))
    {
        if (strcmp(line, "\n") == 0) continue;

        char *token = strtok(line, ",");

        int array[MAX_VALUE_LIST];
        int length = 0;
        while(token != NULL)
        {
            int number = atoi(token);
            array[length] = number;
            length++;
            token = strtok(NULL, ",");
        }

        int valid = 1;
        for (int j = length - 2; j >= 0; j--)
        {
             for (int i = j; i < length-1; i++)
             {
                if(checkIfInValueList(array[i+1], array[j]))
                {
                    valid = 0;
                    break;
                }
             }
        }

        if(valid){
            printArray(array, length);
            count_1 += array[(length)/2];
        }
    }
    printf("Answer: %d\n", count_1);
}

int checkIfKeyExists(int key)
{
    if (number_of_items == 0)
        return -1;

    for (int i = 0; i < number_of_items; i++)
    {
        if (DICT[i].key == key)
            return i;
    }
    return -1;
}

void printKeyValue(void)
{
    for (int i = 0; i < number_of_items; i++)
    {
        KeyValue key_value = DICT[i];
        printf("key: %d, n: %d, ", key_value.key, key_value.n);
        printf("value: [");
        for (int j = 0; j < key_value.n; j++)
        {
            printf(" %d,", key_value.value[j]);
        }
        printf("]\n");
    }
}

int checkIfInValueList(int value, int key)
{
    int index = checkIfKeyExists(key);
    if(index==-1) return 0;
    KeyValue key_value = DICT[index];
    for(int i = 0; i < key_value.n; i++)
    {
        if (value == key_value.value[i]) return 1;
    }
    return 0;
}
