#include "operaciones.h"

Operaciones::Operaciones()
{
    width = 300;
    height = 300;
    this->vecinos = 0;
    kernelValue = 0;

    for(int i = 0; i<width;i++){
        for(int j = 0; j < height ; j++){
            matrizAuxResultante[i][j] = 0;
        }
    }

    for (int i = 0; i < 256; i++) {
        pointersArray[i] = i;
    }


}
void Operaciones::inicializarKernel(int nVal, int tipo)
{
    this->vecinos = nVal;
    this->kernelValue = (nVal*2 +1)*(nVal*2 +1);
    if(tipo == 1){
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
                //cout<<kernelGauss[i][j]<<" ";
            }
            //cout<<endl;
        }
        cout<<acum<<endl;
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
        RGB(transf);
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

void Operaciones::RGB(int color){
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
    inicializarKernel(numVecinos, tipo);
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
        filtroGaussiano(imagen);
    }else if(tipo == 2 || tipo == 3){
        filtroOrden(imagen, tipo);
    }else if(tipo == 6)
        filtroSigma(imagen);
    else if(tipo == 5)
        filtroNagao(imagen);
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
    pixel2pointers(imagen);
}


void Operaciones::calcularHistograma(){
    int indice;
    for (int i = 0; i < 300; ++i) {
        for (int j = 0; j < 300; ++j) {
            indice = matrixC1[i][j];
            histograma[indice] = histograma[indice] + 1;
        }
    }
}

void Operaciones::ecualizarHistograma(){
    const int G = 256;
    size = width*height;
    float oper=0.0f;
    int H[G];
    for (int i = 0; i < G; i++) {
        H[i] = 0;
    }
    H[0] = histograma[0];
    for (int i = 1; i < G; i++) {
        H[i] = H[i-1] + histograma[i];

    }
    for (int i = 0; i < 256; i++) {
        oper = (255/size)*H[i];
        histogramaEcualizado[i] = floor(oper);
    }
}

void Operaciones::ecualizarImagen(QImage & imagen){
    int indice;
    for (int i = 0; i < 300; i++) {
        for (int j = 0; j < 300; j++) {
            indice = matrixC1[i][j];
            imagen.setPixel(i,j,qRgb(histogramaEcualizado[indice], histogramaEcualizado[indice], histogramaEcualizado[indice]));
        }
    }
}














































