#include <stdio.h>
#include <string.h>
#include "pandas.h"

void init_dataframe(DataFrame *df, char column_names[][MAX_COLUMN_NAME_LEN], int num_columns)
{
    df->num_columns = num_columns;
    df->num_rows = 0;
    for (int i = 0; i < num_columns; i++)
    {
        strncpy(df->column_names[i], column_names[i], MAX_COLUMN_NAME_LEN);
    }
}

void add_row(DataFrame *df, int row_data[])
{
    if (df->num_rows < MAX_ROWS)
    {
        for (int i = 0; i < df->num_columns; i++)
        {
            df->data[df->num_rows][i] = row_data[i];
        }
        df->num_rows++;
    }
    else
    {
        printf("DataFrame is full. Cannot add more rows.\n");
    }
}

void print_dataframe(const DataFrame *df)
{
    for (int i = 0; i < df->num_columns; i++)
    {
        printf("%-10s ", df->column_names[i]);
    }
    printf("\n");

    for (int i = 0; i < df->num_rows; i++)
    {
        for (int j = 0; j < df->num_columns; j++)
        {
            printf("%-10d ", df->data[i][j]);
        }
        printf("\n");
    }
}

void select_column(const DataFrame *df, int column_index)
{
    if (column_index < 0 || column_index >= df->num_columns)
    {
        printf("Invalid column index\n");
        return;
    }

    printf("Column: %s\n", df->column_names[column_index]);
    for (int i = 0; i < df->num_rows; i++)
    {
        printf("%d\n", df->data[i][column_index]);
    }
}

void filter_rows(const DataFrame *df, int column_index, int value)
{
    if (column_index < 0 || column_index >= df->num_columns)
    {
        printf("Invalid column index\n");
        return;
    }

    printf("Rows where %s == %d:\n", df->column_names[column_index], value);
    for (int i = 0; i < df->num_rows; i++)
    {
        if (df->data[i][column_index] == value)
        {
            for (int j = 0; j < df->num_columns; j++)
            {
                printf("%-10d ", df->data[i][j]);
            }
            printf("\n");
        }
    }
}

int read_csv(DataFrame* df, const char *filename){
    FILE *file = fopen(filename, "r");
    if (!file){
        printf("Could not open file : %s",filename);
        return -1;
    }
    char line[1024]; // Max 1024 lines of CSV 
    int row = 0;

    if (fgets(line, sizeof(line), file)){
        char* token = strtok(line,","); // tokenize line based on ,
        while (token && df->num_columns < MAX_COLUMNS){
            strncpy(df->column_names[df->num_columns++], token, MAX_COLUMN_NAME_LEN);
            token = strtok(NULL, ",");
        }
    }
    while (fgets(line, sizeof(line), file) && df->num_rows < MAX_ROWS){
        int col = 0;
        char* token = strtok(line, ",");
        while(token && col < df->num_columns){
            df->data[df->num_rows][col++] = atoi(token);
            token = strtok(NULL, ",");
        }
        df->num_rows++;
    }
    fclose(file);
    return 0;
}

void head(const DataFrame* df, int n){
    if (n > df->num_rows){
        n = df->num_rows;
    }
    for (int i = 0; i < df->num_columns; i++){
        printf("%-10s ",df->column_names[i]);
    }
}

