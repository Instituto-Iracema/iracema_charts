#include "iracemalineseriesview.h"

IracemaLineSeriesView::IracemaLineSeriesView(QQuickItem *parent) :
QQuickItem(parent),
_hasScales(false),
_removeGridHorizontal(false),
_updateTime(50),
_xScaleTop(10000),
_xScaleBottom(0),
_xTickCount(0),
_yTickCount(0),
_verticalScaleHeigth(50),
_horizontalScaleWidth(50),
_plotAreaRigthPadding(50 * 0.3), // _horizontalScaleWidth * 0.3
_xTitle(),
_yTitle(),
_gridLineWidth(1),
_gridColor(Qt::gray),
_gridSize(QSizeF(1, 1)),
_gridOffset(QSizeF(0, 0)),
_scaleColor(Qt::white),
_backgroundColor(Qt::white),
_lines(),
_dashedLines(),
_verticalScaleLabels(),
_horizontalScaleLabels(),
_isProcessingImage(false),
_redrawGrid(true),
_redrawLines(true),
_redrawPeakLabels(true),
_updateTimerId(-1)
{
    QQuickItem::setFlag(ItemHasContents, true);

    connect(this, &IracemaLineSeriesView::gridSizeChanged, &IracemaLineSeriesView::_onGridSizeChanged);
}

IracemaLineSeriesView::~IracemaLineSeriesView()
{
    _deleteLists();
}

void IracemaLineSeriesView::addPoint(quint32 lineIndex, const QPointF& point)
{
    _lines[lineIndex]->addPoint(point);
}

void IracemaLineSeriesView::addPoint(quint32 lineIndex, qreal x, qreal y)
{
    _lines[lineIndex]->addPoint(QPointF(x, y));
}

void IracemaLineSeriesView::addPoints(quint32 lineIndex, const QList<QPointF>& points)
{
    for (const auto& point : points)
    {
        _lines[lineIndex]->addPoint(point);
    }
}

void IracemaLineSeriesView::clearData()
{
    for (auto& line : qAsConst(_lines))
    {
        line->clearData();
    }

    _redrawGrid = true;
}

void IracemaLineSeriesView::clearLine(quint32 lineIndex)
{
    _lines[lineIndex]->clearData();

    _redrawGrid = true;
}

QQmlListProperty<IracemaLineSeries> IracemaLineSeriesView::lines()
{
    return QQmlListProperty<IracemaLineSeries>(this, nullptr, &IracemaLineSeriesView::_appendLine,
                                                nullptr, nullptr, nullptr);
}

QQmlListProperty<IracemaDashedLine> IracemaLineSeriesView::dashedLines()
{
    return QQmlListProperty<IracemaDashedLine>(this, nullptr, &IracemaLineSeriesView::_appendDashedLine,
                                                nullptr, nullptr, nullptr);
}

QQmlListProperty<IracemaScaleLabel> IracemaLineSeriesView::verticalScaleLabels()
{
    return QQmlListProperty<IracemaScaleLabel>(this, nullptr, &IracemaLineSeriesView::_appendVerticalScaleLabel,
                                                nullptr, nullptr, nullptr);
}

QQmlListProperty<IracemaScaleLabel> IracemaLineSeriesView::horizontalScaleLabels()
{
    return QQmlListProperty<IracemaScaleLabel>(this, nullptr, &IracemaLineSeriesView::_appendHorizontalScaleLabel,
                                                nullptr, nullptr, nullptr);
}

void IracemaLineSeriesView::_appendLine(QQmlListProperty<IracemaLineSeries>* list, IracemaLineSeries* line)
{
    auto view = qobject_cast<IracemaLineSeriesView*>(list->object);
    if (view)
    {
        line->setParentItem(view);
        view->_lines.append(line);
        connect(line, &IracemaLineSeries::yScaleTopChanged, view, [view] { view->_setRedrawAll(); });
        connect(line, &IracemaLineSeries::yScaleBottomChanged, view, [view] { view->_setRedrawAll(); });
        connect(line, &IracemaLineSeries::graphPointLabelsChanged, view, [view] { view->_redrawPeakLabels = true; });
    }
}

