#ifndef OBJETO_H
#define OBJETO_H

#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QString>

class Objeto : public QGraphicsItem
{
public:
    Objeto(qreal x, qreal y, qreal width, qreal height, const QString &imagePath, QGraphicsItem* parent = nullptr);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

private:
    QGraphicsPixmapItem *pixmapItem;
    QRectF rect;
};

#endif // OBJETO_H
