//copyright Michel Chapron ENSEA Cergy-Pontoise
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *fio,*fir;

int main() 
{
unsigned char chi;
int *ior,*iov,*iob,*irr,*irv,*irb;
long int k=3,s=1,nbg;
long int i,j,dimx,dimy,taille;
char entree[35],sortie[35],chaine[10];

printf("donner entree sans .ppm\n");
scanf("%s",entree);
strcat(entree,".ppm");

printf("donner sortie sans .ppm\n");
scanf("%s",sortie);
strcat(sortie,".ppm");

fio=fopen(entree,"rb");
fir=fopen(sortie,"wb+");

if(fio !=NULL) printf("ouverture du fichier in\n");
if(fir !=NULL) printf("ouverture du fichier out\n");

//lecture entete ppm
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

ior=(int *)malloc(dimx*dimy*sizeof(int));
iov=(int *)malloc(dimx*dimy*sizeof(int));
iob=(int *)malloc(dimx*dimy*sizeof(int));

irr=(int *)malloc(dimx*dimy*sizeof(int));
irv=(int *)malloc(dimx*dimy*sizeof(int));
irb=(int *)malloc(dimx*dimy*sizeof(int));

if(irb==NULL) printf("allocation iob impossible\n");

taille=dimx*dimy;
printf("taille=%ld\n",taille);

//lecture des pixels
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)	
	{
		chi=(unsigned char)fgetc(fio);
		ior[i*dimx+j]=(int)chi;
		chi=(unsigned char)fgetc(fio);
		iov[i*dimx+j]=(int)chi;
		chi=(unsigned char)fgetc(fio);
		iob[i*dimx+j]=(int)chi;
	}


///////////////////////////////////////////////////////////////////////////
//TRAITEMENT 
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++) 
	{
		irr[i*dimx+j]=255-ior[i*dimx+j];
		irv[i*dimx+j]=255-iov[i*dimx+j];
		irb[i*dimx+j]=255-iob[i*dimx+j];
	}
	
//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////////////

//Sauvegarde des 3 tableaux rouge vert et bleu résultats dans le fichier fir
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++) 
	{
		fputc((unsigned char)irr[i*dimx+j],fir);
		fputc((unsigned char)irv[i*dimx+j],fir);
		fputc((unsigned char)irb[i*dimx+j],fir);
	}

//Libération des tableaux et fermeture des fichiers fio et fir
free(ior); free(iov); free(iob);
free(irr); free(irv); free(irb);
fclose(fio); fclose(fir);
return 0;
}
