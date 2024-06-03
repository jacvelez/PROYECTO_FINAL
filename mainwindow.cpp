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
    fondoX4(0), // Agregamos inicialización de fondoX4
    velocidadSalto(0),
    gravedad(15), // Ajustar la gravedad según sea necesario
    saltando(false),
    enElAire(false)
{
    personaje = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/LABORATORIO 5/LABORATORIO5/imagenes/sprites/Prisoner_1.png", 6, 4);
    personaje->setZValue(2);

    npc1 = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/LABORATORIO5/imagenes/sprites/blanco.png", 8, 1);
    npc1->setZValue(2);
    npc2 = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/LABORATORIO5/imagenes/sprites/blanco.png", 8, 1);
    npc2->setZValue(2);

    int posicionInicialX = 200;
    int posicionInicialY = 530;
    personaje->setPos(posicionInicialX, posicionInicialY);

    int posicionInicialX2 = 300;
    int posicionInicialY2 = 490;
    npc2->setPos(posicionInicialX2, posicionInicialY2);

    int posicionInicialX3 = 400;
    int posicionInicialY3 = 490;
    npc1->setPos(posicionInicialX3, posicionInicialY3);

    QPixmap fondo("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/LABORATORIO 5/LABORATORIO5/imagenes/escenas/escena nivel 1.jpg");

    fondoItem1 = new QGraphicsPixmapItem(fondo);
    fondoItem2 = new QGraphicsPixmapItem(fondo);
    fondoItem3 = new QGraphicsPixmapItem(fondo);
    fondoItem4 = new QGraphicsPixmapItem(fondo);

    fondoX1 = 0;
    fondoX2 = fondo.width();
    fondoX3 = 2 * fondo.width();
    fondoX4 = 3 * fondo.width();

    fondoItem1->setPos(fondoX1, 0);
    fondoItem2->setPos(fondoX2, 0);
    fondoItem3->setPos(fondoX3, 0);
    fondoItem4->setPos(fondoX4, 0);

    fondoItem1->setZValue(0);
    fondoItem2->setZValue(0);
    fondoItem3->setZValue(0);
    fondoItem4->setZValue(0);

    escena->addItem(fondoItem1);
    escena->addItem(fondoItem2);
    escena->addItem(fondoItem3);
    escena->addItem(fondoItem4);

    setCentralWidget(vista);
    vista->setScene(escena);
    escena->addItem(personaje);
    escena->addItem(npc1);
    escena->addItem(npc2);

    connect(temporizador, &QTimer::timeout, this, &MainWindow::moverPersonaje);
    temporizador->start(150);
    QTimer *npcTimer = new QTimer(this);
    connect(npcTimer, &QTimer::timeout, this, &MainWindow::moverNPCsIndependientes);
    npcTimer->start(100);
    connect(temporizadorEspecial, &QTimer::timeout, this, &MainWindow::detenerAnimacionEspecial);

    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->centerOn(personaje);
}

MainWindow::~MainWindow() {
    delete npc1;
    delete npc2;
}

void MainWindow::moverPersonaje() {
    if (moviendo || personaje->estaAnimando() || saltando) {
        personaje->siguienteFrame(modoEspecial);
        npc1->siguienteFrame(modoEspecial);
        npc2->siguienteFrame(modoEspecial);

        float velocidadFondo = 5.0;
        fondoX1 -= velocidadFondo;
        fondoX2 -= velocidadFondo;
        fondoX3 -= velocidadFondo;
        fondoX4 -= velocidadFondo;

        if (fondoX1 + fondoItem1->pixmap().width() <= 0) {
            fondoX1 = fondoX4 + fondoItem4->pixmap().width();
        }
        if (fondoX2 + fondoItem2->pixmap().width() <= 0) {
            fondoX2 = fondoX1 + fondoItem1->pixmap().width();
        }
        if (fondoX3 + fondoItem3->pixmap().width() <= 0) {
            fondoX3 = fondoX2 + fondoItem2->pixmap().width();
        }
        if (fondoX4 + fondoItem4->pixmap().width() <= vista->width()) {
            fondoX4 = fondoX3 + fondoItem3->pixmap().width();
        }

        fondoItem1->setPos(fondoX1, 0);
        fondoItem2->setPos(fondoX2, 0);
        fondoItem3->setPos(fondoX3, 0);
        fondoItem4->setPos(fondoX4, 0);

        vista->centerOn(personaje);

        // Verifica colisiones con los NPCs
        if (personaje->collidesWithItem(npc1) || personaje->collidesWithItem(npc2)) {
            // Si hay colisión con alguno de los NPCs, devuelve al personaje al punto inicial
            personaje->setPos(200, 530);
        } else {
            float minX = 0;
            float maxX = fondoX3 + fondoItem3->pixmap().width() - personaje->boundingRect().width();
            float nuevaPosX = qBound(minX, personaje->x(), maxX);
            personaje->setX(nuevaPosX);

            if (saltando) {
                personaje->setY(personaje->y() + velocidadSalto);
                velocidadSalto += gravedad;

                if (personaje->y() >= 530) {
                    personaje->setY(530);
                    saltando = false;
                    enElAire = false;
                    velocidadSalto = 0;
                }
            } else {
                float minY = 0;
                float maxY = 530;
                float nuevaPosY = qBound(minY, personaje->y(), maxY);
                personaje->setY(nuevaPosY);
            }

            // Movimiento de personajes adicionales
            npc1->moverPersonajeAdicional(5, minX, maxX);
            npc2->moverPersonajeAdicional(5, minX, maxX);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    int step = 5;

    switch (event->key()) {
    case Qt::Key_W:
        if (!saltando && !enElAire) {
            saltando = true;
            enElAire = true;
            velocidadSalto = -60;
        }
        break;
    case Qt::Key_S:
        if (personaje->y() < 530) {
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
void MainWindow::moverNPCsIndependientes() {
    // Llama al método moverPersonajeAdicional de cada NPC para actualizar su posición
    npc1->moverPersonajeAdicional(5, 400, 650);
    npc2->moverPersonajeAdicional(5, 500, 750);
    // Agrega más llamadas para otros NPCs si los tienes
}
void MainWindow::detenerAnimacionEspecial() {
    personaje->detenerAnimacionEspecial();
    modoEspecial = false;
    animando = false;
    temporizadorEspecial->stop();
}


