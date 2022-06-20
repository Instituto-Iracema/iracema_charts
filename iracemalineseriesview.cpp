#include "iracemalineseriesview.h"

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
    this->_reDrawGrid = true;
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
    this->_reDrawGrid = true;
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

QQmlListProperty<IracemaScaleLabel> IracemaLineSeriesView::verticalScaleLabels()
{
    return QQmlListProperty<IracemaScaleLabel>(this, nullptr, &IracemaLineSeriesView::appendVerticalScaleLabel,
                                               nullptr, nullptr, nullptr);
}

QQmlListProperty<IracemaScaleLabel> IracemaLineSeriesView::horizontalScaleLabels()
{
    return QQmlListProperty<IracemaScaleLabel>(this, nullptr, &IracemaLineSeriesView::appendHorizontalScaleLabel,
                                               nullptr, nullptr, nullptr);
}

qreal IracemaLineSeriesView::plotAreaRigthPadding() const
{
    return _plotAreaRigthPadding;
}

void IracemaLineSeriesView::setPlotAreaRigthPadding(qreal newPlotAreaRigthPadding)
{
    if (qFuzzyCompare(_plotAreaRigthPadding, newPlotAreaRigthPadding))
        return;
    _plotAreaRigthPadding = newPlotAreaRigthPadding;
    emit plotAreaRigthPaddingChanged();
}

qreal IracemaLineSeriesView::verticalScaleHeigth() const
{
    return _verticalScaleHeigth;
}

void IracemaLineSeriesView::setVerticalScaleHeigth(qreal newVerticalScaleHeigth)
{
    if (qFuzzyCompare(_verticalScaleHeigth, newVerticalScaleHeigth))
        return;
    _verticalScaleHeigth = newVerticalScaleHeigth;
    emit verticalScaleHeigthChanged();
}

qreal IracemaLineSeriesView::HorizontalScaleWidth() const
{
    return _horizontalScaleWidth;
}

void IracemaLineSeriesView::setHorizontalScaleWidth(qreal newHorizontalScaleWidth)
{
    if (qFuzzyCompare(_horizontalScaleWidth, newHorizontalScaleWidth))
        return;
    _horizontalScaleWidth = newHorizontalScaleWidth;
    emit HorizontalScaleWidthChanged();
}

qreal IracemaLineSeriesView::yTickCount() const
{
    return _yTickCount;
}

void IracemaLineSeriesView::setYTickCount(qreal newYTickCount)
{
    if (qFuzzyCompare(_yTickCount, newYTickCount))
        return;
    _yTickCount = newYTickCount;
    emit yTickCountChanged();
}

void IracemaLineSeriesView::setTickCount(qreal newTickCount)
{
    setYTickCount(newTickCount);
    setXTickCount(newTickCount);
}

qreal IracemaLineSeriesView::xTickCount() const
{
    return _xTickCount;
}

void IracemaLineSeriesView::setXTickCount(qreal newXTickCount)
{
    if (qFuzzyCompare(_xTickCount, newXTickCount))
        return;
    _xTickCount = newXTickCount;
    emit xTickCountChanged();
}

bool IracemaLineSeriesView::hasScales() const
{
    return _hasScales;
}

void IracemaLineSeriesView::setHasScales(bool newHasScales)
{
    if (_hasScales == newHasScales)
        return;
    _hasScales = newHasScales;
    emit hasScalesChanged();
}

void IracemaLineSeriesView::_drawGridHorizontal(QSGNode *mainNode)
{
    qreal x, y, width, height;
    QRectF plotArea =  _calculatePlotArea(x, y, width, height);
    qreal currentY = y;
    qreal limit = y + height;
    qreal gridHeigth = 0;
    qreal labelValue = _yScaleTop();
    qreal labelValueInterval;
    // used to solve problems of rouding labelValueInterval by odd tickCount
    int drawedGridLines = 0;
    const int GRID_LINES_TO_DRAW = (_yTickCount? _yTickCount : (height / gridHeigth)) + 1;

    if (_yTickCount) {
        gridHeigth = height / _yTickCount;
        labelValueInterval = labelValue / _yTickCount;
    } else {
        gridHeigth = _gridSize.height();
        labelValueInterval = labelValue / (height / gridHeigth);
    }

    while (currentY <= limit || drawedGridLines < GRID_LINES_TO_DRAW) {
        if ( currentY > limit) {
            currentY = limit;
            labelValue = _yScaleBottom();
        }

        QLineF line(_horizontalScaleWidth * 0.95, currentY, x+width, currentY);
        _drawOneLine(mainNode, line, _gridLineWidth, _gridMaterial);
        drawedGridLines++;

        if (_hasScales)
            _drawScaleLabel(mainNode, (_horizontalScaleWidth * 0.9) - 50, currentY - 10, QString::number((int)labelValue), QTextOption(Qt::AlignRight));

        currentY += gridHeigth;
        labelValue -= labelValueInterval;
    }

    for (auto label: qAsConst(_verticalScaleLabels)) {
        qreal newY = _convertValueToNewScale(label->scalePoint(), _yScaleBottom(), _yScaleTop(), plotArea.bottom(), plotArea.top());
        _drawScaleLabel(mainNode, (_horizontalScaleWidth * 0.9) - 50, newY - 10, label->scaleText(), QTextOption(Qt::AlignRight));
    }
}

