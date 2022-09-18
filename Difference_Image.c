#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

FILE *fio1,*fio2,*fir;

int main() 
{
unsigned char chi1,chi2;
int *io1,*io2,*ir;

int nbg'zs;
register long int i,j;
long int dimx,dimy,taille;
char entree1[35],entree2[35],sortie[35],chaine[10];

printf("donner entree1 sans .pgm\n");
scanf("%s",entree1);
strcat(entree1,".pgm");

printf("donner entree2 sans .pgm\n");
scanf("%s",entree2);
strcat(entree2,".pgm");

printf("donner sortie  sans .pgm\n");
scanf("%s",sortie );
strcat(sortie ,".pgm");

fio1=fopen(entree1,"rb");
fio2=fopen(entree2,"rb");
fir =fopen(sortie,"wb+");

if(fio1 !=NULL) printf("ouverture du fichier 1 in\n");
if(fio2 !=NULL) printf("ouverture du fichier 2 in\n");
if(fir  !=NULL) printf("ouverture du fichier out\n");

//lecture entete pgm
fscanf(fio1,"%s\n",chaine);
fscanf(fio2,"%s\n",chaine);
fprintf(fir,"%s\n",chaine);

i=0;
while(i<1) 
{
	chi1=fgetc(fio1);
	chi2=fgetc(fio2);
	fputc(chi2,fir);
	if(chi2=='\n') i++;
}

fscanf(fio1,"%ld %ld\n",&dimx,&dimy);
fscanf(fio2,"%ld %ld\n",&dimx,&dimy);
fprintf(fir,"%ld %ld\n",dimx,dimy);

fscanf(fio1,"%d\n",&nbg);
fscanf(fio2,"%d\n",&nbg);
fprintf(fir,"%d\n",nbg);

printf("dimx=%d dimy=%d nbg=%d\n",(int)dimx,(int)dimy,(int)nbg);

//allocation dynamique de mémoire des images io et ir
io1=(int *)malloc(dimx*dimy*sizeof(int));
io2=(int *)malloc(dimx*dimy*sizeof(int));
ir =(int *)malloc(dimx*dimy*sizeof(int));
if(ir==NULL) printf("allocation ir impossible\n");

taille=dimx*dimy;
printf("taille=%ld\n",taille);

//lecture des pixels
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++) 
	{
		chi1=(unsigned char)fgetc(fio1);
		chi2=(unsigned char)fgetc(fio2);
		io1[i*dimx+j]=(int)chi1;
		io2[i*dimx+j]=(int)chi2;
	}


///////////////////////////////////////////////////////////////////
//TRAITEMENT
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		ir[i*dimx+j]=abs(io1[i*dimx+j]-io2[i*dimx+j]);
//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////
 
//Sauvegarde de l image résultat dans le fichier fir
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		fputc((unsigned char)ir[i*dimx+j],fir);

//libération de de la mémoire des tableaux io et ir et fermeture des 2 fichiers fio et fir
free(io1);free(io2); free(ir);
fclose(fio1);fclose(fio2); fclose(fir);
return 0;
}
