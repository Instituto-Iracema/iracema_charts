#include "iracemapointlabel.h"

IracemaPointLabel::IracemaPointLabel() :
_graphPoint{},
_text{}
{}

IracemaPointLabel::IracemaPointLabel(QPointF graphPoint, QString text) :
_graphPoint{graphPoint},
_text{text}
{}
