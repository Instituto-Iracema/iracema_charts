#include "iracemapointlabel.h"

IracemaPointLabel::IracemaPointLabel(QQuickItem* parent) :
QQuickItem(parent),
_graphPoint(),
_text(),
_upperText()
{}

IracemaPointLabel::IracemaPointLabel(QPointF graphPoint, QString text, QString upperText) :
QQuickItem(nullptr),
_graphPoint(graphPoint),
_text(text),
_upperText(upperText)
{}
