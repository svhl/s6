// dvr

#include <stdio.h>

void main()
{
	int nodes, updated, costmatrix[10][10], distance[10][10], nexthop[10][10];
	printf("Enter no. of nodes: ");
	scanf("%d", &nodes);
	printf("Enter cost matrix (-1 for infinity):\n");

	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			scanf("%d", &costmatrix[i][j]);
	
			if (i == j)
			{
				costmatrix[i][j] = 0;
			}

			if (costmatrix[i][j] == -1)
			{
				costmatrix[i][j] = 9999;
				nexthop[i][j] = -1;
			}

			else
			{
				nexthop[i][j] = j;
			}

			distance[i][j] = costmatrix[i][j];
		}
	}

	do
	{
		updated = 0;

		for (int i = 0; i < nodes; i++)
		{
			for (int j = 0; j < nodes; j++)
			{
				for (int k = 0; k < nodes; k++)
				{
					if (distance[i][k] > costmatrix[i][j] + distance[j][k])
					{
						distance[i][k] = costmatrix[i][j] + distance[j][k];
						nexthop[i][k] = nexthop[i][j];
						updated = 1;
					}
				}
			}
		}
	} while (updated);

	printf("\nRouting tables:\n");

	for (int i = 0; i < nodes; i++)
	{
		printf("Router %d:\n", i);
		printf("Destination\tCost\tNext Hop\n");
		
		for (int j = 0; j < nodes; j++)
		{
			if (nexthop[i][j]==j)
			{
				printf("%d\t\t%d\t-\n", j, distance[i][j]);
			}
	
			else
			{
				printf("%d\t\t%d\t%d\n", j, distance[i][j], nexthop[i][j]);
			}
		}

		printf("\n");
	}
}
