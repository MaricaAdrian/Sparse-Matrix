#include <stdio.h>
#include <stdlib.h>

struct matrix {

    int rows;
    int columns;
    int assigned;
    float values[100][100];
    float detailed[3][1000];
    unsigned int detail_size;
    unsigned int sparse;
    unsigned int density;
    unsigned int sparsity;
    struct matrix *nextMatrix;



}matrix;



void add_matrix (struct matrix *matrix, int rows, int columns) {


    struct matrix *iterator = matrix;

    while(iterator->nextMatrix != NULL)
        iterator = iterator->nextMatrix;

    struct matrix *newMatrix = malloc(sizeof ( struct matrix));
    iterator->nextMatrix = newMatrix;
    newMatrix->nextMatrix = NULL;
    newMatrix->rows = rows;
    newMatrix->columns = columns;
    newMatrix->assigned = 0;
    newMatrix->density = 0;
    newMatrix->sparsity = 0;
    add_matrix_values (newMatrix);

    newMatrix->assigned = 1;
}



void add_random_matrix (struct matrix *matrix, int rows, int columns) {

    int random;
    unsigned int i, j, counter;
    struct matrix *iterator = matrix;

    while(iterator->nextMatrix != NULL)
        iterator = iterator->nextMatrix;

    struct matrix *newMatrix = malloc(sizeof ( struct matrix));
    iterator->nextMatrix = newMatrix;
    newMatrix->nextMatrix = NULL;
    newMatrix->rows = rows;
    newMatrix->columns = columns;
    newMatrix->assigned = 0;
    newMatrix->density = 0;
    newMatrix->sparsity = 0;

    for (i = 0; i < newMatrix->rows; i++)
        for (j = 0; j < newMatrix->columns; j++) {
            random = rand() % 100;
            if (random % 2 == 0)
                newMatrix->values[i][j] = random;
            else
                newMatrix->values[i][j] = 0;
        }

    counter = 0;
    for (i = 0; i < newMatrix->rows; i++)
        for (j = 0; j < newMatrix->columns; j++) {
            if(newMatrix->values[i][j] != 0 || newMatrix->values[i][j] < 0 || newMatrix->values[i][j] > 0) {
                newMatrix->detailed[0][counter] = i;
                newMatrix->detailed[1][counter] = j;
                newMatrix->detailed[2][counter] = newMatrix->values[i][j];
                counter++;
            }
        }
    newMatrix->density =  (100 * counter) / (newMatrix->rows * newMatrix->columns);
    newMatrix->sparsity = 100 - newMatrix->density;
    newMatrix->detail_size = counter;
    newMatrix->assigned = 1;

    printf("\nMatrix generated successfully.");

}

void add_matrix_values (struct matrix *matrix) {

    unsigned int i, j, counter;

    if(matrix->assigned == 1) {
        printf ("\nYou've already populated the matrix");
        return;
    }

    for (i = 0; i < matrix->rows; i++)
        for (j = 0; j < matrix->columns; j++) {
            printf ("\nMatrix[%d][%d] = ", i, j);
            scanf("%f", &matrix->values[i][j]);
        }

    counter = 0;
    for (i = 0; i < matrix->rows; i++)
        for (j = 0; j < matrix->columns; j++) {
            if(matrix->values[i][j] != 0 || matrix->values[i][j] < 0 || matrix->values[i][j] > 0) {
                matrix->detailed[0][counter] = i;
                matrix->detailed[1][counter] = j;
                matrix->detailed[2][counter] = matrix->values[i][j];
                counter++;
            }
        }
    matrix->density =  (100 * counter) / (matrix->rows * matrix->columns);
    matrix->sparsity = 100 - matrix->density;
    matrix->detail_size = counter;

}


void show_all_matrix (struct matrix *matrix) {

    unsigned int counter = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    struct matrix *iterator = matrix;
    while (iterator->nextMatrix != NULL) {
        counter++;
        printf ("\nMatrix No. %d\n", counter);
        for (i = 0; i < iterator->nextMatrix->rows; i++) {
            for (j = 0; j < iterator->nextMatrix->columns; j++) {
                printf ("%.1f ", iterator->nextMatrix->values[i][j]);
            }
            printf ("\n");
        }
        if(iterator->nextMatrix->density >= iterator->nextMatrix->sparsity)
            printf ("\nMatrix No. %d is not a sparse matrix.\tDensity: %d%%\tSparsity: %d%%", counter, iterator->nextMatrix->density, iterator->nextMatrix->sparsity);
        else
            printf ("\nMatrix No. %d is sparse matrix.\tSparsity: %d%%\tDensity: %d%%", counter, iterator->nextMatrix->sparsity, iterator->nextMatrix->density);
        iterator = iterator->nextMatrix;
        printf ("\n");
    }

}

