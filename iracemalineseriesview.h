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

    /**
     * \fn _drawGridHorizontal
     * \param mainNode The main node of the grid.
     * \brief Draws the horizontal grid.
     * \details Creates the x, y, width and height variables.
     * \n Calls the _calculatePlotArea function, which is the area to be plotted.
     * \n Sets the currentY variable as the y variable.
     * \n Sets the limitY variable as the y variable plus the height variable.
     * \n Sets the grid height as zero
     * \n Gets the the label, and cretes the labelValueInterval variable.
     * \n Creates the variables drawedGridLines and GRID_LINES_TO_DRAW, used to solve problems of rouding labelValueInterval by odd tickCount.
     * \n Then checks if there is a _yTickCount, then:
     * \n  -set the gridHeight as the height variable divided by the _yTickCount.
     * \n  -Set the labelValueInterval as the labelValue divided by the _yTickCount.
     * \n Else, then:
     * \n  -Set the gridHeigth as the height variable.
     * \n  -Set the labelValueInterval as the labelValue divided by the height variable, divided by the gridHeigth.
     * \n Then, while the currentY is lower than the limitY, or the drawedGridLines is lower than the GRID_LINES_TO_DRAW, then:
     * \n  -Checks if the current Y is greater than the limit value, if it is:
     * \n    --Sets the currentY as the limitY, and the labelValue as _yScaleBottom.
     * \n  -Creates a new material and sets it color as the grid color
     * \n  -Creates a new line and draws it, then add it to the counter of drawedGridLines.
     * \n  -If it has scales then:
     * \n    -- Sets the number of digits as 2.
     * \n    -- Creates a truncValue variable.
     * \n    -- Finds the number of digits where they became equal
     * \n    -- Finds the number of digits where they became different
     * \n    -- Truncate them and draw the scale label.
     * \n  -Increments the currentY by the gridHeight.
     * \n  -Decrements the labelValue by the labelValueInterval.
     * \n For each label in the _verticalScaleLabels, then draws the scale label with new values of Y.
    */
    void _drawGridHorizontal(QSGNode* mainNode);

    /**
     * \fn _drawGridVertical
     * \param mainNode The main node of the grid.
     * \brief Draws the vertical grid.
     * \details Creates the x, y, width and height variables.
     * \n Calls the _calculatePlotArea function, which is the area to be plotted.
     * \n Sets the currentX variable as the x variable.
     * \n Sets the limitX variable as the x variable plus the width variable.
     * \n Sets the grid width as zero
     * \n Gets the the label, and cretes the labelValueInterval variable.
     * \n Creates the variables drawedGridLines and GRID_LINES_TO_DRAW, used to solve problems of rouding labelValueInterval by odd tickCount.
     * \n Then checks if there is a _xTickCount, then:
     * \n  -set the gridWidth as the width variable divided by the _xTickCount.
     * \n  -Set the labelValueInterval as the labelValue divided by the _xTickCount.
     * \n Else, then:
     * \n  -Set the gridWidth as the width variable.
     * \n  -Set the labelValueInterval as the labelValue divided by the width variable, divided by the gridWidth.
     * \n Then, while the currentX is lower than the limitX, or the drawedGridLines is lower than the GRID_LINES_TO_DRAW, then:
     * \n  -Checks if the current X is greater than the limit value, if it is:
     * \n    --Sets the currentX as the limitX, and the labelValue as _xScaleBottom.
     * \n  -Creates a new material and sets it color as the grid color
     * \n  -Creates a new line and draws it, then add it to the counter of drawedGridLines.
     * \n  -If it has scales then:
     * \n    -- Sets the number of digits as 2.
     * \n    -- Creates a truncValue variable
     * \n    -- Finds the number of digits where they became equal
     * \n    -- Finds the number of digits where they became different
     * \n    -- Truncate them and draw the scale label.
     * \n  -Increments the currentX by the gridWidth.
     * \n  -Icrements the labelValue by the labelValueInterval.
     * \n For each label in the _horizontalScaleLabels, then draws the scale label with new values of X.
     * \n  -Center the label component.
    */
    void _drawGridVertical(QSGNode* mainNode);

    /**
     * \fn _drawTitles
     * \param mainNode The main node of the grid.
     * \brief Draws the titles.
     * \details Creates the widht and height variables and set them as 300 and 20 respectively.
     * \n Creates the plot area and sets the x and y mid points.
     * \n Instantiates the font and pen .
     * \n Instantiates the pimaxY and pimaxX objects and set them as transparents.
     * \n Sets the fonts and pens of the painterX and painterY objects.
     * \n Creates a rectangle X and Y objects, draws text of painterX, and also set the translation, rotation and text of PainterY
     * \n Creates texture for the X and Y objects.
     * \n Creates a child node for the X and Y objects, setting it's texture, rectangle, markDirty, and flags, for each of them, and also append them as child node of the main Node.
     * 
    */
    void _drawTitles(QSGNode* mainNode);

    /**
     * \fn _drawLines
     * \param lineSeriesNode The main node of the lines.
     * \param redrawAllData The boolean that defines if all data will be redrawn.
     * \brief Draws the lines.
     * \details For each lineSeries in lines:
     * \n - Creates a line series node, sets it flags if it it owned by a parent or it has its own geometry.
     * \n - Also Draws the çline Series and append the lineSeriesNode as a child node of the main node.
    */
    void _drawLines(QSGNode* lineSeriesNode, bool redrawAllData = false);

    /**
     * \fn _drawLineSeries
     * \param mainNode The main node of the lines.
     * \param lineSeries The line that will be drawn.
     * \param invertY The boolean that defines if the Y axis will be inverted.
     * \param redrawAllData The boolean that defines if all data will be redrawn.
     * \brief Draws the line series.
     * \details Creates the x, y, width and height variables.
     * \n Calls the _calculatePlotArea function, which is the area to be plotted.
     * \n Creates a dataToDraw variable,which is a list of points.
     * \n If the redrawAllData is true, then:
     * \n - Apply data buffer to LineSeries.
     * \n - Sets dataToDraw as the data of the lineSeries.
     * \n Else:
     * \n - Sets dataToDraw as the data buffer of the lineSeries.
     * \n - Apply data buffer to LineSeries.
     * \n For each line in dataToDraw, then:
     * \n - Creates a new X1,X2,Y1 and Y2 variables.
     * \n - Clip the values to view boundaries.
     * \n - Checks if the Y is inverted, if it is, then invert the Y1 and Y2.
     * \n - Else if the Y is not inverted, then just increment the Y1 and Y2 by the y variable.
     * \n - Creates the points P1 and P2 and creates a line with them.
     * \n - Creates a new material and sets it color as the line color.
     * \n - Draws the line.
     **/ 
    void _drawLineSeries(QSGNode* mainNode, IracemaLineSeries* line, bool invertY = true, bool redrawAllData = false);
    
    /**
     * \fn _drawPeaksLabels
     * \param redrawAll The boolean that defines if all data will be redrawn.
     * \brief Draws the peak labels.
     * \details Creates the reclangle plot area, the y scale top and bottom variables, and the labels to draw.
     * \n For each line series in lines, then:
     * \n - If redrawAll is true, then:
     * \n  --Apply point labels buffer to LineSeries.
     * \n  --Sets the labelsToDraw as the point labels of the line series.
     * \n -Else:
     * \n  --Sets the labelsToDraw as the point labels buffer of the line series.
     * \n  --Apply point labels buffer to LineSeries.
     * \n - For each point label in labels to draw, then:
     * \n  --Creates a label variable.
     * \n  --Sets the flag of the label according if it is owned by a parent or it has its own geometry.
     * \n  --Creates newX and newY variables.
     * \n  --Draws the scale label.
     * \n  -- Append the child node of the peak label layer, as the label.
    */
    void _drawPeaksLabels(bool redrawAll = false);

    /**
     * \fn _drawPeakLabel
     * \param mainNode The main node of the peak label.
     * \param line The line that will be drawn.
     * \param invertY The boolean that defines if the Y axis will be inverted.
     * \brief Draws the peak label.
     * \details Calculates the plot area.
     * \n Creates variables for the inital points x and y,and the final points x and y.
     * \n Clips the values to view boundaries.
     * \n Checks if the Y is inverted, if it is, then invert the Y1 and Y2.
     * \n If it is not inverted, then just increment the Y1 and Y2 by the y variable.
     * \n Draws the dashed line.
     **/
    void _convertAndDrawDashedLine(QSGNode* mainNode, IracemaDashedLine* line, bool invertY);

    /**
     * \fn _drawDashedLine
     * \param mainNode The main node of the dashed line.
     * \param lineColor The color of the dashed line.
     * \param lineWidth The width of the dashed line.
     * \param initialPoint The initial point of the dashed line.
     * \param finalPoint The final point of the dashed line.
     * \param percentage The percentage of the dashed line.
     * \brief Draws the dashed line.
     * \details Creates variables for the x and y dot values, and for the current X and Y which are the initial points.
     * \n For each point in 100 divided by the double of the percentage, then:
     * \n  - Createss a new line material and sets it color as the line color.
     * \n  - Creates a new line.
     * \n  - Draws the line with the main node, new line, line width and line material.
     * \n  - Increments the current X by the doubled value of x dot.
     * \n  - Decrements the current Y by the doubled value of y dot.
    */
    void _drawDashedLine(QSGNode* mainNode, const QColor& lineColor, const qreal lineWidth, const QPointF &initialPoint, const QPointF &finalPoint, int percentage);

    /**
     * \fn _drawScaleLabel
     * \param mainNode The main node of the scale label.
     * \param x The x coordinate of the scale label.
     * \param y The y coordinate of the scale label.
     * \param label The label that will be drawn.
     * \param textOption The text option of the scale label.
     * \brief Draws the scale label.
     * \details Creates a transparent pixmap, and a painter with it.
     * \n Creates a font and sets it as the painter font.
     * \n Creates a pen and sets it as the painter pen.
     * \n Creates a rectangle and draws the text of the painter with the rectangle and the text option.
     * \n Creates a texture from the pixmap.
     * \n Creates a child node, setting it's texture, rectangle, markDirty, and flags, and also append it as child node of the main Node.
    */
    void _drawScaleLabel(QSGNode* mainNode, qreal x, qreal y, QString label, QTextOption textOption = QTextOption(Qt::AlignCenter));

    /**
     * \fn _drawOneLine
     * \param mainNode The main node of the line.
     * \param line The line that will be drawn.
     * \param lineWidth The width of the line.
     * \param lineMaterial The material of the line.
     * \brief Draws the line.
     * \details Creates a geometry object, and sets its line width and drawing mode.
     * \n Creates a child node, setting it's geometry as the geometry object, sets the material as the line material, and also sets its flags according if it is owned by a parent or it has its own geometry, or if it owns material.
     * \n Get the verticies of the geometry object as a 2D point.
     * \n Sets the two vertices as the line points (x1,y1) and (x2,y2).
     * \n Append the child node of the main node, as the child node.
    */
    void _drawOneLine(QSGNode* mainNode, QLineF line, qreal lineWidth, QSGFlatColorMaterial* lineMaterial);

    /**
     * \fn _calculatePlotArea
     * \brief Calculates the plot area.
     * \details Creates the x, y, width and height variables.
     * \n Returns the plot area.
    */
    QRectF _calculatePlotArea();

    /**
     * \fn _calculatePlotArea
     * \param x The x coordinate of the plot area.
     * \param y The y coordinate of the plot area.
     * \param width The width of the plot area.
     * \param heigth The height of the plot area.
     * \brief Calculates the plot area.
     * \details Checks if the _hasScales is true, if it is, then:
     * \n - Sets x as the _horizontalScaleWidth.
     * \n - Sets y as 25% of the _verticalScaleHeigth.
     * \n - Sets the width as the width variable minus the _horizontalScaleWidth minus the _plotAreaRigthPadding.
     * \n - Sets the height as the height variable minus _verticalScaleHeigth times 1.25.
     * \n Else, then:
     * \n - Sets x and y as 0.
     * \n - Sets the width as the width variable.
     * \n - Sets the height as the height variable.
     * \n Returns the plot area, which is a QRectF oject.
     * \return plotArea (QRectF)
    */
    QRectF _calculatePlotArea(qreal &x, qreal &y, qreal &width, qreal &heigth);

    /**
     * \fn _yScaleTop
     * \brief Getter of the yScaleTop property.
     * \details Creates a maxScaleTop variable as 0.
     * \n For each line in lines, then:
     * \n -Checks if the line yScaleTop is greater than the maxScaleTop, if it is, then:
     * \n  --Sets the maxScaleTop as the line yScaleTop.
     * \n Returns the maxScaleTop.
    */
    qreal _yScaleTop();

    /**
     * \fn _yScaleBottom
     * \brief Getter of the yScaleBottom property.
     * \details Creates a minScaleBottom variable as 0.
     * \n For each line in lines, then:
     * \n -Checks if the line yScaleBottom is lower than the minScaleBottom, if it is, then:
     * \n  --Sets the minScaleBottom as the line yScaleBottom.
     * \n Returns the minScaleBottom.
    */
    qreal _yScaleBottom();

    /**
     * \fn _truncate
     * \param value The value that will be truncated.
     * \param numberOfDigits The number of digits that will be truncated.
     * \brief Truncates the value.
     * \details Creates a truncValue variable as 0.
     * \n Creates the number of digits where they became equal and different. It will be 10 to the power of the number of digits.
     * \n Truncates the value, it will be the value multiplied by the number of digits.
     * \n Returns the truncValue divided by the number of digits.
     * \n 
     * 
    */
    qreal _truncate(qreal value, int numberOfDigits) const;

    /**
     * \fn _convertValueToNewScale
     * \param oldValue The old value that will be converted.
     * \param oldScaleBottom The old bottom value of the scale.
     * \param oldScaleTop The old top value of the scale.
     * \param newScaleBottom The new bottom value of the scale.
     * \param newScaleTop The new top value of the scale.
     * \brief Converts the value to the new scale.
     * \details Creates a newValue variable as the old value minus the old scale bottom.
     * \n Multiplies the new value by the new scale top minus the new scale bottom.
     * \n Divides the new value by the old scale top minus the old scale bottom.
     * \n Increments the new value by the new scale bottom.
     * \n Returns the newValue.
     * \return newValue (qreal)
    */
    qreal _convertValueToNewScale(qreal oldValue, qreal oldScaleBottom, qreal oldScaleTop, qreal newScaleBottom, qreal newScaleTop);

    /**
     * \fn _deleteLists
     * \brief Deletes all lists.
     * \details Go through each list and deletes all elements of lists and calls the clear method of each list.
     * \n Deletes the list of lines, dashed lines, vertical scale labels and horizontal scale labels.
    */
    void _deleteLists();

