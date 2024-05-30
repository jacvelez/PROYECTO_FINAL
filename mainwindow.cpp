#include "mainwindow.h"
#include <QPixmap>
#include <QTimer>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    vista(new QGraphicsView(this)),
    escena(new QGraphicsScene(this)),
    temporizador(new QTimer(this)),
    temporizadorEspecial(new QTimer(this)),
    modoEspecial(false),
    moviendo(false),
    animando(false)
{
    // Crear un objeto de la clase Objetos y agregarlo a la escena
    Objetos *rectangulo = new Objetos();
    escena->addItem(rectangulo);
    rectangulo->setZValue(1);

    personaje = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/LABORATORIO 5/LABORATORIO5/imagenes/sprites/Prisoner_1.png", 6, 4);
    personaje->setZValue(1);

    // Cambiar la posición inicial del personaje
    int posicionInicialX = 200; // Ajusta este valor según sea necesario
    int posicionInicialY = 190; // Ajusta este valor según sea necesario
    personaje->setPos(posicionInicialX, posicionInicialY);

    QPixmap fondo("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/LABORATORIO 5/LABORATORIO5/imagenes/escenas/escena nivel 1.jpg");
    QGraphicsPixmapItem *fondoItem = new QGraphicsPixmapItem(fondo);

    escena->addItem(fondoItem);
    setCentralWidget(vista);
    vista->setScene(escena);
    escena->addItem(personaje);

    connect(temporizador, &QTimer::timeout, this, &MainWindow::moverPersonaje);
    temporizador->start(150);

    connect(temporizadorEspecial, &QTimer::timeout, this, &MainWindow::detenerAnimacionEspecial);
}

MainWindow::~MainWindow() {
}

void MainWindow::moverPersonaje() {
    if (moviendo || personaje->estaAnimando()) {
        personaje->siguienteFrame(modoEspecial);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_W:
        personaje->mover(0, -5);
        break;
    case Qt::Key_S:
        personaje->mover(0, 5);
        break;
    case Qt::Key_A:
        moviendo = true;
        personaje->mover(-5, 0);
        break;
    case Qt::Key_D:
        moviendo = true;
        personaje->mover(5, 0);
        break;
    case Qt::Key_K:
        personaje->alternarModoEspecial();
        modoEspecial = !modoEspecial;
        animando = true;
        temporizadorEspecial->start(900);
        break;
    default:
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_A:
    case Qt::Key_D:
        moviendo = false;
        break;
    default:
        QMainWindow::keyReleaseEvent(event);
    }
}

void MainWindow::detenerAnimacionEspecial() {
    personaje->detenerAnimacionEspecial();
    modoEspecial = false;
    animando = false;
    temporizadorEspecial->stop();
}
