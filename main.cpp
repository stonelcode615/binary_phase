
#include "header.h"

int   rowGec,  rowGecWeight,  rowLab,  rowLabWeight,   rowStep;
double **Gec,  **GecWeight,   **Lab,   **LabWeight,    **Step;


int main(int argc, char* argv[]){

   MPI_Init( &argc, &argv);
 
   double **StepSize;
   double tem, chi2;
   double x, Ktem, gMixing;
   
   double **fit;
   int I;

   int    n;

   int EXE;
//   srand( time(NULL) );
   srand(1); 

   EXE = atoi(argv[1]);
   cout << "EXE = " << EXE <<  endl;
   cout << "argc = " << argc << endl;
   if(EXE==1){
     ifstream fileGec("./parameter/331gec.dat");
     Gec = file_read(fileGec, rowGec);
   }
   if(EXE==3){
     ifstream fileGec0("./parameter/test.dat");
     Gec = file_read(fileGec0, rowGec);
   }
   ifstream fileGecWeight("./parameter/331gec_weight.dat");
   GecWeight = file_read(fileGecWeight, rowGecWeight);
   ifstream fileLab("./parameter/lab20.dat");
   Lab = file_read(fileLab, rowLab);
   ifstream fileLabWeight("./parameter/lab20_weight.dat");
   LabWeight = file_read(fileLabWeight, rowLabWeight);
   ifstream fileStep("./parameter/331step.dat");
   Step = file_read(fileStep, rowStep);

   StepSize = new double* [rowStep];
   for(int i=0; i<rowStep; i++)
      StepSize[i] = new double [int(Step[i][0])];
   
//===============================================================
//             Annealing Procedure
//===============================================================
if(EXE==1 || EXE==3){
   chi2 = Metropolis(StepSize, 100.00, 0);
   cout << "Initial chi2 is " << chi2 << '\n' << endl;
   for(n=0; n<=TEMNUM; n++){
      tem  = TEMINI / pow(TEMVAR, n);
      for(int i=0; i<rowStep; i++)
         for(int j=0; j<int(Step[i][0]); j++)
            StepSize[i][j] = Step[i][j+1]/pow(TEMVAR, 0.5*n); 
      chi2 = Metropolis(StepSize, tem, 1);
      cout << "n=" << n << "  tem=" << tem << "  chi2=" << chi2 << endl;

      for(int i=0; i<rowGec; i++){
         for(int j=0; j<int(Gec[i][0]);j++)
            cout << Gec[i][j+1] << " ";
         cout << endl;
      }
      cout << endl;
   }
   ofstream fileGec1("./parameter/test0.dat");
   for(int i=0; i<rowGec; i++){
      for(int j=0; j<int(Gec[i][0]); j++)
         fileGec1 << Gec[i][j+1] << " ";
         fileGec1 << endl;
   }
}
//===============================================================
//               Testing
//===============================================================
if(EXE==1 || EXE==2 || EXE==3){
   if(EXE==2){
       ifstream fileGec("./parameter/test0.dat");
       Gec = file_read(fileGec, rowGec);
   }
   ofstream filegMixing("./summary/gm.dat");
   Ktem = Lab[0][2]+273.15; 
   for(int i=1; i<10000; i++){
       x = i*0.0001;
       gMixing = Test(x, 25+273.15, 1);
       filegMixing << x << "  " << gMixing << endl;
   }
}           

//===============================================================
//               Fitting
//===============================================================
if(EXE==4){
   ifstream fileGec2("./parameter/newton.dat");
   Gec = file_read(fileGec2, rowGec);
   ofstream fileFit("./summary/fit.dat");

   fit = new double*[rowLab];
   for(int i=0; i<rowLab; i++){
      fit[i] = new double[2];
   }

   for(int i=0; i<rowLab/2; i++){
       I = rowLab-i-1;
       Ktem = Lab[i][2]+273.15;
       Fit(fit[i][0], fit[I][0],  Ktem);
       fit[i][1] = Lab[i][2];
       fit[I][1] = Lab[I][2];
   }
   cout << endl;
   for(int i=0; i<rowLab; i++){
      cout << fit[i][0] << "  " << fit[i][1] << endl;
      fileFit << fit[i][0] << "  " << fit[i][1] << endl;
   }
}

//===============================================================
//              Free and Closing
//===============================================================
    for(int i=0; i<rowLab; i++){
       free(Lab[i]);
       free(LabWeight[i]);
    }
    free(Lab);
    free(LabWeight);
    for(int i=0; i<rowGec; i++){
       free(Gec[i]);
       free(GecWeight[i]);
       free(Step[i]);
    }
    free(Gec);
    free(GecWeight);
    free(Step);
   
    MPI_Finalize();
   
    return 0;
}
    
