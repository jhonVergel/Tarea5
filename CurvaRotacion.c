

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void Datos(int nfilas, FILE *in, float *x, float *y);
float Likelihood(float *yobs,float *ymod);

#define iteraciones 20000
#define bb 0.2497
#define bd 5.16
#define ad 0.3105
#define ah 64.3
#define chfact 200000.0

int main()
{
	FILE *in = fopen("mynewfile.txt", "r");
	float *yobs;
	float *ymod;
	float *ypri;
	float *Robs;
	float *mb_walk;
	float *md_walk;
	float *mh_walk;
	float *l_walk;
	int i;
	
	
	yobs = malloc((300)*sizeof(float));
	ymod = malloc((300)*sizeof(float));
	ypri = malloc((300)*sizeof(float));
	Robs = malloc((300)*sizeof(float));

	mb_walk = malloc((2000)*sizeof(float));
	md_walk = malloc((2000)*sizeof(float));
	mh_walk = malloc((2000)*sizeof(float));
	l_walk = malloc((2000)*sizeof(float));
	
	Datos(600, in, Robs , yobs);
	//para cero
	mb_walk[0]= 400;
	mh_walk[0]= 10000;
	md_walk[0]= 7500;
	for(i=0;i<300;i++)
	{
		ymod[i]=sqrt(mb_walk[0])*Robs[i]/ pow(pow(Robs[i],2)+pow(bb,2),3/2) + sqrt(md_walk[0])*Robs[i]/(pow(pow(Robs[i],2)+pow((bd+ad),2),3/2))+ sqrt(mh_walk[0])/(pow(pow(Robs[i],2)+pow(ah,2),1/4));
		
	}



        l_walk[0]= Likelihood(yobs,ymod);
	int j;
	float bprime;
	float hprime;
	float dprime;
	float del=1;
	float beta;
	float lini;
	float lprime;
	float alpha;

	for(j=1;j<2000;j++)
	{
		
		beta=(double)rand()/(double)RAND_MAX;
		bprime=mb_walk[j-1]+ del*(((double)rand()/(double)RAND_MAX)-(1/2));
		hprime=mh_walk[j-1]+ del*(((double)rand()/(double)RAND_MAX)-(1/2));
		dprime=md_walk[j-1]+ del*(((double)rand()/(double)RAND_MAX)-(1/2));
		
		for(i=0;i<300;i++)
		{
		ymod[i]=sqrt(mb_walk[j])*Robs[i]/ pow(pow(Robs[i],2)+pow(bb,2),3/2) + sqrt(md_walk[j])*Robs[i]/(pow(pow(Robs[i],2)+pow((bd+ad),2),3/2))+ sqrt(mh_walk[j])/(pow(pow(Robs[i],2)+pow(ah,2),1/4));
		}
		for(i=0;i<300;i++)
		{
		ypri[i]=sqrt(bprime)*Robs[i]/ pow(pow(Robs[i],2)+pow(bb,2),3/2) + sqrt(dprime)*Robs[i]/(pow(pow(Robs[i],2)+pow((bd+ad),2),3/2))+ sqrt(hprime)/(pow(pow(Robs[i],2)+pow(ah,2),1/4));
		}

		lini= Likelihood(yobs,ymod);
		lprime= Likelihood(yobs,ypri);
		alpha= lprime/lini;
		if(alpha>=1.0)	
		{
			mb_walk[j+1]= bprime;
			mh_walk[j+1]= hprime;
			md_walk[j+1]= dprime;
			l_walk[j+1]= lprime;

		}
		else if(beta<=alpha)
		{
			mb_walk[j+1]= bprime;
			mh_walk[j+1]= hprime;
			md_walk[j+1]= dprime;
			l_walk[j+1]= lprime;	
		}

		else if(beta>=alpha)
		{
			mb_walk[j]= mb_walk[j-1];
			mh_walk[j]= mb_walk[j-1];
			md_walk[j]= mb_walk[j-1];
			l_walk[j]= lini;	
		}


		
	}

	float max = l_walk[0];
	int c;
	int locc;
 
    for ( c = 1 ; c < 2000 ; c++ ) 
    {
        if ( l_walk[c] > max ) 
        {
           max = l_walk[c];
	   locc=c;
	 }
     }
	printf(" %f \n",mb_walk[locc] );
	printf(" %f \n",md_walk[locc] );
	printf(" %f \n",mh_walk[locc] );
  
  
	

	return 0;
}




float Likelihood(float *yobs,float *ymod)
{

	float chi=0;
	int i;
	for(i=0;i<300;i++)
		{
		chi+=pow(yobs[i]-ymod[i],2);
		
		}
	float chi_sq;
	chi_sq= chi/chfact;
	float expoo;
	
	expoo= 1.0/(double)pow(M_E,chi_sq);

	return expoo;

}




void Datos(int nfilas, FILE *in, float *x, float *y)
{
	int i;
	int nx;
	int ny;
	for(i=0; i < nfilas; i++)
	{	
		
		if((i%2)==0)
        	{
			fscanf(in, "%f \n", &x[nx]);
        		nx++;
        	}
                                        
        	else
        	{
        		fscanf(in, "%f \n", &y[ny]);
			ny++;
		}
	
	}
	
}
