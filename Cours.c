// % Cours TP1
// % Construction d'un l'histogramme (144px x 256px)

longint hist[256], nmax; //On définit des varariable en longint car ces entiers peuvent être grand

//Constitution de l'histogramme
for(i=0; i<256; i++) hist[i]=0; //pas besoin d'accolades (=création d'un block) avec 1 seul instruction (mais oui pour 2) 

for(i=0; i<dimy; i++)
	for(j=0; j<dimx; j++)
		hist[io[i*dimx+j]]++;


ir = int(*)malloc(256*144*sizeof(int));


// Normalisation de l'histogramme
//Programme qui sert à mieux répartir le NG, "mais plus on est nombreux plus on est vu" (= les grosses populations de pixels avec un NG proche seront mise en avant, et les petites peuvent disparaître)
nmax = hist[0];

for(i=1; i<256; i++) if(hist[i]>nmax) nmax=hist[i];

for(i=1; i<256; i++) hist[i]=((longint)143*hist[i])/nmax;//normalisation

for(j=0; j<256; j++) //remplissage
	for(i=0; i<(143-hist[j]; i++) ir[i*256+j]=0;

for(i=(143-hist[j]); i<144; i++) ir[i*256+j]=255;

// % Egalisation d'Histogramme

//Histogramme Cumulé
histc[0] = hist[0];

for(i=1; i<256; i++)
	histc[i] = histc[i-1] + hist[i];
	
//Normalisation
for (i=0; i<256; i++)
	LUT[i] = (int)((long int)255*histc[i])(taille);
	
// io --> ir

for(i=0; i<dimy; i++)
	for (j=0; j<dimx; j++)
		ir[i*dimx+j] = LUT[io[i*dimx + j]];
