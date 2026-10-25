#include <stdio.h>

int main()
{
    int rows, col, i, j, k, totalAvailable=0, middle, distance;
    int count, start, found=0, check, seatRow;
    
    printf("Enter the number of rows: ");
    scanf("%d", &rows);

    printf("Enter the number of seats per row: ");
    scanf("%d", &col);

    int seats[rows][col];
    int availableSeats[rows];

    for (i=0; i<rows; i++)
    {
        for (j=0; j<col; j++)
        {
            printf("Enter the seat status (1=booked, 0=available) for seat [%d][%d]: ", i, j);
            scanf("%d", &seats[i][j]);

            if (seats[i][j] != 0 && seats[i][j] != 1)
            {
                printf("Invalid input\n");
                j--;
            }
        }
    }

    printf("\n\n");
    for (j=0; j<col; j++)
    {
        printf("\t%d ", j);
    }
    
    for (i=0; i<rows; i++)
    {
        printf("\n");
        printf("R%d\t", i);

        availableSeats[i] = 0;
        
        for (j=0; j<col; j++)
        {
            if (seats[i][j] == 1)
            {
                printf("X\t", i, j);
            }
            else
            {
                printf("_\t", i, j);
                availableSeats[i] = availableSeats[i] + 1;
                totalAvailable= totalAvailable + 1;
            }
        }
    }

    printf("\n\n\n");
    printf("Free seats per row: ");
    for (i=0; i<rows; i++)
    {
        printf("\t%d", availableSeats[i]);
    }
    printf("\nTotal free: %d\n", totalAvailable);

    printf("Enter the number of customers who want to sit together: ");
    scanf("%d", &k);

    if (k<=0 || k>col)
    {
        printf("Invalid number of customers\n");
        return 0;
    }
    
    middle = rows/2;

    for (distance=0; (distance<rows && found==0); distance++)
    {
        for (check=0; (check<2 && found==0); check++)
        {
            if (check == 0)
                seatRow = middle-distance;
            else
                seatRow = middle+distance;

            if (distance == 0 && check == 1)
                continue;

            if (seatRow >= 0 && seatRow<rows)
            {
                count=0;
                for (j=0; j<col; j++)
                {
                    if (seats[seatRow][j] == 0)
                    {
                        count++;
                        if (count==k)
                        {
                            start= (j-k)+1;
                            found=1;
                            break;
                        }
                    }
                    else
                        count=0;

                }
            }
        }
    }

    printf("\n\n");
    if (found==1)
    {
        for (j=start; j<start+k; j++)
        {
            seats[seatRow][j] = 1;
        }

        printf("Group of %d seated in Row %d, Seats %d to %d\n", k, seatRow, start, start+k-1);

        for (j=0; j<col; j++)
            printf("\t%d", j);

        for (i=0; i<rows; i++)
        {
            printf("\nR%d\t", i);

            for (j=0; j<col; j++)
            {
                if (seats[i][j] == 1)
                    printf("X\t");
                else
                    printf("_\t");
            }
        }

        totalAvailable=0;

        for (i=0; i<rows; i++)
        {
            for (j=0; j<col; j++)
            {
                if (seats[i][j] == 0)
                    totalAvailable++;
            }
        }

        printf("\nRemaining free seats: %d\n", totalAvailable);
    }
    else
        printf("No consecutive seats available for %d customers\n", k);

    return 0;
}