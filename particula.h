#ifndef PARTICULA_H
#define PARTICULA_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Particula : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Particula(QString rutaImagen, qreal velocidadX, qreal velocidadY, qreal duracion, int ancho, int alto, QObject *parent = nullptr);
    ~Particula();

private slots:
    void mover();

private:
    qreal velocidadX;
    qreal velocidadY;
    qreal duracion;
    QTimer *timer;
};

#endif // PARTICULA_H
