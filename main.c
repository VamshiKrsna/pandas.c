#include <stdio.h>
#include "dataframe.h"

int main()
{
    DataFrame df;

    char column_names[3][MAX_COLUMN_NAME_LEN] = {"ID", "Age", "Score"};
    init_dataframe(&df, column_names, 3);

    int row1[] = {1, 20, 85};
    int row2[] = {2, 22, 90};
    int row3[] = {3, 20, 75};
    add_row(&df, row1);
    add_row(&df, row2);
    add_row(&df, row3);

    printf("DataFrame:\n");
    print_dataframe(&df);

    printf("\nSelecting 'Age' column:\n");
    select_column(&df, 1);

    printf("\nFiltering rows where 'Age' is 20:\n");
    filter_rows(&df, 1, 20);

    return 0;
}
