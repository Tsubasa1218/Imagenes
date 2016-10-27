
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
#include "qcustomplot.h"

#define PI 3.14159265359
#define EULER 2.718281828

using namespace std;
class Operaciones
{
public:
    Operaciones();
    void inicializarKernel();
    int width;
    int height;
    int matrixC1[350][350];
    int matrixC2[350][350];
    int matrixC3[350][350];
    int matrizAuxResultante[350][350];
    int histograma[256];
    int histogramaEcualizado[256];
    float ** kernelGauss;
    int vecinos;
    float kernelValue;
    QImage imagenRed;
    QImage leerImagen(QString ruta, int transf);
    void writeNewImage(QImage &imagen, int transf);
    void R_G_B(int color);
    void convolucion(QImage & imagen, int numVecinos, int tipo);
    void filtroGaussiano(QImage &imagen);
    void filtroOrden(QImage & imagen, int tipo);
    void filtroSigma(QImage & imagen);
    void filtroNagao(QImage & imagen);
    void calcularHistograma(QImage & imagen);
    void ecualizarHistograma();
    void ecualizarImagen(QImage & imagen);
    void contrasteGamma(QImage & imagen, float y);
    void contrasteStretching(QImage & imagen);
    int calcMin(QImage & imagen);
    int calcMax(QImage &imagen);
    void filtroSobel(QImage & imagen);
    void filtroPrewitt(QImage & imagen);
    void filtroRoberts(QImage & imagen);
    QVector<double> getData(int tipo);
    void otsuThreshold();
};

#endif // OPERACIONES_H
