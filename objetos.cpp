#include "objetos.h"
#include <QBrush>
#include <QPixmap>
Objetos::Objetos(QGraphicsItem *parent) : QGraphicsRectItem(parent)
{
    // Configurar el rectángulo principal
    setRect(0, 685, 7100, -50); // Ajusta el ancho según el tamaño de tu escena

    // Cargar la imagen PNG
    QPixmap imagen("C:/Users/Juan Andres/Desktop/UDEA/INFORMATICA II/LABORATORIO 5/LABORATORIO5/imagenes/objetos/piso.png"); // Reemplaza "ruta/a/imagen.png" con la ruta de tu imagen PNG

    // Crear un pincel con la textura de la imagen
    QBrush texturaBrush(imagen);

    // Establecer el pincel como el relleno del rectángulo principal
    setBrush(texturaBrush);



    // Crear un rectángulo adicional
    QGraphicsRectItem *rectangulo = new QGraphicsRectItem(100, 100, 200, 100);

    // Configurar el Z-value del rectángulo adicional
    rectangulo->setZValue(2); // Este rectángulo se dibujará encima del rectángulo principal


    }
