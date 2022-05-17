#include "iracemalineseriesview.h"

#include <QBrush>
#include <math.h>
#include <QRandomGenerator>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QQuickItemGrabResult>
#include <QSGSimpleRectNode>
#include <QRectF>

IracemaLineSeriesView::IracemaLineSeriesView(QQuickItem *parent) : QQuickItem(parent)
{
    setFlag(ItemHasContents, true);

    _gridMaterial = new QSGFlatColorMaterial();
    _gridMaterial->setColor(_gridColor);

    connect(this, &IracemaLineSeriesView::gridSizeChanged, &IracemaLineSeriesView::onGridSizeChanged);
}

const QSizeF &IracemaLineSeriesView::gridSize() const
{
    return _gridSize;
}

void IracemaLineSeriesView::setGridSize(const QSizeF &newGridSize)
{
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

void IracemaLineSeriesView::onGridSizeChanged()
{
    _reDrawGrid = true;
}

QQmlListProperty<IracemaLineSeries> IracemaLineSeriesView::lines()
{
    return QQmlListProperty<IracemaLineSeries>(this, nullptr, &IracemaLineSeriesView::appendLine,
                                               nullptr, nullptr, nullptr);
}

void IracemaLineSeriesView::_drawGridHorizontal(QSGNode *mainNode)
{
    qreal currentPosition = _gridOffset.height();
    while(currentPosition <= height())
    {
        QLineF line(0, currentPosition, width(), currentPosition);
        _drawOneLine(mainNode, line, _gridLineWidth, _gridMaterial);
        currentPosition += _gridSize.height();
    }
}

void IracemaLineSeriesView::_drawGridVertical(QSGNode *mainNode)
{
    qreal currentPosition = _gridOffset.width();
    while(currentPosition <= width())
    {
        QLineF line(currentPosition, 0, currentPosition, height());
        _drawOneLine(mainNode, line, _gridLineWidth, _gridMaterial);
        currentPosition += _gridSize.width();
    }
}

void IracemaLineSeriesView::_drawGrid(QSGNode *mainNode)
{
    if (_gridSize.width() <= 0 || _gridSize.height() <= 0) return;

    _drawGridHorizontal(mainNode);
    _drawGridVertical(mainNode);
}

void IracemaLineSeriesView::_drawLineSeries(QSGNode *mainNode, IracemaLineSeries *lineSeries, bool invertY)
{

    for (QLineF line : lineSeries->dataBuffer())
    {
        qreal newX1 = _convertValueToNewScale(line.p1().x(), _xScaleBottom, _xScaleTop, 0, width());
        qreal newX2 = _convertValueToNewScale(line.p2().x(), _xScaleBottom, _xScaleTop, 0, width());
        qreal newY1 = _convertValueToNewScale(line.p1().y(), lineSeries->yScaleBottom(), lineSeries->yScaleTop(), 0, height());
        qreal newY2 = _convertValueToNewScale(line.p2().y(),lineSeries->yScaleBottom(), lineSeries->yScaleTop(),  0, height());

        //Clip values to view boundaries
        newY1 = std::max(0.0, std::min(newY1, height()));
        newY2 = std::max(0.0, std::min(newY2, height()));

        if (invertY) {
            newY1 = height() - newY1;
            newY2 = height() - newY2;
        }

        QPointF newP1(newX1, newY1);
        QPointF newP2(newX2, newY2);
        QLineF newLine(newP1, newP2);
        _drawOneLine(mainNode, newLine, lineSeries->lineWidth(), lineSeries->lineMaterial());
    }

    lineSeries->applyBuffer();
}

void IracemaLineSeriesView::_drawLines(QSGNode *mainNode)
{
    for (auto lineSeries : qAsConst(_lines))
    {
        QSGNode *lineSeriesNode = new QSGNode();
        lineSeriesNode->setFlags(QSGNode::OwnedByParent | QSGNode::OwnsGeometry);
        _drawLineSeries(lineSeriesNode, lineSeries);
        mainNode->appendChildNode(lineSeriesNode);
    }
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
    for (IracemaLineSeries *line : qAsConst(_lines))
    {
        line->clearData();
    }
    _reDrawGrid = true;
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
    _gridMaterial->setColor(_gridColor);
    emit gridColorChanged();
}

void IracemaLineSeriesView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    std::ignore = oldGeometry;
    std::ignore = newGeometry;

    _reDrawGrid = true;

    if (_updateTimerId == -1)
    {
        _updateTimerId = startTimer(_updateTime, Qt::PreciseTimer);
    }

}

void IracemaLineSeriesView::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _updateTimerId && !_isProcessingImage)
    {
        update();
    }
}

void IracemaLineSeriesView::_drawOneLine(QSGNode *mainNode, QLineF line, qreal lineWidth, QSGFlatColorMaterial *lineMaterial)
{
    auto childNode = new QSGGeometryNode;

    auto geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setLineWidth(lineWidth);
    geometry->setDrawingMode(QSGGeometry::DrawLineStrip);
    childNode->setGeometry(geometry);
    childNode->setFlags(QSGNode::OwnedByParent | QSGNode::OwnsGeometry);

    childNode->setMaterial(lineMaterial);

    QSGGeometry::Point2D *vertices = geometry->vertexDataAsPoint2D();

    vertices[0].set(line.x1(), line.y1());
    vertices[1].set(line.x2(), line.y2());

    mainNode->appendChildNode(childNode);
}

QSGNode *IracemaLineSeriesView::updatePaintNode(QSGNode *oldNode, UpdatePaintNodeData *)
{
    if (!oldNode)
    {
        oldNode = new QSGNode;
    }

    if (_reDrawGrid)
    {
        oldNode->removeAllChildNodes();
        QSGNode *backgroundNode = new QSGSimpleRectNode(QRectF(0, 0, width(), height()), _backgroundColor);
        oldNode->appendChildNode(backgroundNode);
        _drawGrid(oldNode);
        _reDrawGrid = false;
    }

    _drawLines(oldNode);

    return oldNode;
}
