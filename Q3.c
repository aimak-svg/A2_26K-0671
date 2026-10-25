#include <stdio.h>

void inputReadings(int sensor, int hour, int temp[sensor][hour])
{
    int i, j;

    for (i=0; i<sensor; i++)
    {
        printf("\nEnter readings for sensor %d: \n", i+1);
        for (j=0; j<hour; j++)
        {
            printf("Enter reading for hour %d: ", j+1);
            scanf("%d", &temp[i][j]);
        }
        printf("\n");
    }
}
float analyze(int readings[], int hours, int sensorNumber)
{
    int i, total=0, max, min, critical=0, warning=0, streak=0, longest=0;
    float avg;

    max=readings[0];
    min=readings[0];

    for (i=0; i<hours; i++)
    {
        total = total+readings[i];

        if (readings[i]>max)
            max = readings[i];


        if (readings[i]<min)
            min = readings[i];

        if (readings[i] >= 40)
            critical++;

        if (readings[i] >= 35 && readings[i] <= 39)
            warning++;

        if (readings[i] >= 35)
        {
            streak++;
            if (streak>longest)
                longest=streak;
        }
        else
            streak=0;

    }

    avg = (float) total/hours;

    printf("\nSensor %d: Total=%d  Avg=%.2f  Max=%d  Min=%d\n", sensorNumber, total, avg, max, min);
    printf("\t  Critical=%d  Warning=%d  Longest hot streak=%d\n", critical, warning, longest);

    return avg;
}

int highestAverage(int sensor, float averages[])
{
    int i, highestSensor=0;

    for (i=1; i<sensor; i++)
    {
        if (averages[i] > averages[highestSensor])
            highestSensor=i;
    }

    return highestSensor;
}

int main()
{
    int i, j, hour, sensor, highestSensor;

    printf("Enter the number of sensors: ");
    scanf("%d", &sensor);

    printf("Enter the number of hourly readings: ");
    scanf("%d", &hour);

    int temp[sensor][hour];
    float averages[sensor];

    inputReadings(sensor, hour, temp);

    for (i=0; i<sensor; i++)
    {
        averages[i] = analyze(temp[i], hour, i+1);
    }

   highestSensor = highestAverage(sensor, averages);

    printf("\nHighest average: Sensor %d (%.2f)\n", highestSensor+1, averages[highestSensor]);

    return 0;
}