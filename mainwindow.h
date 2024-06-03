#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include "personajes.h"
#include "objetos.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void moverPersonaje();
    void detenerAnimacionEspecial();
    void moverNPCsIndependientes();
    void detectarColisiones();

private:
    const float minX = 0; // Límite izquierdo de movimiento
    const float maxX = 4600; // Límite derecho de movimiento (ajusta este valor según sea necesario)

    QGraphicsView *vista;
    QGraphicsScene *escena;
    QTimer *temporizador;
    QTimer *temporizadorEspecial;
    bool modoEspecial;
    bool moviendo;
    bool animando;
    Personaje *personaje;
    Personaje *npc1;
    Personaje *npc2;
    QGraphicsPixmapItem *fondoItem1;
    QGraphicsPixmapItem *fondoItem2;
    QGraphicsPixmapItem *fondoItem3;
    QGraphicsPixmapItem *fondoItem4;
    float velocidadSalto;
    float gravedad;
    bool saltando;
    bool enElAire;


};

#endif // MAINWINDOW_H
