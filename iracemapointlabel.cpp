#include "iracemapointlabel.h"

IracemaPointLabel::IracemaPointLabel()
{
    IracemaPointLabel(QPointF(0,0), "");
}

IracemaPointLabel::IracemaPointLabel(QPointF graphPoint, QString text) : _graphPoint(graphPoint), _text(text)
{

}

QPointF IracemaPointLabel::graphPoint() const
{
    return _graphPoint;
}

void IracemaPointLabel::setGraphPoint(QPointF newGraphPoint)
{
    if (_graphPoint == newGraphPoint)
        return;
    _graphPoint = newGraphPoint;
    emit graphPointChanged();
}

const QString &IracemaPointLabel::text() const
{
    return _text;
}

void IracemaPointLabel::setText(const QString &newText)
{
    if (_text == newText)
        return;
    _text = newText;
    emit textChanged();
}