void IracemaLineSeriesView::_appendDashedLine(QQmlListProperty<IracemaDashedLine>* list, IracemaDashedLine* label)
{
    auto view = qobject_cast<IracemaLineSeriesView*>(list->object);
    if (view)
    {
        label->setParentItem(view);
        view->_dashedLines.append(label);
    }
}

void IracemaLineSeriesView::_appendVerticalScaleLabel(QQmlListProperty<IracemaScaleLabel>* list, IracemaScaleLabel* label)
{
    auto view = qobject_cast<IracemaLineSeriesView*>(list->object);
    if (view)
    {
        label->setParentItem(view);
        view->_verticalScaleLabels.append(label);
    }
}

void IracemaLineSeriesView::_appendHorizontalScaleLabel(QQmlListProperty<IracemaScaleLabel>* list, IracemaScaleLabel* label)
{
    auto view = qobject_cast<IracemaLineSeriesView*>(list->object);
    if (view)
    {
        label->setParentItem(view);
        view->_horizontalScaleLabels.append(label);
    }
}

void IracemaLineSeriesView::_setRedrawAll()
{
    _redrawGrid = true;
    _redrawLines = true;
    _redrawPeakLabels = true;
}

void IracemaLineSeriesView::_drawGrid(QSGNode* mainNode)
{
    if ((_gridSize.width() <= 0) || (_gridSize.height() <= 0))
    {
        return;
    }

    if (_removeGridHorizontal)
    {
        _drawTopAndBottom(mainNode);
    }
    else
    {
        _drawGridHorizontal(mainNode);
    }

    _drawGridVertical(mainNode);

    if (_hasScales)
    {
        _drawTitles(mainNode);
    }

    for (auto line: qAsConst(_dashedLines))
    {
        _convertAndDrawDashedLine(mainNode, line, true);
    }
}

void IracemaLineSeriesView::_drawTopAndBottom(QSGNode* mainNode)
{
    qreal x, y, width, height;
    auto plotArea = _calculatePlotArea(x, y, width, height);

    auto topMaterial = new QSGFlatColorMaterial();
    topMaterial->setColor(_gridColor);

    auto lineTop = QLineF(x, y, x+width, y);
    _drawOneLine(mainNode, lineTop, _gridLineWidth, topMaterial);

    auto bottomMaterial = new QSGFlatColorMaterial();
    bottomMaterial->setColor(_gridColor);

    auto lineBottom = QLineF(x, (_hasScales ? y + height + _verticalScaleHeigth * 0.1 : y+height), x+width, (_hasScales ? y + height + _verticalScaleHeigth * 0.1 : y+height));
    _drawOneLine(mainNode, lineBottom, _gridLineWidth, bottomMaterial);

    if (!_hasScales)
    {
        return;
    }

    for (auto label : qAsConst(_verticalScaleLabels))
    {
        auto strings = label->scaleText().split("|", Qt::SkipEmptyParts);
        auto newY = _convertValueToNewScale(label->scalePoint(), _yScaleBottom(), _yScaleTop(), plotArea.bottom(), plotArea.top());
        _drawScaleLabel(mainNode, x - 55, newY - 10, strings.at(0), QTextOption(Qt::AlignRight));
        _drawScaleLabel(mainNode, x + width + 10, newY - 10, strings.at(1), QTextOption(Qt::AlignLeft));
    }
}

