#include "iracemascaleline.h"

IracemaScaleLine::IracemaScaleLine() :
_initialPoint(QPointF(0, 0)),
_finalPoint(QPointF(0, 0)),
_lineWidth(1),
_yScaleTop(1000),
_yScaleBottom(0),
_lineColor(Qt::black),
_lineMaterial(new QSGFlatColorMaterial())
{
    _lineMaterial->setColor(_lineColor);
}
