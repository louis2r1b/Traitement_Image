//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//FILE *fio,*fir;

int arrondi(double x){
	if(x>0.0) return (int)(x+0.5);
	else return (int)(x-O.5);}
	
double g(double alpha, double x){
	double res;
	return 1.0/(1.0+(alpha*x*alpha*x));

int main() 
{
unsigned char chi;
int tii[8]={0,-1,-1,-1,0,1,1,1};
int tji[8]={1,1,0,-1,-1,-1,0,1};
int ti[4]={0,-1,0,1};
int dd[8], d[4],i,j,k;
double alpha, som,somN;
int ir[100],io[100]={1,1,1,1,1,3,3,3,3,3,
					 1,8,1,1,3,3,3,3,3,3,
					 1,1,1,5,5,3,3,3,3,3,
					 1,1,5,5,5,5,3,3,3,3,
					 1,5,5,5,5,2,5,3,3,3,
					 5,5,5,5,5,5,5,5,3,3,
					 7,5,5,5,5,5,5,5,5,3,
					 7,7,7,5,5,5,5,9,9,9,
					 7,1,7,7,5,5,9,2,9,9,
					 7,7,7,7,7,9,9,9,9,9};

///////////////////////////////////////////////////////////////////
//TRAITEMENT				 

printf("\n Choisir un alpha :");
scanf("%lf", &alpha);

for(i=0;i<dimy;i++)
{
	printf("\n")
	for(j=0;i<dimx;j++)
		printf("%d", io[dimx*i+j]);
}

for(i=0;i<dimy;i++)
	for(j=0;i<dimx;j++)
		ir[i*dimx+j]=io[i*dimx+j]);
		
for(i=1;i<dimy-1;i++)
	for(j=1;i<dimx-1;j++)
	{
		for(k=0;k<4;k++) d[k]=io[(i+ti[k])*dimx+j+tj[k]] - io[i*dimx+j];
		som=0.0;
		for(k=0;k<4;k++) som+= g(alpha,fabs((double)d[k]));
		somN=0.0;
		for(k=0;k<4;k++)somN += (double)d[k]*g(alpha,fabs((double)d[k]));
		ir[i*dimx+j]+=arrondi(somN/som);
	}

printf("\n");

for(i=0;i<dimy;i++)
{
	printf("\n");
	for(j=0;j<dimx;j++)
	printf("%d", ir[i*dimx+j]);
}
return 0;

//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////////////

 
//Sauvegarde de l image résultat dans le fichier fir
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		fputc((unsigned char)irr[i*dimx+j],fir);

//libération de de la mémoire des tableaux io, ir... et fermeture des 2 fichiers fio et fir
free(io); free(ir); free(irxx); free(iryy); free(irr);
fclose(fio); fclose(fir);
return 0;
}
