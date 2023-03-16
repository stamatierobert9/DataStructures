#include <stdio.h>
#include <stdlib.h>

int main()
{
	int** x;
    int *a;
    int *b;
    int n, m, y, aux = 0;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &y);
    a = malloc(y * sizeof(int));
    b = malloc(y * sizeof(int));
    for(int i = 0; i < y; i++)
        {scanf("%d", &a[i]);
        scanf("%d", &b[i]);
        }
    x = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++){
        x[i] = calloc(m, sizeof(int));
    }
    while(aux < y){
    for(int i = 0; i <= a[aux]; i++)
        for(int j = 0; j <= b[aux]; j++)
        {
            x[i][j]++;
        }
    aux++;
    }
    
    for(int i = 0; i < n; i++)
        {for(int j = 0; j < m; j++)
            printf("%d", x[i][j]);
        printf("\n");}

	return 0;
}