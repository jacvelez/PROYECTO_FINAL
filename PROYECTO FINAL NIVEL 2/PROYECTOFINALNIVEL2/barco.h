#ifndef BARCO_H
#define BARCO_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QPixmap>
#include <QTimer>

class Barco : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Barco(QGraphicsItem *parent = nullptr);
    Barco(const QString &imagePath, int fila, QGraphicsItem *parent = nullptr); // Nuevo constructor

    void setFilaActual(int fila);
    void mover();
private slots:
    void actualizarFrame();

private:
    QPixmap sprite;
    int filaActual;
    int frameActual;
    int anchoFrame;
    int altoFrame;
};

#endif // BARCO_H
