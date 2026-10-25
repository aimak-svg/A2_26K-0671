#include <stdio.h>

int getValidDays()
{
    int days;

    printf("Enter the number of festival days (1-7): ");
    scanf("%d", &days);

    while (days<1 || days>7)
    {
        printf("Invalid input. Enter a value between 1 and 7: ");
        scanf("%d", &days);
    }

    return days;
}

float calculateDailySales(int dayNumber)
{
    int orders, i;
    float total=0, amount, avg, highest;

    printf("\nEnter number of orders for Day %d: ", dayNumber);
    scanf("%d", &orders);

    while (orders<1)
    {
        printf("invalid input. Enter atleast one order: ");
        scanf("%d", &orders);
    }

    highest=0;

    for (i=0; i<orders; i++)
    {
        printf("Enter amount for order %d: ", i+1);
        scanf("%f", &amount);

        while (amount <= 0)
        {
            printf("Invalid amount. Enter an amount greater than zero: ");
            scanf("%f", &amount);
        }

        total = total+amount;

        if (amount>highest)
            highest=amount;
    }

    avg = total/orders;

    printf("Total sales: Rs. %.2f\n", total);
    printf("Average order: Rs. %.2f\n", avg);
    printf("Highest order: Rs. %.2f\n", highest);

    return total;
}

int findHighestSalesDay(float dailySales[], int numberOfDays)
{
    int i, highestDay=0;

    for (i=1; i<numberOfDays; i++)
    {
        if (dailySales[i] > dailySales[highestDay])
            highestDay=i;
    }

    return highestDay;
}

void displayBarChart(float dailySales[], int numberOfDays)
{
    int i, j, count;

    printf("\n===== DAILY SALES BAR CHART =====\n");

    for (i=0; i<numberOfDays; i++)
    {
        printf("Day %d: ", i+1);

        count= dailySales[i]/100;

        for (j=0; j<count; j++)
        {
            printf("*");
        }
        printf("  (Rs. %.2f)\n", dailySales[i]);
    }
}

int main()
{
    int days, i, highestDay;
    float dailySales[7], festivalTotal=0;

    days=getValidDays();

    for (i=0; i<days; i++)
    {
        dailySales[i] = calculateDailySales(i+1);
        festivalTotal = festivalTotal + dailySales[i];
    }

    highestDay = findHighestSalesDay(dailySales, days);

    printf("\n===== FESTIVAL SUMMARY =====\n");
    printf("Total festival sales: Rs. %.2f\n", festivalTotal);
    printf("Day with highest sales: Day %d\n", highestDay+1);
    printf("Highest daily sales: Rs. %.2f\n", dailySales[highestDay]);

    displayBarChart(dailySales, days);

    return 0;
}