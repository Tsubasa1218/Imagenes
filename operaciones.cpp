#include "operaciones.h"

Operaciones::Operaciones()
{
    width = 350;
    height = 350;
    this->vecinos = 0;
    kernelValue = 0;

    for(int i = 0; i<width;i++){
        for(int j = 0; j < height ; j++){
            matrizAuxResultante[i][j] = 0;
        }
    }

    for (int i = 0; i < 256; i++) {
        histograma[i] = 0;
        histogramaEcualizado[i] = i;
    }


}
void Operaciones::inicializarKernel()
{


    int n = vecinos*2 + 1;
    kernelGauss = (float **)malloc(n*sizeof(float *));
    for(int i = 0; i < n; i++){
        kernelGauss[i] = (float*)malloc(n*sizeof(float));
    }

    float acum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            kernelGauss[i][j]=(1/PI)*pow(EULER, -2*(i*i + j*j));
            acum += kernelGauss[i][j];
        }
    }


}

QImage Operaciones::leerImagen(QString ruta, int transf){
    int C1 = 0;
    int C2 = 0;
    int C3 = 0;
    QImage imagen(ruta);
    imagenRed = imagen.scaled(width, height);

    float convMatrix[3][3] = {{0.430574, 0.34155, 0.178326},
                              {0.222014, 0.706654, 0.0713301},
                              {0.0201831, 0.129553, 0.939181}};


    if(transf == 1 || transf == 2 || transf == 0){
        R_G_B(transf);
    }else if(transf == 3){
        for(int i = 0; i<width;i++){
            for(int j = 0; j < height ; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                C1 = 0.299*R + 0.587*G + 0.114*B;
                matrixC1[i][j] = C1;
            }
        }
    }else if(transf == 4){
        for(int i = 0; i<width;i++){
            for(int j = 0; j < height ; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                C1 = 0.299*R + 0.587*G + 0.114*B;
                C2 = -0.147*R - 0.289*G + 0.436*B;
                C2 =  0.615*R - 0.515*G - 0.100*B;
                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }
    }else if(transf == 5){
        for(int i = 0; i<width;i++){
            for(int j = 0; j < height ; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                C1 = 0.299*R + 0.587*G + 0.114*B;
                C2 = 0.596*R - 0.274*G - 0.322*B;
                C2 = 0.212*R - 0.523*G + 0.311*B;

                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }
    }else if(transf == 6){
        for(int i = 0; i<width;i++){
            for(int j = 0; j < height ; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                C1 = 0.2989*R + 0.5866*G + 0.1145*B;
                C2 = -0.1688*R - 0.3312*G + 0.5000*B;
                C3 = 0.5000*R - 0.4184*G - 0.0816*B;
                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }
    }else if(transf == 7){
        for(int i = 0; i<width; i++){
            for(int j = 0; j < height; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();
                int alfa = R - (G + B)*0.5;
                int beta = G - B;
                beta *= sqrt(3)/2;

                C1 = atan2(beta, alfa)* 180 / 3.14159265359;
                C2 = sqrt(alfa*alfa + beta*beta);
                C3 = R + G + B;
                C3 /= 3;
                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }
    }else if(transf == 8){
        for(int i = 0; i<width; i++){
            for(int j = 0; j < height; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                int position = 0;
                int max = 0;
                int min = 0;
                if(R > G){
                    max = R;
                    min = G;
                }else{
                    max = G;
                    min = R;
                    position = 1;
                }

                if(max < B){
                    max = B;
                    position = 2;
                }
                if(min > B)
                    min = B;

                C3 = max;

                if(max != 0){
                    C2 = max - min;
                    C2 = C2/max;
                }else{
                    C2 = 0;
                }

                if(C2 != 0){
                    if(position == 0){
                        C1 = 1 + (G - B)/(max - min);
                    }else if(position == 1){
                        C1 = 3 + (B - R)/(max - min);
                    }else{
                        C1 = 5 + (R - G)/(max - min);
                    }
                }
                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }
    }else if(transf == 9){
        for(int i = 0; i<width; i++){
            for(int j = 0; j < height; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                C1 = (R -G)/sqrt(2);
                C2 = (R+G-2*B)/sqrt(6);
                C3 = (R+G+B)/sqrt(3);

                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }

    }else if(transf == 10){
        for(int i = 0; i<width; i++){
            for(int j = 0; j < height; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                C1 = convMatrix[0][0]*R + convMatrix[0][1]*G + convMatrix[0][2]*B;
                C2 = convMatrix[1][0]*R + convMatrix[1][1]*G + convMatrix[1][2]*B;
                C3 = convMatrix[2][0]*R + convMatrix[2][1]*G + convMatrix[2][2]*B;


                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }
    }
    else if(transf == 11){
        for(int i = 0; i<width; i++){
            for(int j = 0; j < height; j++){
                int R = QColor(imagenRed.pixel(i,j)).red();
                int G = QColor(imagenRed.pixel(i,j)).green();
                int B = QColor(imagenRed.pixel(i,j)).blue();

                C1 = (R + G + B)*0.33;
                C2 = (R - B)*0.5;
                C3 = (2*G - R - B)*0.25;


                matrixC1[i][j] = C1;
                matrixC2[i][j] = C2;
                matrixC3[i][j] = C3;
            }
        }
    }

    writeNewImage(imagenRed, transf);

    return imagenRed;
}

void Operaciones::writeNewImage(QImage & imagen, int transf){

    if(transf == 0){
        for(int i = 0; i < width; i++){
            for(int j = 0; j<height; j++){
                imagen.setPixel(i,j, qRgb(matrixC1[i][j], 0, 0));
            }
        }

    }else if(transf == 1){
        for(int i = 0; i < width; i++){
            for(int j = 0; j<height; j++){
                imagen.setPixel(i,j, qRgb(0, matrixC1[i][j], 0));
            }
        }

    }else if(transf == 2){
        for(int i = 0; i < width; i++){
            for(int j = 0; j<height; j++){
                imagen.setPixel(i,j, qRgb(0, 0, matrixC1[i][j]));
            }
        }

    }else if(transf == 3){
        for(int i = 0; i < width; i++){
            for(int j = 0; j<height; j++){
                imagen.setPixel(i,j, qRgb(matrixC1[i][j], matrixC1[i][j], matrixC1[i][j]));
            }
        }

    }else{
        for(int i = 0; i < width; i++){
            for(int j = 0; j<height; j++){
                imagen.setPixel(i,j, qRgb(matrixC1[i][j], matrixC2[i][j], matrixC3[i][j]));
            }
        }

    }
}

void Operaciones::R_G_B(int color){
    for(int i = 0; i<width;i++){
        for(int j = 0; j < height ; j++){
            if(color == 0){
                int R = QColor(imagenRed.pixel(i,j)).red();
                matrixC1[i][j] = R;
            }else if(color == 1){
                int G = QColor(imagenRed.pixel(i,j)).green();
                matrixC1[i][j] = G;
            }else if(color == 2){
                int B = QColor(imagenRed.pixel(i,j)).blue();
                matrixC1[i][j] = B;
            }
        }
    }
}

void Operaciones::convolucion(QImage & imagen, int numVecinos, int tipo){
    this->vecinos = numVecinos;
    this->kernelValue = (vecinos*2 +1)*(vecinos*2 +1);

    if(tipo ==0){
        for(int i = vecinos; i<height - vecinos; i++){
            for(int j = vecinos; j<width - vecinos; j++){
                float acum = 0;
                for(int k = i-vecinos; k<i+vecinos+1; k++){
                    for(int l = j - vecinos; l<j+vecinos+1; l++){
                        acum += matrixC1[k][l];
                    }
                }

                acum /= kernelValue;
                matrizAuxResultante[i][j] = floor(acum);
                imagen.setPixel(i,j, qRgb(matrizAuxResultante[i][j], matrizAuxResultante[i][j], matrizAuxResultante[i][j]));
            }
        }
    }else if(tipo == 1){
        inicializarKernel();
        filtroGaussiano(imagen);
        delete kernelGauss;
        kernelGauss = 0;
    }else if(tipo == 2 || tipo == 3){
        filtroOrden(imagen, tipo);
    }else if(tipo == 6)
        filtroSigma(imagen);
    else if(tipo == 5)
        filtroNagao(imagen);
    else if(tipo == 12)
        filtroSobel(imagen);
    else if(tipo == 13)
        filtroPrewitt(imagen);
    else if(tipo==14)
        filtroRoberts(imagen);
}

void Operaciones::filtroGaussiano(QImage & imagen){

    for(int i = vecinos; i<height - vecinos; i++){
        for(int j = vecinos; j<width - vecinos; j++){
            float acum = 0;
            int n = 0;
            int m = 0;
            for(int k = i-vecinos; k<i+vecinos+1; k++){
                for(int l = j - vecinos; l<j+vecinos+1; l++){
                    acum += matrixC1[k][l]*kernelGauss[n][m];
                    m++;
                }
                m = 0;
                n++;
            }

            matrizAuxResultante[i][j] = floor(acum);
            imagen.setPixel(i,j, qRgb(matrizAuxResultante[i][j], matrizAuxResultante[i][j], matrizAuxResultante[i][j]));
        }
    }
}

void Operaciones::filtroOrden(QImage &imagen, int tipo){
    if(tipo == 2){
        for(int i = vecinos; i<height - vecinos; i++){
            for(int j = vecinos; j<width - vecinos; j++){
                float aux = 0;

                for(int k = i-vecinos; k<i+vecinos+1; k++){
                    for(int l = j - vecinos; l<j+vecinos+1; l++){
                        if(aux < matrixC1[k][l]){
                            aux = matrixC1[k][l];
                        }
                    }
                }

                matrizAuxResultante[i][j] = floor(aux);
                imagen.setPixel(i,j, qRgb(matrizAuxResultante[i][j], matrizAuxResultante[i][j], matrizAuxResultante[i][j]));
            }
        }
    }else{
        for(int i = vecinos; i<height - vecinos; i++){
            for(int j = vecinos; j<width - vecinos; j++){
                float aux = 300;

                for(int k = i-vecinos; k<i+vecinos+1; k++){
                    for(int l = j - vecinos; l<j+vecinos+1; l++){
                        if(aux > matrixC1[k][l]){
                            aux = matrixC1[k][l];
                        }
                    }
                }

                matrizAuxResultante[i][j] = floor(aux);
                imagen.setPixel(i,j, qRgb(matrizAuxResultante[i][j], matrizAuxResultante[i][j], matrizAuxResultante[i][j]));
            }
        }
    }
}

void Operaciones::filtroSigma(QImage &imagen){
    int sigma = 5;
    for(int i = vecinos; i<height - vecinos; i++){
        for(int j = vecinos; j<width - vecinos; j++){
            float aux = 0;
            int inRange = 0;
            for(int k = i-vecinos; k<i+vecinos+1; k++){
                for(int l = j - vecinos; l<j+vecinos+1; l++){
                    if((matrixC1[i][j] - matrixC1[k][l]) <= sigma){
                        aux += matrixC1[k][l];
                        inRange++;
                    }
                }
            }
            aux /= (vecinos*2 +1 )*(vecinos*2 +1 ) - ((vecinos*2 +1 )*(vecinos*2 +1 ) - inRange);
            matrizAuxResultante[i][j] = floor(aux);
            imagen.setPixel(i,j, qRgb(matrizAuxResultante[i][j], matrizAuxResultante[i][j], matrizAuxResultante[i][j]));
        }
    }
}

void Operaciones::filtroNagao(QImage & imagen){

    this->vecinos = 2;
    float promedio[9] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    float varianza[9] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
    float min;
    int indice;

    for(int i = vecinos; i<height - vecinos; i++){
        for(int j = vecinos; j<width - vecinos; j++){

            promedio[0] = matrixC1[i][j] + matrixC1[i-1][j-1] + matrixC1[i-2][j-1] + matrixC1[i-1][j] + matrixC1[i-2][j]
                    + matrixC1[i-1][j+1] + matrixC1[i-2][j+1];

            promedio[1] = matrixC1[i][j] + matrixC1[i-1][j+1] + matrixC1[i-1][j+2] + matrixC1[i][j+1] + matrixC1[i][j+2]
                    + matrixC1[i+1][j+1] + matrixC1[i+1][j+2];

            promedio[2] = matrixC1[i][j] + matrixC1[i+1][j-1] + matrixC1[i+2][j-1] + matrixC1[i+1][j] + matrixC1[i+2][j]
                    + matrixC1[i+1][j+1] + matrixC1[i+2][j+1];

            promedio[3] = matrixC1[i][j] + matrixC1[i-1][j-2] + matrixC1[i-1][j-1] + matrixC1[i][j-1] + matrixC1[i][j-2]
                    + matrixC1[i+1][j-2] + matrixC1[i+1][j-1];

            promedio[4] = matrixC1[i][j] + matrixC1[i-1][j-1] + matrixC1[i-2][j-2] + matrixC1[i-2][j-1] + matrixC1[i-1][j]
                    + matrixC1[i-1][j-2] + matrixC1[i][j-1];

            promedio[5] = matrixC1[i][j] + matrixC1[i-1][j+1] + matrixC1[i-2][j+2] + matrixC1[i-1][j] + matrixC1[i-2][j+1]
                    + matrixC1[i][j+1] + matrixC1[i-1][j+2];

            promedio[6] = matrixC1[i][j] + matrixC1[i+1][j+1] + matrixC1[i+2][j+2] + matrixC1[i+1][j] + matrixC1[i+2][j+1]
                    + matrixC1[i][j+1] + matrixC1[i+1][j+2];

            promedio[7] = matrixC1[i+1][j-1] + matrixC1[i+2][j-2] + matrixC1[i][j-1] + matrixC1[i+1][j-2] + matrixC1[i+1][j]
                    + matrixC1[i+2][j-1] + matrixC1[i][j];

            for (int m = i-1; m < i+1; m++) {
                for (int n = j-1; n <j+1 ; n++) {
                    promedio[8] += matrixC1[m][n];
                }
            }

            for(int h = 0; h<8;h++){
                promedio[h] /= 7;
            }
            promedio[8] /= 9;

            varianza[0] = (matrixC1[i][j] - promedio[0])*(matrixC1[i][j] - promedio[0])
                    + (matrixC1[i-1][j-1] - promedio[0])*(matrixC1[i-1][j-1] - promedio[0]);
                    + (matrixC1[i-2][j-1] - promedio[0])*(matrixC1[i-2][j-1] - promedio[0])
                    + (matrixC1[i-1][j] - promedio[0])*(matrixC1[i-1][j] - promedio[0])
                    + (matrixC1[i-2][j] - promedio[0])*(matrixC1[i-2][j] - promedio[0])
                    + (matrixC1[i-1][j+1] - promedio[0])*(matrixC1[i-1][j+1] - promedio[0])
                    + (matrixC1[i-2][j+1] - promedio[0])*(matrixC1[i-2][j+1] - promedio[0]);

            varianza[1] = (matrixC1[i][j] - promedio[1])*(matrixC1[i][j] - promedio[1])
                    + (matrixC1[i-1][j+1] - promedio[1])*(matrixC1[i-1][j+1] - promedio[1])
                    + (matrixC1[i-1][j+2] - promedio[1])*(matrixC1[i-1][j+2] - promedio[1])
                    + (matrixC1[i][j+1] - promedio[1])*(matrixC1[i][j+1] - promedio[1])
                    + (matrixC1[i][j+2] - promedio[1])*(matrixC1[i][j+2] - promedio[1])
                    + (matrixC1[i+1][j+1] - promedio[1])*(matrixC1[i+1][j+1] - promedio[1])
                    + (matrixC1[i+1][j+2] - promedio[1])*(matrixC1[i+1][j+2] - promedio[1]);

            varianza[2] = (matrixC1[i][j] - promedio[2])*(matrixC1[i][j] - promedio[2])
                    + (matrixC1[i+1][j-1] - promedio[2])*(matrixC1[i+1][j-1] - promedio[2])
                    + (matrixC1[i+2][j-1] - promedio[2])*(matrixC1[i+2][j-1] - promedio[2])
                    + (matrixC1[i+1][j] - promedio[2])*(matrixC1[i+1][j] - promedio[2])
                    + (matrixC1[i+2][j] - promedio[2])*(matrixC1[i+2][j] - promedio[2])
                    + (matrixC1[i+1][j+1] - promedio[2])*(matrixC1[i+1][j+1] - promedio[2])
                    + (matrixC1[i+2][j+1] - promedio[2])*(matrixC1[i+2][j+1] - promedio[2]);

            varianza[3] = (matrixC1[i][j] - promedio[3])*(matrixC1[i][j] - promedio[3])
                    + (matrixC1[i-1][j-2] - promedio[3])*(matrixC1[i-1][j-2] - promedio[3])
                    + (matrixC1[i-1][j-1] - promedio[3])*(matrixC1[i-1][j-1] - promedio[3])
                    + (matrixC1[i][j-1] - promedio[3])*(matrixC1[i][j-1] - promedio[3])
                    + (matrixC1[i][j-2] - promedio[3])*(matrixC1[i][j-2] - promedio[3])
                    + (matrixC1[i+1][j-2] - promedio[3])*(matrixC1[i+1][j-2] - promedio[3])
                    + (matrixC1[i+1][j-1] - promedio[3])*(matrixC1[i+1][j-1]) - promedio[3];

            varianza[4] = (matrixC1[i][j] - promedio[4])*(matrixC1[i][j] - promedio[4])
                    + (matrixC1[i-1][j-1] - promedio[4])*(matrixC1[i-1][j-1] - promedio[4])
                    + (matrixC1[i-2][j-2] - promedio[4])*(matrixC1[i-2][j-2] - promedio[4])
                    + (matrixC1[i-2][j-1] - promedio[4])*(matrixC1[i-2][j-1] - promedio[4])
                    + (matrixC1[i-1][j] - promedio[4])*(matrixC1[i-1][j] - promedio[4])
                    + (matrixC1[i-1][j-2] - promedio[4])*(matrixC1[i-1][j-2] - promedio[4])
                    + (matrixC1[i][j-1] - promedio[4])*(matrixC1[i][j-1] - promedio[4]);

            varianza[5] = (matrixC1[i][j] - promedio[5])*(matrixC1[i][j] - promedio[5])
                    + (matrixC1[i-1][j+1] - promedio[5])*(matrixC1[i-1][j+1] - promedio[5])
                    + (matrixC1[i-2][j+2] - promedio[5])*(matrixC1[i-2][j+2] - promedio[5])
                    + (matrixC1[i-1][j] - promedio[5])*(matrixC1[i-1][j] - promedio[5])
                    + (matrixC1[i-2][j+1] - promedio[5])*(matrixC1[i-2][j+1] - promedio[5])
                    + (matrixC1[i][j+1] - promedio[5])*(matrixC1[i][j+1] - promedio[5])
                    + (matrixC1[i-1][j+2] - promedio[5])*(matrixC1[i-1][j+2]) - promedio[5];

            varianza[6] = (matrixC1[i][j] - promedio[6])*(matrixC1[i][j] - promedio[6])
                    + (matrixC1[i+1][j+1] - promedio[6])*(matrixC1[i+1][j+1] - promedio[6])
                    + (matrixC1[i+2][j+2] - promedio[6])*(matrixC1[i+2][j+2] - promedio[6])
                    + (matrixC1[i+1][j] - promedio[6])*(matrixC1[i+1][j] - promedio[6])
                    + (matrixC1[i+2][j+1] - promedio[6])*(matrixC1[i+2][j+1] - promedio[6])
                    + (matrixC1[i][j+1] - promedio[6])*(matrixC1[i][j+1] - promedio[6])
                    + (matrixC1[i+1][j+2] - promedio[6])*(matrixC1[i+1][j+2] - promedio[6]);

            varianza[7] = (matrixC1[i+1][j-1] - promedio[7])*(matrixC1[i+1][j-1] - promedio[7])
                    + (matrixC1[i+2][j-2] - promedio[7])*(matrixC1[i+2][j-2] - promedio[7])
                    + (matrixC1[i][j-1] - promedio[7])*(matrixC1[i][j-1] - promedio[7])
                    + (matrixC1[i+1][j-2] - promedio[7])*(matrixC1[i+1][j-2] - promedio[7])
                    + (matrixC1[i+1][j] - promedio[7])*(matrixC1[i+1][j] - promedio[7])
                    + (matrixC1[i+2][j-1] - promedio[7])*(matrixC1[i+2][j-1] - promedio[7])
                    + (matrixC1[i][j] - promedio[7])*(matrixC1[i][j] - promedio[7]);

            for (int m = i-1; m < i+1; m++) {
                for (int n = j-1; n <j+1 ; n++) {
                    varianza[8] += (matrixC1[m][n] -  promedio[8])*(matrixC1[m][n] -  promedio[8]);
                }
            }

            for(int h = 0; h<8;h++){
                varianza[h] /= 7;
            }
            varianza[8] /= 9;
            min = 500.0f;
            indice = 0;
            for(int h = 0; h<9; h++){
                if(promedio[h]<min){
                    min = promedio[h];
                    indice = h;
                }
            }

            matrizAuxResultante[i][j] = floor(promedio[indice]);
            imagen.setPixel(i,j, qRgb(matrizAuxResultante[i][j], matrizAuxResultante[i][j], matrizAuxResultante[i][j]));
        }
    }
}

void Operaciones::calcularHistograma(QImage &imagen){
    for(int i = 0; i<256;i++){
        histograma[i]=0;
        histogramaEcualizado[i]=0;
    }
    int R;
    for (int m = 0; m < height; m++) {
        for (int n = 0; n <width ; n++) {
            R = QColor(imagen.pixel(m,n)).red();
            histograma[R] = histograma[R] + 1;
        }
    }
}


void Operaciones::ecualizarHistograma(){
    const int G = 256;

    float oper=0.0f;
    int H[G];
    for (int i = 0; i < G; i++) {
        H[i] = 0;
    }
    H[0] = histograma[0];

    //cout<<histograma[0]<<"\t"<<H[0]<<endl;
    for (int i = 1; i < G; i++) {
        H[i] = H[i-1] + histograma[i];

        //cout<<histograma[i]<<"\t"<<H[i]<<endl;
    }
    int aux;
    for (int i = 0; i < 256; i++) {
        oper = (255.0f/122500.0f)*H[i];
        aux = floorf(oper);
        histogramaEcualizado[i] = aux;
    }
}

void Operaciones::ecualizarImagen(QImage & imagen){
    int indice;
    for (int i = 0; i < 350; i++) {
        for (int j = 0; j < 350; j++) {
            indice = matrixC1[i][j];
            imagen.setPixel(i,j,qRgb(histogramaEcualizado[indice], histogramaEcualizado[indice], histogramaEcualizado[indice]));
        }
    }

}


void Operaciones::contrasteGamma(QImage & imagen, float y){
    float output;
    int final_output;
    for (int i = 0; i < 350; i++) {
        for (int j = 0; j < 350; j++) {
            output = pow(QColor(imagen.pixel(i,j)).red(), 1.0f/y);
            final_output = floor(output);
            cout<<final_output<<endl;
            if(final_output>255)
                final_output=255;
            imagen.setPixel(i,j,qRgb(final_output, final_output, final_output));
        }
    }
}


void Operaciones::contrasteStretching(QImage & imagen){
    float output;
    int final_output;
    int min = calcMin(imagen);
    int max = calcMax(imagen);
    for (int i = 0; i < 350; i++) {
        for (int j = 0; j < 350; j++) {
            output = ((matrixC1[i][j] - min)*250)/(max-min);
            final_output = floor(output);
            imagen.setPixel(i,j,qRgb(final_output, final_output, final_output));
        }
    }
}

int Operaciones::calcMin(QImage & imagen){
    int min = 256;
    for (int i = 0; i < 350; i++) {
        for (int j = 0; j < 350; j++) {
            if(QColor(imagen.pixel(i,j)).red()<min)
                min = QColor(imagen.pixel(i,j)).red();
        }
    }
    return min;
}


int Operaciones::calcMax(QImage & imagen){
    int max = -1;
    for (int i = 0; i < 350; i++) {
        for (int j = 0; j < 350; j++) {
            if(QColor(imagen.pixel(i,j)).red()>max)
                max = QColor(imagen.pixel(i,j)).red();
        }
    }
    return max;
}

void Operaciones::filtroSobel(QImage & imagen){

    int h1[3][3] = {{1,2,1},{0,0,0},{-1,-2,-1}};
    int h2[3][3] = {{1,0,-1},{2,0,-2},{1,0,-1}};


    int matriz1[350][350];
    int matriz2[350][350];
    for (int i = 0; i < 350; ++i) {
        for (int j = 0; j < 350; ++j) {
            matriz1[i][j]=0;
            matriz2[i][j]=0;
        }
    }

    int acum1, acum2;
    int m,n;
    for(int i = 1; i<height - 1; i++){
        for(int j = 1; j<width - 1; j++){
            acum1 = 0;
            acum2 = 0;
            m=0;
            n=0;
            for(int k = i-1; k<i+2; k++){
                for(int l = j - 1; l<j+2; l++){
                    acum1 += matrixC1[k][l]*h1[m][n];
                    acum2 += matrixC1[k][l]*h2[m][n];
                    n++;
                }
                m++;
                n=0;
            }
            matriz1[i][j] = floor(acum1);
            matriz2[i][j] = floor(acum2);

        }
    }
    acum1=0;
    for (int i = 0; i < 350; ++i) {
        for (int j = 0; j < 350; ++j) {
            acum1 = matriz1[i][j] + matriz2[i][j];
            if(acum1<50){
                acum1=0;
            }else{
                acum1=255;
            }
            imagen.setPixel(i,j, qRgb(acum1, acum1,acum1));
        }
    }
}

void Operaciones::filtroPrewitt(QImage & imagen){

    int h1[3][3] = {{1,1,1},{0,0,0},{-1,-1,-1}};
    int h2[3][3] = {{1,0,-1},{1,0,-1},{1,0,-1}};


    int matriz1[350][350];
    int matriz2[350][350];
    for (int i = 0; i < 350; ++i) {
        for (int j = 0; j < 350; ++j) {
            matriz1[i][j]=0;
            matriz2[i][j]=0;
        }
    }

    int acum1, acum2;
    int m,n;
    for(int i = 1; i<height - 1; i++){
        for(int j = 1; j<width - 1; j++){
            acum1 = 0;
            acum2 = 0;
            m=0;
            n=0;
            for(int k = i-1; k<i+2; k++){
                for(int l = j - 1; l<j+2; l++){
                    acum1 += matrixC1[k][l]*h1[m][n];
                    acum2 += matrixC1[k][l]*h2[m][n];
                    n++;
                }
                m++;
                n=0;
            }
            matriz1[i][j] = floor(acum1);
            matriz2[i][j] = floor(acum2);

        }
    }
    acum1=0;
    for (int i = 0; i < 350; ++i) {
        for (int j = 0; j < 350; ++j) {
            acum1 = matriz1[i][j] + matriz2[i][j];
            if(acum1<50){
                acum1=0;
            }else{
                acum1=255;
            }
            imagen.setPixel(i,j, qRgb(acum1, acum1,acum1));
        }
    }
}



QVector<double> Operaciones::getData(int tipo){
   QVector<double> data;
   if(tipo ==1){
       for (int i = 0; i < 256; ++i) {
           data << (double)histograma[i];
       }
   }else{
       for (int i = 0; i < 256; ++i) {
           data << (double)histogramaEcualizado[i];
       }
   }
   return data;
}

void Operaciones::filtroRoberts(QImage & imagen){
    int h1[2][2] = {{1,0},{0,-1}};
    int h2[2][2] = {{0,1},{-1,0}};


    int matriz1[350][350];
    int matriz2[350][350];
    for (int i = 0; i < 350; ++i) {
        for (int j = 0; j < 350; ++j) {
            matriz1[i][j]=0;
            matriz2[i][j]=0;
        }
    }

    int acum1, acum2;
    int m,n;
    for(int i = 1; i<height - 1; i++){
        for(int j = 1; j<width - 1; j++){
            acum1 = 0;
            acum2 = 0;
            m=0;
            n=0;
            for(int k = i; k<i+2; k++){
                for(int l = j; l<j+2; l++){
                    acum1 += matrixC1[k][l]*h1[m][n];
                    acum2 += matrixC1[k][l]*h2[m][n];
                    n++;
                }
                m++;
                n=0;
            }
            matriz1[i][j] = floor(acum1);
            matriz2[i][j] = floor(acum2);

        }
    }
    acum1=0;
    for (int i = 0; i < 350; ++i) {
        for (int j = 0; j < 350; ++j) {
            acum1 = matriz1[i][j] + matriz2[i][j];
            if(acum1<50){
                acum1=0;
            }else{
                acum1=255;
            }
            imagen.setPixel(i,j, qRgb(acum1, acum1,acum1));
        }
    }
}



























