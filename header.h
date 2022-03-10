#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <time.h>
#include <sstream>
#include <limits>

#include <stdlib.h>
#include <stdio.h>

#include "mpi.h"
using namespace std;



#define R 8.314
//#define R 0.00198709369

#define TEMNUM 100
#define TEMINI 1.0
#define TEMVAR 1.5

#define STEPNUM 20000

extern int   rowGec,  rowGecWeight,  rowLab,  rowLabWeight;
extern double **Gec,  **GecWeight,   **Lab,   **LabWeight;

double** file_read(ifstream &file, int& linenum);
double Metropolis(double **StepSize, double tem, int last);
double* Error();
double Chi2(double *errLab, double *errGec, int numGec);
double Test(double x, double Ktem, int term);
double min(double x, double y);
double max(double x, double y);
void   Fit(double& x_alpha, double& x_beta, double Ktem);
