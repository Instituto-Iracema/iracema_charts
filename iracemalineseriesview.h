#ifndef IRACEMALINESERIESVIEW_H
#define IRACEMALINESERIESVIEW_H

#include "iracemalineseries.h"
#include "iracemascalelabel.h"

#include <QPainter>
#include <QQuickItem>
#include <QSGFlatColorMaterial>
#include <QSizeF>
#include <QBrush>
#include <math.h>
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

class IracemaLineSeriesView : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(IracemaLineSeriesView)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QSizeF gridSize READ gridSize WRITE setGridSize NOTIFY gridSizeChanged)
    Q_PROPERTY(QSizeF gridOffset READ gridOffset WRITE setGridOffset NOTIFY gridOffsetChanged)
    Q_PROPERTY(qreal xTickCount READ xTickCount WRITE setXTickCount NOTIFY xTickCountChanged)
    Q_PROPERTY(qreal yTickCount READ yTickCount WRITE setYTickCount NOTIFY yTickCountChanged)
    Q_PROPERTY(unsigned int updateTime READ updateTime WRITE setUpdateTime NOTIFY updateTimeChanged)
    Q_PROPERTY(qreal gridLineWidth READ gridLineWidth WRITE setGridLineWidth NOTIFY gridLineWidthChanged)
    Q_PROPERTY(qreal xScaleBottom READ xScaleBottom WRITE setXScaleBottom NOTIFY xScaleBottomChanged)
    Q_PROPERTY(qreal xScaleTop READ xScaleTop WRITE setXScaleTop NOTIFY xScaleTopChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(QQmlListProperty<IracemaLineSeries> lines READ lines NOTIFY linesChanged)
    Q_PROPERTY(QQmlListProperty<IracemaScaleLabel> verticalScaleLabels READ verticalScaleLabels NOTIFY verticalScaleLabelsChanged)
    Q_PROPERTY(QQmlListProperty<IracemaScaleLabel> horizontalScaleLabels READ horizontalScaleLabels NOTIFY horizontalScaleLabelsChanged)
    Q_PROPERTY(bool hasScales READ hasScales WRITE setHasScales NOTIFY hasScalesChanged)
    Q_PROPERTY(qreal horizontalScaleWidth READ HorizontalScaleWidth WRITE setHorizontalScaleWidth NOTIFY HorizontalScaleWidthChanged)
    Q_PROPERTY(qreal verticalScaleHeigth READ verticalScaleHeigth WRITE setVerticalScaleHeigth NOTIFY verticalScaleHeigthChanged)
    Q_PROPERTY(qreal plotAreaRigthPadding READ plotAreaRigthPadding WRITE setPlotAreaRigthPadding NOTIFY plotAreaRigthPaddingChanged)
    Q_PROPERTY(QColor scaleColor READ scaleColor WRITE setScaleColor NOTIFY scaleColorChanged)
    QML_NAMED_ELEMENT(IracemaChart)

private:
    // QProperties
    QColor _scaleColor = Qt::white;

    QColor _backgroundColor = Qt::white;
    /**
     * @brief Color of the grid lines
     */
    QColor _gridColor = Qt::gray;
    /**
     * @brief Size of the grid on X and Y axis in pixels
     */
    QSizeF _gridSize = QSizeF(1, 1);
    /**
     * @brief Offset of the grid, from left and top in pixels
     */
    QSizeF _gridOffset = QSizeF(0, 0);
    /**
     * @brief Width of the line of the grid
     */
    qreal _gridLineWidth = 1;

    qreal _xScaleBottom = 0;
    qreal _xScaleTop = 10000;
    qreal _maxPixmapSize = 1000;

    unsigned int _updateTime = 50;
    unsigned int _resizeTime = 500;

    QList<IracemaLineSeries *> _lines;
    QList<IracemaScaleLabel *> _verticalScaleLabels;
    QList<IracemaScaleLabel *> _horizontalScaleLabels;
    QQmlListProperty<IracemaLineSeries> lines();
    QQmlListProperty<IracemaScaleLabel> verticalScaleLabels();
    QQmlListProperty<IracemaScaleLabel> horizontalScaleLabels();


    QSGFlatColorMaterial *_gridMaterial;
    bool _redrawGrid = true;
    bool _redrawLines = true;
    bool _redrawPeakLabels = true;

    int _updateTimerId = -1;

    bool _isResizing = false;

    bool _isProcessingImage = false;

    bool _hasScales = false;

    qreal _xTickCount = 0;
    qreal _yTickCount = 0;

    qreal _horizontalScaleWidth = 50;
    qreal _verticalScaleHeigth = 40;
    qreal _plotAreaRigthPadding = _horizontalScaleWidth * 0.3;

    void _setRedrawAll();
    qreal truncate(qreal value, int numberOfDigits) const;
    void _drawGridHorizontal(QSGNode *mainNode);
    void _drawGridVertical(QSGNode *mainNode);
    void _drawGrid(QSGNode *mainNode);
    void _drawScaleLabel(QSGNode *mainNode, qreal x, qreal y, QString label, QTextOption textOption = QTextOption(Qt::AlignCenter));
    void _drawOneLine(QSGNode *mainNode, QLineF line, qreal lineWidth, QSGFlatColorMaterial *lineMaterial);
    void _drawLineSeries(QSGNode *mainNode, IracemaLineSeries *line, bool invertY = true, bool redrawAllData = false);
    void _drawLines(QSGNode *lineSeriesNode, bool redrawAllData = false);
    void _drawPeaksLabels(bool redrawAll = false);
    qreal _convertValueToNewScale(qreal oldValue, qreal oldScaleBottom, qreal oldScaleTop, qreal newScaleBottom, qreal newScaleTop);
    QRectF _calculatePlotArea(qreal &x, qreal &y, qreal &width, qreal &heigth);
    QRectF _calculatePlotArea();

    qreal _yScaleTop();
    qreal _yScaleBottom();

    static void appendLine(QQmlListProperty<IracemaLineSeries> *list, IracemaLineSeries *line);
    static void appendHorizontalScaleLabel(QQmlListProperty<IracemaScaleLabel> *list, IracemaScaleLabel *label);
    static void appendVerticalScaleLabel(QQmlListProperty<IracemaScaleLabel> *list, IracemaScaleLabel *label);

public:
    explicit IracemaLineSeriesView(QQuickItem *parent = nullptr);

    Q_INVOKABLE void addPoint(quint32 lineIndex, QPointF point);
    Q_INVOKABLE void addPoint(quint32 lineIndex, qreal x, qreal y);
    Q_INVOKABLE void addPoints(quint32 lineIndex, QList<QPointF> points);
    Q_INVOKABLE void clearData();
    Q_INVOKABLE void clearLine(quint32 lineIndex);

    void paint(QPainter *painter);

    const QColor &gridColor() const;
    void setGridColor(const QColor &newGridColor);

    const QSizeF &gridSize() const;
    void setGridSize(const QSizeF &newGridSize);

    const QSizeF &gridOffset() const;
    void setGridOffset(const QSizeF &newGridOffset);

    unsigned int updateTime() const;
    void setUpdateTime(unsigned int newUpdateTime);

    qreal gridLineWidth() const;
    void setGridLineWidth(qreal newGridLineWidth);

    qreal xScaleBottom() const;
    void setXScaleBottom(qreal newXScaleBottom);

    qreal xScaleTop() const;
    void setXScaleTop(qreal newXScaleTop);

    const QColor &backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    bool hasScales() const;
    void setHasScales(bool newHasScales);

    qreal xTickCount() const;
    void setXTickCount(qreal newXTickCount);

    qreal yTickCount() const;
    void setYTickCount(qreal newYTickCount);

    qreal HorizontalScaleWidth() const;
    void setHorizontalScaleWidth(qreal newHorizontalScaleWidth);

    qreal verticalScaleHeigth() const;
    void setVerticalScaleHeigth(qreal newVerticalScaleHeigth);

    qreal plotAreaRigthPadding() const;
    void setPlotAreaRigthPadding(qreal newPlotAreaRigthPadding);

    const QColor &scaleColor() const;
    void setScaleColor(const QColor &newScaleColor);

    void setReDrawGrid(bool newReDrawGrid);

signals:
    void gridColorChanged();
    void gridSizeChanged();
    void gridOffsetChanged();
    void updateTimeChanged();
    void gridLineWidthChanged();
    void xSizeChanged();
    void xScaleBottomChanged();
    void xScaleTopChanged();
    void backgroundColorChanged();
    void linesChanged();
    void hasScalesChanged();
    void xTickCountChanged();
    void yTickCountChanged();
    void HorizontalScaleWidthChanged();
    void verticalScaleHeigthChanged();
    void plotAreaRigthPaddingChanged();
    void verticalScaleLabelsChanged();
    void horizontalScaleLabelsChanged();
    void scaleColorChanged();

private slots:
    void onGridSizeChanged();

protected:
    // QQuickItem interface
    void geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry);

    // QObject interface
    void timerEvent(QTimerEvent *event);

    QSGNode *updatePaintNode(QSGNode * oldNode, UpdatePaintNodeData *);

    // Nodes pointers
    QSGNode* _backgroundLayer;
    QSGNode* _gridLayer;
    QSGNode* _linesLayer;
    QSGNode* _peakLabelLayer;

};

#endif // IRACEMALINESERIESVIEW_H
