#include "iracemalineseriesview.h"

#include <QBrush>
#include <math.h>
#include <QRandomGenerator>

const QSizeF &IracemaLineSeriesView::gridSize() const
{
    return _gridSize;
}

void IracemaLineSeriesView::setGridSize(const QSizeF &newGridSize)
{
    qDebug() << "setgridsize";
    if (_gridSize == newGridSize)
        return;
    _gridSize = newGridSize;
    emit gridSizeChanged();
}

const QSizeF &IracemaLineSeriesView::gridOffset() const
{
    return _gridOffset;
}

void IracemaLineSeriesView::setGridOffset(const QSizeF &newGridOffset)
{
    if (_gridOffset == newGridOffset)
        return;
    _gridOffset = newGridOffset;
    emit gridOffsetChanged();
}

unsigned int IracemaLineSeriesView::updateTime() const
{
    return _updateTime;
}

void IracemaLineSeriesView::setUpdateTime(unsigned int newUpdateTime)
{
    if (_updateTime == newUpdateTime)
        return;
    _updateTime = newUpdateTime;
    emit updateTimeChanged();
}

qreal IracemaLineSeriesView::gridLineWidth() const
{
    return _gridLineWidth;
}

void IracemaLineSeriesView::setGridLineWidth(qreal newGridLineWidth)
{
    if (qFuzzyCompare(_gridLineWidth, newGridLineWidth))
        return;
    _gridLineWidth = newGridLineWidth;
    emit gridLineWidthChanged();
}

qreal IracemaLineSeriesView::xScaleBottom() const
{
    return _xScaleBottom;
}

void IracemaLineSeriesView::setXScaleBottom(qreal newXScaleBottom)
{
    if (qFuzzyCompare(_xScaleBottom, newXScaleBottom))
        return;
    _xScaleBottom = newXScaleBottom;
    emit xScaleBottomChanged();
}

qreal IracemaLineSeriesView::xScaleTop() const
{
    return _xScaleTop;
}

void IracemaLineSeriesView::setXScaleTop(qreal newXScaleTop)
{
    if (qFuzzyCompare(_xScaleTop, newXScaleTop))
        return;
    _xScaleTop = newXScaleTop;
    emit xScaleTopChanged();
}

const QColor &IracemaLineSeriesView::backgroundColor() const
{
    return _backgroundColor;
}

void IracemaLineSeriesView::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (_backgroundColor == newBackgroundColor)
        return;
    _backgroundColor = newBackgroundColor;
    emit backgroundColorChanged();
}

QQmlListProperty<IracemaLineSeries> IracemaLineSeriesView::lines()
{
    return QQmlListProperty<IracemaLineSeries>(this, nullptr, &IracemaLineSeriesView::appendLine,
                                               nullptr, nullptr, nullptr);
}

void IracemaLineSeriesView::_drawGridHorizontal(QPainter *painter)
{
    qreal currentPosition = _gridOffset.height();
    while(currentPosition <= height())
    {
        painter->drawLine(0, currentPosition, width(), currentPosition);
        currentPosition += _gridSize.height();
    }
}

void IracemaLineSeriesView::_drawGridVertical(QPainter *painter)
{
    qreal currentPosition = _gridOffset.width();
    while(currentPosition <= width())
    {
        painter->drawLine(currentPosition, 0, currentPosition, height());
        currentPosition += _gridSize.width();
    }
}

void IracemaLineSeriesView::_drawGrid()
{
    _startPainter();

    if (_gridSize == QSizeF(0, 0)) return;

    _pixmapPainter->setPen(QPen(QBrush(_gridColor, Qt::SolidPattern), _gridLineWidth, Qt::SolidLine, Qt::RoundCap));

    _drawGridHorizontal(_pixmapPainter);
    _drawGridVertical(_pixmapPainter);

    _endPainter();
}

