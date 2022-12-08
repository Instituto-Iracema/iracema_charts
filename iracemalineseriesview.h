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
    explicit IracemaLineSeriesView(QQuickItem* parent = nullptr);
    ~IracemaLineSeriesView();

    // Properties Getters and Setters

    bool hasScales() const {
        return _hasScales;
    }
    void setHasScales(bool newHasScales) {
        if(_hasScales == newHasScales)
            return;
        _hasScales = newHasScales;
        emit hasScalesChanged();
    }

    bool removeGridHorizontal() const {
        return _removeGridHorizontal;
    }
    void setRemoveGridHorizontal(bool newRemoveGridHorizontal) {
        if(_removeGridHorizontal == newRemoveGridHorizontal)
            return;
        _removeGridHorizontal = newRemoveGridHorizontal;
        emit removeGridHorizontalChanged();
    }

    unsigned int updateTime() const {
        return _updateTime;
    }
    void setUpdateTime(unsigned int newUpdateTime) {
        if(_updateTime == newUpdateTime)
            return;
        _updateTime = newUpdateTime;
        emit updateTimeChanged();        
    }

    qreal xScaleTop() const {
        return _xScaleTop;
    }
    void setXScaleTop(qreal newXScaleTop) {
        if(qFuzzyCompare(_xScaleTop, newXScaleTop))
            return;
        _xScaleTop = newXScaleTop;
        emit xScaleTopChanged();
        _setRedrawAll();
    }

    qreal xScaleBottom() const {
        return _xScaleBottom;
    }
    void setXScaleBottom(qreal newXScaleBottom) {
        if(qFuzzyCompare(_xScaleBottom, newXScaleBottom))
            return;
        _xScaleBottom = newXScaleBottom;
        emit xScaleBottomChanged();
        _setRedrawAll();
    }

    qreal xTickCount() const {
        return _xTickCount;
    }
    void setXTickCount(qreal newXTickCount) {
        if(qFuzzyCompare(_xTickCount, newXTickCount))
            return;
        _xTickCount = newXTickCount;
        emit xTickCountChanged();
    }

    qreal yTickCount() const {
        return _yTickCount;
    }
    void setYTickCount(qreal newYTickCount) {
        if(qFuzzyCompare(_yTickCount, newYTickCount))
            return;
        _yTickCount = newYTickCount;
        emit yTickCountChanged();
    }

    qreal verticalScaleHeigth() const {
        return _verticalScaleHeigth;
    }
    void setVerticalScaleHeigth(qreal newVerticalScaleHeigth) {
        if(qFuzzyCompare(_verticalScaleHeigth, newVerticalScaleHeigth))
            return;
        _verticalScaleHeigth = newVerticalScaleHeigth;
        emit verticalScaleHeigthChanged();
    }

    qreal horizontalScaleWidth() const {
        return _horizontalScaleWidth;
    }
    void setHorizontalScaleWidth(qreal newHorizontalScaleWidth) {
        if(qFuzzyCompare(_horizontalScaleWidth, newHorizontalScaleWidth))
            return;
        _horizontalScaleWidth = newHorizontalScaleWidth;
        emit horizontalScaleWidthChanged();
    }

    qreal plotAreaRigthPadding() const {
        return _plotAreaRigthPadding;
    }
    void setPlotAreaRigthPadding(qreal newPlotAreaRigthPadding) {
        if(qFuzzyCompare(_plotAreaRigthPadding, newPlotAreaRigthPadding))
            return;
        _plotAreaRigthPadding = newPlotAreaRigthPadding;
        emit plotAreaRigthPaddingChanged();
    }

    qreal gridLineWidth() const {
        return _gridLineWidth;
    }
    void setGridLineWidth(qreal newGridLineWidth) {
        if(qFuzzyCompare(_gridLineWidth, newGridLineWidth))
            return;
        _gridLineWidth = newGridLineWidth;
        emit gridLineWidthChanged();
    }

    const QColor gridColor() const {
        return _gridColor;
    }
    void setGridColor(const QColor &newGridColor) {
        if(_gridColor == newGridColor)
            return;
        _gridColor = newGridColor;
        emit gridColorChanged();
    }

    const QSizeF gridSize() const {
        return _gridSize;
    }
    void setGridSize(const QSizeF &newGridSize) {
        if(_gridSize == newGridSize)
            return;
        _gridSize = newGridSize;
        emit gridSizeChanged();
    }

    const QSizeF gridOffset() const {
        return _gridOffset;
    }
    void setGridOffset(const QSizeF &newGridOffset) {
        if(_gridOffset == newGridOffset)
            return;
        _gridOffset = newGridOffset;
        emit gridOffsetChanged();
    }

    const QColor scaleColor() const {
        return _scaleColor;
    }
    void setScaleColor(const QColor &newScaleColor) {
        if(_scaleColor == newScaleColor)
            return;
        _scaleColor = newScaleColor;
        emit scaleColorChanged();   
    }

    const QColor backgroundColor() const {
        return _backgroundColor;
    }
    void setBackgroundColor(const QColor &newBackgroundColor) {
        if(_backgroundColor == newBackgroundColor)
            return;
        _backgroundColor = newBackgroundColor;
        emit backgroundColorChanged();
    }

    Q_INVOKABLE void addPoint(quint32 lineIndex, const QPointF& point);
    Q_INVOKABLE void addPoint(quint32 lineIndex, qreal x, qreal y);
    Q_INVOKABLE void addPoints(quint32 lineIndex, const QList<QPointF>& points);

    Q_INVOKABLE void clearData();
    Q_INVOKABLE void clearLine(quint32 lineIndex);

    QQmlListProperty<IracemaLineSeries> lines();
    QQmlListProperty<IracemaDashedLine> dashedLines();
    QQmlListProperty<IracemaScaleLabel> verticalScaleLabels();
    QQmlListProperty<IracemaScaleLabel> horizontalScaleLabels();

