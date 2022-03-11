#include "header.h"

double Metropolis(double **StepSize, double tem, int last)
{
    int    numGec;
    int    count=0;
    double *errLab, *errGec, chi2, chi2n, t1, t2;
   
    double bufGec;
    double xrand, acceptRatio, probability;

    double diff_mean, mean0=0.0, mean1=0.0, sum_chi2=0.0;
 
    errLab = Error();
    numGec = 0;
    for(int i=0; i<rowGec; i++)
       numGec += Gec[i][0];
    errGec = new double[numGec];
    numGec = 0;
    for(int i=0; i<rowGec; i++)
       for(int j=0; j<int(Gec[i][0]); j++)
          errGec[numGec++] = Gec[i][j+1];
    
    chi2 = Chi2(errLab, errGec, numGec);
    if(last == 1){
      for(int istep=1; istep<=STEPNUM; istep++){
          //cout << "istep = " << istep << endl;
          for(int i=0; i<rowGec; i++){
              for(int j=0; j<int(Gec[i][0]); j++){
                  xrand  = rand()/(double)(RAND_MAX)-0.5;
                  bufGec = Gec[i][j+1];
                  Gec[i][j+1]  = Gec[i][j+1] + xrand*StepSize[i][j];
                  errLab = Error();
                  numGec=0;
                  for(int m=0; m<rowGec; m++)
                     for(int n=0; n<int(Gec[m][0]); n++)
                        errGec[numGec++] = Gec[m][n+1];             
                  chi2n  = Chi2(errLab, errGec, numGec);
                  t1 = chi2n-chi2;
                  t2 = -t1/tem;
                  acceptRatio = exp(t2);
                  probability = rand()/(double)(RAND_MAX);
                  if(acceptRatio >= probability){
                     chi2 = chi2n;
                     count++;
                     sum_chi2 += chi2;
                     mean0 = mean1;
                     mean1 = sum_chi2/count;
                  }
                  else{
                     Gec[i][j+1] = bufGec;
                  }
                  //cout << "Gec[" << i << "][" << j+1 << "] = " << Gec[i][j+1] << endl;
              }          //end of j loop
          }             // end of i loop
          //cout << "chi2 = " << chi2 << endl;
      }  // end of istep
//      cout <<  "Average Accept Ratio is " << double(count)/(numGec*STEPNUM) << endl;
      diff_mean = mean1-mean0;
//      cout <<  "The Mean Value difference is " << mean1 << " - " << mean0 << " = " << diff_mean << endl;
    }  // end of if last == 1

    free(errLab);
    free(errGec);
    return chi2;
}

double Chi2(double *errLab, double *errGec, int numGec)
{
   double buff1, buff2, err1, err2;
 
   err1 = 0.0;
   err2 = 0.0;
   for(int i=0; i<rowLab; i++){
      buff1 = 0.0;
      for(int j=0; j<rowLab; j++)
         buff1 += errLab[j]*LabWeight[i][j+1];
      err1 += buff1 * errLab[i];
   }
   for(int i=0; i<numGec; i++){
      buff2 = 0.0;
      for(int j=0; j<numGec; j++)
          buff2 += errGec[j]*GecWeight[i][j+1];
      err2 += buff2 * errGec[i];
   }
   return err1+err2;
}


double* Error()
{
   double x1, x2, RT, muex1, muex2, Ge, GeDev;
   double *Muex1, *Muex2, *Error;
   double x1_alpha, x2_alpha, x1_beta, x2_beta;
 
   double vectem[4], item[3], itemd[3];
   
   Muex1 = new double[rowLab];
   Muex2 = new double[rowLab];
   Error = new double[rowLab];
   for(int i=0; i<rowLab; i++){
      vectem[0] = 1.0;
      vectem[1] = (Lab[i][2]+273.15)*(-1.0);
      vectem[2] = (Lab[i][2]+273.15)*log(Lab[i][2]+273.15)*(-1.0);
      vectem[3] = pow((Lab[i][2]+273.15),2)*(-1.0);
 
      x2 = Lab[i][1];
      x1 = 1.0 - x2;
      item[0] = 1;                itemd[0] = 0;
      item[1] = (x1-x2);          itemd[1] = 2;
      item[2] = pow((x1-x2),2);   itemd[2] = 4*(x1-x2);
 
      muex1 = 0.0; muex2 = 0.0;
      for(int j=0; j<rowGec; j++){
         Ge    = 0.0;
         GeDev = 0.0;
	 for(int k=0; k<int(Gec[j][0]); k++){
          Ge     += Gec[j][k+1]*vectem[j]*(x1*x2*item[k]);
          GeDev  += Gec[j][k+1]*vectem[j]*(x1*x2*itemd[k]+   (x2-x1)*item[k]);
         }
         muex1 += (Ge + GeDev*x2);
         muex2 += (Ge - GeDev*x1);
      }
      Muex1[i] = muex1;
      Muex2[i] = muex2;
   }                     // end of i loop;

   for(int i=0; i<rowLab/2; i++){
      RT  = R*(273.15+Lab[i][2]);   
      x2_alpha = Lab[i][1];
      x2_beta  = Lab[rowLab-i-1][1];
      x1_alpha = 1.0 - x2_alpha;
      x1_beta  = 1.0 - x2_beta;
      Error[i]          = RT*log(x1_beta)-RT*log(x1_alpha)+(Muex1[rowLab-i-1]-Muex1[i]);
      Error[rowLab-i-1] = RT*log(x2_beta)-RT*log(x2_alpha)+(Muex2[rowLab-i-1]-Muex2[i]); 
   }
  
   free(Muex1);
   free(Muex2);
   return Error;
}      
   
