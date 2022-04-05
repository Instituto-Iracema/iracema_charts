#include "iracemalineseriesview.h"

/**
 * @brief Lines getter
 * @return The list of lineseries of the view
 */
const QList<IracemaLineSeries *> &IracemaLineSeriesView::lines() const
{
    return _lines;
}

/**
 * @brief Lines Setter
 * @param newLines - The new list of line series to be setted
 */
void IracemaLineSeriesView::setLines(const QList<IracemaLineSeries *> &newLines)
{
    if (_lines == newLines)
        return;
    _lines = newLines;
    emit linesChanged();
}

/**
 * @brief GridColor Getter
 * @return The Grid Color
 */
const QColor &IracemaLineSeriesView::gridColor() const
{
    return _gridColor;
}

/**
 * @brief GridColor Setter
 * @param newGridColor - The new GridColor to be set
 */
void IracemaLineSeriesView::setGridColor(const QColor &newGridColor)
{
    if (_gridColor == newGridColor)
        return;
    _gridColor = newGridColor;
    emit gridColorChanged();
}

/**
 * @brief GridSize Getter
 * @return The Grid Size as a QSize
 */
const QSizeF &IracemaLineSeriesView::gridSize() const
{
    return _gridSize;
}

/**
 * @brief GridSize Setter
 * @param newGridSize - The new GridSize to be set
 */
void IracemaLineSeriesView::setGridSize(const QSizeF &newGridSize)
{
    if (_gridSize == newGridSize)
        return;
    _gridSize = newGridSize;
    emit gridSizeChanged();
}

void IracemaLineSeriesView::componentComplete()
{

}

/**
 * @brief Draws a LineSeries on the view
 * @param painter - Reference to the painter
 * @param line - The line to be drawn
 */
void IracemaLineSeriesView::_drawLine(QPainter *painter, IracemaLineSeries *line)
{

}

/**
 * @brief Draws the horizontal grid lines on the view
 * @param painter - Reference to the painter
 */
void IracemaLineSeriesView::_drawHorizontalGrid(QPainter *painter)
{
    painter->setPen(QPen(_gridColor));
    for (float currentPosition = 0; currentPosition < height(); currentPosition += _gridSize.height())
    {
        painter->drawLine(QPointF(0, currentPosition), QPointF(width(), currentPosition));
    }
}

/**
 * @brief Draws the vertical grid lines on the view
 * @param painter - Reference to the painter
 */
void IracemaLineSeriesView::_drawVerticalGrid(QPainter *painter)
{

}

/**
 * @brief Draws the grid on the view
 * @param painter - Reference to the painter
 */
void IracemaLineSeriesView::_drawGrid(QPainter *painter)
{

}

/**
 * @brief Constructs a new LineSeriesView
 * @param parent - The parent QObject
 */
IracemaLineSeriesView::IracemaLineSeriesView(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setFlag(QQuickItem::ItemHasContents, true);
//    _pixmap = QPixmap(boundingRect().width(), boundingRect().height());
//    _pixmapPainter = new QPainter();
//    _pixmapPainter->begin(&_pixmap);
}


IracemaLineSeriesView::~IracemaLineSeriesView()
{

}

/**
 * @brief Called the the system needs to redraw the item
 * @param painter - Reference to the painter
 */
void IracemaLineSeriesView::paint(QPainter *painter)
{
//    updateChart();
//    painter->drawPixmap(QPointF(), _pixmap);
    painter->setPen(QPen(Qt::red));
    painter->drawRect(boundingRect());
}

/**
 * @brief Updates the view with new data
 */
void IracemaLineSeriesView::updateChart()
{
    _drawHorizontalGrid(_pixmapPainter);
}

/**
 * @brief Redraws the view to fit new size
 */
void IracemaLineSeriesView::updateChartSize()
{

}
