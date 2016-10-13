#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <QString>
#include <QImage>
#include <QColor>
#include <math.h>
#include <vector>
#define PI 3.14159265359
#define EULER 2.718281828

using namespace std;
class Operaciones
{
public:
    Operaciones();
    void inicializarKernel(int nVal, int tipo);
    int width;
    int height;
    int matrixC1[300][300];
    int matrixC2[300][300];
    int matrixC3[300][300];
    int matrizAuxResultante[300][300];
    int histograma[256];
    int histogramaEcualizado[256];
    float ** kernelGauss;
    int vecinos;
    float kernelValue;
    QImage imagenRed;
    QImage leerImagen(QString ruta, int transf);
    void writeNewImage(QImage &imagen, int transf);
    void RGB(int color);
    void convolucion(QImage & imagen, int numVecinos, int tipo);
    void filtroGaussiano(QImage &imagen);
    void filtroOrden(QImage & imagen, int tipo);
    void filtroSigma(QImage & imagen);
    void filtroNagao(QImage & imagen);
    void calcularHistograma();
    void ecualizarHistograma();
    void ecualizarImagen(QImage & imagen)
};

#endif // OPERACIONES_H
