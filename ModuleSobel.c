//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

FILE *fio,*fir;

int main() 
{
unsigned char chi;
int *io,*ir;
int nbg, somx, somy,mmax;
int sx[3][3] = {{-1,0,1},
				{-2,0,2},
				{-1,0,1}};
int sy[3][3] = {{1,2,1},
				{0,0,0},
				{-1,-2,-1}};
register long int i,j,l,k;
long int dimx,dimy,taille;
char entree[35],sortie[35],chaine[10];

printf("donner entree sans .pgm\n");//Brute et non ASCII
scanf("%s",entree);
strcat(entree,".pgm");

printf("donner sortie sans .pgm\n");
scanf("%s",sortie);
strcat(sortie,".pgm");

fio=fopen(entree,"rb");
fir=fopen(sortie,"wb+");

if(fio !=NULL) printf("ouverture du fichier in\n");
if(fir !=NULL) printf("ouverture du fichier out\n");

//lecture entete pgm
fscanf(fio,"%s\n",chaine);
fprintf(fir,"%s\n",chaine);

i=0;
while(i<1) 
{
	chi=fgetc(fio);
	fputc(chi,fir);
	if(chi=='\n') i++;
}

fscanf(fio,"%ld %ld\n",&dimx,&dimy);
fprintf(fir,"%ld %ld\n",dimx,dimy);

fscanf(fio,"%d\n",&nbg);
fprintf(fir,"%d\n",nbg);

printf("dimx=%d dimy=%d nbg=%d\n",(int)dimx, (int)dimy, (int)nbg);

//allocation dynamique de mémoire des images io et ir
io=(int *)malloc(dimx*dimy*sizeof(int));
ir=(int *)malloc(dimx*dimy*sizeof(int));
if(ir==NULL) printf("allocation ir impossible\n");

taille=dimx*dimy;
printf("taille=%ld\n",taille);

//lecture des pixels
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++) 
	{
		chi=(unsigned char)fgetc(fio);
		io[i*dimx+j]=(int)chi;
		ir[i*dimx+j]=0;
	}

///////////////////////////////////////////////////////////////////////////
//TRAITEMENT 
for(i=1;i<dimy-1;i++)
	for(j=1;j<dimx-1;j++)
	{
		somx=0;somy=0;
		for(l=-1;l<2;l++)
		for(k=-1;k<2;k++)
		{somx +=io[(i+l)*dimx+j+k]*sx[l+1][k+1];somy+=io[(i+l)*dimx+j+k]*sy[l+1][k+1];}
		ir[i*dimx+j]=abs(somx) + abs(somy);
	}

mmax=ir[0];
for(i=1;i<dimy-1;i++)
	for(j=1;j<dimx-1;j++)
		if(ir[i*dimx+j]>mmax) mmax = ir[i*dimx+j];
		
printf("Max = %d", mmax);

for(i=1;i<dimy-1;i++)
	for(j=1;j<dimx-1;j++)
		ir[i*dimx+j]=(int)(((long int)255*(long int)ir[i*dimx+j])/(long int)mmax);
		
//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////////////

 
//Sauvegarde de l image résultat dans le fichier fir
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		fputc((unsigned char)ir[i*dimx+j],fir);

//libération de de la mémoire des tableaux io et ir et fermeture des 2 fichiers fio et fir
free(io); free(ir);
fclose(fio); fclose(fir);
return 0;
}