void IracemaLineSeriesView::_drawGridHorizontal(QSGNode* mainNode)
{
    qreal x, y, width, height;
    auto plotArea =  _calculatePlotArea(x, y, width, height);
    qreal currentY = y;
    qreal limit = y + height;
    qreal gridHeigth = 0;
    qreal labelValue = _yScaleTop();
    qreal labelValueInterval;
    // used to solve problems of rouding labelValueInterval by odd tickCount
    int drawedGridLines = 0;
    const int GRID_LINES_TO_DRAW = (_yTickCount ? _yTickCount : (height / gridHeigth)) + 1;

    if (_yTickCount)
    {
        gridHeigth = height / _yTickCount;
        labelValueInterval = labelValue / _yTickCount;
    }
    else
    {
        gridHeigth = _gridSize.height();
        labelValueInterval = labelValue / (height / gridHeigth);
    }

    while ((currentY <= limit) || (drawedGridLines < GRID_LINES_TO_DRAW))
    {
        if ( currentY > limit)
        {
            currentY = limit;
            labelValue = _yScaleBottom();
        }

        auto material = new QSGFlatColorMaterial();
        material->setColor(_gridColor);

        auto line = QLineF(_horizontalScaleWidth * 0.95, currentY, x+width, currentY);
        _drawOneLine(mainNode, line, _gridLineWidth, material);
        drawedGridLines++;

        if (_hasScales)
        {
            int numberOfDigits = 2;
            qreal truncValue = 0;
            // Finds the number of digits where they became equal
            while (!qFuzzyCompare(_truncate(labelValue, numberOfDigits), _truncate(labelValue - labelValueInterval, numberOfDigits)))
            {
                if (numberOfDigits <= 0)
                {
                    break;
                }
                --numberOfDigits;
            }

            // Finds the number of digits where they became different
            while (qFuzzyCompare(_truncate(labelValue, numberOfDigits), _truncate(labelValue - labelValueInterval, numberOfDigits)))
            {
                if (numberOfDigits >= 3)
                {
                    break;
                }
                ++numberOfDigits;
            }

            truncValue = _truncate(labelValue, numberOfDigits);
            _drawScaleLabel(mainNode, x - 55, currentY - 10, QString::number(truncValue), QTextOption(Qt::AlignRight));
        }
        currentY += gridHeigth;
        labelValue -= labelValueInterval;
    }

    for (auto label : qAsConst(_verticalScaleLabels))
    {
        auto newY = _convertValueToNewScale(label->scalePoint(), _yScaleBottom(), _yScaleTop(), plotArea.bottom(), plotArea.top());
        _drawScaleLabel(mainNode, x + width + 10, newY - 10, label->scaleText(), QTextOption(Qt::AlignLeft));
    }
}

void IracemaLineSeriesView::_drawGridVertical(QSGNode* mainNode)
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

    if (_xTickCount)
    {
        gridWidth = width / _xTickCount;
        labelValueInterval = _xScaleTop / _xTickCount;
    }
    else
    {
        gridWidth = _gridSize.width();
        labelValueInterval = _xScaleTop / (width / gridWidth);
    }

    while ((currentX <= limit) || (drawedGridLines < GRID_LINES_TO_DRAW))
    {
        if (currentX > limit)
        {
            currentX = limit;
            labelValue = _xScaleTop;
        }

        auto material = new QSGFlatColorMaterial();
        material->setColor(_gridColor);

        auto line = QLineF(currentX, y, currentX, (_hasScales ? y + height + _verticalScaleHeigth * 0.1 : y+height));
        _drawOneLine(mainNode, line, _gridLineWidth, material);
        drawedGridLines++;

        if (_hasScales)
        {
            int numberOfDigits = 2;
            qreal truncValue = 0;
            // Finds the number of digits where they became equal
            while (!qFuzzyCompare(_truncate(labelValue, numberOfDigits), _truncate(labelValue - labelValueInterval, numberOfDigits)))
            {
                if (numberOfDigits <= 0)
                {
                    break;
                }
                --numberOfDigits;
            }

            // Finds the number of digits where they became different
            while (qFuzzyCompare(_truncate(labelValue, numberOfDigits), _truncate(labelValue - labelValueInterval, numberOfDigits)))
            {
                if (numberOfDigits >= 3)
                {
                    break;
                }
                ++numberOfDigits;
            }

            truncValue = _truncate(labelValue, numberOfDigits);
            _drawScaleLabel(mainNode, currentX - 25, (_hasScales? y + height + _verticalScaleHeigth * 0.15 : y + height), QString::number(truncValue), QTextOption(Qt::AlignHCenter));
        }

        currentX += gridWidth;
        labelValue += labelValueInterval;
    }

    for (auto label : qAsConst(_horizontalScaleLabels))
    {
        auto newX = _convertValueToNewScale(label->scalePoint(), _xScaleBottom, _xScaleTop, x, x+width);
        // center label component
        newX -= 25;
        _drawScaleLabel(mainNode, newX , (_hasScales? y + height + _verticalScaleHeigth * 0.15 : y + height), label->scaleText(), QTextOption(Qt::AlignHCenter));
    }
}