void IracemaLineSeriesView::_drawGridVertical(QSGNode *mainNode)
{
    qreal x, y, width, height;
    _calculatePlotArea(x, y, width, height);
    qreal currentX = x;
    qreal limit = x + width;
    qreal gridWidth = 0;
    qreal labelValue = 0;
    qreal labelValueInterval;
    // used to solve problems of rouding labelValueInterval by odd tickCount
    int drawedGridLines = 0;
    const int GRID_LINES_TO_DRAW = (_xTickCount? _xTickCount : (width / gridWidth)) + 1;

    if (_xTickCount) {
        gridWidth = width / _xTickCount;
        labelValueInterval = _xScaleTop / _xTickCount;
    } else {
        gridWidth = _gridSize.width();
        labelValueInterval = _xScaleTop / (width / gridWidth);
    }

    while (currentX <= limit ||  drawedGridLines < GRID_LINES_TO_DRAW) {
        if (currentX > limit) {
            currentX = limit;
            labelValue = _xScaleTop;
        }

        QLineF line(currentX, y, currentX, (_hasScales? y + height + _verticalScaleHeigth * 0.1 : y+height));
        _drawOneLine(mainNode, line, _gridLineWidth, _gridMaterial);
        drawedGridLines++;

        if (_hasScales)
            _drawScaleLabel(mainNode, currentX - 25, (_hasScales? y + height + _verticalScaleHeigth * 0.15 : y + height), QString::number((int)labelValue), QTextOption(Qt::AlignHCenter));

        currentX += gridWidth;
        labelValue += labelValueInterval;
    }

    for (auto label: _horizontalScaleLabels) {
        qreal newX = _convertValueToNewScale(label->scalePoint(), _xScaleBottom, _xScaleTop, x, x+width);
        // center label component
        newX -= 25;
        _drawScaleLabel(mainNode, newX , (_hasScales? y + height + _verticalScaleHeigth * 0.15 : y + height), label->scaleText(), QTextOption(Qt::AlignHCenter));
    }
}

void IracemaLineSeriesView::_drawGrid(QSGNode *mainNode)
{
    if (_gridSize.width() <= 0 || _gridSize.height() <= 0) return;

    _drawGridHorizontal(mainNode);
    _drawGridVertical(mainNode);
}

void IracemaLineSeriesView::_drawScaleLabel(QSGNode *mainNode, qreal x, qreal y, QString label, QTextOption textOption)
{
    auto childNode = new QSGSimpleTextureNode;
    QPixmap pixmap(QSize(100,100));
    pixmap.fill(Qt::transparent);
    const QRect rectangle = QRect(0, 0, 100, 100);
    QPainter painter(&pixmap);
    QFont labelFont;
    QPen pen;
    labelFont.setPixelSize(30);
    pen.setColor(Qt::white);
    painter.setFont(labelFont);
    painter.setPen(pen);
    painter.drawText(rectangle, label, textOption);
    painter.end();

    QSGTexture *texture = window()->createTextureFromImage(pixmap.toImage());
    childNode->setOwnsTexture(true);
    childNode->setRect(QRectF(x, y, 50, 50));
    childNode->markDirty(QSGNode::DirtyForceUpdate);
    childNode->setTexture(texture);
    mainNode->appendChildNode(childNode);
}

void IracemaLineSeriesView::_drawLineSeries(QSGNode *mainNode, IracemaLineSeries *lineSeries, bool invertY, bool redrawAllData)
{
    qreal x, y, width, height;
    _calculatePlotArea(x, y, width, height);
    QVector<QLineF> dataToDraw;

    if (redrawAllData) {
        lineSeries->applyBuffer();
        dataToDraw = lineSeries->data();
    } else {
        dataToDraw = lineSeries->dataBuffer();
        lineSeries->applyBuffer();
    }

    for (QLineF line : dataToDraw) {
        qreal newX1 = _convertValueToNewScale(line.p1().x(), _xScaleBottom, _xScaleTop, 0, width) + x;
        qreal newX2 = _convertValueToNewScale(line.p2().x(), _xScaleBottom, _xScaleTop, 0, width) + x;
        qreal newY1 = _convertValueToNewScale(line.p1().y(), lineSeries->yScaleBottom(), lineSeries->yScaleTop(), 0, height);
        qreal newY2 = _convertValueToNewScale(line.p2().y(), lineSeries->yScaleBottom(), lineSeries->yScaleTop(), 0, height);

        //Clip values to view boundaries
        newY1 = std::max(0.0, std::min(newY1, height));
        newY2 = std::max(0.0, std::min(newY2, height));

        if (invertY) {
            newY1 = this->height() - newY1 - (this->height() - height - y);
            newY2 = this->height() - newY2 - (this->height() - height - y);
        } else {
            newY1 += y;
            newY2 += y;
        }

        QPointF newP1(newX1, newY1);
        QPointF newP2(newX2, newY2);
        QLineF newLine(newP1, newP2);
        _drawOneLine(mainNode, newLine, lineSeries->lineWidth(), lineSeries->lineMaterial());
    }

    lineSeries->applyBuffer();
}

