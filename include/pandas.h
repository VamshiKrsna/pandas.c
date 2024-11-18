#ifndef PANDAS_H
#define PANDAS_H

#define MAX_COLUMNS 100
#define MAX_ROWS 1000
#define MAX_COLUMN_NAME_LEN 50

typedef struct
{
    char column_names[MAX_COLUMNS][MAX_COLUMN_NAME_LEN];
    int data[MAX_ROWS][MAX_COLUMNS];
    int num_columns;
    int num_rows;
} DataFrame;

void init_dataframe(DataFrame *df, char column_names[][MAX_COLUMN_NAME_LEN], int num_columns);
void add_row(DataFrame *df, int row_data[]);
void print_dataframe(const DataFrame *df);
void select_column(const DataFrame *df, int column_index);
void filter_rows(const DataFrame *df, int column_index, int value);

#endif