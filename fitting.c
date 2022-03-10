#include "header.h"

void Fit(double& x_a, double& x_b, double Ktem)
{
  double RT;
  double x2_alpha, x2_beta, x1_alpha, x1_beta;
  double Muex1_alpha, Muex2_alpha, Muex1_beta, Muex2_beta;
  double error1, error2, chi2, chi2_min;
  double x_alpha, x_beta;
  int    index1, index2, I;
  double a, b, x0_alpha, x0_beta;
  double gedev2_xa, gedev2_xb;

  RT = R*Ktem;
  for(int i=1; i<1000; i++){
      x2_alpha = i*0.001;
      x1_alpha = 1.0 - x2_alpha;
      gedev2_xa = Test(x2_alpha, Ktem, 7);
      if(gedev2_xa < 0.0) break;
      Muex1_alpha = Test(x2_alpha, Ktem, 3);
      Muex2_alpha = Test(x2_alpha, Ktem, 4);
      for(int j=999; j>i; j--){
         x2_beta = j * 0.001;
         x1_beta = 1.0 - x2_beta;
         gedev2_xb = Test(x2_beta, Ktem, 7);
         if(gedev2_xb < 0.0) break;
         Muex1_beta = Test(x2_beta, Ktem, 3);
         Muex2_beta = Test(x2_beta, Ktem, 4);
         error1 = RT*log(x1_beta)-RT*log(x1_alpha)+(Muex1_beta-Muex1_alpha);
         error2 = RT*log(x2_beta)-RT*log(x2_alpha)+(Muex2_beta-Muex2_alpha);
         chi2  = pow(error1, 2.0) + pow(error2, 2.0);
         if(i==1 && j==999){ 
           chi2_min = chi2;
         }else if(chi2_min > chi2){
           chi2_min = chi2;
           index1 = i;
           index2 = j;
         }
      }
  }
   x_a = index1*0.001;
   x_b = index2*0.001;
//   cout << x_a << "  " << x_b << "  " << chi2_min << endl;


}