private slots:
    /**
     * \fn _onGridSizeChanged
     * \brief Slot that is called when the grid size is changed.
     * \details Sets the _redrawGrid to true.
    */
    void _onGridSizeChanged();

protected:
    // QQuickItem interface

    /**
     * \fn geometryChanged
     * \param newGeometry The new geometry of the item.
     * \param oldGeometry The old geometry of the item.
     * \brief Slot that is called when the geometry is changed.
     * \details Sets the _redrawGrid to true.
     * \n If the _updateTimerId is equal to -1, then:
     * \n -Sets the _updateTimerId as the startTimer of the _updateTime.
    */
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry) override;

    // QObject interface

    /**
     * \fn timerEvent
     * \param event The timer event.
     * \brief Slot that is called when the timer event is called.
     * \details If the event timer id is equal to the _updateTimerId, and the _isProcessingImage is false, then:
     * \n Calls the update method from the QQuickItem.
    */
    void timerEvent(QTimerEvent* event) override;

    /**
     * \fn updatePaintNode
     * \param oldNode The old node.
     * \param updatePaintNodeData The update paint node data.
     * \brief Slot that is called when the paint node is updated.
     * \details If there is no old node, then:
     * \n -Creates a new node.
     * \n -Sets the _backgroundLayer to the new node.
     * \n -Sets the _gridLayer as to new node.
     * \n -Sets the _peakLabelLayer as to new node.
     * \n If the _redrawGrid is true, then:
     * \n - Remove the child nodes of the old node.
     * \n - Deletes the grid layer.
     * \n - Creates a new grid layer.
     * \n - Draws the grid.
     * \n - Draws the lines 
     * \n - Sets the _redrawGrid as false.
     * \n - Sets the redraw Peak Labels as true.
     * \n - Insert the grid layer as a child node of the old node, and also insert the background layer as a child node of the old node.
     * \n Else:
     * \n - Draws the lines with the grid layer.
     * \n If the _redrawPeakLabels is true, then:
     * \n - Removes the child nodes of the old node.
     * \n - Deletes the peak label layer.
     * \n - Creates a new peak label layer.
     * \n - Draws the peak labels.
     * \n - Sets the _redrawPeakLabels as false.
     * \n - Inserts the peak label layer as a child node of the old node.
     * \n Else:
     * \n - Draws the peak labels with the peak label layer.
     * \n Returns the old node.
     * \return oldNode (QSGNode*)
    */
    QSGNode* updatePaintNode(QSGNode* oldNode, UpdatePaintNodeData*) override;

    // Nodes pointers

    /**
     * \fn _backgroundLayer
     * \brief The background layer node.
    */
    QSGNode* _backgroundLayer;

    /**
     * \fn _gridLayer
     * \brief The grid layer node.
    */
    QSGNode* _gridLayer;

    /**
     * \fn _peakLabelLayer
     * \brief The peak label layer node.
    */
    QSGNode* _peakLabelLayer;