private:
    // QProperties

    bool _hasScales = false;
    bool _removeGridHorizontal = false;

    unsigned int _updateTime = 50;

    qreal _xScaleTop = 10000;
    qreal _xScaleBottom = 0;
    qreal _xTickCount = 0;
    qreal _yTickCount = 0;
    qreal _verticalScaleHeigth = 40;
    qreal _horizontalScaleWidth = 50;
    qreal _plotAreaRigthPadding = _horizontalScaleWidth * 0.3;

    qreal _gridLineWidth = 1;
    QColor _gridColor = Qt::gray;
    QSizeF _gridSize = QSizeF(1, 1);
    QSizeF _gridOffset = QSizeF(0, 0);

    QColor _scaleColor = Qt::white;
    QColor _backgroundColor = Qt::white;

    QList<IracemaLineSeries*> _lines;
    QList<IracemaDashedLine*> _dashedLines;
    QList<IracemaScaleLabel*> _verticalScaleLabels;
    QList<IracemaScaleLabel*> _horizontalScaleLabels;

    // Other Members
    bool _isProcessingImage = false;

    bool _redrawGrid = true;
    bool _redrawLines = true;
    bool _redrawPeakLabels = true;

    int _updateTimerId = -1;

    static void _appendLine(QQmlListProperty<IracemaLineSeries>* list, IracemaLineSeries* line);
    static void _appendDashedLine(QQmlListProperty<IracemaDashedLine>* list, IracemaDashedLine* label);
    static void _appendHorizontalScaleLabel(QQmlListProperty<IracemaScaleLabel>* list, IracemaScaleLabel* label);
    static void _appendVerticalScaleLabel(QQmlListProperty<IracemaScaleLabel>* list, IracemaScaleLabel* label);

    void _setRedrawAll();

    void _drawGrid(QSGNode* mainNode);
    void _drawTopAndBottom(QSGNode* mainNode);
    void _drawGridHorizontal(QSGNode* mainNode);
    void _drawGridVertical(QSGNode* mainNode);

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
