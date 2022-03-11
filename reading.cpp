#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstdio>
using namespace std;



double** file_read(ifstream &file, int& linenum)
{
    int row, col;
    double term;
    double **M; 

    row = 0;
    string line;
    while(getline(file,line))
          row++;
    M = new double*[row];
    linenum = row;
    file.clear();
    file.seekg (0, file.beg);

    for(row = 0; getline(file, line); row++){
       col = 0;
       istringstream iss(line);
       while(iss >> term)
            col++;
       M[row] = new double[col+1];
    }
    file.clear();
    file.seekg (0, file.beg);
   
    for(row = 0; getline(file, line); row++){
       col = 1;
       istringstream iss(line);
       while(iss >> term){
             M[row][col++] = term;
       }
       M[row][0] = double (col-1);
    }

    for(int i = 0; i < row; i++){
       for(int j = 1; j <=int(M[i][0]); j++)
          cout << M[i][j] << " ";
       cout << endl;
    }
    cout << endl;  

    return M; 
}
