#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "operaciones.h"
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString textoImagen;

    enum{
        RED,
        GREEN,
        BLUE,
        Y,
        YUV,
        YIQ,
        YCbCr,
        HSI,
        HSV,
        OPP,
        CIE,
        III,
        SOB,
        PRE,
        ROB
    };
    QImage imagenFinal, imagenOriginal;
    Operaciones * transformer;
    void mostrarHistograma(int tipo);


private slots:
    void on_botonAbrir_clicked();

    void on_botonTrans_clicked();

    void on_boton_filtro_clicked();

    void on_ecualizarBoton_clicked();

    void on_calcularHistogramaButton_clicked();

    void on_originalImagen_clicked();

    void on_boton_contraste_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
