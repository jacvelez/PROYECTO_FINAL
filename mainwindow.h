#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QKeyEvent>
#include <QMessageBox>
#include "personajes.h"
#include "objetos.h"
#include "particula.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void moverPersonaje();
    void detenerAnimacionEspecial();
    void moverNPCsIndependientes();
    void detectarColisiones();
    void mostrarMensaje(const QString& mensaje); // Agregada función para mostrar el mensaje flotante

private:
    const float minX = 0; // Límite izquierdo de movimiento
    const float maxX = 4600; // Límite derecho de movimiento (ajusta este valor según sea necesario)
    const float minY = 0; // Límite superior de movimiento
    const float maxY = 530; // Límite inferior de movimiento
    int intentos; // Variable para contar los intentos
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
    Objeto *objetoInteractivo;
    Objeto *objetoInteractivo1;
    Objeto *objetoInteractivo2;
    Objeto *objetointeractivorectangulo;
    Objeto *objetointeractivorectangulo2;
    Objeto *objetointeractivorectangulo3;
    QGraphicsPixmapItem *fondoItem1;
    QGraphicsPixmapItem *fondoItem2;
    QGraphicsPixmapItem *fondoItem3;
    QGraphicsPixmapItem *fondoItem4;
    float velocidadSalto;
    float gravedad;
    bool saltando;
    bool enElAire;
    QMessageBox* messageBox; // Cuadro de mensaje flotante

};

#endif // MAINWINDOW_H
