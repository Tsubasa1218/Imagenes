#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabs->setTabEnabled(1, false);
    ui->tabs->setCurrentIndex(0);
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

    QPixmap imagenOriginal2 = imagenOriginal.scaled(300,300);
    ui->original->setPixmap(imagenOriginal2);
    ui->transformed->clear();
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

    QPixmap final;
    final.convertFromImage(imagenFinal);
    ui->transformed->setPixmap(final);
    if(!imagenFinal.isNull())
        ui->tabs->setTabEnabled(1,true);
}

void MainWindow::on_boton_filtro_clicked()
{
    QImage imagenFiltrada = imagenFinal;
    int numVecinos = ui->numVecinos->text().toInt();
    if(ui->comboFiltros->currentText() == "Promedio"){
        transformer->convolucion(imagenFiltrada, numVecinos, 0);
    }else if(ui->comboFiltros->currentText() == "Gaussiano"){
        transformer->convolucion(imagenFiltrada, numVecinos, 1);
    }else if(ui->comboFiltros->currentText() == "Maximo"){
        transformer->convolucion(imagenFiltrada, numVecinos, 2);
    }else if(ui->comboFiltros->currentText() == "Minimo"){
            transformer->convolucion(imagenFiltrada, numVecinos, 3);
    }else if(ui->comboFiltros->currentText() == "Mediana"){
        transformer->convolucion(imagenFiltrada, numVecinos, 4);
    }else if(ui->comboFiltros->currentText() == "Nagao-Matsuyama"){
        transformer->convolucion(imagenFiltrada, numVecinos, 5);
    }else if(ui->comboFiltros->currentText() == "Sigma"){
        transformer->convolucion(imagenFiltrada, numVecinos, 6);
    }


    QPixmap imagenOriginal;
    imagenOriginal.convertFromImage(imagenFiltrada);
    ui->filtrada->setPixmap(imagenOriginal);
}

void MainWindow::on_tabs_tabBarClicked(int index)
{
    if(index == 1){
        QPixmap imagenOriginal;
        imagenOriginal.convertFromImage(imagenFinal);
        ui->original_filtro->setPixmap(imagenOriginal);
    }
}