void IracemaLineSeriesView::_drawLines(QSGNode *mainNode, bool redrawAllData)
{
    for (auto lineSeries : qAsConst(_lines)) {
        QSGNode *lineSeriesNode = new QSGNode();
        lineSeriesNode->setFlags(QSGNode::OwnedByParent | QSGNode::OwnsGeometry);
        _drawLineSeries(lineSeriesNode, lineSeries, true, redrawAllData);
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

QRectF IracemaLineSeriesView::_calculatePlotArea(qreal &x, qreal &y, qreal &width, qreal &heigth, bool standard)
{
    if (!standard && _hasScales) {
        x = _horizontalScaleWidth;
        y = _verticalScaleHeigth * 0.25;
        width = this->width() - _horizontalScaleWidth - _plotAreaRigthPadding;
        heigth = this->height() - _verticalScaleHeigth * 1.25;
    } else {
        x = 0;
        y= 0;
        width = this->width();
        heigth = this->height();
    }

    return QRectF(x, y, width, heigth);
}

QRectF IracemaLineSeriesView::_calculatePlotArea(bool standard)
{
    qreal x, y, width, heigth;

    _calculatePlotArea(x,y,width,heigth,standard);

    return QRectF(x, y, width, heigth);
}

qreal IracemaLineSeriesView::_yScaleTop()
{
    qreal maxScaleTop = 0;
    for (auto line : qAsConst(_lines)) {
        if (line->yScaleTop() > maxScaleTop)
            maxScaleTop = line->yScaleTop();
    }

    return maxScaleTop;
}

qreal IracemaLineSeriesView::_yScaleBottom()
{
    qreal mimScaleBottom = 0;
    for (auto line : qAsConst(_lines)) {
        if (line->yScaleBottom() < mimScaleBottom)
            mimScaleBottom = line->yScaleBottom();
    }

    return mimScaleBottom;
}

void IracemaLineSeriesView::appendLine(QQmlListProperty<IracemaLineSeries> *list, IracemaLineSeries *line)
{
    IracemaLineSeriesView *view = qobject_cast<IracemaLineSeriesView *>(list->object);

    if (view) {
        line->setParentItem(view);
        view->_lines.append(line);
        connect(line, &IracemaLineSeries::yScaleTopChanged, view, [view] { view->_reDrawGrid = true; });
        connect(line, &IracemaLineSeries::yScaleBottomChanged, view, [view] { view->_reDrawGrid = true; });
    }
}

void IracemaLineSeriesView::appendHorizontalScaleLabel(QQmlListProperty<IracemaScaleLabel> *list, IracemaScaleLabel *label)
{
    IracemaLineSeriesView *view = qobject_cast<IracemaLineSeriesView *>(list->object);

    if (view) {
        label->setParentItem(view);
        view->_horizontalScaleLabels.append(label);
    }
}

void IracemaLineSeriesView::appendVerticalScaleLabel(QQmlListProperty<IracemaScaleLabel> *list, IracemaScaleLabel *label)
{
    IracemaLineSeriesView *view = qobject_cast<IracemaLineSeriesView *>(list->object);

    if (view) {
        label->setParentItem(view);
        view->_verticalScaleLabels.append(label);
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
        _lines[lineIndex]->addPoint(point);
}

void IracemaLineSeriesView::clearData()
{
    for (auto line : qAsConst(_lines))
        line->clearData();

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
        _updateTimerId = startTimer(_updateTime, Qt::PreciseTimer);

}

void IracemaLineSeriesView::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == _updateTimerId && !_isProcessingImage)
        update();
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
    if (!oldNode) {
        oldNode = new QSGNode;
    }

    if (_reDrawGrid) {
        oldNode->removeAllChildNodes();
        QSGNode *backgroundNode = new QSGSimpleRectNode(_calculatePlotArea(true), _backgroundColor);
        oldNode->appendChildNode(backgroundNode);
        _drawGrid(oldNode);
        _drawLines(oldNode, true);
        _reDrawGrid = false;
    } else
        _drawLines(oldNode);

    return oldNode;
}
