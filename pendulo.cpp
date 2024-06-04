#include "pendulo.h"
#include <QtMath> // Para usar qSin y qCos

Pendulo::Pendulo(QObject *parent) : QObject(parent), QGraphicsPixmapItem()
{
    // Configurar los parámetros del péndulo
    longitud = 100;
    angulo = 0;
    amplitud = 0.5; // Amplitud del ángulo (en radianes)
    periodo = 2000; // Período del movimiento oscilatorio en milisegundos

    // Cargar la imagen del péndulo
    setPixmap(QPixmap(":/imagenes/objetos/pendulo.png")); // Asegúrate de tener esta imagen en tus recursos

    // Escalar la imagen del péndulo
    qreal factorEscala = 0.5; // Cambia este valor para ajustar el tamaño del sprite
    setScale(factorEscala);

    setTransformOriginPoint(pixmap().width() / 2, 0); // El origen de la transformación es la parte superior central

    // Crear el timer para actualizar el ángulo
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Pendulo::actualizarAngulo);

    // Establecer el punto fijo del péndulo
    puntoFijo = QPointF(400, 100);
}

void Pendulo::iniciarMovimiento()
{
    timer->start(20); // Iniciar el timer con un intervalo de 20 ms
}

void Pendulo::actualizarAngulo()
{
    // Actualizar el ángulo del péndulo
    static qreal tiempoAcumulado = 0;
    tiempoAcumulado += timer->interval();

    qreal tiempo = tiempoAcumulado / periodo;
    angulo = amplitud * qSin(2 * M_PI * tiempo);

    // Rotar el péndulo
    setRotation(angulo * (180 / M_PI)); // Convertir radianes a grados
}
