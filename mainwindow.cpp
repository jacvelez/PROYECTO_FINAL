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
    animando(false),
    fondoX1(0),
    fondoX2(0),
    fondoX3(0),
    fondoX4(0) // Agregamos inicialización de fondoX4
{
    personaje = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/LABORATORIO 5/LABORATORIO5/imagenes/sprites/Prisoner_1.png", 6, 4);
    personaje->setZValue(2);

    // Cambiar la posición inicial del personaje
    int posicionInicialX = 200; // Ajusta este valor según sea necesario
    int posicionInicialY = 530; // Ajusta este valor según sea necesario
    personaje->setPos(posicionInicialX, posicionInicialY);

    QPixmap fondo("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/LABORATORIO 5/LABORATORIO5/imagenes/escenas/escena nivel 1.jpg");

    // Crear cuatro elementos de fondo para efecto infinito
    fondoItem1 = new QGraphicsPixmapItem(fondo);
    fondoItem2 = new QGraphicsPixmapItem(fondo);
    fondoItem3 = new QGraphicsPixmapItem(fondo);
    fondoItem4 = new QGraphicsPixmapItem(fondo);

    fondoX1 = 0;
    fondoX2 = fondo.width();
    fondoX3 = 2 * fondo.width();
    fondoX4 = 3 * fondo.width(); // Establecemos la posición inicial de fondoX4

    fondoItem1->setPos(fondoX1, 0);
    fondoItem2->setPos(fondoX2, 0);
    fondoItem3->setPos(fondoX3, 0);
    fondoItem4->setPos(fondoX4, 0); // Ajustamos la posición en Y del cuarto fondo

    fondoItem1->setZValue(0);
    fondoItem2->setZValue(0);
    fondoItem3->setZValue(0);
    fondoItem4->setZValue(0);

    escena->addItem(fondoItem1);
    escena->addItem(fondoItem2);
    escena->addItem(fondoItem3);
    escena->addItem(fondoItem4); // Agregamos el cuarto fondo a la escena

    setCentralWidget(vista);
    vista->setScene(escena);
    escena->addItem(personaje);

    connect(temporizador, &QTimer::timeout, this, &MainWindow::moverPersonaje);
    temporizador->start(150);

    connect(temporizadorEspecial, &QTimer::timeout, this, &MainWindow::detenerAnimacionEspecial);

    // Configurar el QGraphicsView para seguir al personaje
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->centerOn(personaje);
}


MainWindow::~MainWindow() {
}

void MainWindow::moverPersonaje() {
    if (moviendo || personaje->estaAnimando()) {
        personaje->siguienteFrame(modoEspecial);

        // Mover el fondo para crear efecto continuo
        float velocidadFondo = 5.0; // Ajustar la velocidad del fondo si es necesario
        fondoX1 -= velocidadFondo;
        fondoX2 -= velocidadFondo;
        fondoX3 -= velocidadFondo;
        fondoX4 -= velocidadFondo; // Agregar movimiento al fondo 4

        if (fondoX1 + fondoItem1->pixmap().width() <= 0) {
            fondoX1 = fondoX4 + fondoItem4->pixmap().width(); // Ajustar el movimiento del fondo 1 al llegar al final
        }
        if (fondoX2 + fondoItem2->pixmap().width() <= 0) {
            fondoX2 = fondoX1 + fondoItem1->pixmap().width();
        }
        if (fondoX3 + fondoItem3->pixmap().width() <= 0) {
            fondoX3 = fondoX2 + fondoItem2->pixmap().width();
        }
        if (fondoX4 + fondoItem4->pixmap().width() <= vista->width()) { // Agregar condición para el fondo 4
            fondoX4 = fondoX3 + fondoItem3->pixmap().width();
        }

        fondoItem1->setPos(fondoX1, 0);
        fondoItem2->setPos(fondoX2, 0);
        fondoItem3->setPos(fondoX3, 0);
        fondoItem4->setPos(fondoX4, 0); // Agregar posición al fondo 4

        // Mover la vista para seguir al personaje
        vista->centerOn(personaje);

        // Establecer los límites de movimiento del personaje en el eje X
        float minX = 0;
        float maxX = fondoX3 + fondoItem3->pixmap().width() - personaje->boundingRect().width();
        float nuevaPosX = qBound(minX, personaje->x(), maxX);
        personaje->setX(nuevaPosX);

        // Establecer los límites de movimiento del personaje en el eje Y
        float minY = 0;
        float maxY = 530; // Límite superior en Y
        float nuevaPosY = qBound(minY, personaje->y(), maxY);
        personaje->setY(nuevaPosY);
    }
}



void MainWindow::keyPressEvent(QKeyEvent *event) {
    int step = 5; // Define la cantidad de movimiento por cada pulsación de tecla

    switch (event->key()) {
    case Qt::Key_W:
        if (personaje->y() > 0) { // Verifica si el personaje está dentro del límite superior
            personaje->mover(0, -step);
        }
        break;
    case Qt::Key_S:
        if (personaje->y() < 530) { // Verifica si el personaje está dentro del límite inferior
            personaje->mover(0, step);
        }
        break;
    case Qt::Key_A:
        moviendo = true;
        personaje->mover(-step, 0);
        break;
    case Qt::Key_D:
        moviendo = true;
        personaje->mover(step, 0);
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