void IracemaLineSeriesView::_drawTitles(QSGNode* mainNode)
{
    const auto width = 300;
    const auto height = 20;

    const auto rect = _calculatePlotArea();
    const qint32 xMidPoint = (rect.width() - width)/2 + rect.x();
    const qint32 yMidPoint = (rect.height() - width)/2 + rect.y();

    QFont font;
    font.setPixelSize(15);
    QPen pen;
    pen.setColor(_scaleColor);
    QTextOption textOption(Qt::AlignCenter);

    auto pixmapX = QPixmap(QSize(width, height));
    pixmapX.fill(Qt::transparent);
    QPainter painterX(&pixmapX);
    auto pixmapY = QPixmap(QSize(height, width));
    pixmapY.fill(Qt::transparent);
    QPainter painterY(&pixmapY);

    painterX.setFont(font);
    painterX.setPen(pen);
    painterY.setFont(font);
    painterY.setPen(pen);

    const auto rectangleX = QRect(0, 0, width, height);
    painterX.drawText(rectangleX, _xTitle, textOption);
    const auto rectangleY = QRect(0, 0, width, height);
    painterY.translate(0, width);
    painterY.rotate(-90);
    painterY.drawText(rectangleY, _yTitle, textOption);
    painterY.translate(0, -width);

    auto textureX = window()->createTextureFromImage(pixmapX.toImage());
    auto textureY = window()->createTextureFromImage(pixmapY.toImage());

    auto childNodeX = new QSGSimpleTextureNode;
    childNodeX->setOwnsTexture(true);
    childNodeX->setRect(QRectF(xMidPoint, rect.y() + rect.height() + 25, width, height));
    childNodeX->markDirty(QSGNode::DirtyForceUpdate);
    childNodeX->setTexture(textureX);
    childNodeX->setFlags(QSGNode::OwnedByParent);
    mainNode->appendChildNode(childNodeX);

    auto childNodeY = new QSGSimpleTextureNode;
    childNodeY->setOwnsTexture(true);
    childNodeY->setRect(QRectF(0, yMidPoint, height, width));
    childNodeY->markDirty(QSGNode::DirtyForceUpdate);
    childNodeY->setTexture(textureY);
    childNodeY->setFlags(QSGNode::OwnedByParent);
    mainNode->appendChildNode(childNodeY);
}

void IracemaLineSeriesView::_drawLines(QSGNode* mainNode, bool redrawAllData)
{
    for (auto lineSeries : qAsConst(_lines))
    {
        QSGNode* lineSeriesNode = new QSGNode();
        lineSeriesNode->setFlags(QSGNode::OwnedByParent | QSGNode::OwnsGeometry);
        _drawLineSeries(lineSeriesNode, lineSeries, true, redrawAllData);
        mainNode->appendChildNode(lineSeriesNode);
    }
}

