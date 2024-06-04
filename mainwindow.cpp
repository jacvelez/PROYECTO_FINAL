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
        // Crear objetos interactivos y establecer sus posiciones
        Objeto *objetoInteractivo = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetoInteractivo->setPos(500, 600);
        objetoInteractivo->setSize(100, 100);
        escena->addItem(objetoInteractivo);
        objetoInteractivo->setZValue(2);
        Objeto *objetoInteractivo2 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetoInteractivo2->setPos(600, 600);
        objetoInteractivo2->setSize(100, 100);
        escena->addItem(objetoInteractivo2);

        Objeto *objetoInteractivo3 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetoInteractivo3->setPos(600, 500);
        objetoInteractivo3->setSize(100, 100);
        escena->addItem(objetoInteractivo3);

        Objeto *objetointeractivorectangulo = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/piso.png");
        objetointeractivorectangulo->setPos(800, 410);
        objetointeractivorectangulo->setSize(100, 100);
        escena->addItem(objetointeractivorectangulo);

        Objeto *objetointeractivorectangulo2 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/piso.png");
        objetointeractivorectangulo2->setPos(900, 410);
        objetointeractivorectangulo2->setSize(100, 100);
        escena->addItem(objetointeractivorectangulo2);

        Objeto *objetointeractivorectangulo3 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/piso.png");
        objetointeractivorectangulo3->setPos(1000, 410);
        objetointeractivorectangulo3->setSize(100, 100);
        escena->addItem(objetointeractivorectangulo3);

        Objeto *objetointeractivorectangulo4 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/piso.png");
        objetointeractivorectangulo4->setPos(1200, 410);
        objetointeractivorectangulo4->setSize(100, 100);
        escena->addItem(objetointeractivorectangulo4);

        Objeto *objetointeractivorectangulo5 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/piso.png");
        objetointeractivorectangulo5->setPos(1400, 410);
        objetointeractivorectangulo5->setSize(100, 100);
        escena->addItem(objetointeractivorectangulo5);

        Objeto *objetointeractivorectangulo6 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/piso.png");
        objetointeractivorectangulo6->setPos(1600, 410);
        objetointeractivorectangulo6->setSize(100, 100);
        escena->addItem(objetointeractivorectangulo6);

        Objeto *objetointeractivocaja = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja->setPos(1750, 600);
        objetointeractivocaja->setSize(100, 100);
        escena->addItem(objetointeractivocaja);

        Objeto *objetointeractivocaja2 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja2->setPos(1850, 600);
        objetointeractivocaja2->setSize(100, 100);
        escena->addItem(objetointeractivocaja2);

        Objeto *objetointeractivocaja3 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja3->setPos(1850, 500);
        objetointeractivocaja3->setSize(100, 100);
        escena->addItem(objetointeractivocaja3);

        Objeto *objetointeractivocaja4 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja4->setPos(1950, 600);
        objetointeractivocaja4->setSize(100, 100);
        escena->addItem(objetointeractivocaja4);

        Objeto *objetointeractivocaja5 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja5->setPos(1950, 500);
        objetointeractivocaja5->setSize(100, 100);
        escena->addItem(objetointeractivocaja5);

        Objeto *objetointeractivocaja6 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja6->setPos(1950, 400);
        objetointeractivocaja6->setSize(100, 100);
        escena->addItem(objetointeractivocaja6);

        Objeto *objetointeractivorectangulo7 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/piso.png");
        objetointeractivorectangulo7->setPos(2200, 350);
        objetointeractivorectangulo7->setSize(100, 100);
        escena->addItem(objetointeractivorectangulo7);

        Objeto *objetointeractivocaja7 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja7->setPos(3000, 600);
        objetointeractivocaja7->setSize(100, 100);
        escena->addItem(objetointeractivocaja7);

        Objeto *objetointeractivocaja8 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja8->setPos(3000, 500);
        objetointeractivocaja8->setSize(100, 100);
        escena->addItem(objetointeractivocaja8);


        Objeto *objetointeractivocaja9 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja9->setPos(3000, 400);
        objetointeractivocaja9->setSize(100, 100);
        escena->addItem(objetointeractivocaja9);

        Objeto *objetointeractivocaja10 = new Objeto("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/caja.png");
        objetointeractivocaja10->setPos(3000, 300);
        objetointeractivocaja10->setSize(100, 100);
        escena->addItem(objetointeractivocaja10);


        Pendulo *pendulo = new Pendulo();
        pendulo->setPos(300, 200); // Ajustar la posición según sea necesario
        escena->addItem(pendulo);
        pendulo->iniciarMovimiento(); // Iniciar el movimiento del péndulo

        // Crear personaje principal y NPCs, establecer posiciones y añadirlos a la escena
        personaje = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/sprites/Prisoner_1.png", 6, 4);
        personaje->setZValue(2);

        npc1 = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/sprites/blanco.png", 8, 1);
        npc1->setZValue(2);

        npc2 = new Personaje("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/sprites/blanco.png", 8, 1);
        npc2->setZValue(2);

        int posicionInicialX = 300;
        int posicionInicialY = 530;
        personaje->setPos(posicionInicialX, posicionInicialY);

        int posicionInicialX2 = 700;
        int posicionInicialY2 = 490;
        npc2->setPos(posicionInicialX2, posicionInicialY2);

        int posicionInicialX1 = 2000;
        int posicionInicialY1 = 490;
        npc1->setPos(posicionInicialX1, posicionInicialY1);

        // Crear y configurar los objetos para el fondo
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

        // Agregar los fondos a la escena
        escena->addItem(fondoItem1);
        escena->addItem(fondoItem2);
        escena->addItem(fondoItem3);
        escena->addItem(fondoItem4);

        // Establecer la escena y los objetos principales en la vista
        setCentralWidget(vista);
        vista->setScene(escena);
        escena->addItem(personaje);
        escena->addItem(npc1);
        escena->addItem(npc2);

        // Conectar los temporizadores a sus respectivas funciones de movimiento
        connect(temporizador, &QTimer::timeout, this, &MainWindow::moverPersonaje);
        temporizador->start(150);
        QTimer *npcTimer = new QTimer(this);
        connect(npcTimer, &QTimer::timeout, this, &MainWindow::moverNPCsIndependientes);
        npcTimer->start(100);
        connect(temporizadorEspecial, &QTimer::timeout, this, &MainWindow::detenerAnimacionEspecial);

        // Configurar la vista
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

        bool colisionConCaja = false;

        if (personaje->collidesWithItem(npc1) || personaje->collidesWithItem(npc2)) {
            mostrarMensaje("Te atraparon, intenta de nuevo");
            personaje->setPos(200, 530);
            colisionConCaja = true;
        } else {
            colisionConCaja = false;
            float minX = 0;
            float maxX = 5000; // Cambia este valor a 5000
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

        if (!colisionConCaja) {
            detectarColisiones();
        }
    }
}



