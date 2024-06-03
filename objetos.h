#ifndef OBJETOS_H
#define OBJETOS_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

    class Objeto : public QGraphicsPixmapItem
{
public:
    Objeto(const QString &imagePath, QGraphicsItem *parent = nullptr);
    void setSize(float width, float height);  // Nuevo método para cambiar el tamaño
    QRectF getBoundingBox() const {
        return boundingRect();
    }

protected:
    QRectF boundingRect() const override;  // Redefinición de boundingRect
    QPainterPath shape() const override;   // Definir la forma de colisión

private:
    QGraphicsRectItem *collisionRect;  // Rectángulo de colisión
};

#endif // OBJETOS_H