void IracemaLineSeriesView::_drawLineSeries(QPainter *painter, IracemaLineSeries *lineSeries)
{
    painter->setPen(QPen(QBrush(lineSeries->lineColor(), Qt::SolidPattern), lineSeries->lineWidth(), Qt::SolidLine, Qt::RoundCap));

    for (QLineF line : lineSeries->dataBuffer())
    {
        qreal newX1 = _convertValueToNewScale(line.p1().x(), _xScaleBottom, _xScaleTop, 0, painter->window().width());
        qreal newX2 = _convertValueToNewScale(line.p2().x(), _xScaleBottom, _xScaleTop, 0, painter->window().width());
        QPointF newP1(newX1, _pixmap.height() - line.p1().y());
        QPointF newP2(newX2, _pixmap.height() - line.p2().y());
        line.setPoints(newP1, newP2);
        painter->drawLine(line);
    }

    lineSeries->applyBuffer();
}

void IracemaLineSeriesView::_drawLines()
{
    _startPainter();

    for (auto lineSeries : qAsConst(_lines))
    {
        _drawLineSeries(_pixmapPainter, lineSeries);
    }

    _endPainter();
}

void IracemaLineSeriesView::_recreatePixmap(qreal width, qreal height)
{
    _pixmap = QPixmap(width, height);
}

void IracemaLineSeriesView::_startPainter()
{
    _pixmapPainter->begin(&_pixmap);
}

void IracemaLineSeriesView::_endPainter()
{
    _pixmapPainter->end();
}

qreal IracemaLineSeriesView::_convertValueToNewScale(qreal oldValue, qreal oldScaleBottom, qreal oldScaleTop, qreal newScaleBottom, qreal newScaleTop)
{
    qreal newValue = oldValue - oldScaleBottom;
    newValue *= newScaleTop - newScaleBottom;
    newValue /= oldScaleTop - oldScaleBottom;
    newValue += newScaleBottom;

    return newValue;
}

void IracemaLineSeriesView::appendLine(QQmlListProperty<IracemaLineSeries> *list, IracemaLineSeries *line)
{
    IracemaLineSeriesView *view = qobject_cast<IracemaLineSeriesView *>(list->object);
    if (view) {
        line->setParentItem(view);
        view->_lines.append(line);
    }
}

IracemaLineSeriesView::IracemaLineSeriesView(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{

}

void IracemaLineSeriesView::addPoint(quint32 lineIndex, QPointF point)
{
    _lines[lineIndex]->addPoint(point);
}

void IracemaLineSeriesView::addPoint(quint32 lineIndex, qreal x, qreal y)
{
    _lines[lineIndex]->addPoint(QPointF(x, y));
}

void IracemaLineSeriesView::addPoints(quint32 lineIndex, QList<QPointF> points)
{
    for (QPointF point: points)
    {
        _lines[lineIndex]->addPoint(point);
    }
}

void IracemaLineSeriesView::clearData()
{
    for (IracemaLineSeries *line : _lines)
    {
        line->clearData();
    }
}

void IracemaLineSeriesView::clearLine(quint32 lineIndex)
{
    _lines[lineIndex]->clearData();
}

const QColor &IracemaLineSeriesView::gridColor() const
{
    return _gridColor;
}

void IracemaLineSeriesView::setGridColor(const QColor &newGridColor)
{
    if (_gridColor == newGridColor)
        return;
    _gridColor = newGridColor;
    emit gridColorChanged();
}

void IracemaLineSeriesView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    if (_updateTimerId == -1)
    {
        _updateTimerId = startTimer(_updateTime, Qt::PreciseTimer);
    }

    std::ignore = oldGeometry;

    _recreatePixmap(newGeometry.width(), newGeometry.height());

    if (_pixmapPainter->isActive()) _pixmapPainter->end();

    _drawGrid();
}

void IracemaLineSeriesView::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _updateTimerId)
    {
        _drawLines();
        update();
    }
}

void IracemaLineSeriesView::paint(QPainter *painter)
{
    painter->drawPixmap(0, 0, _pixmap);
}
