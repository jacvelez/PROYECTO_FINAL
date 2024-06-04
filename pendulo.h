#ifndef PENDULO_H
#define PENDULO_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>

class Pendulo : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit Pendulo(QObject *parent = nullptr);
    void iniciarMovimiento();

private:
    qreal longitud; // Longitud del péndulo
    qreal angulo;   // Ángulo actual del péndulo
    qreal amplitud; // Amplitud del movimiento oscilatorio
    qreal periodo;  // Período del movimiento oscilatorio
    QTimer *timer;
    QPointF puntoFijo; // Punto fijo del péndulo

private slots:
    void actualizarAngulo();
};

#endif // PENDULO_H
