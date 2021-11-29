#pragma once

#include <string>
#include "matrix.h"


Matrix ReadMNIST(const std::string &path);
void printMNISTImage(const Matrix &m);

Matrix ReadMNISTLabels(const std::string &path);