void IracemaLineSeriesView::_drawLineSeries(QSGNode* mainNode, IracemaLineSeries* lineSeries, bool invertY, bool redrawAllData)
{
    qreal x, y, width, height;
    _calculatePlotArea(x, y, width, height);
    QVector<QLineF> dataToDraw;

    if (redrawAllData)
    {
        lineSeries->applyDataBuffer();
        dataToDraw = lineSeries->data();
    }
    else
    {
        dataToDraw = lineSeries->dataBuffer();
        lineSeries->applyDataBuffer();
    }

    for (const auto& line : qAsConst(dataToDraw))
    {
        auto newX1 = _convertValueToNewScale(line.p1().x(), _xScaleBottom, _xScaleTop, 0, width) + x;
        auto newX2 = _convertValueToNewScale(line.p2().x(), _xScaleBottom, _xScaleTop, 0, width) + x;
        auto newY1 = _convertValueToNewScale(line.p1().y(), lineSeries->yScaleBottom(), lineSeries->yScaleTop(), 0, height);
        auto newY2 = _convertValueToNewScale(line.p2().y(), lineSeries->yScaleBottom(), lineSeries->yScaleTop(), 0, height);

        //Clip values to view boundaries
        newY1 = std::max(0.0, std::min(newY1, height));
        newY2 = std::max(0.0, std::min(newY2, height));

        if (invertY)
        {
            newY1 = this->height() - newY1 - (this->height() - height - y);
            newY2 = this->height() - newY2 - (this->height() - height - y);
        }
        else
        {
            newY1 += y;
            newY2 += y;
        }

        auto newP1 = QPointF(newX1, newY1);
        auto newP2 = QPointF(newX2, newY2);
        auto newLine = QLineF(newP1, newP2);

        auto lineMaterial = new QSGFlatColorMaterial();
        lineMaterial->setColor(lineSeries->lineColor());
        _drawOneLine(mainNode, newLine, lineSeries->lineWidth(), lineMaterial);
    }
}

void IracemaLineSeriesView::_drawPeaksLabels(bool redrawAll)
{
    QRectF rectangle = _calculatePlotArea();
    qreal yScaleTop = _yScaleTop();
    qreal yScaleBottom = _yScaleBottom();
    QList<IracemaPointLabel*> labelsToDraw;

    for (auto lineSeries : qAsConst(_lines))
    {
        if (redrawAll)
        {
            lineSeries->applyPointLabelsBuffer();
            labelsToDraw = lineSeries->pointLabels();
        }
        else
        {
            labelsToDraw = lineSeries->pointLabelsBuffer();
            lineSeries->applyPointLabelsBuffer();
        }

        for (auto pointLabel : qAsConst(labelsToDraw))
        {
            QSGNode* label = new QSGNode();
            label->setFlags(QSGNode::OwnedByParent | QSGNode::OwnsGeometry);
            auto newX = _convertValueToNewScale(pointLabel->graphPoint().x(), _xScaleBottom, _xScaleTop, rectangle.x(), rectangle.right());
            auto newY = _convertValueToNewScale(pointLabel->graphPoint().y(), yScaleBottom, yScaleTop, rectangle.bottom(), rectangle.top());
            _drawScaleLabel(label, newX - 25, newY - 10, pointLabel->text(), QTextOption(Qt::AlignHCenter));
            _drawScaleLabel(label, newX - 25, newY - 30, pointLabel->upperText(), QTextOption(Qt::AlignHCenter));
            _peakLabelLayer->appendChildNode(label);
        }
    }
}

void IracemaLineSeriesView::_convertAndDrawDashedLine(QSGNode* mainNode, IracemaDashedLine* line, bool invertY)
{
    qreal x, y, width, height;
    _calculatePlotArea(x, y, width, height);

    auto initialPointX = _convertValueToNewScale(line->initialPoint().x(), _xScaleBottom, _xScaleTop, 0, width) + x;
    auto initialPointY = _convertValueToNewScale(line->initialPoint().y(), line->yScaleBottom(), line->yScaleTop(), 0, height);

    auto finalPointX = _convertValueToNewScale(line->finalPoint().x(), _xScaleBottom, _xScaleTop, 0, width) + x;
    auto finalPointY = _convertValueToNewScale(line->finalPoint().y(), line->yScaleBottom(), line->yScaleTop(), 0, height);

    //Clip values to view boundaries
    initialPointY = std::max(0.0, std::min(initialPointY, height));
    finalPointY = std::max(0.0, std::min(finalPointY, height));

    if (invertY)
    {
        initialPointY = this->height() - initialPointY - (this->height() - height - y);
        finalPointY = this->height() - finalPointY - (this->height() - height - y);
    }
    else
    {
        initialPointY += y;
        finalPointY += y;
    }

    _drawDashedLine(mainNode, line->lineColor(), line->lineWidth(), QPointF(initialPointX, initialPointY), QPointF(finalPointX, finalPointY), 2);
}

