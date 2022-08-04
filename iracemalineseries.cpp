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
    _lineMaterial->setColor(_lineColor);
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

const QList<IracemaPointLabel *> &IracemaLineSeries::pointLabels() const
{
    return _graphPointLabels;
}

const QVector<QLineF> &IracemaLineSeries::dataBuffer() const
{
    return _dataBuffer;
}

const QList<IracemaPointLabel *> IracemaLineSeries::pointLabelsBuffer()
{
    return this->_graphPointLabelsBuffer;
}

qreal IracemaLineSeries::yScaleTop() const
{
    return _yScaleTop;
}

void IracemaLineSeries::setYScaleTop(qreal newYScaleTop)
{
    if (qFuzzyCompare(_yScaleTop, newYScaleTop))
        return;
    _yScaleTop = newYScaleTop;
    emit yScaleTopChanged();
}

qreal IracemaLineSeries::yScaleBottom() const
{
    return _yScaleBottom;
}

void IracemaLineSeries::setYScaleBottom(qreal newYScaleBottom)
{
    if (qFuzzyCompare(_yScaleBottom, newYScaleBottom))
        return;
    _yScaleBottom = newYScaleBottom;
    emit yScaleBottomChanged();
}

QSGFlatColorMaterial *IracemaLineSeries::lineMaterial() const
{
    return _lineMaterial;
}

void IracemaLineSeries::_addPointToBuffer(QPointF point)
{
    QLineF line;
    if (_dataBuffer.empty()) {
        if (_data.empty()) {
            line.setP1(point);
        } else {
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
    _lineMaterial = new QSGFlatColorMaterial();
    _lineMaterial->setColor(_lineColor);
}

IracemaLineSeries::~IracemaLineSeries()
{
    _graphPointLabels.clear();
    _graphPointLabelsBuffer.clear();
}

void IracemaLineSeries::addData(QVector<QPointF> data)
{
    for (QPointF point : data)
        _addPointToBuffer(point);
}

void IracemaLineSeries::addPoint(QPointF point)
{
    _addPointToBuffer(point);
}

void IracemaLineSeries::addPoint(float x, float y)
{
    _addPointToBuffer(QPointF(x, y));
}

void IracemaLineSeries::applyDataBuffer()
{
    for (QLineF line : qAsConst(_dataBuffer))
        _data.append(line);

    _dataBuffer.clear();
}

void IracemaLineSeries::applyPointLabelsBuffer()
{
    for (auto pointLabel : qAsConst(_graphPointLabelsBuffer))
        _graphPointLabels.append(pointLabel);

    _graphPointLabelsBuffer.clear();
}

QLineF IracemaLineSeries::at(int index)
{
    return _data.at(index);
}

QPointF IracemaLineSeries::pointAt(int index)
{
    return index < _data.length() ? _data.at(index).p2() : _dataBuffer.at(index - _data.length()).p2();
}

int IracemaLineSeries::count()
{
    return _data.size();
}

void IracemaLineSeries::clearData()
{
    _data.clear();
    _dataBuffer.clear();
    _graphPointLabels.clear();
    _graphPointLabelsBuffer.clear();
}

void IracemaLineSeries::appendGraphPointLabels(QPointF position, QString text)
{
    auto label = new IracemaPointLabel(position, text);
    this->_graphPointLabelsBuffer.append(label);
    emit this->graphPointLabelsChanged();
}

void IracemaLineSeries::appendGraphPointLabels(qreal x, qreal y, QString text)
{
    appendGraphPointLabels(QPointF(x, y), text);
}

QQmlListProperty<IracemaPointLabel> IracemaLineSeries::graphPointLabels()
{
    return QQmlListProperty<IracemaPointLabel>(this, nullptr, &IracemaLineSeries::appendGraphPointLabels,
                                               nullptr, nullptr, nullptr);
}

void IracemaLineSeries::appendGraphPointLabels(QQmlListProperty<IracemaPointLabel> *list, IracemaPointLabel *label)
{
    IracemaLineSeries *line = qobject_cast<IracemaLineSeries *>(list->object);

    if (line) {
        label->setParentItem(line);
        line->_graphPointLabelsBuffer.append(label);
        emit line->graphPointLabelsChanged();
    }
}
