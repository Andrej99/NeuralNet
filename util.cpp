#include "util.h"

#include <fstream>
#include <iostream>
#include <cctype>

uint32_t swap_endian(uint32_t x)
{
    x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
    return (x << 16) | (x >> 16);
}


void printMNISTImage(const Matrix &m)
{
       for (size_t i = 0; i < 28; i++){
        for (size_t j = 0; j < 28; j++) {
            if(m.M[i*28 + j] > 0 ){
                printf("0 ");
            }else{
                printf("* ");
            }
           
        }
        
        printf("\n");
    }


}


Matrix ReadMNIST(const std::string &path)
{
    std::ifstream file(path,std::ios::binary);
   
    if (!file.is_open()){  
        printf("Error reading file!\n");
        exit(-1);
    }
    
    u_int32_t magic;
    u_int32_t n_images;
    u_int32_t n_rows;
    u_int32_t n_columns;

 
    u_char test[28*28];
   
    file.read((char*)&magic,4);
    file.read((char*)&n_images,4);
    file.read((char*)&n_rows,4);
    file.read((char*)&n_columns,4);
    
     magic  = swap_endian(magic);
     n_images = swap_endian( n_images);
     n_rows = swap_endian( n_rows);
     n_columns = swap_endian(n_columns);

    if(magic != 2051){
        printf("Wrong file type!\n");
        exit(-1);
    }


    Matrix m(n_images,n_rows*n_columns);

    for (size_t i = 0; i < n_images; i++){
       file.read((char*)test,28*28);
       m.FillRow(test,i);
    }

    file.close();
    printMNISTImage(m.row(0));
    return m;
}


Matrix ReadMNISTLabels(const std::string &path)
{
    std::ifstream file(path,std::ios::binary);
   
    if (!file.is_open()){  
        printf("Error reading file!\n");
        exit(-1);
    }
    
    u_int32_t magic;
    u_int32_t n_labels;

    file.read((char*)&magic,4);
    file.read((char*)&n_labels,4);

    magic  = swap_endian(magic);
    n_labels = swap_endian( n_labels);


    if(magic != 2049){
        printf("Wrong file type!\n");
        exit(-1);
    }

    Matrix m(n_labels,1);
    u_char* data = (u_char*)malloc(n_labels);
    file.read((char*)data,n_labels);
    std::copy(data,data+n_labels,m.M.get());



    file.close();
   printf("First label: %lf",m.M[0]);
    return m;

}