
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QLinearGradient gradient(0, 0, 0, 400);
    gradient.setColorAt(0, QColor(90, 90, 90));
    gradient.setColorAt(0.38, QColor(105, 105, 105));
    gradient.setColorAt(1, QColor(70, 70, 70));
    ui->customPlot->setBackground(QBrush(gradient));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_botonAbrir_clicked()
{
    textoImagen = QFileDialog::getOpenFileName(this,
                                                   tr("Busca la imagen")
                                                   );

    /*QPixmap imagenOriginal;

    imagenOriginal.load(textoImagen);

    QPixmap imagenOriginal2 = imagenOriginal.scaled(350,350);
    ui->imagenF->setPixmap(imagenOriginal2);*/

    QImage imagenPrueba(textoImagen);

    QList<int*> kluster1;
    QList<int*> kluster2;
    QList<int*> kluster3;
    QList<int*> kluster4;

    int c1[3] = {0,0,0};
    int c2[3] = {120,120,120};
    int c3[3] = {180,180,180};
    int c4[3] = {255,255,255};

    int c1v[3] = {0,0,0};
    int c2v[3] = {120,120,120};
    int c3v[3] = {180,180,180};
    int c4v[3] = {255,255,255};

    //int m1 = 0;
    //int m2 = 0;
    //int m3 = 0;
    //int m4=0;
    int min1=0;

    while(c1[0] == c1v[0] && c1[1] == c1v[1] && c1[2] == c1v[2] &&
          c2[0] == c2v[0] && c2[1] == c2v[1] && c2[2] == c2v[2] &&
          c3[0] == c3v[0] && c3[1] == c3v[1] && c3[2] == c3v[2] &&
          c4[0] == c4v[0] && c4[1] == c4v[1] && c4[2] == c4v[2]){
        for(int i = 0; i<3;i++){
            c1v[i] = c1[i];
            c2v[i] = c2[i];
            c3v[i] = c3[i];
            c4v[i] = c4[i];
        }
        kluster1.clear();
        kluster2.clear();
        kluster3.clear();
        kluster4.clear();

        for(int i = 0; i<imagenPrueba.width();i++){
            for(int j = 0; j < imagenPrueba.height() ; j++){
                int R = QColor(imagenPrueba.pixel(i,j)).red();
                int G = QColor(imagenPrueba.pixel(i,j)).green();
                int B = QColor(imagenPrueba.pixel(i,j)).blue();

                const int m1 = sqrt((R-c1[0])*(R-c1[0]) + (G-c1[1])*(G-c1[1]) +(B-c1[2])*(B-c1[2]));
                const int m2 = sqrt((R-c2[0])*(R-c2[0]) + (G-c2[1])*(G-c2[1]) +(B-c2[2])*(B-c2[2]));
                const int m3 = sqrt((R-c3[0])*(R-c3[0]) + (G-c3[1])*(G-c3[1]) +(B-c3[2])*(B-c3[2]));
                const int m4 = sqrt((R-c4[0])*(R-c4[0]) + (G-c4[1])*(G-c4[1]) +(B-c4[2])*(B-c4[2]));

                min1 = min(min(m1,m2), min(m3,m4));

                if (min1 == m1){
                    int aux[5] ={R, G , B, i, j};
                    kluster1 << aux;
                }else if (min1 == m2){
                    int aux[5] ={R, G , B, i, j};
                    kluster2 << aux;
                }else if (min1 == m3){
                    int aux[5] ={R, G , B, i, j};
                    kluster3 << aux;
                }else if (min1 == m4){
                    int aux[5] ={R, G , B, i, j};
                    kluster4 << aux;
                }

            }
        }

        int pr;
        int pg;
        int pb;

        for(int i = 0; i<kluster1.size();i++){

            pr += kluster1[i][0];
            pg += kluster1[i][1];
            pb += kluster1[i][2];

        }
        c1[0] = floor(pr/kluster1.size());
        c1[1] = floor(pg/kluster1.size());
        c1[3] = floor(pb/kluster1.size());

        for(int i = 0; i<kluster2.size();i++){
            pr += kluster2[i][0];
            pg += kluster2[i][1];
            pb += kluster2[i][2];
        }
        c2[0] = floor(pr/kluster2.size());
        c2[1] = floor(pg/kluster2.size());
        c2[3] = floor(pb/kluster2.size());

        for(int i = 0; i<kluster3.size();i++){
            pr += kluster3[i][0];
            pg += kluster3[i][1];
            pb += kluster3[i][2];
        }
        c3[0] = floor(pr/kluster3.size());
        c3[1] = floor(pg/kluster3.size());
        c3[3] = floor(pb/kluster3.size());

        for(int i = 0; i<kluster4.size();i++){
            pr += kluster4[i][0];
            pg += kluster4[i][1];
            pb += kluster4[i][2];
        }
        c4[0] = floor(pr/kluster4.size());
        c4[1] = floor(pg/kluster4.size());
        c4[3] = floor(pb/kluster4.size());

    }

    //construir la imagen
    for(int k = i-vecinos; k<i+vecinos+1; k++){
        for(int l = j - vecinos; l<j+vecinos+1; l++){
            acum += matrixC1[k][l];
        }
    }

    acum /= kernelValue;
    matrizAuxResultante[i][j] = floor(acum);
    imagen.setPixel(i,j, qRgb(matrizAuxResultante[i][j], matrizAuxResultante[i][j], matrizAuxResultante[i][j]));
        QPixmap imagenOriginal;
        imagenOriginal.load(textoImagen);
        QPixmap imagenOriginal2 = imagenOriginal.scaled(350,350);
        ui->imagenF->setPixmap(imagenOriginal2);

    /*QPixmap imagenOriginal;

    imagenOriginal.load(textoImagen);

    QPixmap imagenOriginal2 = imagenOriginal.scaled(350,350);
    ui->imagenF->setPixmap(imagenOriginal2);*/
}