signals:

    /**
     * \fn hasScalesChanged
     * \brief Signal that is emitted when the hasScales property is changed.
    */
    void hasScalesChanged();

    /**
     * \fn removeGridHorizontalChanged
     * \brief Signal that is emitted when the removeGridHorizontal property is changed.
    */
    void removeGridHorizontalChanged();


    /**
     * \fn updateTimeChanged
     * \brief Signal that is emitted when the updateTime property is changed.
    */
    void updateTimeChanged();


    /**
     * \fn xScaleTopChanged
     * \brief Signal that is emitted when the xScaleTop property is changed.
    */
    void xScaleTopChanged();

    /**
     * \fn xScaleBottomChanged
     * \brief Signal that is emitted when the xScaleBottom property is changed.
    */
    void xScaleBottomChanged();

    /**
     * \fn xTickCountChanged
     * \brief Signal that is emitted when the xTickCount property is changed.
    */
    void xTickCountChanged();

    /**
     * \fn yTickCountChanged
     * \brief Signal that is emitted when the yTickCount property is changed.
    */
    void yTickCountChanged();

    /**
     * \fn verticalScaleHeigthChanged
     * \brief Signal that is emitted when the verticalScaleHeigth property is changed.
    */
    void verticalScaleHeigthChanged();

    /**
     * \fn horizontalScaleWidthChanged
     * \brief Signal that is emitted when the horizontalScaleWidth property is changed.
    */
    void horizontalScaleWidthChanged();

    /**
     * \fn plotAreaRigthPaddingChanged
     * \brief Signal that is emitted when the plotAreaRigthPadding property is changed.
    */
    void plotAreaRigthPaddingChanged();


    /**
     * \fn xTitleChanged
     * \brief Signal that is emitted when the xTitle property is changed.
    */
    void xTitleChanged();

    /**
     * \fn yTitleChanged
     * \brief Signal that is emitted when the yTitle property is changed.
    */
    void yTitleChanged();


    /**
     * \fn gridLineWidthChanged
     * \brief Signal that is emitted when the gridLineWidth property is changed.
    */
    void gridLineWidthChanged();

    /**
     * \fn gridColorChanged
     * \brief Signal that is emitted when the gridColor property is changed.
    */
    void gridColorChanged();

    /**
     * \fn gridSizeChanged
     * \brief Signal that is emitted when the gridSize property is changed.
    */
    void gridSizeChanged();

    /**
     * \fn gridOffsetChanged
     * \brief Signal that is emitted when the gridOffset property is changed.
    */
    void gridOffsetChanged();

    /**
     * \fn scaleColorChanged
     * \brief Signal that is emitted when the scaleColor property is changed.
    */
    void scaleColorChanged();

    /**
     * \fn backgroundColorChanged
     * \brief Signal that is emitted when the backgroundColor property is changed.
    */
    void backgroundColorChanged();


    /**
     * \fn linesChanged
     * \brief Signal that is emitted when the lines property is changed.
    */
    void linesChanged();

    /**
     * \fn dashedLinesChanged
     * \brief Signal that is emitted when the dashedLines property is changed.
    */
    void dashedLinesChanged();

    /**
     * \fn verticalScaleLabelsChanged
     * \brief Signal that is emitted when the verticalScaleLabels property is changed.
    */
    void verticalScaleLabelsChanged();

    /**
     * \fn horizontalScaleLabelsChanged
     * \brief Signal that is emitted when the horizontalScaleLabels property is changed.
    */
    void horizontalScaleLabelsChanged();
};

#endif // IRACEMALINESERIESVIEW_H
