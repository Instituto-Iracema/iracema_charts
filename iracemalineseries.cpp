#include "iracemalineseries.h"

IracemaLineSeries::IracemaLineSeries(QQuickItem* parent) :
QQuickItem(parent),
_lineWidth(1),
_yScaleTop(1000),
_yScaleBottom(0),
_data(),
_dataBuffer(),
_graphPointLabels(),
_graphPointLabelsBuffer(),
_lineColor(Qt::black)
{}

IracemaLineSeries::~IracemaLineSeries()
{
    _deleteGraphPoint();
}

QLineF IracemaLineSeries::at(int index)
{
    return _data.at(index);
}

QPointF IracemaLineSeries::pointAt(int index)
{
    return (index < _data.length()) ? _data.at(index).p2() : _dataBuffer.at(index - _data.length()).p2();
}

int IracemaLineSeries::count()
{
    return _data.size();
}

void IracemaLineSeries::applyDataBuffer()
{
    for (const auto& line : qAsConst(_dataBuffer))
    {
        _data.append(line);
    }

    _dataBuffer.clear();
}

void IracemaLineSeries::applyPointLabelsBuffer()
{
    for (const auto& pointLabel : qAsConst(_graphPointLabelsBuffer))
    {
        _graphPointLabels.append(pointLabel);
    }

    _graphPointLabelsBuffer.clear();
}

void IracemaLineSeries::addData(const QVector<QPointF>& data)
{
    for (const auto& point : data)
    {
        _addPointToBuffer(point);
    }
}

void IracemaLineSeries::addPoint(const QPointF& point)
{
    _addPointToBuffer(point);
}

void IracemaLineSeries::addPoint(float x, float y)
{
    _addPointToBuffer(QPointF(x, y));
}

void IracemaLineSeries::appendGraphPointLabels(const QPointF& position, const QString& text, const QString& upperText)
{
    auto label = new IracemaPointLabel(position, text, upperText);
    if (label == nullptr)
    {
        return;
    }

    _graphPointLabelsBuffer.append(label);
    emit graphPointLabelsChanged();
}

void IracemaLineSeries::appendGraphPointLabels(qreal x, qreal y, const QString& text, const QString& upperText)
{
    appendGraphPointLabels(QPointF(x, y), text, upperText);
}

void IracemaLineSeries::clearData()
{
    _data.clear();
    _dataBuffer.clear();
    _deleteGraphPoint();
}

QQmlListProperty<IracemaPointLabel> IracemaLineSeries::graphPointLabels()
{
    return QQmlListProperty<IracemaPointLabel>(this, nullptr, &IracemaLineSeries::_appendGraphPointLabels,
                                                nullptr, nullptr, nullptr);
}

void IracemaLineSeries::_appendGraphPointLabels(QQmlListProperty<IracemaPointLabel> *list, IracemaPointLabel *label)
{
    auto line = qobject_cast<IracemaLineSeries*>(list->object);

    if (line)
    {
        label->setParentItem(line);
        line->_graphPointLabelsBuffer.append(label);
        emit line->graphPointLabelsChanged();
    }
}

void IracemaLineSeries::_addPointToBuffer(const QPointF& point)
{
    auto line = QLineF();
    if (_dataBuffer.empty())
    {
        if (_data.empty())
        {
            line.setP1(point);
        }
        else
        {
            line.setP1(_data.last().p2());
        }
    }
    else
    {
        line.setP1(_dataBuffer.last().p2());
    }

    line.setP2(point);
    _dataBuffer.append(line);
}

void IracemaLineSeries::_deleteGraphPoint() noexcept
{
    for (auto &point : _graphPointLabels)
    {
        delete point;
    }
    _graphPointLabels.clear();

    for (auto &pointBuffer : _graphPointLabelsBuffer)
    {
        delete pointBuffer;
    }
    _graphPointLabelsBuffer.clear();
}