#include "particula.h"
#include <QPixmap>

Particula::Particula(QString rutaImagen, qreal velocidadX, qreal velocidadY, qreal duracion, int ancho, int alto, QObject *parent) : QObject(parent), QGraphicsPixmapItem() {
    setPixmap(QPixmap(rutaImagen).scaled(ancho, alto)); // Escalar la imagen al tamaño deseado
    this->velocidadX = velocidadX;
    this->velocidadY = velocidadY;
    this->duracion = duracion;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Particula::mover);
    timer->start(30); // Ajusta el tiempo de acuerdo a tus necesidades
}

Particula::~Particula() {
    delete timer;
}

void Particula::mover() {
    // Actualizar la posición
    setPos(x() + velocidadX, y() + velocidadY);

    // Reducir la duración
    duracion -= 0.00003; // Ajusta el valor de acuerdo a tus necesidades

    // Si la partícula ha terminado su duración, la eliminamos
    if (duracion <= 0) {
        delete this;
    }
}
