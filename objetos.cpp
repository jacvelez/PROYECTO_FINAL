#include "objetos.h"

Objeto::Objeto(const QString &imagePath, QGraphicsItem *parent) :
    QGraphicsPixmapItem(QPixmap(imagePath), parent),
    collisionRect(new QGraphicsRectItem(this)) // Inicializar el rectángulo de colisión
{
    setZValue(1); // Asegura que el objeto esté delante del fondo
    collisionRect->setRect(boundingRect()); // Establecer el rectángulo de colisión
}

void Objeto::setSize(float width, float height)
{
    // Redimensiona el pixmap del objeto manteniendo su relación de aspecto
    QPixmap scaledPixmap = pixmap().scaled(width, height, Qt::KeepAspectRatio);
    setPixmap(scaledPixmap);
    collisionRect->setRect(boundingRect()); // Actualizar el rectángulo de colisión
}

QRectF Objeto::boundingRect() const {
    // Devuelve el rectángulo delimitador del objeto en relación con su posición
    return QRectF(0, 0, pixmap().width(), pixmap().height());
}

QPainterPath Objeto::shape() const {
    // Devuelve la forma de colisión del objeto
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}
