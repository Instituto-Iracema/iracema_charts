#include "iracemalineseriesview.h"

#include <QBrush>

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

qreal IracemaLineSeriesView::xSize() const
{
    return _xSize;
}

void IracemaLineSeriesView::setXSize(qreal newXSize)
{
    if (qFuzzyCompare(_xSize, newXSize))
        return;
    _xSize = newXSize;
    emit xSizeChanged();
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

void IracemaLineSeriesView::_drawGrid(QPainter *painter)
{
    qDebug() << _gridSize;

    if (_gridSize == QSizeF(0, 0)) return;

    painter->setPen(QPen(QBrush(_gridColor, Qt::SolidPattern), _gridLineWidth, Qt::SolidLine, Qt::RoundCap));

    _drawGridHorizontal(painter);
    _drawGridVertical(painter);
}

void IracemaLineSeriesView::_drawLine(QPainter *painter, IracemaLineSeries *line)
{
    painter->setPen(QPen(QBrush(line->lineColor(), Qt::SolidPattern), line->lineWidth(), Qt::SolidLine, Qt::RoundCap));


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
    qDebug() << "init";
    qDebug() << width();
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
    qDebug() << "geometry changed";
    qDebug() << newGeometry.width();

    std::ignore = oldGeometry;

    _pixmap = QPixmap(newGeometry.width(), newGeometry.height());

    if (_pixmapPainter->isActive()) _pixmapPainter->end();
    _pixmapPainter->begin(&_pixmap);

    _drawGrid(_pixmapPainter);
}

void IracemaLineSeriesView::timerEvent(QTimerEvent *event)
{
    std::ignore = event;
}

void IracemaLineSeriesView::paint(QPainter *painter)
{
    qDebug() << "paint!";
    qDebug() << width();

    painter->drawPixmap(0,0, _pixmap);
}
