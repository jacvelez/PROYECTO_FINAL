#ifndef PERSONAJES_H
#define PERSONAJES_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

class Personaje : public QGraphicsPixmapItem {
public:
    Personaje(const QString &rutaSprite, int totalFrames, int fila, QGraphicsItem *parent = nullptr);
    void siguienteFrame(bool modoEspecial);
    void mover(int dx, int dy);
    void iniciarAnimacionEspecial();
    void detenerAnimacionEspecial();
    void alternarModoEspecial();
    bool estaAnimando() const;

private:
    QPixmap hojaSprite;
    int frameActual;
    int totalFrames;
    int anchoFrame;
    int altoFrame;
    int fila;
    bool modoEspecial;
    bool animando;
};

#endif // PERSONAJES_H
