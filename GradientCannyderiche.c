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
int nbg;
register long int i,j;
long int dimx,dimy,taille;
char entree[35],sortie[35],chaine[10];
double alpha, gamma, expalpha, exp2alpha,*Bm,*Bp,*Cm,*Cp,*irx,*iry,*irr;
double exp(double x);

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
Bm=(double *)malloc(dimx*sizeof(double));
Bp=(double *)malloc(dimx*sizeof(double));
Cm=(double *)malloc(dimy*sizeof(double));
Cp=(double *)malloc(dimy*sizeof(double));
irx=(double *)malloc(dimx*dimy*sizeof(double));
iry=(double *)malloc(dimx*dimy*sizeof(double));
irr=(double *)malloc(dimx*dimy*sizeof(double));
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
		ir[i*dimx+j]=0; //Dérivée sur les bords nulles car cte sur les bords = à 0.
	}


///////////////////////////////////////////////////////////////////
//TRAITEMENT

printf("\n Choisir un alpha :");
scanf("%lf", &alpha);
gamma=-(1.0-exp(-alpha))/exp(-alpha);
expalpha=exp(-alpha);
exp2alpha=exp(-2.0*alpha);

for(i=0;i<dimy;i++)
	{
		Bm[0]=0.0;Bm[1]=gamma*expalpha*(double)io[i*dimx];
		for(j=2;j<dimx;j++)
		Bm[j]=gamma*expalpha*(double)io[i*dimx+j-1]+2.0*expalpha*Bm[j-1]-exp2alpha*Bm[j-2];
		
		Bp[dimx-1]=0.0;Bp[dimx-2]=gamma*expalpha*(double)io[i*dimx+dimx-1];
		for(j=dimx-3;j>-1;j--)
		Bp[j]=gamma*expalpha*(double)io[i*dimx+j+1]+2.0*expalpha*Bp[j+1]-exp2alpha*Bp[j+2];
		
		for(j=0;j<dimx;j++) irx[i*dimx+j]=(Bm[j]+Bp[j]);
	}

for(j=0;j<dimx;j++)
	{
		Cm[0]=0.0;Cm[1]=gamma*expalpha*(double)io[j];
		for(i=2;i<dimy;i++)
		Cm[i]=gamma*expalpha*(double)io[(i-1)*dimx+j]+2.0*expalpha*Cm[i-1]-exp2alpha*Cm[i-2];
		
		Cp[dimy-1]=0.0;Cp[dimy-2]=gamma*expalpha*(double)io[(dimy-1)*dimx+j];
		for(i=dimy-3;i>-1;i--)
		Cp[j]=-gamma*expalpha*(double)io[(i+1)*dimx+j]+2.0*expalpha*Cp[i+1]-exp2alpha*Cp[i+2];
		
		for(i=0;i<dimy;i++) iry[i*dimx+j]=(Cm[i]+Cp[i]);
	}
	
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		irr[i*dimx+j]= fabs(irx[i*dimx+j]) + fabs(iry[i*dimx+j]);
	
mmax=irr[0];
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		if(irr[i*dimx+j]>mmax) mmax=irr[i*dimx+j];
	
	/*
	mmax=iry[0];
	for(i=0;i<dimy;i++)
		for(j=0;j<dimx;j++)
			if(iry[i*dimx+j]>mmax) mmax=iry[i*dimx+j];
	*/
	
for(i=0;i<dimy;i++)
for(j=0;j<dimx;j++)
ir[i*dimx+j]=(int)((irr[i*dimx+j]*(double)255)/mmax);
		
		
//FIN TRAITEMENT
///////////////////////////////////////////////////////////////////
 
//Sauvegarde de l image résultat dans le fichier fir
for(i=0;i<dimy;i++)
	for(j=0;j<dimx;j++)
		fputc((unsigned char)irr[i*dimx+j],fir);

//libération de de la mémoire des tableaux io et ir et fermeture des 2 fichiers fio et fir
free(io); free(ir);
fclose(fio); fclose(fir);
return 0;
}
