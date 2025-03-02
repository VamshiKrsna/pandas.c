#include <stdio.h>
#include "pandas.h"

int main()
{
    printf("Program starting...\n");

    DataFrame df = {0}; // Initialize all members to 0
    char column_names[3][MAX_COLUMN_NAME_LEN] = {"ID", "Age", "Score"};

    printf("Initializing DataFrame...\n");
    init_dataframe(&df, column_names, 3);

    printf("Adding test data...\n");
    int row1[] = {1, 20, 85};
    int row2[] = {2, 22, 90};
    int row3[] = {3, 20, 75};

    add_row(&df, row1);
    add_row(&df, row2);
    add_row(&df, row3);

    printf("\nFull DataFrame:\n");
    print_dataframe(&df);

    printf("\nAge column:\n");
    select_column(&df, 1);

    printf("\nFiltering by Age = 20:\n");
    filter_rows(&df, 1, 20);

    printf("\nTesting read_csv function...\n");
    DataFrame csv_df = {0};
    if (read_csv(&csv_df, "data.csv") == 0) {
        printf("\nData from CSV file:\n");
        print_dataframe(&csv_df);
    } else {
        printf("Failed to read CSV file\n");
    }

    printf("\nProgram completed successfully!\n");
    return 0;
}