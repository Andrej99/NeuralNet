#include "matrix.h"
#include <iostream>
#include "util.h"

void print(const  Matrix &m)
{
       for (size_t i = 0; i < m.n_rows; i++)
    {
        for (size_t j= 0; j < m.n_columns; j++)
        {

            printf("%lf ",m(i,j));
         
        }
        puts("");
        
    }
    puts("-----------------");

}

double sigmoid(double x) { return 1/(1 + exp(-x));}
double d_sigmoid(double x) { return sigmoid(x)*( 1-sigmoid(x)); }

double relu(double x) {return x <=0 ? 0:x;}
double d_relu(double x) {return x <= 0 ? 0 : 1;}

double compute_error(const Matrix &out, const Matrix &labels)
{
    double error = 0;
    int n = 0;

    for (size_t i = 0; i < out.n_rows; i++){
        n++;
        error += (out(i,0) - labels(i,0))*(out(i,0) - labels(i,0));

    }

    return error/n;

}


int main()
{

 


    Matrix X(4,2);

    X.set(0,0,0);
    X.set(0,0,1);

    X.set(0,1,0);
    X.set(1,1,1);

    X.set(1,2,0);
    X.set(0,2,1);
    
    X.set(1,3,0);
    X.set(1,3,1);


    Matrix y(4,1);
    y.set(0,0,0);
    y.set(1,1,0);
    y.set(1,2,0);
    y.set(0,3,0);
    
  

    Matrix W1(2,2);
    Matrix W2(1,2);

    Matrix b1 = Matrix(2,1,false);
    Matrix b2 = Matrix(1,1,false);

    const size_t n_iter =10000;

    for (size_t i = 0; i < n_iter; i++)
    {
        size_t j = i % 4;

        if(i%100 ==0)
        printf("-");
      

        Matrix x =X.row(j).Transpose();
        Matrix Z1 = W1 * x + b1 ;
        Matrix A1 = Z1.copy();
        A1.f(sigmoid);
     
        Matrix Z2 = W2 * A1 + b2;
        Matrix A2 = Z2.copy();
        A2.f(sigmoid);
        
    
        

        Matrix D2 = (A2 - y.row(j).Transpose());
       
        Z2.f(d_sigmoid);
        D2.Multiply(Z2);
        

        

        Matrix D1 = W2.Transpose() * D2;
        Z1.f(d_sigmoid);
        D1.Multiply(Z1);

       

        Matrix DW2 = A1 * D2.Transpose();
        Matrix DW1 = x * D1.Transpose();

       
        
        DW1.f([](double x){return x*0.1;});
        DW2.f([](double x){return x*0.1;});

        D1.f([](double x){return x*0.1;});
        D2.f([](double x){return x*0.1;});

        W2 -= DW2.Transpose();
        W1 -= DW1.Transpose();
        b2 -= D2;
        b1 -= D1;
        

        
        

        

        
}
    puts("done");
    for(size_t u = 0; u < 4; u++){
       Matrix x =X.row(u).Transpose();
        Matrix Z1 = W1 * x + b1 ;
        Matrix A1 = Z1.copy();
        A1.f(sigmoid);
     
        Matrix Z2 = W2 * A1 + b2;
        Matrix A2 = Z2.copy();
        A2.f(sigmoid);
        print(A2);
    }
   
    
  




    
    return 0;
}
