
#include "mainwindow.h"
#include "ui_mainwindow.h"


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

    QPixmap imagenOriginal;

    imagenOriginal.load(textoImagen);

    QPixmap imagenOriginal2 = imagenOriginal.scaled(350,350);
    ui->imagenF->setPixmap(imagenOriginal2);
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
    int threshold;
    threshold = -1;
    if(ui->manualThreshold->isChecked()){
        try{
            threshold = ui->userThreshold->text().toInt();
        }catch(...){
            cout<<"Error"<<endl;
        }
    }else if(ui->isoButton->isChecked()){
        threshold = 2;
    }else if(ui->otsuButton->isChecked()){
        threshold = 1;
    }

    transformer->calcularHistograma(imagenFinal, threshold);
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
