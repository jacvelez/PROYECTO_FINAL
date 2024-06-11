#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QProgressBar>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>

class Barco;
class Objeto;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void regenerarEnergia();
    void moverNPC();

private:
    Ui::MainWindow *ui;
    QGraphicsView *vista;
    QGraphicsScene *escena;
    Barco *barco;
    QList<Barco*> barcosNPC;
    QList<Objeto*> faros;
    QProgressBar *energiaBar;
    QTimer *energiaTimer;
    QTimer *npcTimer;

    void checkCollisions();
    void mostrarMensajeDeFallo();
    void mostrarMensajeDeVictoria();
};

#endif // MAINWINDOW_H


