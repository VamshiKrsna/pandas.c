#include <stdio.h>
#include <string.h>
#include "pandas.h"

void init_dataframe(DataFrame *df, char column_names[][MAX_COLUMN_NAME_LEN], int num_columns)
{
    if (num_columns > MAX_COLUMNS)
    {
        printf("Error: too many columns\n");
        return;
    }
    df->num_columns = num_columns;
    df->num_rows = 0;
    for (int i = 0; i < num_columns; i++)
    {
        strncpy(df->column_names[i], column_names[i], MAX_COLUMN_NAME_LEN - 1);
        df->column_names[i][MAX_COLUMN_NAME_LEN - 1] = '\0';
    }
}

void add_row(DataFrame *df, int row_data[])
{
    if (df->num_rows >= MAX_ROWS)
    {
        printf("Error: DataFrame is full\n");
        return;
    }
    for (int i = 0; i < df->num_columns; i++)
    {
        df->data[df->num_rows][i] = row_data[i];
    }
    df->num_rows++;
}

void print_dataframe(const DataFrame *df)
{
    // Print column names
    for (int i = 0; i < df->num_columns; i++)
    {
        printf("%-10s ", df->column_names[i]);
    }
    printf("\n");

    // Print data
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
        printf("Error: Invalid column index\n");
        return;
    }

    printf("Column %s:\n", df->column_names[column_index]);
    for (int i = 0; i < df->num_rows; i++)
    {
        printf("%d\n", df->data[i][column_index]);
    }
}

void filter_rows(const DataFrame *df, int column_index, int value)
{
    if (column_index < 0 || column_index >= df->num_columns)
    {
        printf("Error: Invalid column index\n");
        return;
    }

    printf("Rows where %s = %d:\n", df->column_names[column_index], value);
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

int read_csv(DataFrame* df, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", filename);
        return -1;
    }

    char line[1024];
    char *trimmed_token;
    int row = 0;

    // Read header row for column names
    if (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",\n\r");
        df->num_columns = 0;

        while (token && df->num_columns < MAX_COLUMNS) {
            // Remove leading/trailing whitespace
            while (*token == ' ' || *token == '\t') token++;
            trimmed_token = token;
            int len = strlen(trimmed_token);
            while (len > 0 && (trimmed_token[len-1] == ' ' || trimmed_token[len-1] == '\t')) {
                trimmed_token[--len] = '\0';
            }

            strncpy(df->column_names[df->num_columns], trimmed_token, MAX_COLUMN_NAME_LEN - 1);
            df->column_names[df->num_columns][MAX_COLUMN_NAME_LEN - 1] = '\0';
            df->num_columns++;
            token = strtok(NULL, ",\n\r");
        }
    } else {
        printf("Error: Empty CSV file\n");
        fclose(file);
        return -1;
    }

    // Read data rows
    df->num_rows = 0;
    while (fgets(line, sizeof(line), file) && df->num_rows < MAX_ROWS) {
        int col = 0;
        char *token = strtok(line, ",\n\r");

        while (token && col < df->num_columns) {
            // Remove leading/trailing whitespace
            while (*token == ' ' || *token == '\t') token++;
            trimmed_token = token;
            int len = strlen(trimmed_token);
            while (len > 0 && (trimmed_token[len-1] == ' ' || trimmed_token[len-1] == '\t')) {
                trimmed_token[--len] = '\0';
            }

            // Convert string to integer
            char *endptr;
            long val = strtol(trimmed_token, &endptr, 10);
            if (*endptr != '\0') {
                printf("Error: Invalid integer value '%s' at row %d, column %d\n", 
                       trimmed_token, df->num_rows + 1, col + 1);
                fclose(file);
                return -1;
            }
            df->data[df->num_rows][col++] = (int)val;
            token = strtok(NULL, ",\n\r");
        }

        if (col < df->num_columns) {
            printf("Error: Too few columns at row %d\n", df->num_rows + 1);
            fclose(file);
            return -1;
        }

        df->num_rows++;
    }

    fclose(file);
    return 0;
}