void MainWindow::detectarColisiones() {
    QList<QGraphicsItem *> objetos = escena->items();

    foreach (QGraphicsItem *objeto, objetos) {
        if (Objeto *caja = dynamic_cast<Objeto*>(objeto)) {
            if (personaje->collidesWithItem(caja)) {
                qDebug() << "¡Colisión detectada con la caja!";

                moviendo = false;

                QRectF cajaRect = caja->getBoundingBox(); // Utiliza el nuevo método público

                if (velocidadSalto > 0) {
                    velocidadSalto = 0;
                    personaje->setY(caja->y() - personaje->boundingRect().height()+50);
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
                return;
            }
        }
    }
    qDebug() << "No hay colisión con la caja.";
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

    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    Particula *particula = nullptr; // Declarar la variable fuera del switch

    switch (event->button()) {
    case Qt::RightButton:
        // Crear nueva partícula
        particula = new Particula("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/PROYECTO FINAL/PROYECTOFINAL/imagenes/objetos/bala.png", 20, -2, 1.5, 30, 30); // Escala la imagen a un tamaño de 20x20 píxeles
        particula->setPos(personaje->x() + personaje->pixmap().width() / 2, personaje->y() + personaje->pixmap().height() / 2);
        escena->addItem(particula);
        break;
    default:
        QMainWindow::mousePressEvent(event);
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
    npc2->moverPersonajeAdicional(5, 700, 1700);
}

void MainWindow::detenerAnimacionEspecial() {
    personaje->detenerAnimacionEspecial();
    modoEspecial = false;
    animando = false;
    temporizadorEspecial->stop();
}
void MainWindow::mostrarMensaje(const QString& mensaje) {
    QMessageBox::information(this, tr("Mensaje"), mensaje);
}

