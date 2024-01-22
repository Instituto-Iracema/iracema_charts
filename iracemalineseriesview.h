#ifndef IRACEMALINESERIESVIEW_H
#define IRACEMALINESERIESVIEW_H

#include "iracemalineseries.h"
#include "iracemascalelabel.h"
#include "iracemadashedline.h"

#include <QPainter>
#include <QQuickItem>
#include <QSGFlatColorMaterial>
#include <QSizeF>
#include <QBrush>
#include <QRandomGenerator>
#include <QSGGeometryNode>
#include <QSGFlatColorMaterial>
#include <QQuickItemGrabResult>
#include <QSGSimpleRectNode>
#include <QRectF>
#include <QSGSimpleTextureNode>
#include <QSGImageNode>
#include <QPixmap>
#include <QQuickWindow>

#include <math.h>

/**
 * \class IracemaLineSeriesView
 * \brief The IracemaLineSeriesView class is a QQuickItem that draws the visualization of a line series chart.
 * 
 * \startuml
 * skinparam classAttributeIconSize 0
 * class IracemaLineSeriesView {
 *      +hasScales()
 *      +setHasScales()
 *      +removeGridHorizontal()
 *      +setRemoveGridHorizontal()
 *      +updateTime()
 *      +setUpdateTime()
 *      +xScaleTop()
 *      +setXScaleTop()
 *      +xScaleBottom()
 *      +setXScaleBottom()
 *      +xTickCount()
 *      +setXTickCount()
 *      +yTickCount()
 *      +setYTickCount()
 *      +verticalScaleHeigth()
 *      +setVerticalScaleHeigth()
 *      +horizontalScaleWidth()
 *      +setHorizontalScaleWidth()
 *      +plotAreaRigthPadding()
 *      +setPlotAreaRigthPadding()
 *      +xTitle()
 *      +setXTitle()
 *      +yTitle()
 *      +setYTitle()
 *      +gridLineWidth()
 *      +setGridLineWidth()
 *      +gridColor()
 *      +setGridColor()
 *      +gridSize()
 *      +setGridSize()
 *      +gridOffset()
 *      +setGridOffset()
 *      +scaleColor()
 *      +setScaleColor()
 *      +backgroundColor()
 *      +setBackgroundColor()
 *      +addPoint()
 *      +addPoint()
 *      +addPoints()
 *      +clearData()
 *      +clearLine()
 *      +lines()
 *      +dashedLines()
 *      +verticalScaleLabels()
 *      +horizontalScaleLabels()
 *      +{signal} hasScalesChanged()
 *      +{signal} removeGridHorizontalChanged()
 *      +{signal} updateTimeChanged()
 *      +{signal} xScaleTopChanged()
 *      +{signal} xScaleBottomChanged()
 *      +{signal} xTickCountChanged()
 *      +{signal} yTickCountChanged()
 *      +{signal} verticalScaleHeigthChanged()
 *      +{signal} horizontalScaleWidthChanged()
 *      +{signal} plotAreaRigthPaddingChanged()
 *      +{signal} xTitleChanged()
 *      +{signal} yTitleChanged()
 *      +{signal} gridLineWidthChanged()
 *      +{signal} gridColorChanged()
 *      +{signal} gridSizeChanged()
 *      +{signal} gridOffsetChanged()
 *      +{signal} scaleColorChanged()
 *      +{signal} backgroundColorChanged()
 *      +{signal} linesChanged()
 *      +{signal} dashedLinesChanged()
 *      +{signal} verticalScaleLabelsChanged()
 *      +{signal} horizontalScaleLabelsChanged()
 *      -_appendLine()
 *      -_appendDashedLine()
 *      -_appendHorizontalScaleLabel()
 *      -_appendVerticalScaleLabel()
 *      -_setRedrawAll()
 *      -_drawGrid()
 *      -_drawTopAndBottom()
 *      -_drawGridHorizontal()
 *      -_drawGridVertical()
 *      -_drawTitles()
 *      -_drawLines()
 *      -_drawLineSeries()
 *      -_drawPeaksLabels()
 *      -_convertAndDrawDashedLine()
 *      -_drawDashedLine()
 *      -_drawScaleLabel()
 *      -_drawOneLine()
 *      -_calculatePlotArea()
 *      -_calculatePlotArea()
 *      -_yScaleTop()
 *      -_yScaleBottom()
 *      -_truncate()
 *      -_convertValueToNewScale()
 *      -_deleteLists()
 *      -_hasScales
 *      -_removeGridHorizontal
 *      -_updateTime
 *      -_xScaleTop
 *      -_xScaleBottom
 *      -_xTickCount
 *      -_yTickCount
 *      -_verticalScaleHeigth
 *      -_horizontalScaleWidth
 *      -_plotAreaRigthPadding
 *      -_xTitle
 *      -_yTitle
 *      -_gridLineWidth
 *      -_gridColor
 *      -_gridSize
 *      -_gridOffset
 *      -_scaleColor
 *      -_backgroundColor
 *      -_lines
 *      -_dashedLines
 *      -_verticalScaleLabels
 *      -_horizontalScaleLabels
 *      -_isProcessingImage
 *      -_redrawGrid
 *      -_redrawLines
 *      -_redrawPeakLabels
 *      -_updateTimerId
 *      -{slot} _onGridSizeChanged()
 *      #geometryChanged()
 *      #timerEvent()
 *      #updatePaintNode()
 *      #_backgroundLayer
 *      #_gridLayer
 *      #_peakLabelLayer
 * }
 * IracemaLineSeriesView <|-- QQuickItem
 * \enduml
*/
class IracemaLineSeriesView : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(IracemaLineSeriesView)

    Q_PROPERTY(bool hasScales READ hasScales WRITE setHasScales NOTIFY hasScalesChanged)
    Q_PROPERTY(bool removeGridHorizontal READ removeGridHorizontal WRITE setRemoveGridHorizontal NOTIFY removeGridHorizontalChanged)

    Q_PROPERTY(unsigned int updateTime READ updateTime WRITE setUpdateTime NOTIFY updateTimeChanged)

    Q_PROPERTY(qreal xScaleTop READ xScaleTop WRITE setXScaleTop NOTIFY xScaleTopChanged)
    Q_PROPERTY(qreal xScaleBottom READ xScaleBottom WRITE setXScaleBottom NOTIFY xScaleBottomChanged)
    Q_PROPERTY(qreal xTickCount READ xTickCount WRITE setXTickCount NOTIFY xTickCountChanged)
    Q_PROPERTY(qreal yTickCount READ yTickCount WRITE setYTickCount NOTIFY yTickCountChanged)
    Q_PROPERTY(qreal verticalScaleHeigth READ verticalScaleHeigth WRITE setVerticalScaleHeigth NOTIFY verticalScaleHeigthChanged)
    Q_PROPERTY(qreal horizontalScaleWidth READ horizontalScaleWidth WRITE setHorizontalScaleWidth NOTIFY horizontalScaleWidthChanged)
    Q_PROPERTY(qreal plotAreaRigthPadding READ plotAreaRigthPadding WRITE setPlotAreaRigthPadding NOTIFY plotAreaRigthPaddingChanged)

    Q_PROPERTY(QString xTitle READ xTitle WRITE setXTitle NOTIFY xTitleChanged)
    Q_PROPERTY(QString yTitle READ yTitle WRITE setYTitle NOTIFY yTitleChanged)

    Q_PROPERTY(qreal gridLineWidth READ gridLineWidth WRITE setGridLineWidth NOTIFY gridLineWidthChanged)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QSizeF gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(QSizeF gridOffset READ gridOffset WRITE setGridOffset NOTIFY gridOffsetChanged)

    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor NOTIFY scaleColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

    Q_PROPERTY(QQmlListProperty<IracemaLineSeries> lines READ lines NOTIFY linesChanged)
    Q_PROPERTY(QQmlListProperty<IracemaDashedLine> dashedLines READ dashedLines NOTIFY dashedLinesChanged)
    Q_PROPERTY(QQmlListProperty<IracemaScaleLabel> verticalScaleLabels READ verticalScaleLabels NOTIFY verticalScaleLabelsChanged)
    Q_PROPERTY(QQmlListProperty<IracemaScaleLabel> horizontalScaleLabels READ horizontalScaleLabels NOTIFY horizontalScaleLabelsChanged)

    QML_NAMED_ELEMENT(IracemaChart)

