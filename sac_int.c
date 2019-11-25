#include<stdlib.h>
#include<stdio.h>

#define MAX 1000

/* 
	@param a	: premier entier
	@param b	: deuxieme entier
	@return 	: le plus grand entre a et b
	
*/
int max(int a, int b) {
	return (a > b) ? a : b;
}

//===================================================================

/* 
	@param M 		: la capacite du sac a dos
	@param n 		: nombre d'elements
	@param value[]	: table des valeurs de n elements
	@param weight[]	: table des poids des n elements
	@return 		: La valeur total des elements dans le sac a dos
*/
int sacados(int M, int n, int value[], int weight[])
{
    int K[n+1][M+1];

	for (int i=0; i<=n; i++) {
		for (int j=0; j<=M; j++) {
			if (i == 0 || j == 0) {
				// remplir la premiere ligne et la premiere colonne avec des 0
				K[i][j] = 0;
			} else if (weight[i-1] > j) {
				// premiere equation de reccurence 
				K[i][j] = K[i-1][j];
			} else {
				// deuxieme equation de reccurence 
				K[i][j] = max(value[i-1] + K[i-1][j - weight[i-1]], K[i-1][j]);
			}
		}
	}
	printf("=============La matrice :============= \n");
	for (int i = 0; i <= n; ++i)
	{
		for (int j = 0; j <= M; ++j)
		{
			// affichage des elements de la matrice génrée
			printf("%d\t", K[i][j]);
		}
		printf("\n");
	}

	// tableau qui permet d'avoir les elements pris
	int x[n];
	int c = n, w = M;
	while(c>0 && w>0)
    {
        if (K[c][w]== K[c-1][w]){
        	// meme poids donc element non pris
            x[c-1]= 0;
        }else{
        	// poids a changé donc element pris
        	x[c-1] = 1;
            w = w - weight[c-1];
        }
        c--;
    }
    printf("=============Les elements pris :============= \n");
    for(int j=0;j<n;j++)
    {
        if(x[j]==1)
            {
            	// si la valeur dans la table des elements == 1 donc l'element est pris 
                printf("object numero %d est dans le sac w %d: v :%d  \n",j+1, weight[j], value[j]);
            }
    }

	return K[n][M];

}
int main()
{
    // table des valeurs
	int value[MAX] = {60, 120, 90, 100};
	// table des poids
	int weight[MAX] = {10, 30, 48, 20};
	// capacite maximale du tableau
	int M = 99;
	// nombre d'elements dans le tableau
	int n=4;
	// appel de la fonction sacados qui retourne la valeur des elements dans le sac a dos
	printf("La valeur des elements pris :  %d\n", sacados(M, n, value, weight));
    return EXIT_SUCCESS;
}