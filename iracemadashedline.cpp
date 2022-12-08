#include "iracemadashedline.h"

IracemaDashedLine::IracemaDashedLine() :
_lineWidth(),
_yScaleTop(100),
_yScaleBottom(),
_initialPoint(),
_finalPoint(),
_lineColor(Qt::black),
_lineMaterial(new QSGFlatColorMaterial())
{
    _lineMaterial->setColor(_lineColor);
}

// IracemaDashedLine::~IracemaDashedLine() {
//     qDebug() << "oi";
//     delete _lineMaterial;
// }
