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
    velocidadSalto(0),
    gravedad(15),
    saltando(false),
    enElAire(false)
{
    Objeto *objetoInteractivo = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
    objetoInteractivo->setPos(500, 600);
    objetoInteractivo->setSize(100, 100);
    escena->addItem(objetoInteractivo);
    objetoInteractivo->setZValue(2);

    personaje = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/sprites/Prisoner_1.png", 6, 4);
    personaje->setZValue(2);

    npc1 = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/sprites/blanco.png", 8, 1);
    npc1->setZValue(2);
    npc2 = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/sprites/blanco.png", 8, 1);
    npc2->setZValue(2);

    int posicionInicialX = 200;
    int posicionInicialY = 530;
    personaje->setPos(posicionInicialX, posicionInicialY);

    int posicionInicialX2 = 1000;
    int posicionInicialY2 = 490;
    npc2->setPos(posicionInicialX2, posicionInicialY2);

    int posicionInicialX1 = 2000;
    int posicionInicialY1 = 490;
    npc1->setPos(posicionInicialX1, posicionInicialY1);

    QPixmap fondo("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/escenas/escena nivel 1.jpg");

    fondoItem1 = new QGraphicsPixmapItem(fondo);
    fondoItem2 = new QGraphicsPixmapItem(fondo);
    fondoItem3 = new QGraphicsPixmapItem(fondo);
    fondoItem4 = new QGraphicsPixmapItem(fondo);

    fondoItem1->setPos(0, 0);
    fondoItem2->setPos(fondo.width(), 0);
    fondoItem3->setPos(2 * fondo.width(), 0);
    fondoItem4->setPos(3 * fondo.width(), 0);

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

        vista->centerOn(personaje);

        if (personaje->collidesWithItem(npc1) || personaje->collidesWithItem(npc2)) {
            personaje->setPos(200, 530);
        } else {
            float minX = 0;
            float maxX = escena->width() - personaje->boundingRect().width();
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

            npc1->moverPersonajeAdicional(5, minX, maxX);
            npc2->moverPersonajeAdicional(5, minX, maxX);
        }
    }
}

void MainWindow::detectarColisiones() {
    QList<QGraphicsItem *> objetos = escena->items();
    foreach (QGraphicsItem *objeto, objetos) {
        if (Objeto *caja = dynamic_cast<Objeto*>(objeto)) {
            if (objeto->collidesWithItem(personaje)) {
                moviendo = false;
                QRectF cajaRect = caja->getBoundingBox();
                if (velocidadSalto > 0) {
                    velocidadSalto = 0;
                    personaje->setY(caja->y() - personaje->boundingRect().height() + 50);
                    saltando = false;
                    enElAire = false;
                } else {
                    if (personaje->y() + personaje->boundingRect().height() <= caja->y()) {
                        personaje->setY(caja->y() - personaje->boundingRect().height());
                        if (saltando) {
                            saltando = false;
                            enElAire = false;
                            velocidadSalto = 0;
                        }
                    } else {
                        if (personaje->x() < caja->x()) {
                            personaje->setX(caja->x() - personaje->boundingRect().width());
                        } else {
                            personaje->setX(caja->x() + cajaRect.width());
                        }
                    }
                }
                qDebug() << "¡Colisión detectada con la caja!";
                return;
            }
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
    npc1->moverPersonajeAdicional(5, 2000, 2200);
    npc2->moverPersonajeAdicional(5, 1000, 1200);
}

void MainWindow::detenerAnimacionEspecial() {
    personaje->detenerAnimacionEspecial();
    modoEspecial = false;
    animando = false;
    temporizadorEspecial->stop();
}
