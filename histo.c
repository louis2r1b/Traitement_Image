//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *fio,*fir;

int main() 
{
unsigned char chi;
int *io,*ir;
int nbg, LUT[256];
register long int i,j;
long int dimx,dimy,taille, dimhx, dimhy;
char entree[35],sortie[35],chaine[10];

dimhx = 256;
dimhy = 144;

printf("donner entree sans .pgm\n");
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
fprintf(fir,"%ld %ld\n",dimhx,dimhy);

fscanf(fio,"%d\n",&nbg);
fprintf(fir,"%d\n",nbg);

//allocation dynamique de mémoire des images io et ir
io=(int *)malloc(dimx*dimy*sizeof(int));
ir=(int *)malloc(dimhx*dimhy*sizeof(int));
if(ir==NULL) printf("allocation ir impossible\n");


taille=dimx*dimy;
printf("taille=%ld\n",taille);

//lecture des pixels
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++) 
	{
		chi=(unsigned char)fgetc(fio);
		io[i*dimx+j]=(int)chi;
	}

///////////////////////////////////////////////////////////////////
//TRAITEMENT
//Construction d'un l'histogramme (144px x 256px)

long int hist[256], nmax; //On définit des varariable en longint car ces entiers peuvent être grand


//Constitution de l'histogramme

//pas besoin d'accolades (=création d'un block) avec 1 seul instruction (mais oui pour 2) 
for(i=0;i<256;i++) hist[i]=0; //On met à 0 notre liste hist

for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++) //On parcours toute l'image
		hist[io[i*dimx+j]]++;   // l'indice (i*larg+i) corresponds à la place du pixel (i,j) 
// dans le fichier 1D.

for (i=0; i<256; i++)
	LUT[i] = hist[i] 
	
for(j=0; j<256;j++){ //Remplissage
	for (i=0;i<144 - LUT[j] ; i++)
		ir[i*256+j] = 0;
	for (i=143 - LUT[j];i<144 ; i++)
		ir[i*256+j] = 255;
} //accollades car 2 instructions

//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////

//Sauvegarde de l image résultat dans le fichier fir
for(i=0;i<dimhy;i++)
	for(j=0;j<dimhx;j++)
		fputc((unsigned char)ir[i*dimhx+j],fir);

//libération de de la mémoire des tableaux io et ir et fermeture des 2 fichiers fio et fir
free(io); free(ir);
fclose(fio); fclose(fir);
return 0;
}
