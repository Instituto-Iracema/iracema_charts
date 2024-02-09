#ifndef IRACEMALINESERIES_H
#define IRACEMALINESERIES_H

#include <QLineF>
#include <QPointF>
#include <QQuickItem>
#include <QSGFlatColorMaterial>
#include <QVector>
#include <iracemapointlabel.h>

/**
 * \class IracemaLineSeries
 * \brief Used to instantiate the line series in the QML type.
 *
 * \startuml
 * skinparam classAttributeIconSize 0
 * class IracemaLineSeries {
 *      +IracemaLineSeries()
 *      +~IracemaLineSeries()
 *      +lineWidth()
 *      +setLineWidth()
 *      +yScaleTop()
 *      +setYScaleTop()
 *      +yScaleBottom()
 *      +setYScaleBottom()
 *      +data()
 *      +dataBuffer()
 *      +pointLabels()
 *      +pointLabelsBuffer()
 *      +lineColor()
 *      +setLineColor()
 *      +at()
 *      +pointAt()
 *      +count()
 *      +applyDataBuffer()
 *      +applyPointLabelsBuffer()
 *      +addData()
 *      +addPoint()
 *      +appendGraphPointLabels()
 *      +clearData()
 *      +graphPointLabels()
 *      -_appendGraphPointLabels()
 *      -_addPointToBuffer()
 *      -_deleteGraphPoint()
 *      -_lineWidth
 *      -_yScaleTop
 *      -_yScaleBottom
 *      -_data
 *      -_dataBuffer
 *      -_graphPointLabels
 *      -_graphPointLabelsBuffer
 *      -_lineColor
 *      +{signal} lineWidthChanged()
 *      +{signal} yScaleTopChanged()
 *      +{signal} yScaleBottomChanged()
 *      +{signal} lineColorChanged()
 *      +{signal} graphPointLabelsChanged()
 * }
 * IracemaLineSeries <|-- QQuickItem
 * \enduml
 */
