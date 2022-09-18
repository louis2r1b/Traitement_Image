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
int *io,*ir, *ifm;
int nbg, t[9], tmp, ind, mmin, imin, pourcent;
register long int i,j,l,k,n,m;
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

if(fio !=NULL) printf("ouverture du fichier in\n");
if(fir !=NULL) printf("ouverture du fichier out\n");

printf("Entrer un pourcentage :");
scanf("%d", &pourcent);

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
ifm=(int *)malloc(dimx*dimy*sizeof(int));
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
		ifm[i*dimx+j]=io[i*dimx+j];
	}


///////////////////////////////////////////////////////////////////////////
//TRAITEMENT 

//Bruit
nbPix=((long int)pourcent*taille)/(long int)100;

srand(time(NULL));
for (k=0;k<nbPix;k++) {
	i=rand()%dimy; 
	j=rand()%dimx;
	if(io[i*dimx+j]>127) ir[i*dimx+j]=0; //On met du blanc
	else ir[i*dimx+j]=255; //On met du noir
	}

//Médian
for(i=1;i<dimy-1;i++)
for(j=1;j<dimx-1;j++)
	{
	ind=0;
	for(l=-1;l<=1;l++)
	for(k=-1;k<=1;k++)
	t[ind++]=ir[(i+l)*dimx+j+k];
	for(n=0;n<5;n++)
		{
		mmin=t[n];
		for(m=n+1;m<9;m++) if(t[m]<mmin) {imin=m;mmin=t[m];}
		tmp=t[n];t[n]=mmin;t[imin]=tmp;
		}
	ifm[i*dimx+j]=t[4];
	}

//MSE 

double MSE = 0.0;

for(i=1;i<dimy-1;i++)
	for(j=1;j<dimx-1;j++)
		MSE += (double)(io[i*dimx+j]-ifm[i*dimx+j])*(double)(io[i*dimx+j]-ifm[i*dimx+j]);
MSE = MSE/((double)(dimx-2)*(double)(dimy-2));
printf("MSE = %lf", MSE);

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


