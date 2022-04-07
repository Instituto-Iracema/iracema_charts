#include "iracemalineseries.h"

const QColor &IracemaLineSeries::lineColor() const
{
    return _lineColor;
}

void IracemaLineSeries::setLineColor(const QColor &newLineColor)
{
    if (_lineColor == newLineColor)
        return;
    _lineColor = newLineColor;
    emit lineColorChanged();
}

qreal IracemaLineSeries::lineWidth() const
{
    return _lineWidth;
}

void IracemaLineSeries::setLineWidth(qreal newLineWidth)
{
    if (qFuzzyCompare(_lineWidth, newLineWidth))
        return;
    _lineWidth = newLineWidth;
    emit lineWidthChanged();
}

IracemaLineSeries::IracemaLineSeries(QQuickItem *parent) : QQuickItem(parent)
{

}

void IracemaLineSeries::addData(QVector<QPointF> data)
{
    _dataBuffer.append(data);
}

void IracemaLineSeries::addPoint(QPointF point)
{
    _dataBuffer.append(point);
}

void IracemaLineSeries::addPoint(float x, float y)
{
    _dataBuffer.append(QPointF(x, y));
}