public:
    /**
     * \fn IracemaLineSeriesView
     * \param parent The parent QQuickItem.
     * \brief Constructor of IracemaLineSeriesView.
     * \details Creates a IracemaLineSeriesView object with the given parent.
     * \n Set the flag ItemHasContents to true.
     * \n Connects the signal gridSizeChanged to the slot _onGridSizeChanged.
     * \return IracemaLineSeriesView object.
    */
    explicit IracemaLineSeriesView(QQuickItem* parent = nullptr);

    /**
     * \fn ~IracemaLineSeriesView
     * \brief Destructor of IracemaLineSeriesView.
     * \details Destroys the IracemaLineSeriesView object.
     * \n Calls the _deleteLists function.
    */
    ~IracemaLineSeriesView();

    // Properties Getters and Setters

    /**
     * \fn hasScales
     * \brief Getter of the hasScales property.
     * \details Returns the value of the hasScales property.
     * \return hasScales (bool)
    */
    bool hasScales() const {
        return _hasScales;
    }

    /**
     * \fn setHasScales
     * \param newHasScales The new value of the hasScales property.
     * \brief Setter of the hasScales property.
     * \details Sets the value of the hasScales property.
     * \n Otherwise, the function sets the new value and emits the signal hasScalesChanged.
     * \n If the new value is equal to the old value, the function returns.
    */
    void setHasScales(bool newHasScales) {
        if(_hasScales == newHasScales)
            return;
        _hasScales = newHasScales;
        emit hasScalesChanged();
    }

    /**
     * \fn removeGridHorizontal
     * \brief Getter of the removeGridHorizontal property.
     * \details Returns the value of the removeGridHorizontal property.
     * \return removeGridHorizontal (bool)
    */
    bool removeGridHorizontal() const {
        return _removeGridHorizontal;
    }

    /**
     * \fn setRemoveGridHorizontal
     * \param newRemoveGridHorizontal The new value of the removeGridHorizontal property.
     * \brief Setter of the removeGridHorizontal property.
     * \details Sets the value of the removeGridHorizontal property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal removeGridHorizontalChanged.
    */
    void setRemoveGridHorizontal(bool newRemoveGridHorizontal) {
        if(_removeGridHorizontal == newRemoveGridHorizontal)
            return;
        _removeGridHorizontal = newRemoveGridHorizontal;
        emit removeGridHorizontalChanged();
    }

    /**
     * \fn updateTime
     * \brief Getter of the updateTime property.
     * \details Returns the value of the updateTime property.
     * \return updateTime (unsigned int)
    */
    unsigned int updateTime() const {
        return _updateTime;
    }

    /**
     * \fn setUpdateTime
     * \param newUpdateTime The new value of the updateTime property.
     * \brief Setter of the updateTime property.
     * \details Sets the value of the updateTime property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal updateTimeChanged.
    */
    void setUpdateTime(unsigned int newUpdateTime) {
        if(_updateTime == newUpdateTime)
            return;
        _updateTime = newUpdateTime;
        emit updateTimeChanged();        
    }

    /**
     * \fn xScaleTop
     * \brief Getter of the xScaleTop property.
     * \details Returns the value of the xScaleTop property.
     * \return xScaleTop (qreal)
    */
    qreal xScaleTop() const {
        return _xScaleTop;
    }

    /**
     * \fn setXScaleTop
     * \param newXScaleTop The new value of the xScaleTop property.
     * \brief Setter of the xScaleTop property.
     * \details Sets the value of the xScaleTop property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal xScaleTopChanged.
     * \n The function also calls the _setRedrawAll function.
    */
    void setXScaleTop(qreal newXScaleTop) {
        if(qFuzzyCompare(_xScaleTop, newXScaleTop))
            return;
        _xScaleTop = newXScaleTop;
        emit xScaleTopChanged();
        _setRedrawAll();
    }

    /**
     * \fn xScaleBottom
     * \brief Getter of the xScaleBottom property.
     * \details Returns the value of the xScaleBottom property.
     * \return xScaleBottom (qreal)
    */
    qreal xScaleBottom() const {
        return _xScaleBottom;
    }

    /**
     * \fn setXScaleBottom
     * \param newXScaleBottom The new value of the xScaleBottom property.
     * \brief Setter of the xScaleBottom property.
     * \details Sets the value of the xScaleBottom property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal xScaleBottomChanged.
     * \n The function also calls the _setRedrawAll function.
    */
    void setXScaleBottom(qreal newXScaleBottom) {
        if(qFuzzyCompare(_xScaleBottom, newXScaleBottom))
            return;
        _xScaleBottom = newXScaleBottom;
        emit xScaleBottomChanged();
        _setRedrawAll();
    }

    /**
     * \fn xTickCount
     * \brief Getter of the xTickCount property.
     * \details Returns the value of the xTickCount property.
     * \return xTickCount (qreal)
    */
    qreal xTickCount() const {
        return _xTickCount;
    }

    /**
     * \fn setXTickCount
     * \param newXTickCount The new value of the xTickCount property.
     * \brief Setter of the xTickCount property.
     * \details Sets the value of the xTickCount property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal xTickCountChanged.
    */
    void setXTickCount(qreal newXTickCount) {
        if(qFuzzyCompare(_xTickCount, newXTickCount))
            return;
        _xTickCount = newXTickCount;
        emit xTickCountChanged();
    }

    /**
     * \fn yTickCount
     * \brief Getter of the yTickCount property.
     * \details Returns the value of the yTickCount property.
     * \return yTickCount (qreal)
    */
    qreal yTickCount() const {
        return _yTickCount;
    }

    /**
     * \fn setYTickCount
     * \param newYTickCount The new value of the yTickCount property.
     * \brief Setter of the yTickCount property.
     * \details Sets the value of the yTickCount property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal yTickCountChanged.
    */
    void setYTickCount(qreal newYTickCount) {
        if(qFuzzyCompare(_yTickCount, newYTickCount))
            return;
        _yTickCount = newYTickCount;
        emit yTickCountChanged();
    }

    /**
     * \fn verticalScaleHeigth
     * \brief Getter of the verticalScaleHeigth property.
     * \details Returns the value of the verticalScaleHeigth property.
     * \return verticalScaleHeigth (qreal)
    */
    qreal verticalScaleHeigth() const {
        return _verticalScaleHeigth;
    }

    /**
     * \fn setVerticalScaleHeigth
     * \param newVerticalScaleHeigth The new value of the verticalScaleHeigth property.
     * \brief Setter of the verticalScaleHeigth property.
     * \details Sets the value of the verticalScaleHeigth property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal verticalScaleHeigthChanged.
    */
    void setVerticalScaleHeigth(qreal newVerticalScaleHeigth) {
        if(qFuzzyCompare(_verticalScaleHeigth, newVerticalScaleHeigth))
            return;
        _verticalScaleHeigth = newVerticalScaleHeigth;
        emit verticalScaleHeigthChanged();
    }

    /**
     * \fn horizontalScaleWidth
     * \brief Getter of the horizontalScaleWidth property.
     * \details Returns the value of the horizontalScaleWidth property.
     * \return horizontalScaleWidth (qreal)
    */
    qreal horizontalScaleWidth() const {
        return _horizontalScaleWidth;
    }

    /**
     * \fn setHorizontalScaleWidth
     * \param newHorizontalScaleWidth The new value of the horizontalScaleWidth property.
     * \brief Setter of the horizontalScaleWidth property.
     * \details Sets the value of the horizontalScaleWidth property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal horizontalScaleWidthChanged.
    */
    void setHorizontalScaleWidth(qreal newHorizontalScaleWidth) {
        if(qFuzzyCompare(_horizontalScaleWidth, newHorizontalScaleWidth))
            return;
        _horizontalScaleWidth = newHorizontalScaleWidth;
        emit horizontalScaleWidthChanged();
    }

    /**
     * \fn plotAreaRigthPadding
     * \brief Getter of the plotAreaRigthPadding property.
     * \details Returns the value of the plotAreaRigthPadding property.
     * \return plotAreaRigthPadding (qreal)
    */
    qreal plotAreaRigthPadding() const {
        return _plotAreaRigthPadding;
    }

    /**
     * \fn setPlotAreaRigthPadding
     * \param newPlotAreaRigthPadding The new value of the plotAreaRigthPadding property.
     * \brief Setter of the plotAreaRigthPadding property.
     * \details Sets the value of the plotAreaRigthPadding property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal plotAreaRigthPaddingChanged.
    */
    void setPlotAreaRigthPadding(qreal newPlotAreaRigthPadding) {
        if(qFuzzyCompare(_plotAreaRigthPadding, newPlotAreaRigthPadding))
            return;
        _plotAreaRigthPadding = newPlotAreaRigthPadding;
        emit plotAreaRigthPaddingChanged();
    }

    /**
     * \fn xTitle
     * \brief Getter of the xTitle property.
     * \details Returns the value of the xTitle property.
     * \return xTitle (QString)
    */
    QString xTitle() const {
        return _xTitle;
    }

    /**
     * \fn setXTitle
     * \param newXTitle The new value of the xTitle property.
     * \brief Setter of the xTitle property.
     * \details Sets the value of the xTitle property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal xTitleChanged.
    */
    void setXTitle(QString newXTitle) {
        if(_xTitle.compare(newXTitle) == 0)
            return;
        _xTitle = newXTitle;
        emit xTitleChanged();
    }
    /**
     * \fn yTitle
     * \brief Getter of the yTitle property.
     * \details Returns the value of the yTitle property.
     * \return yTitle (QString)
    */
    QString yTitle() const {
        return _yTitle;
    }

    /**
     * \fn setYTitle
     * \param newYTitle The new value of the yTitle property.
     * \brief Setter of the yTitle property.
     * \details Sets the value of the yTitle property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal yTitleChanged.
    */
    void setYTitle(QString newYTitle) {
        if(_yTitle.compare(newYTitle) == 0)
            return;
        _yTitle = newYTitle;
        emit yTitleChanged();
    }

    /**
     * \fn gridLineWidth
     * \brief Getter of the gridLineWidth property.
     * \details Returns the value of the gridLineWidth property.
     * \return gridLineWidth (qreal)
    */
    qreal gridLineWidth() const {
        return _gridLineWidth;
    }

    /**
     * \fn setGridLineWidth
     * \param newGridLineWidth The new value of the gridLineWidth property.
     * \brief Setter of the gridLineWidth property.
     * \details Sets the value of the gridLineWidth property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal gridLineWidthChanged.
    */
    void setGridLineWidth(qreal newGridLineWidth) {
        if(qFuzzyCompare(_gridLineWidth, newGridLineWidth))
            return;
        _gridLineWidth = newGridLineWidth;
        emit gridLineWidthChanged();
    }

    /**
     * \fn gridColor
     * \brief Getter of the gridColor property.
     * \details Returns the value of the gridColor property.
     * \return gridColor (QColor)
    */
    const QColor gridColor() const {
        return _gridColor;
    }

    /**
     * \fn setGridColor
     * \param newGridColor The new value of the gridColor property.
     * \brief Setter of the gridColor property.
     * \details Sets the value of the gridColor property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal gridColorChanged.
    */
    void setGridColor(const QColor &newGridColor) {
        if(_gridColor == newGridColor)
            return;
        _gridColor = newGridColor;
        emit gridColorChanged();
    }

    /**
     * \fn gridSize
     * \brief Getter of the gridSize property.
     * \details Returns the value of the gridSize property.
     * \return gridSize (QSizeF)
    */
    const QSizeF gridSize() const {
        return _gridSize;
    }

    /**
     * \fn setGridSize
     * \param newGridSize The new value of the gridSize property.
     * \brief Setter of the gridSize property.
     * \details Sets the value of the gridSize property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal gridSizeChanged.
     */
    void setGridSize(const QSizeF &newGridSize) {
        if(_gridSize == newGridSize)
            return;
        _gridSize = newGridSize;
        emit gridSizeChanged();
    }

    /**
     * \fn gridOffset
     * \brief Getter of the gridOffset property.
     * \details Returns the value of the gridOffset property.
     * \return gridOffset (QSizeF)
    */
    const QSizeF gridOffset() const {
        return _gridOffset;
    }

    /**
     * \fn setGridOffset
     * \param newGridOffset The new value of the gridOffset property.
     * \brief Setter of the gridOffset property.
     * \details Sets the value of the gridOffset property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the signal gridOffsetChanged.
    */
    void setGridOffset(const QSizeF &newGridOffset) {
        if(_gridOffset == newGridOffset)
            return;
        _gridOffset = newGridOffset;
        emit gridOffsetChanged();
    }

    /**
     * \fn scaleColor
     * \brief Getter of the scaleColor property.
     * \details Returns the value of the scaleColor property.
     * \return scaleColor (QColor)
    */
    const QColor scaleColor() const {
        return _scaleColor;
    }

    /**
     * \fn setScaleColor
     * \param newScaleColor The new value of the scaleColor property.
     * \brief Setter of the scaleColor property.
     * \details Sets the value of the scaleColor property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the scaleColorChanged.
    */
    void setScaleColor(const QColor &newScaleColor) {
        if(_scaleColor == newScaleColor)
            return;
        _scaleColor = newScaleColor;
        emit scaleColorChanged();   
    }

    /**
     * \fn backgroundColor
     * \brief Getter of the backgroundColor property.
     * \details Returns the value of the backgroundColor property.
     * \return backgroundColor (QColor)
    */
    const QColor backgroundColor() const {
        return _backgroundColor;
    }

    /**
     * \fn setBackgroundColor
     * \param newBackgroundColor The new value of the backgroundColor property.
     * \brief Setter of the backgroundColor property.
     * \details Sets the value of the backgroundColor property.
     * \n If the new value is equal to the old value, the function returns.
     * \n Otherwise, the function sets the new value and emits the backgroundColorChanged.
    */
    void setBackgroundColor(const QColor &newBackgroundColor) {
        if(_backgroundColor == newBackgroundColor)
            return;
        _backgroundColor = newBackgroundColor;
        emit backgroundColorChanged();
    }

    /**
     * \fn addPoint
     * \param lineIndex The index of the line that will receive the point.
     * \param point The point that will be added to the line.
     * \brief Adds a point to the line with the given index.
     * \details Adds a point to the line with the given index.
     * \n Add the point which is a QPointF to the line with the given index.
     * \n This function can be called from QML.
    */
    Q_INVOKABLE void addPoint(quint32 lineIndex, const QPointF& point);

    /**
     * \fn addPoint
     * \param lineIndex The index of the line that will receive the point.
     * \param x The x coordinate of the point that will be added to the line.
     * \param y The y coordinate of the point that will be added to the line.
     * \brief Adds a point to the line with the given index.
     * \details Adds a point to the line with the given index.
     * \n Creates and add the point which is a QPointF to the line with the given index.
     * \n This function can be called from QML.
    */
    Q_INVOKABLE void addPoint(quint32 lineIndex, qreal x, qreal y);

    /**
     * \fn addPoints
     * \param lineIndex The index of the line that will receive the points.
     * \param points The points that will be added to the line.
     * \brief Adds a list of points to the line with the given index.
     * \details For each point in the list, add the point which is a QPointF to the line with the given index.
     * \n Add the points which are a QList<QPointF> to the line with the given index.
     * \n This function can be called from QML.
    */
    Q_INVOKABLE void addPoints(quint32 lineIndex, const QList<QPointF>& points);

    /**
     * \fn clearData
     * \brief Clears all data from all lines.
     * \details Clears all data from all lines.
     * \n for each line, clear the data.
     * \n Sets the _redrawLines to true.
     * \n This function can be called from QML.
    */
    Q_INVOKABLE void clearData();

    /**
     * \fn clearLine
     * \param lineIndex The index of the line that will be cleared.
     * \brief Clears all data from the line with the given index.
     * \details Clears all data from the line with the given index.
     * \n Sets the _redrawLines to true.
     * \n This function can be called from QML.
    */
    Q_INVOKABLE void clearLine(quint32 lineIndex);

    /**
     * \fn lines
     * \brief Getter of the lines property.
     * \details Returns the value of the lines property.
     * \return lines (QQmlListProperty<IracemaLineSeries>)
    */
    QQmlListProperty<IracemaLineSeries> lines();

    /**
     * \fn dashedLines
     * \brief Getter of the dashedLines property.
     * \details Returns the value of the dashedLines property.
     * \return dashedLines (QQmlListProperty<IracemaDashedLine>)
    */
    QQmlListProperty<IracemaDashedLine> dashedLines();

    /**
     * \fn verticalScaleLabels
     * \brief Getter of the verticalScaleLabels property.
     * \details Returns the value of the verticalScaleLabels property.
     * \return verticalScaleLabels (QQmlListProperty<IracemaScaleLabel>)
    */
    QQmlListProperty<IracemaScaleLabel> verticalScaleLabels();

    /**
     * \fn horizontalScaleLabels
     * \brief Getter of the horizontalScaleLabels property.
     * \details Returns the value of the horizontalScaleLabels property.
     * \return horizontalScaleLabels (QQmlListProperty<IracemaScaleLabel>)
    */
    QQmlListProperty<IracemaScaleLabel> horizontalScaleLabels();