void IracemaLineSeriesView::_drawDashedLine(QSGNode* mainNode, const QColor& lineColor, const qreal lineWidth, const QPointF &initialPoint, const QPointF &finalPoint, int percentage)
{
    const qreal xDotValue = std::fabs(initialPoint.x() - finalPoint.x()) * percentage / 100.0;
    const qreal yDotValue = std::fabs(initialPoint.y() - finalPoint.y()) * percentage / 100.0;

    qreal currentX = initialPoint.x();
    qreal currentY = initialPoint.y();

    for (int i = 0; i < 100 / (percentage * 2); i++)
    {
        auto lineMaterial = new QSGFlatColorMaterial();
        lineMaterial->setColor(lineColor);
        auto newLine = QLineF(QPointF(currentX, currentY), QPointF(currentX + xDotValue, currentY - yDotValue));
        _drawOneLine(mainNode, newLine, lineWidth, lineMaterial);
        currentX += xDotValue * 2;
        currentY -= yDotValue * 2;
    }
}

void IracemaLineSeriesView::_drawScaleLabel(QSGNode* mainNode, qreal x, qreal y, QString label, QTextOption textOption)
{
    auto pixmap = QPixmap(QSize(50,50));
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);

    QFont labelFont;
    labelFont.setPixelSize(15);
    painter.setFont(labelFont);

    QPen pen;
    pen.setColor(_scaleColor);
    painter.setPen(pen);

    const auto rectangle = QRect(0, 0, 50, 50);
    painter.drawText(rectangle, label, textOption);

    auto texture = window()->createTextureFromImage(pixmap.toImage());

    auto childNode = new QSGSimpleTextureNode;
    childNode->setOwnsTexture(true);
    childNode->setRect(QRectF(x, y, 50, 50));
    childNode->markDirty(QSGNode::DirtyForceUpdate);
    childNode->setTexture(texture);
    childNode->setFlags(QSGNode::OwnedByParent);
    mainNode->appendChildNode(childNode);
}

void IracemaLineSeriesView::_drawOneLine(QSGNode* mainNode, QLineF line, qreal lineWidth, QSGFlatColorMaterial* lineMaterial)
{
    auto geometry = new QSGGeometry(QSGGeometry::defaultAttributes_Point2D(), 2);
    geometry->setLineWidth(lineWidth);
    geometry->setDrawingMode(QSGGeometry::DrawLineStrip);

    auto childNode = new QSGGeometryNode;
    childNode->setGeometry(geometry);
    childNode->setMaterial(lineMaterial);
    childNode->setFlags(QSGNode::OwnedByParent | QSGNode::OwnsGeometry | QSGNode::OwnsMaterial);

    auto vertices = geometry->vertexDataAsPoint2D();

    vertices[0].set(line.x1(), line.y1());
    vertices[1].set(line.x2(), line.y2());

    mainNode->appendChildNode(childNode);
}

QRectF IracemaLineSeriesView::_calculatePlotArea()
{
    qreal x, y, width, heigth;

    return _calculatePlotArea(x,y,width,heigth);
}

QRectF IracemaLineSeriesView::_calculatePlotArea(qreal &x, qreal &y, qreal &width, qreal &heigth)
{
    if (_hasScales)
    {
        x = _horizontalScaleWidth;
        y = _verticalScaleHeigth * 0.25;
        width = this->width() - _horizontalScaleWidth * 2 - _plotAreaRigthPadding;
        heigth = this->height() - _verticalScaleHeigth * 1.25;
    }
    else
    {
        x = 0;
        y = 0;
        width = this->width();
        heigth = this->height();
    }

    return QRectF(x, y, width, heigth);
}