void MainWindow::on_botonTrans_clicked()
{
    transformer = new Operaciones();

    if(ui->comboBox->currentText() == "RGB -> Y"){
         imagenFinal= transformer->leerImagen(textoImagen, Y);

    }else if(ui->comboBox->currentText() == "RGB -> YUV"){
        imagenFinal = transformer->leerImagen(textoImagen, YUV);

    }else if(ui->comboBox->currentText() == "RGB -> HSI"){
        imagenFinal = transformer->leerImagen(textoImagen, HSI);

    }else if(ui->comboBox->currentText() == "RGB -> HSV"){
        imagenFinal = transformer->leerImagen(textoImagen, HSV);

    }else if(ui->comboBox->currentText() == "RGB -> R"){
        imagenFinal = transformer->leerImagen(textoImagen, RED);

    }else if(ui->comboBox->currentText() == "RGB -> G"){
        imagenFinal = transformer->leerImagen(textoImagen, GREEN);

    }else if(ui->comboBox->currentText() == "RGB -> B"){
        imagenFinal = transformer->leerImagen(textoImagen, BLUE);

    }else if(ui->comboBox->currentText() == "RGB -> YIQ"){
        imagenFinal = transformer->leerImagen(textoImagen, YIQ);

    }else if(ui->comboBox->currentText() == "RGB -> YCbCr"){
        imagenFinal = transformer->leerImagen(textoImagen, YCbCr);
    }else if(ui->comboBox->currentText() == "RGB -> Opponent"){
        imagenFinal = transformer->leerImagen(textoImagen, OPP);
    }else if(ui->comboBox->currentText() == "RGB -> CIE"){
        imagenFinal = transformer->leerImagen(textoImagen, CIE);
    }else if(ui->comboBox->currentText() == "RGB -> I1I2I3"){
            imagenFinal = transformer->leerImagen(textoImagen, III);
    }
    imagenOriginal=imagenFinal;
    QPixmap final;
    final.convertFromImage(imagenFinal);
    ui->imagenF->setPixmap(final);
}

void MainWindow::on_boton_filtro_clicked()
{
    int numVecinos = ui->numVecinos->text().toInt();
    if(ui->comboFiltros->currentText() == "Promedio"){
        transformer->convolucion(imagenFinal, numVecinos, 0);
    }else if(ui->comboFiltros->currentText() == "Gaussiano"){
        transformer->convolucion(imagenFinal, numVecinos, 1);
    }else if(ui->comboFiltros->currentText() == "Maximo"){
        transformer->convolucion(imagenFinal, numVecinos, 2);
    }else if(ui->comboFiltros->currentText() == "Minimo"){
            transformer->convolucion(imagenFinal, numVecinos, 3);
    }else if(ui->comboFiltros->currentText() == "Mediana"){
        transformer->convolucion(imagenFinal, numVecinos, 4);
    }else if(ui->comboFiltros->currentText() == "Nagao-Matsuyama"){
        transformer->convolucion(imagenFinal, numVecinos, 5);
    }else if(ui->comboFiltros->currentText() == "Sobel"){
        transformer->convolucion(imagenFinal, 0, 12);
    }else if(ui->comboFiltros->currentText() == "Prewitt"){
        transformer->convolucion(imagenFinal, 0, 13);
    }else if(ui->comboFiltros->currentText() == "Roberts"){
        transformer->convolucion(imagenFinal, 0, 14);
    }else if(ui->comboFiltros->currentText() == "Sigma"){
        transformer->convolucion(imagenFinal, numVecinos, 6);
    }


    QPixmap imagen;
    imagen.convertFromImage(imagenFinal);
    ui->imagenF->setPixmap(imagen);
}