private:
    // QProperties

    /**
     * \fn _hasScales
     * \brief The hasScales property, used to define if the chart has scales.
    */
    bool _hasScales = false;

    /**
     * \fn _removeGridHorizontal
     * \brief The removeGridHorizontal property, used to define if the horizontal grid will be removed.
    */
    bool _removeGridHorizontal = false;

    /**
     * \fn _updateTime
     * \brief The updateTime property, used to define the time between updates.
    */
    unsigned int _updateTime = 50;

    /**
     * \fn _xScaleTop
     * \brief The xScaleTop property, used to define the top value of the x scale.
    */
    qreal _xScaleTop = 10000;

    /**
     * \fn _xScaleBottom
     * \brief The xScaleBottom property, used to define the bottom value of the x scale.
    */
    qreal _xScaleBottom = 0;

    /**
     * \fn _xTickCount
     * \brief The xTickCount property, used to define the number of ticks in the x scale.
    */
    qreal _xTickCount = 0;

    /**
     * \fn _yTickCount
     * \brief The yTickCount property, used to define the number of ticks in the y scale.
    */
    qreal _yTickCount = 0;

    /**
     * \fn _verticalScaleHeigth
     * \brief The verticalScaleHeigth property, used to define the height of the vertical scale.
    */
    qreal _verticalScaleHeigth = 50;

    /**
     * \fn _horizontalScaleWidth
     * \brief The horizontalScaleWidth property, used to define the width of the horizontal scale.
    */
    qreal _horizontalScaleWidth = 50;

    /**
     * \fn _plotAreaRigthPadding
     * \brief The plotAreaRigthPadding property, used to define the padding of the plot area.
    */
    qreal _plotAreaRigthPadding = _horizontalScaleWidth * 0.3;

    /**
     * \fn _xTitle
     * \brief The xTitle property, used to define the title of the x scale.
    */
    QString _xTitle = "";

    /**
     * \fn _yTitle
     * \brief The yTitle property, used to define the title of the y scale.
    */
    QString _yTitle = "";

    /**
     * \fn _gridLineWidth
     * \brief The gridLineWidth property, used to define the width of the grid lines.
    */
    qreal _gridLineWidth = 1;

    /**
     * \fn _gridColor
     * \brief The gridColor property, used to define the color of the grid lines.
    */
    QColor _gridColor = Qt::gray;

    /**
     * \fn _gridSize
     * \brief The gridSize property, used to define the size of the grid.
    */
    QSizeF _gridSize = QSizeF(1, 1);

    /**
     * \fn _gridOffset
     * \brief The gridOffset property, used to define the offset of the grid.
    */
    QSizeF _gridOffset = QSizeF(0, 0);

    /**
     * \fn _scaleColor
     * \brief The scaleColor property, used to define the color of the scales.
    */
    QColor _scaleColor = Qt::white;

    /**
     * \fn _backgroundColor
     * \brief The backgroundColor property, used to define the color of the background.
    */
    QColor _backgroundColor = Qt::white;


    // Lists

    /**
     * \fn _lines
     * \brief The lines property, used to define the list of lines.
    */
    QList<IracemaLineSeries*> _lines;

    /**
     * \fn _dashedLines
     * \brief The dashedLines property, used to define the list of dashed lines.
    */
    QList<IracemaDashedLine*> _dashedLines;

    /**
     * \fn _verticalScaleLabels
     * \brief The verticalScaleLabels property, used to define the list of vertical scale labels.
    */
    QList<IracemaScaleLabel*> _verticalScaleLabels;

    /**
     * \fn _horizontalScaleLabels
     * \brief The horizontalScaleLabels property, used to define the list of horizontal scale labels.
    */
    QList<IracemaScaleLabel*> _horizontalScaleLabels;

    // Other Members

    /**
     * \fn _isProcessingImage
     * \brief The isProcessingImage property, used to define if the image is being processed.
    */
    bool _isProcessingImage = false;
    

    /**
     * \fn _redrawGrid
     * \brief The redrawGrid property, used to define if the grid will be redrawn.
    */
    bool _redrawGrid = true;

    /**
     * \fn _redrawLines
     * \brief The redrawLines property, used to define if the lines will be redrawn.
    */
    bool _redrawLines = true;

    /**
     * \fn _redrawPeakLabels
     * \brief The redrawPeakLabels property, used to define if the peak labels will be redrawn.
    */
    bool _redrawPeakLabels = true;

    /**
     * \fn _updateTimerId
     * \brief The updateTimerId property, used to define the id of the update timer.
    */
    int _updateTimerId = -1;


    // Functions

    /**
     * \fn _appendLine
     * \param list The list of lines.
     * \param line The line that will be added to the list.
     * \brief Appends a line to the list of lines.
     * \details Appends a line to the list of lines.
     * \n Creates a view object.
     * \n Checks if the line is not null.
     * \n   -If the line is not null, append the line to the list
     * \n   -Connects the signal yScaleTopChanged to the slot _setRedrawAll.
     * \n   -Connects the signal yScaleBottomChanged to the slot _setRedrawAll.
     * \n   -Connects the signal graphDataChanged to the slot _redrawPeakLabels.
    */
    static void _appendLine(QQmlListProperty<IracemaLineSeries>* list, IracemaLineSeries* line);

    /**
     * \fn _appendDashedLine
     * \param list The list of dashed lines.
     * \param line The dashed line that will be added to the list.
     * \brief Appends a dashed line to the list of dashed lines.
     * \details Appends a dashed line to the list of dashed lines.
     * \n Creates a view object.
     * \n Checks if the dashed line is not null.
     * \n   -If the dashed line is not null, append the dashed line to the list
     * \n   -Set the parent  item of the line as the view object.
    */
    static void _appendDashedLine(QQmlListProperty<IracemaDashedLine>* list, IracemaDashedLine* label);

    /**
     * \fn _appendHorizontalScaleLabel
     * \param list The list of horizontal scale labels.
     * \param label The horizontal scale label that will be added to the list.
     * \brief Appends a horizontal scale label to the list of horizontal scale labels.
     * \details Appends a horizontal scale label to the list of horizontal scale labels.
     * \n Creates a view object.
     * \n Checks if the horizontal scale label is not null.
     * \n   -If the horizontal scale label is not null, append the horizontal scale label to the list
     * \n   -Set the parent  item of the label as the view object.
    */
    static void _appendHorizontalScaleLabel(QQmlListProperty<IracemaScaleLabel>* list, IracemaScaleLabel* label);


     /**
     * \fn _appendVerticalScaleLabel
     * \param list The list of vertical scale labels.
     * \param label The vertical scale label that will be added to the list.
     * \brief Appends a vertical scale label to the list of vertical scale labels.
     * \details Appends a vertical scale label to the list of vertical scale labels.
     * \n Creates a view object.
     * \n Checks if the vertical scale label is not null.
     * \n   -If the vertical scale label is not null, append the vertical scale label to the list
     * \n   -Set the parent  item of the label as the view object.
    */
    static void _appendVerticalScaleLabel(QQmlListProperty<IracemaScaleLabel>* list, IracemaScaleLabel* label);

    /**
     * \fn _setRedrawAll
     * \brief Sets all the _redraw properties to true.
     * \details Sets the _redrawGrid, _redrawLines and _redrawPeakLabels to true.
    */
    void _setRedrawAll();

    /**
     * \fn _drawGrid
     * \param mainNode The main node of the grid.
     * \brief Draws the grid.
     * \details If the grid widht or the grid height are lower or equal to 0, the function returns.
     * \n If the _removeGridHorizontal is true, the function draws the grid top and bottom.
     * \n Otherwise, the function draws the grid horizontally and vertically.
     * \n If the _hasScales is true, the function draws the titles.
     * \n Then goes through the lines and draws the lines.
    */
    void _drawGrid(QSGNode* mainNode);

    /**
     * \fn _drawTopAndBottom
     * \param mainNode The main node of the grid.
     * \brief Draws the top and bottom of the grid.
     * \details Creates the x, y, width and height variables.
     * \n Calls the _calculatePlotArea function, which is the area to be plotted.
     * \n Creates the topMaterial and bottomMaterial. and sets it collors
     * \n Creates the line on top and according to the x, y, width and height variables, and draws it.
     * \n Creates the line on bottom and according to the x, y, width and height variables, and draws it.
     * \n If the _hasScales is false, the function returns.
     * \n For eaach label in verticalScaleLabels, the function draws the label, with the x, y, width and height variables.
    */
    void _drawTopAndBottom(QSGNode* mainNode);

    
    void _drawGridHorizontal(QSGNode* mainNode);
    void _drawGridVertical(QSGNode* mainNode);
    void _drawTitles(QSGNode* mainNode);

    void _drawLines(QSGNode* lineSeriesNode, bool redrawAllData = false);
    void _drawLineSeries(QSGNode* mainNode, IracemaLineSeries* line, bool invertY = true, bool redrawAllData = false);
    
    void _drawPeaksLabels(bool redrawAll = false);

    void _convertAndDrawDashedLine(QSGNode* mainNode, IracemaDashedLine* line, bool invertY);
    void _drawDashedLine(QSGNode* mainNode, const QColor& lineColor, const qreal lineWidth, const QPointF &initialPoint, const QPointF &finalPoint, int percentage);

    void _drawScaleLabel(QSGNode* mainNode, qreal x, qreal y, QString label, QTextOption textOption = QTextOption(Qt::AlignCenter));
    void _drawOneLine(QSGNode* mainNode, QLineF line, qreal lineWidth, QSGFlatColorMaterial* lineMaterial);

    QRectF _calculatePlotArea();
    QRectF _calculatePlotArea(qreal &x, qreal &y, qreal &width, qreal &heigth);

    qreal _yScaleTop();
    qreal _yScaleBottom();

    qreal _truncate(qreal value, int numberOfDigits) const;
    qreal _convertValueToNewScale(qreal oldValue, qreal oldScaleBottom, qreal oldScaleTop, qreal newScaleBottom, qreal newScaleTop);
    void _deleteLists();

private slots:
    void _onGridSizeChanged();

protected:
    // QQuickItem interface
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    // QObject interface
    void timerEvent(QTimerEvent* event) override;

    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*) override;

    // Nodes pointers
    QSGNode* _backgroundLayer;
    QSGNode* _gridLayer;
    QSGNode* _peakLabelLayer;

signals:
    void hasScalesChanged();
    void removeGridHorizontalChanged();

    void updateTimeChanged();

    void xScaleTopChanged();
    void xScaleBottomChanged();
    void xTickCountChanged();
    void yTickCountChanged();
    void verticalScaleHeigthChanged();
    void horizontalScaleWidthChanged();
    void plotAreaRigthPaddingChanged();

    void xTitleChanged();
    void yTitleChanged();

    void gridLineWidthChanged();
    void gridColorChanged();
    void gridSizeChanged();
    void gridOffsetChanged();

    void scaleColorChanged();
    void backgroundColorChanged();

    void linesChanged();
    void dashedLinesChanged();
    void verticalScaleLabelsChanged();
    void horizontalScaleLabelsChanged();
};

#endif // IRACEMALINESERIESVIEW_H
