#include <stdio.h>

int divisorsSum(int num)
{
    int i, sum=0;

    for (i=1; i <= num/2; i++)
    {
        if (num%i == 0)
            sum = sum+i;
    }
    return sum;
}

int main()
{
    int n, i, sum, totalPairs=0;

    printf("Enter n: ");
    scanf("%d", &n);

    for (i=2; i <= n; i++)
    {
        sum= divisorsSum(i);

        if (sum>i && sum <= n)
        {
            if (divisorsSum(sum) == i)
            {
                printf("(%d, %d)\n", i, sum);
                totalPairs++;
            }
        }
    }

    if (totalPairs == 0)
        printf("No amicable pairs found\n");

    printf("Total pairs: %d\n", totalPairs);

    return 0;
}
