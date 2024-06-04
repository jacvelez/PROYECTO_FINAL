#include "personajes.h"

Personaje::Personaje(const QString &rutaSprite, int totalFrames, int fila, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), frameActual(0), totalFrames(totalFrames), fila(fila),
    modoEspecial(false), animando(false)
{
    hojaSprite.load(rutaSprite);
    anchoFrame = (hojaSprite.width() / totalFrames) + 10;
    altoFrame = (hojaSprite.height() / 5) - 10;

    QPixmap frameInicial = hojaSprite.copy(frameActual * anchoFrame, fila * altoFrame, anchoFrame, altoFrame);
    setPixmap(frameInicial);
}

Personaje::Personaje(const QString &rutaSprite, int totalFrames, int fila, float x, float y, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), frameActual(0), totalFrames(totalFrames), fila(fila),
    modoEspecial(false), animando(false)
{
    direccionDerecha = true;
    hojaSprite.load(rutaSprite);
    anchoFrame = hojaSprite.width() / totalFrames;
    altoFrame = hojaSprite.height() / 4; // Suponiendo que hay 5 filas en total

    QPixmap frameInicial = hojaSprite.copy(frameActual * anchoFrame, fila * altoFrame, anchoFrame, altoFrame);
    setPixmap(frameInicial);
    setPos(x, y); // Establecer la posición inicial del NPC
}


Personaje::~Personaje() {}
void Personaje::siguienteFrame(bool modoEspecial) {
    frameActual = (frameActual + 1) % totalFrames;
    int yOffset = modoEspecial ? 0 : fila * altoFrame;
    QPixmap recortado = hojaSprite.copy(frameActual * anchoFrame, yOffset, anchoFrame, altoFrame);
    setPixmap(recortado);
}

void Personaje::mover(int dx, int dy) {
    setPos(x() + dx, y() + dy);
}

void Personaje::iniciarAnimacionEspecial() {
    modoEspecial = true;
    animando = true;
    siguienteFrame(modoEspecial);
}

void Personaje::detenerAnimacionEspecial() {
    modoEspecial = false;
    animando = false;
    siguienteFrame(modoEspecial);
}

void Personaje::alternarModoEspecial() {
    modoEspecial = !modoEspecial;
    siguienteFrame(modoEspecial);
}

bool Personaje::estaAnimando() const {
    return animando;
}


void Personaje::moverPersonajeAdicional(int velocidad, float minX, float maxX) {
    // Determina la velocidad y la dirección del movimiento según la dirección actual
    int velocidadX = direccionDerecha ? velocidad : -velocidad;

    // Mueve el NPC horizontalmente
    float nuevaPosX = x() + velocidadX;

    // Verifica si el NPC ha alcanzado los límites de movimiento horizontal
    if (nuevaPosX < minX || nuevaPosX > maxX) {
        // Si el NPC alcanza los límites, invierte la dirección del movimiento
        direccionDerecha = !direccionDerecha;
        // Ajusta la posición para que el NPC permanezca dentro de los límites
        nuevaPosX = direccionDerecha ? minX : maxX;
    }

    setX(nuevaPosX);
    // Actualiza el sprite del NPC
    siguienteFrame(modoEspecial);
}


QRectF Personaje::obtenerRectanguloDelimitador() const {
    return boundingRect();
}