class IracemaLineSeries : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(qreal yScaleTop READ yScaleTop WRITE setYScaleTop NOTIFY yScaleTopChanged)
    Q_PROPERTY(qreal yScaleBottom READ yScaleBottom WRITE setYScaleBottom NOTIFY yScaleBottomChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    Q_PROPERTY(QQmlListProperty<IracemaPointLabel> graphPointLabels READ graphPointLabels NOTIFY graphPointLabelsChanged)
    QML_NAMED_ELEMENT(IracemaLineSeries)

public:
    /**
     * \fn IracemaLineSeries
     * \brief Constructor of the class.
     * \param parent Parent of the QML type.
     * \details The default values of the properties are:
     * \n lineWidth = 1
     * \n yScaleTop = 1000
     * \n yScaleBottom = 0
     * \n lineColor = black
     * \n other properties are empty.
     */
    explicit IracemaLineSeries(QQuickItem* parent = nullptr);

    /**
     * \fn ~IracemaLineSeries
     * \brief Destructor of the class.
     * \details The destructor deletes the graph point labels by calling the _deleteGraphPoint() function.
     */
    virtual ~IracemaLineSeries();

    /**
     * \fn lineWidth
     * \brief Getter of the lineWidth property.
     * \details The function returns the value of the lineWidth property.
     * \return The value of the lineWidth property.
     */
    qreal lineWidth() const {
        return _lineWidth;
    }

    /**
     * \fn setLineWidth
     * \brief Setter of the lineWidth property.
     * \param newLineWidth The new value of the lineWidth property.
     * \details If the new value is equal to the old value, the function returns.
     * \n If the new value is different from the old value, the function sets the new value and emits the lineWidthChanged() signal.
     */
    void setLineWidth(qreal newLineWidth) {
        if (qFuzzyCompare(_lineWidth, newLineWidth))
        {
            return;
        }

        _lineWidth = newLineWidth;
        emit lineWidthChanged();
    }

    /**
     * \fn yScaleTop
     * \brief Getter of the yScaleTop property.
     * \details The function returns the value of the yScaleTop property.
     * \return The value of the yScaleTop property.
     */
    qreal yScaleTop() const {
        return _yScaleTop;
    }

    /**
     * \fn setYScaleTop
     * \brief Setter of the yScaleTop property.
     * \param newYScaleTop The new value of the yScaleTop property.
     * \details If the new value is equal to the old value, the function returns.
     * \n If the new value is different from the old value, the function sets the new value and emits the yScaleTopChanged() signal.
     */
    void setYScaleTop(qreal newYScaleTop) {
        if (qFuzzyCompare(_yScaleTop, newYScaleTop))
        {
            return;
        }

        _yScaleTop = newYScaleTop;
        emit yScaleTopChanged();
    }

    /**
     * \fn yScaleBottom
     * \brief Getter of the yScaleBottom property.
     * \details The function returns the value of the yScaleBottom property.
     * \return The value of the yScaleBottom property.
     */
    qreal yScaleBottom() const {
        return _yScaleBottom;
    }

    /**
     * \fn setYScaleBottom
     * \brief Setter of the yScaleBottom property.
     * \param newYScaleBottom The new value of the yScaleBottom property.
     * \details If the new value is equal to the old value, the function returns.
     * \n If the new value is different from the old value, the function sets the new value and emits the yScaleBottomChanged() signal.
     */
    void setYScaleBottom(qreal newYScaleBottom) {
        if (qFuzzyCompare(_yScaleBottom, newYScaleBottom))
        {
            return;
        }

        _yScaleBottom = newYScaleBottom;
        emit yScaleBottomChanged();
    }

    /**
     * \fn data
     * \brief Getter of the data property.
     * \details The function returns the vector of the data property, which contains the lines of the line series.
     * \return The vector of the data property.
    */
    const QVector<QLineF> data() const {
        return _data;
    }

    /**
     * \fn dataBuffer
     * \brief Getter of the dataBuffer property.
     * \details The function returns the vector of the dataBuffer property, which contains the buffer lines of the line series.
     * \return The vector of the dataBuffer property.
    */
    const QVector<QLineF> dataBuffer() const {
        return _dataBuffer;
    }

    /**
     * \fn pointLabels
     * \brief Getter of the pointLabels property.
     * \details The function returns the list of the pointLabels property, which contains the graph point labels of the line series.
     * \return The list of the pointLabels property.
    */
    const QList<IracemaPointLabel*> pointLabels() const {
        return _graphPointLabels;
    }

    /**
     * \fn pointLabelsBuffer
     * \brief Getter of the pointLabelsBuffer property.
     * \details The function returns the list of the pointLabelsBuffer property, which contains the buffer graph point labels of the line series.
     * \return The list of the pointLabelsBuffer property.
    */
    const QList<IracemaPointLabel*> pointLabelsBuffer() {
        return _graphPointLabelsBuffer;
    }

    /**
     * \fn lineColor
     * \brief Getter of the lineColor property.
     * \details The function returns the value of the lineColor property.
     * \return The value of the lineColor property.
     */
    const QColor lineColor() const {
        return _lineColor;
    }

    /**
     * \fn setLineColor
     * \brief Setter of the lineColor property.
     * \param newLineColor The new value of the lineColor property.
     * \details If the new value is equal to the old value, the function returns.
     * \n If the new value is different from the old value, the function sets the new value and emits the lineColorChanged() signal.
     */
    void setLineColor(const QColor &newLineColor) {
        if (_lineColor == newLineColor)
        {
            return;
        }

        _lineColor = newLineColor;
        emit lineColorChanged();
    }

    /**
     * \fn at
     * \param index The index of the line.
     * \brief Getter of the line at the given index.
     * \details The function returns the line data at the given index.
     * \n This function is used in the QML type to get the line data at the given index.
     * \return The line data at the given index.
     */
    Q_INVOKABLE QLineF at(int index);

    /**
     * \fn pointAt
     * \param index The index of the point.
     * \brief Getter of the point at the given index.
     * \details The function returns the point data at the given index.
     * \n if the index is lower than data length, the function returns the point data at the given index of the data property.
     * \n Else, the function returns the point data at the given index minus the data length, of the dataBuffer property.
     * \n This function is used in the QML type to get the point data at the given index.
     * \return The point data at the given index.
     */
    Q_INVOKABLE QPointF pointAt(int index);

    /**
     * \fn count
     * \brief Getter of the count of the line series.
     * \details Returns the size of the data property.
     * \n This function is used in the QML type to get the size of the line series.
     * \return data size
     */
    Q_INVOKABLE int count();

    /**
     * \fn applyDataBuffer
     * \brief Applies the data buffer to the data property.
     * \details for each line in the dataBuffer property, the function appends the line to the data property.
     * \n Then, the function clears the dataBuffer property.
     * \n This function is used in the QML type to apply the data buffer to the data property.
     */
    Q_INVOKABLE void applyDataBuffer();

    /**
     * \fn applyPointLabelsBuffer
     * \brief Applies the graph point labels buffer to the graph point labels property.
     * \details for each graph point label in the graphPointLabelsBuffer property, the function appends the graph point label to the graphPointLabels property.
     * \n Then, the function clears the graphPointLabelsBuffer property.
     * \n This function is used in the QML type to apply the graph point labels buffer to the graph point labels property.
     */
    Q_INVOKABLE void applyPointLabelsBuffer();

    /**
     * \fn addData
     * \param data The vector of the data to add.
     * \brief Adds the data to the data buffer.
     * \details The function appends the data to the data buffer going through each point of the data.
     * \n This function is used in the QML type to add the data to the data buffer.
     */
    Q_INVOKABLE void addData(const QVector<QPointF>& data);

    /**
     * \fn addPoint
     * \param point The point to add.
     * \brief Adds the point to the data buffer.
     * \details The function appends the point to the data buffer.
     * \n This function is used in the QML type to add the point to the data buffer.
     */
    Q_INVOKABLE void addPoint(const QPointF& point);

    /**
     * \fn addPoint
     * \param x The x coordinate of the point to add.
     * \param y The y coordinate of the point to add.
     * \brief Adds the point to the data buffer.
     * \details The function appends the point to the data buffer.
     * \n This function is used in the QML type to add the point to the data buffer.
     */
    Q_INVOKABLE void addPoint(float x, float y);

    /**
     * \fn appendGraphPointLabels
     * \param position The position of the graph point label.
     * \param text The text of the graph point label.
     * \param upperText The upperText of the graph point label.
     * \brief Appends the graph point label to the graph point labels buffer.
     * \details The function appends the graph point label to the graph point labels buffer.
     * \n Creates a new graph point label with the given position and text.
     * \n Appends the graph point label to the graph point labels buffer.
     * \n Emits the graphPointLabelsChanged() signal.
     * \n This function is used in the QML type to append the graph point label to the graph point labels buffer.
     */
    Q_INVOKABLE void appendGraphPointLabels(const QPointF& position, const QString& text, const QString& upperText);

    /**
     * \fn appendGraphPointLabels
     * \param x The x coordinate of the graph point label.
     * \param y The y coordinate of the graph point label.
     * \param text The text of the graph point label.
     * \param upperText The upperText of the graph point label.
     * \brief Appends the graph point label to the graph point labels.
     * \details The function appends the graph point label to the graph point labels, with x and y coordinates and the given text.
     * \n Appends the graph point label to the graph point labels.
     * \n This function is used in the QML type to append the graph point label to the graph point labels buffer.
     */
    Q_INVOKABLE void appendGraphPointLabels(qreal x, qreal y, const QString& text, const QString& upperText);

    /**
     * \fn clearData
     * \brief Clears the data and the data buffer, and deletes the graph point.
     * \details The function clears the data and the data buffer, and deletes the graph point.
     * \n This function is used in the QML type to clear the data and the data buffer.
     */
    Q_INVOKABLE void clearData();

    /**
     * \fn graphPointLabels
     * \brief Getter of the graphPointLabels property.
     * \details The function returns the QQmlListProperty of the graphPointLabels property.
     * \return The QQmlListProperty of the graphPointLabels property.
     */
    QQmlListProperty<IracemaPointLabel> graphPointLabels();

private:
    /**
     * \fn _lineWidth
     * \brief The width of the line.
     */
    qreal _lineWidth;

    /**
     * \fn _yScaleTop
     * \brief The top of the y scale.
     */
    qreal _yScaleTop;

    /**
     * \fn _yScaleBottom
     * \brief The bottom of the y scale.
     */
    qreal _yScaleBottom;

    /**
     * \fn _data
     * \brief The data of the line series.
     */
    QVector<QLineF> _data;

    /**
     * \fn _dataBuffer
     * \brief The data buffer of the line series.
     */
    QVector<QLineF> _dataBuffer;

    /**
     * \fn _graphPointLabels
     * \brief The graph point labels of the line series.
     */
    QList<IracemaPointLabel*> _graphPointLabels;

    /**
     * \fn _graphPointLabelsBuffer
     * \brief The graph point labels buffer of the line series.
     */
    QList<IracemaPointLabel*> _graphPointLabelsBuffer;

    /**
     * \fn _lineColor
     * \brief The color of the line.
     */
    QColor _lineColor;

    /**
     * \fn _appendGraphPointLabels
     * \param list The QQmlListProperty of the graphPointLabels property.
     * \param label The graph point label to append.
     * \brief Appends the graph point label to the graph point labels.
     * \details The function appends the graph point label to the graph point labels.
     * \n if the line is not null:
     * \n   -Sets the parent of the graph point label to the line series.
     * \n   -Appends the graph point label to the graph point labels.
     * \n   -Emits the graphPointLabelsChanged() signal.
     */
    static void _appendGraphPointLabels(QQmlListProperty<IracemaPointLabel>*, IracemaPointLabel*);

    /**
     * \fn _addPointToBuffer
     * \param point The point to add.
     * \brief Adds the point to the data buffer.
     * \details Creates a new line
     * \n if the data buffer is empty:
     * \n   -if the data is empty:
     * \n     -Sets the initial point to the point.
     * \n   -else:
     * \n     -Sets the initial point to the final point of the last line of the data.
     * \n else:
     * \n   -Sets the initial point to the final point of the last line of the data buffer.
     * \n Sets the final point of the line to the point.
     * \n Appends the line to the data buffer.
     */
    void _addPointToBuffer(const QPointF& point);

    /**
     * \fn _deleteGraphPoint
     * \brief Deletes the graph point labels.
     * \details The function deletes the graph point labels.
     * \n For each graph point label in the graph point labels:
     * \n   -Deletes the graph point label.
     * \n Clears the graph point labels.
     * \n For each graph point label buffer in the graph point labels buffer:
     * \n   -Deletes the graph point label buffer.
     * \n Clears the graph point labels buffer.
     */
    void _deleteGraphPoint() noexcept;

signals:

    /**
     * \fn lineWidthChanged
     * \brief Emitted when the lineWidth property changes.
     */
    void lineWidthChanged();

    /**
     * \fn yScaleTopChanged
     * \brief Emitted when the yScaleTop property changes.
     */
    void yScaleTopChanged();

    /**
     * \fn yScaleBottomChanged
     * \brief Emitted when the yScaleBottom property changes.
     */
    void yScaleBottomChanged();

    /**
     * \fn lineColorChanged
     * \brief Emitted when the lineColor property changes.
     */
    void lineColorChanged();

    /**
     * \fn graphPointLabelsChanged
     * \brief Emitted when the graphPointLabels property changes.
     */
    void graphPointLabelsChanged();
};

#endif // IRACEMALINESERIES_H
