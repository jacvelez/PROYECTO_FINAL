#include "barco.h"

Barco::Barco(QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), filaActual(0), frameActual(0), anchoFrame(180), altoFrame(800 / 5)
{
    // Cargar el sprite
    sprite = QPixmap(":/imagenes/sprites/barco_prisionero.png");

    // Recortar el sprite para mostrar solo la primera fila completa de frames
    int x = frameActual * anchoFrame;
    int y = 0; // Solo la primera fila
    setPixmap(sprite.copy(x, y, anchoFrame, altoFrame));
}


Barco::Barco(const QString &imagePath, int fila, QGraphicsItem *parent)
    : QObject(), QGraphicsPixmapItem(parent), filaActual(fila - 1), frameActual(0), anchoFrame(122), altoFrame(164) // Ajustar el tamaño del frame para un solo cuadro
{
    // Cargar el sprite
    sprite = QPixmap(imagePath);

    // Recortar el sprite para mostrar solo la fila especificada de frames
    int x = frameActual * anchoFrame;
    int y = filaActual * altoFrame;
    QPixmap recorte = sprite.copy(x, y, anchoFrame, altoFrame);

    // Ajustar la escala del QPixmapItem
    setPixmap(recorte.scaled(anchoFrame * 3, altoFrame * 3)); // Aumenta la escala al doble
}

void Barco::actualizarFrame()
{
    // Actualizar el frame del sprite
    frameActual = (frameActual + 1) % 4; // Suponiendo que hay 4 frames en total

    // Recortar y actualizar el pixmap con el nuevo frame
    int x = frameActual * anchoFrame;
    int y = filaActual * altoFrame;
    setPixmap(sprite.copy(x, y, anchoFrame, altoFrame));
}

void Barco::setFilaActual(int fila)
{
    filaActual = fila;
    int x = frameActual * anchoFrame;
    int y = filaActual * altoFrame;
    setPixmap(sprite.copy(x, y, anchoFrame, altoFrame));
}

void Barco::mover()
{
    const int limiteYMin = 0;
    if (this->pos().y() - 5 >= limiteYMin) {
        this->moveBy(0, -5); // Mueve el barco hacia arriba
    } else {
        this->setPos(this->pos().x(), 4000); // Reinicia el barco en la parte inferior
    }
}