void show_number(struct matrix *matrix, unsigned int number) {

    unsigned int i, j, counter = 0;
    struct matrix *iterator = matrix;

    if (number == 0) {
        printf ("\nThere is no matrix with number 0.");
        return;
    }


    while (iterator->nextMatrix != NULL) {
        counter++;
        if (counter == number) {
            printf ("\nMatrix No. %d\n", counter);
            for (i = 0; i < iterator->nextMatrix->rows; i++) {
                for (j = 0; j < iterator->nextMatrix->columns; j++) {
                    printf ("%.1f ", iterator->nextMatrix->values[i][j]);
                }
                printf ("\n");
            }
            printf ("\nRow: ");
            for (i = 0; i < iterator->nextMatrix->detail_size; i++)
                printf ("%.0f ", iterator->nextMatrix->detailed[0][i]);
            printf ("\nColumn: ");
            for (i = 0; i < iterator->nextMatrix->detail_size; i++)
                printf ("%.0f ", iterator->nextMatrix->detailed[1][i]);
            printf ("\nValue: ");
            for (i = 0; i < iterator->nextMatrix->detail_size; i++)
                printf ("%.1f ", iterator->nextMatrix->detailed[2][i]);
            if(iterator->nextMatrix->density >= iterator->nextMatrix->sparsity)
                printf ("\nMatrix No. %d is not a sparse matrix.\tDensity: %d%%\tSparsity: %d%%", counter, iterator->nextMatrix->density, iterator->nextMatrix->sparsity);
            else
                printf ("\nMatrix No. %d is sparse matrix.\tSparsity: %d%%\tDensity: %d%%", counter, iterator->nextMatrix->sparsity, iterator->nextMatrix->density);
            printf ("\n");
            return;
        }
        iterator = iterator->nextMatrix;
    }

    printf ("\nGiven matrix number was not found.");
    return;
}


void show_all_matrix_detailed (struct matrix *matrix) {

    unsigned int counter = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    struct matrix *iterator = matrix;
    while (iterator->nextMatrix != NULL) {
        counter++;
        printf ("\nMatrix No. %d\n", counter);
        for (i = 0; i < iterator->nextMatrix->rows; i++) {
            for (j = 0; j < iterator->nextMatrix->columns; j++) {
                printf ("%.1f ", iterator->nextMatrix->values[i][j]);
            }
            printf ("\n");
        }
        printf ("\nRow: ");
        for (i = 0; i < iterator->nextMatrix->detail_size; i++)
            printf ("%.0f ", iterator->nextMatrix->detailed[0][i]);
        printf ("\nColumn: ");
        for (i = 0; i < iterator->nextMatrix->detail_size; i++)
            printf ("%.0f ", iterator->nextMatrix->detailed[1][i]);
        printf ("\nValue: ");
        for (i = 0; i < iterator->nextMatrix->detail_size; i++)
            printf ("%.1f ", iterator->nextMatrix->detailed[2][i]);
        if(iterator->nextMatrix->density >= iterator->nextMatrix->sparsity)
            printf ("\nMatrix No. %d is not a sparse matrix.\tDensity: %d%%\tSparsity: %d%%", counter, iterator->nextMatrix->density, iterator->nextMatrix->sparsity);
        else
            printf ("\nMatrix No. %d is sparse matrix.\tSparsity: %d%%\tDensity: %d%%", counter, iterator->nextMatrix->sparsity, iterator->nextMatrix->density);
        iterator = iterator->nextMatrix;
        printf ("\n");
    }

}



int main() {

     unsigned int decision;
     unsigned int decision_2;
     unsigned int decision_3;
     struct matrix *matrix = malloc (sizeof (struct matrix));
     matrix->nextMatrix = NULL;
     srand(time(NULL));


     while(1) {
        printf("\n\n\tMenu");
        printf("\n1. Add a matrix.");
        printf("\n2. Print all matrix.");
        printf("\n3. Print all matrix detailed.");
        printf("\n4. Print a given matrix.");
        printf("\n5. Generate random matrix.");
        printf("\n6. Exit.");
        printf("\n\nChoose your option: ");
        scanf("%d", &decision);

        switch (decision) {

            case 1:
                printf ("\nEnter the number of rows: ");
                scanf ("%d", &decision_2);
                printf ("\nEnter the number of columns: ");
                scanf ("%d", &decision_3);
                add_matrix (matrix, decision_2, decision_3);
                break;
            case 2:
                printf ("\nPrinting all matrix...");
                show_all_matrix (matrix);
                break;
            case 3:
                printf ("\nPrinting all matrix detailed...");
                show_all_matrix_detailed (matrix);
                break;
            case 4:
                printf ("\nWhich matrix do you want to be printed: ");
                scanf ("%d", &decision_2);
                show_number (matrix, decision_2);
                break;
            case 5:
                printf ("\nEnter the number of rows: ");
                scanf ("%d", &decision_2);
                printf ("\nEnter the number of columns: ");
                scanf ("%d", &decision_3);
                add_random_matrix (matrix, decision_2, decision_3);
                break;
            case 6:
                return 0;
                break;
        }


     }


}