void MainWindow::on_ecualizarBoton_clicked()
{
    QPixmap imagen;
    transformer->ecualizarHistograma();
    transformer->ecualizarImagen(imagenFinal);
    mostrarHistograma(2);
    imagen.convertFromImage(imagenFinal);
    ui->imagenF->setPixmap(imagen);
}

void MainWindow::on_calcularHistogramaButton_clicked()
{
    transformer->calcularHistograma(imagenFinal);
    mostrarHistograma(1);
}

void MainWindow::on_originalImagen_clicked()
{
    imagenFinal=imagenOriginal;
    QPixmap imagen;

    imagen.convertFromImage(imagenOriginal);
    ui->imagenF->setPixmap(imagen);
}

void MainWindow::on_boton_contraste_clicked()
{
    float gamma = ui->valorGamma->text().toFloat();
    if(ui->combo_constraste->currentText() == "Correccion Gamma"){
        transformer->contrasteGamma(imagenFinal, gamma);
    }else{
        transformer->contrasteStretching(imagenFinal);
    }
    QPixmap imagen;

    imagen.convertFromImage(imagenFinal);
    ui->imagenF->setPixmap(imagen);
}

void MainWindow::mostrarHistograma(int tipo){
    // set dark background gradient:
    ui->customPlot->clearPlottables();


    // create empty bar chart objects:
    QCPBars *values = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    values->setAntialiased(false); // gives more crisp, pixel aligned bar borders

    values->setStackingGap(1);

    // set names and colors:
    values->setName("values");
    values->setPen(QPen(QColor(0, 168, 140).lighter(130)));
    values->setBrush(QColor(0, 168, 140));

    // prepare x axis with country labels:
    QVector<double> ticks;
    QVector<QString> labels;
    for (int i = 0; i < 256; ++i) {
        ticks << i;
    }
    QString valor;
    for (int i = 0; i < 256; ++i) {
        valor = QString::number(i);
        labels << "";
    }

    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    ui->customPlot->xAxis->setTicker(textTicker);
    ui->customPlot->xAxis->setTickLabelRotation(60);
    ui->customPlot->xAxis->setSubTicks(false);
    ui->customPlot->xAxis->setTickLength(0, 4);
    ui->customPlot->xAxis->setRange(0, 270);
    ui->customPlot->xAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->xAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->xAxis->grid()->setVisible(true);
    ui->customPlot->xAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));
    ui->customPlot->xAxis->setTickLabelColor(Qt::white);
    ui->customPlot->xAxis->setLabelColor(Qt::white);

    // prepare y axis:
    ui->customPlot->yAxis->setRange(0, 2000);
    ui->customPlot->yAxis->setPadding(5); // a bit more space to the left border
    ui->customPlot->yAxis->setLabel("Valores");
    ui->customPlot->yAxis->setBasePen(QPen(Qt::white));
    ui->customPlot->yAxis->setTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->setSubTickPen(QPen(Qt::white));
    ui->customPlot->yAxis->grid()->setSubGridVisible(true);
    ui->customPlot->yAxis->setTickLabelColor(Qt::white);
    ui->customPlot->yAxis->setLabelColor(Qt::white);
    ui->customPlot->yAxis->grid()->setPen(QPen(QColor(130, 130, 130), 0, Qt::SolidLine));
    ui->customPlot->yAxis->grid()->setSubGridPen(QPen(QColor(130, 130, 130), 0, Qt::DotLine));

    // Add data:
    QVector<double> valuesData;
    if(tipo ==1)
        valuesData = transformer->getData(1);
    if(tipo ==2)
        valuesData = transformer->getData(2);

    values->setData(ticks, valuesData);

    // setup legend:
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignTop|Qt::AlignHCenter);
    ui->customPlot->legend->setBrush(QColor(255, 255, 255, 100));
    ui->customPlot->legend->setBorderPen(Qt::NoPen);
    QFont legendFont = font();
    legendFont.setPointSize(10);
    ui->customPlot->legend->setFont(legendFont);
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    ui->customPlot->replot();
}
