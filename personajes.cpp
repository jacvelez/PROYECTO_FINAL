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
