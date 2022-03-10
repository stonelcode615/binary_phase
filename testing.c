#include "header.h"

double Test(double x, double Ktem, int term)
{
   double x1, x2;
   double vectem[3], item[3], itemd[3], itemd2[3];
   double Ge, GeDev, GeDev2, muex1, muex2;
   double gMixing=0.0, gMixing_dev=0.0, gMixing_dev2=0.0, mu1Mixing=0.0, mu2Mixing=0.0;

   vectem[0] = 1.0;  
   vectem[1] = Ktem*(-1.0);   
   vectem[2] = Ktem*log(Ktem)*(-1.0);

   x2 = x;
   x1 = 1.0 - x2;
   item[0] = 1.0;              itemd[0] = 0.0;             itemd2[0] = 0.0;
   item[1] = (x1-x2);          itemd[1] = 2.0;             itemd2[1] = 0.0;
   item[2] = pow((x1-x2),2);   itemd[2] = 4.0*(x1-x2);     itemd2[2] = 8.0;

   muex1 = 0.0; muex2 = 0.0; GeDev2 = 0.0;
   for(int j=0; j<rowGec; j++){
      Ge    = 0.0;
      GeDev = 0.0;
      for(int k=0; k<int(Gec[j][0]); k++){
          Ge     += Gec[j][k+1]*vectem[j]*(x1*x2*item[k]);
          GeDev  += Gec[j][k+1]*vectem[j]*(x1*x2*itemd[k]+   (x2-x1)*item[k]);
          GeDev2 += Gec[j][k+1]*vectem[j]*(x1*x2*itemd2[k]+2*(x2-x1)*itemd[k]-2*item[k]);
      }
      muex1 += (Ge + GeDev*x2);
      muex2 += (Ge - GeDev*x1);
      gMixing += Ge;
      gMixing_dev += GeDev;
   }
   gMixing      += R*Ktem*(x1*log(x1)+x2*log(x2));
   gMixing_dev  += R*Ktem*(log(x1)-log(x2));
   gMixing_dev2 += R*Ktem/(x1*x2)+GeDev2;
   mu1Mixing   = gMixing + x2*gMixing_dev;
   mu2Mixing   = gMixing - x1*gMixing_dev;

   switch(term)
   {
      case 1:
              return gMixing;
      case 2:
              return gMixing_dev;
      case 3:
              return muex1;
      case 4:
              return muex2;
      case 5:
              return mu1Mixing;
      case 6:
              return mu2Mixing;
      case 7:
              return gMixing_dev2;
   }

}


