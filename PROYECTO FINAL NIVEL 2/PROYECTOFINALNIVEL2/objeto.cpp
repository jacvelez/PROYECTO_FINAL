#include "objeto.h"
#include <QPainter>
#include <QPixmap>

Objeto::Objeto(qreal x, qreal y, qreal width, qreal height, const QString &imagePath, QGraphicsItem* parent)
    : QGraphicsItem(parent), rect(x, y, width, height)
{
    // Load the image pixmap
    QPixmap pixmap(imagePath);
    pixmap = pixmap.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Create a transparent pixmap for the circle
    QPixmap transparentPixmap(width, height);
    transparentPixmap.fill(Qt::transparent);

    // Paint the image onto the transparent pixmap
    QPainter painter(&transparentPixmap);
    painter.drawPixmap(0, 0, pixmap);
    painter.end();

    // Create a pixmap item with the transparent pixmap
    pixmapItem = new QGraphicsPixmapItem(transparentPixmap, this);
    pixmapItem->setPos(x, y);
}

QRectF Objeto::boundingRect() const
{
    return rect;
}

void Objeto::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(rect);
}

