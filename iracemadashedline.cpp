#include "iracemadashedline.h"

IracemaDashedLine::IracemaDashedLine(QQuickItem* parent) :
QQuickItem(parent),
_lineWidth(),
_yScaleTop(100),
_yScaleBottom(),
_initialPoint(),
_finalPoint(),
_lineColor(Qt::black)
{}
