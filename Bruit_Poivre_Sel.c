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
int nbg, pourcent;
register long int i,j, k;
long int dimx,dimy,taille, nbPix;
char entree[35],sortie[35],chaine[10];

printf("donner entree sans .pgm\n");//Brute et non ASCII
scanf("%s",entree);
strcat(entree,".pgm");

printf("donner sortie sans .pgm\n");
scanf("%s",sortie);
strcat(sortie,".pgm");

fio=fopen(entree,"rb");
fir=fopen(sortie,"wb+");

printf("Entrer un pourcentage :");
scanf("%d", &pourcent);

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

printf("dimx=%d dimy=%d nbg=%d\n",dimx,dimy,nbg);

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
		ir[i*dimx+j]=io[i*dimx+j];
	}


///////////////////////////////////////////////////////////////////////////
//TRAITEMENT 
nbPix=((long int)pourcent*taille)/(long int)100;

srand(time(NULL));
for (k=0;k<nbPix;k++) {
	i=rand()%dimy; 
	j=rand()%dimx;
	if(io[i*dimx+j]>127) ir[i*dimx+j]=0; //On met du blanc
	else ir[i*dimx+j]=255; //On met du noir
	}
	
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
