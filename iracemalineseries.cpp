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

const QVector<QLineF> &IracemaLineSeries::data() const
{
    return _data;
}

const QVector<QLineF> &IracemaLineSeries::dataBuffer() const
{
    return _dataBuffer;
}

void IracemaLineSeries::_addPointToBuffer(QPointF point)
{
    QLineF line;
    if (_dataBuffer.empty()) {
        if (_data.empty())
        {
            line.setP1(point);
        }
        else
        {
            line.setP1(_data.last().p2());
        }
    } else {
        line.setP1(_dataBuffer.last().p2());
    }
    line.setP2(point);
    _dataBuffer.append(line);
}

IracemaLineSeries::IracemaLineSeries(QQuickItem *parent) : QQuickItem(parent)
{

}

void IracemaLineSeries::addData(QVector<QPointF> data)
{
    for (QPointF point : data)
    {
        _addPointToBuffer(point);
    }
}

void IracemaLineSeries::addPoint(QPointF point)
{
    _addPointToBuffer(point);
}

void IracemaLineSeries::addPoint(float x, float y)
{
    _addPointToBuffer(QPointF(x, y));
}

void IracemaLineSeries::applyBuffer()
{
    for (QLineF line : qAsConst(_dataBuffer))
    {
        _data.append(line);
    }
    _dataBuffer.clear();
}

void IracemaLineSeries::clearData()
{

}
