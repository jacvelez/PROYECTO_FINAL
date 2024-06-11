#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "barco.h"
#include "objeto.h"
#include <cstdlib>
#include <ctime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Inicializar generador de números aleatorios
    std::srand(std::time(nullptr));

    // Crear la vista y la escena
    vista = new QGraphicsView(this);
    escena = new QGraphicsScene(this);
    vista->setScene(escena);

    // Crear el barco del jugador y agregarlo a la escena
    barco = new Barco();
    barco->setZValue(2);
    barco->setPos(1000, 0);
    escena->addItem(barco);

    // Crear y agregar barcos NPC a la escena
    for (int i = 0; i < 8; ++i) {
        Barco *npc = new Barco(":/imagenes/sprites/barco_enemigo.png", 4, nullptr);
        npc->setPos(200 * (i + 1), 700 * (i + 1));
        npc->setZValue(2);
        escena->addItem(npc);
        barcosNPC.append(npc);
    }

    // Configurar el fondo de la escena
    QPixmap fondo(":/imagenes/escenas/ESCENA2_NIVEL2.jpg");

    for (int i = 0; i < 4; ++i) {
        QGraphicsPixmapItem *fondoItem = new QGraphicsPixmapItem(fondo);
        fondoItem->setPos(0, i * fondo.height());
        fondoItem->setZValue(0);
        escena->addItem(fondoItem);
    }

    // Crear y agregar varios faros a la escena en posiciones aleatorias
    const int numFaros = 5;
    const int maxX = 1500;
    const int maxY = 4000;

    for (int i = 0; i < numFaros; ++i) {
        int posX = std::rand() % maxX;
        int posY = std::rand() % maxY;

        Objeto *faro = new Objeto(200, 200, 350, 350, ":/imagenes/objetos/faro2.png");
        faro->setPos(posX, posY);
        faro->setZValue(1);
        escena->addItem(faro);
        faros.append(faro);
    }

    // Establecer la vista como widget central en la ventana principal
    setCentralWidget(vista);

    // Inicializar la barra de energía
    ui->energiaBar = new QProgressBar(this);
    ui->energiaBar->setRange(0, 100);
    ui->energiaBar->setValue(100);
    ui->energiaBar->setGeometry(800, 800, 200, 25);

    energiaTimer = new QTimer(this);
    connect(energiaTimer, &QTimer::timeout, this, &MainWindow::regenerarEnergia);
    energiaTimer->start(1000);

    npcTimer = new QTimer(this);
    connect(npcTimer, &QTimer::timeout, this, &MainWindow::moverNPC);
    npcTimer->start(50);
    qDebug() << "Temporizador NPC iniciado.";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QMainWindow::keyPressEvent(event);

    if (ui->energiaBar->value() > 0) {
        const int limiteXMin = 0;
        const int limiteXMax = 1500;
        const int limiteYMin = 0;
        const int limiteYMax = 4000;

        switch (event->key()) {
        case Qt::Key_D:
            if (barco->pos().x() + 10 <= limiteXMax) {
                barco->moveBy(10, 0);
                ui->energiaBar->setValue(ui->energiaBar->value() - 1);
            }
            break;
        case Qt::Key_W:
            if (barco->pos().y() - 10 >= limiteYMin) {
                barco->moveBy(0, -10);
                ui->energiaBar->setValue(ui->energiaBar->value() - 1);
            }
            break;
        case Qt::Key_S:
            if (barco->pos().y() + 10 <= limiteYMax) {
                barco->moveBy(0, 10);
                ui->energiaBar->setValue(ui->energiaBar->value() - 1);
            }
            break;
        case Qt::Key_A:
            if (barco->pos().x() - 10 >= limiteXMin) {
                barco->moveBy(-10, 0);
                ui->energiaBar->setValue(ui->energiaBar->value() - 1);
            }
            break;
        default:
            break;
        }

        vista->centerOn(barco);
        checkCollisions(); // Verificar colisiones después de mover el barco del jugador

        // Verificar si el barco ha alcanzado el límite superior
        if (barco->pos().y() >= 4000) {
            mostrarMensajeDeVictoria();
        }
    }
}

void MainWindow::regenerarEnergia()
{
    if (ui->energiaBar->value() < ui->energiaBar->maximum()) {
        ui->energiaBar->setValue(ui->energiaBar->value() + 8);
    }
}

void MainWindow::moverNPC()
{
    const int limiteYMin = 0;
    for (Barco* npc : barcosNPC) {
        if (npc->pos().y() - 5 >= limiteYMin) {
            npc->moveBy(0, -5);
        } else {
            npc->setPos(npc->pos().x(), 4000);
        }
    }
    checkCollisions(); // Verificar colisiones después de mover los NPCs
}

void MainWindow::checkCollisions()
{
    for (Barco* npc : barcosNPC) {
        if (barco->collidesWithItem(npc)) {
            barco->setPos(1000, 0);
            mostrarMensajeDeFallo();
            return; // Salir del método después de encontrar una colisión
        }
    }

    for (Objeto* faro : faros) {
        if (barco->collidesWithItem(faro)) {
            barco->setPos(1000, 0);
            mostrarMensajeDeFallo();
            return; // Salir del método después de encontrar una colisión
        }
    }
}

void MainWindow::mostrarMensajeDeFallo()
{
    QMessageBox::information(this, "Fallo", "Fallaste, vuelve a intentar.");
}

void MainWindow::mostrarMensajeDeVictoria()
{
    QMessageBox::information(this, "Victoria", "¡Ganaste!");
}