qreal IracemaLineSeriesView::_yScaleTop()
{
    qreal maxScaleTop = 0;
    for (auto line : qAsConst(_lines))
    {
        if (line->yScaleTop() > maxScaleTop)
        {
            maxScaleTop = line->yScaleTop();
        }
    }

    return maxScaleTop;
}

qreal IracemaLineSeriesView::_yScaleBottom()
{
    qreal mimScaleBottom = 0;
    for (auto line : qAsConst(_lines))
    {
        if (line->yScaleBottom() < mimScaleBottom)
        {
            mimScaleBottom = line->yScaleBottom();
        }
    }

    return mimScaleBottom;
}

qreal IracemaLineSeriesView::_truncate(qreal value, int numberOfDigits) const
{
    numberOfDigits = (int) std::pow(10, numberOfDigits);

    double truncValue = int(value * numberOfDigits);
    return truncValue / numberOfDigits;
}

qreal IracemaLineSeriesView::_convertValueToNewScale(qreal oldValue, qreal oldScaleBottom, qreal oldScaleTop, qreal newScaleBottom, qreal newScaleTop)
{
    qreal newValue = oldValue - oldScaleBottom;
    newValue *= newScaleTop - newScaleBottom;
    newValue /= oldScaleTop - oldScaleBottom;
    newValue += newScaleBottom;

    return newValue;
}

void IracemaLineSeriesView::_deleteLists() noexcept
{
    for (auto &line : _lines)
    {
        delete line;
    }
    _lines.clear();

    for (auto &dashedLine : _dashedLines)
    {
        delete dashedLine;
    }
    _dashedLines.clear();

    for (auto &vScale : _verticalScaleLabels)
    {
        delete vScale;
    }
    _verticalScaleLabels.clear();

    for (auto &hScale : _horizontalScaleLabels)
    {
        delete hScale;
    }
    _horizontalScaleLabels.clear();
}

void IracemaLineSeriesView::_onGridSizeChanged()
{
    _redrawGrid = true;
}

void IracemaLineSeriesView::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_UNUSED(oldGeometry);
    Q_UNUSED(newGeometry);

    _redrawGrid = true;

    if (_updateTimerId == -1)
    {
        _updateTimerId = startTimer(_updateTime, Qt::PreciseTimer);
    }

}

void IracemaLineSeriesView::timerEvent(QTimerEvent *event)
{
    if ((event->timerId() == _updateTimerId) && (!_isProcessingImage))
    {
        QQuickItem::update();
    }
}

QSGNode* IracemaLineSeriesView::updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*)
{
    if (!oldNode)
    {
        oldNode = new QSGNode;
        _backgroundLayer = new QSGSimpleRectNode(QRectF(0, 0, this->width(), this->height()), _backgroundColor);
        _gridLayer = new QSGNode;
        _peakLabelLayer = new QSGNode;
        oldNode->appendChildNode(_backgroundLayer);
        oldNode->appendChildNode(_gridLayer);
        oldNode->appendChildNode(_peakLabelLayer);
    }

    if (_redrawGrid)
    {
        oldNode->removeChildNode(_gridLayer);
        delete(_gridLayer);
        _gridLayer = new QSGNode;
        _drawGrid(_gridLayer);
        _drawLines(_gridLayer, true);
        _redrawGrid = false;
        _redrawPeakLabels = true;
        oldNode->insertChildNodeAfter(_gridLayer,_backgroundLayer);
    }
    else
    {
        _drawLines(_gridLayer);
    }

    if (_redrawPeakLabels)
    {
        oldNode->removeChildNode(_peakLabelLayer);
        delete(_peakLabelLayer);
        _peakLabelLayer = new QSGNode;
        _drawPeaksLabels(true);
        _redrawPeakLabels = false;
        oldNode->insertChildNodeAfter(_peakLabelLayer,_gridLayer);
    }
    else
    {
        _drawPeaksLabels();
    }

    return oldNode;
}
