//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//Dilatation éclaircie une image en NG car on décale toutes les valeurs vers le max
//En binaire il supprime les zones noires

FILE *fio,*fir;

int main() 
{
unsigned char chi;
int *io,*ir;
int nbg, support;
register long int i,j,k,l,mmax;
long int dimx,dimy,taille;
char entree[35],sortie[35],chaine[10];

printf("donner entree sans .pgm\n");//Binaire et non ASCII
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
		ir[i*dimx+j]=io[i*dimx+j];
	}


///////////////////////////////////////////////////////////////////
//TRAITEMENT

printf("\n Donner le support : "); //Support doit être impair pour être symétrique p/R à i et j
scanf("%d",&support);

//Passage à zero et module inférieur au seuil (en niveaux de gris) => Pixel noir/On affiche rien
for (i=support/2; i<(dimy-support/2);i++)
	for(j=support/2;j<(dimx-support/2);j++)
	{
		mmax=io[i*dimx+j];
		for(l=(-support/2);l<=support/2;l++) //On viste le voisinnage du support 
			for(k=(-support/2);k<=(support/2);k++)
				if(io[(i+l)*dimx+j+k]>mmax) mmax=io[(i+l)*dimx+j+k]; //On maj max

		ir[i*dimx+j]=mmax;
			
	}
	
//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////
 
//Sauvegarde de l image résultat dans le fichier fir
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		fputc((unsigned char)ir[i*dimx+j],fir);

//libération de de la mémoire des tableaux io et ir et fermeture des 2 fichiers fio et fir
free(io); free(ir);
fclose(fio); fclose(fir);
return 0;
}
