#include "iracemalineseries.h"

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
