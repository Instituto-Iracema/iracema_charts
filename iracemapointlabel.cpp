#include "iracemapointlabel.h"

IracemaPointLabel::IracemaPointLabel(QQuickItem* parent) :
QQuickItem(parent),
_graphPoint(),
_text()
{}

IracemaPointLabel::IracemaPointLabel(QPointF graphPoint, QString text) :
QQuickItem(nullptr),
_graphPoint(graphPoint),
_text(text)
{}
