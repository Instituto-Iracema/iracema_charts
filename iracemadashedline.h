#ifndef IRACEMADASHEDLINE_H
#define IRACEMADASHEDLINE_H

#include <QSGFlatColorMaterial>
#include <QQuickItem>
#include <QPointF>
#include <QColor>

/**
 * \class IracemaDashedLine
 * \brief Used to instantiate the dashed lines in the QML type.
 *
 * \startuml
 * skinparam classAttributeIconSize 0
 * class IracemaDashedLine {
 *      +IracemaDashedLine()
 *      +lineWidth()
 *      +setLineWidth()
 *      +yScaleTop()
 *      +setYScaleTop()
 *      +yScaleBottom()
 *      +setYScaleBottom()
 *      +initialPoint()
 *      +setInitialPoint()
 *      +finalPoint()
 *      +setFinalPoint()
 *      +lineColor()
 *      +setLineColor()
 *      -_lineWidth
 *      -_yScaleTop
 *      -_yScaleBottom
 *      -_initialPoint
 *      -_finalPoint
 *      -_lineColor
 *      +{signal} initialPointChanged()	
 *      +{signal} finalPointChanged()
 *      +{signal} lineWidthChanged()
 *      +{signal} yScaleTopChanged()
 *      +{signal} yScaleBottomChanged()
 *      +{signal} lineColorChanged()
 * }
 * IracemaDashedLine <|-- QQuickItem
 * \enduml
*/


class IracemaDashedLine : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF initialPoint READ initialPoint WRITE setInitialPoint NOTIFY initialPointChanged)
    Q_PROPERTY(QPointF finalPoint READ finalPoint WRITE setFinalPoint NOTIFY finalPointChanged)
    Q_PROPERTY(qreal lineWidth READ lineWidth WRITE setLineWidth NOTIFY lineWidthChanged)
    Q_PROPERTY(qreal yScaleTop READ yScaleTop WRITE setYScaleTop NOTIFY yScaleTopChanged)
    Q_PROPERTY(qreal yScaleBottom READ yScaleBottom WRITE setYScaleBottom NOTIFY yScaleBottomChanged)
    Q_PROPERTY(QColor lineColor READ lineColor WRITE setLineColor NOTIFY lineColorChanged)
    QML_NAMED_ELEMENT(IracemaDashedLine)

public:

    /**
     * \fn IracemaDashedLine
     * \brief Constructor of the class.
     * \details The constructor initializes the private attributes of the class.
     * \n The default values are empty except for the line color, which is black, and the yScaleTop, which is 100.
    */
    IracemaDashedLine();

    /**
     * \fn lineWidth
     * \brief Getter of the lineWidth attribute.
     * \details returns the width of the line.
     * \return The width of the line.
    */
    qreal lineWidth() const {
        return _lineWidth;
    }

    /**
     * \fn setLineWidth
     * \param newLineWidth The new width of the line.
     * \brief Setter of the lineWidth attribute.
     * \details Sets the width of the line.
     * \n If the new width is equal to the current width, the function does nothing.
     * \n If the new width is different from the current width, the function sets the new width and emits the signal lineWidthChanged().
    */
    void setLineWidth(qreal newLineWidth) {
        if(qFuzzyCompare(_lineWidth, newLineWidth))
            return;

        _lineWidth = newLineWidth;
        emit lineWidthChanged();
    }

    /**
     * \fn yScaleTop
     * \brief Getter of the yScaleTop attribute.
     * \details returns the top of the yScale.
     * \return The top of the yScale.
    */
    qreal yScaleTop() const {
        return _yScaleTop;
    }
  
    /**
     * \fn setYScaleTop
     * \param newYScaleTop The new top of the yScale.
     * \brief Setter of the yScaleTop attribute.
     * \details Sets the top of the yScale.
     * \n If the new top is equal to the current top, the function does nothing.
     * \n If the new top is different from the current top, the function sets the new top and emits the signal yScaleTopChanged().
    */
    void setYScaleTop(qreal newYScaleTop) {
        if (qFuzzyCompare(_yScaleTop, newYScaleTop))
            return;

        _yScaleTop = newYScaleTop;
        emit yScaleTopChanged();
    }

    /**
     * \fn yScaleBottom
     * \brief Getter of the yScaleBottom attribute.
     * \details returns the bottom of the yScale.
     * \return The bottom of the yScale.
    */
    qreal yScaleBottom() const {
        return _yScaleBottom;
    }
 
    /**
     * \fn setYScaleBottom
     * \param newYScaleBottom The new bottom of the yScale.
     * \brief Setter of the yScaleBottom attribute.
     * \details Sets the bottom of the yScale.
     * \n If the new bottom is equal to the current bottom, the function does nothing.
     * \n If the new bottom is different from the current bottom, the function sets the new bottom and emits the signal yScaleBottomChanged().
    */
    void setYScaleBottom(qreal newYScaleBottom) {
        if (qFuzzyCompare(_yScaleBottom, newYScaleBottom))
            return;

        _yScaleBottom = newYScaleBottom;
        emit yScaleBottomChanged();
    }

    /**
     * \fn initialPoint
     * \brief Getter of the initialPoint attribute.
     * \details returns the initial point of the line.
     * \return The initial point of the line.
    */
    QPointF initialPoint() const {
        return _initialPoint;
    }
 
    /**
     * \fn setInitialPoint
     * \param newPoint The new initial point of the line.
     * \brief Setter of the initialPoint attribute.
     * \details Sets the initial point of the line.
     * \n If the new initial point is equal to the current initial point, the function does nothing.
     * \n If the new initial point is different from the current initial point, the function sets the new initial point and emits the signal initialPointChanged().
    */
    void setInitialPoint(const QPointF& newPoint) {
        if(_initialPoint == newPoint)
            return;

        _initialPoint = newPoint;
        emit initialPointChanged();
    }

    /**
     * \fn finalPoint
     * \brief Getter of the finalPoint attribute.
     * \details returns the final point of the line.
     * \return The final point of the line.
    */
    QPointF finalPoint() const {
        return _finalPoint;
    }
 
    /**
     * \fn setFinalPoint
     * \param newPoint The new final point of the line.
     * \brief Setter of the finalPoint attribute.
     * \details Sets the final point of the line.
     * \n If the new final point is equal to the current final point, the function does nothing.
     * \n If the new final point is different from the current final point, the function sets the new final point and emits the signal finalPointChanged().
    */
    void setFinalPoint(const QPointF& newPoint) {
        if(_finalPoint == newPoint)
            return;

        _finalPoint = newPoint;
        emit finalPointChanged();
    }

    /**
     * \fn lineColor
     * \brief Getter of the lineColor attribute.
     * \details returns the color of the line.
     * \return The color of the line.
    */
    const QColor lineColor() const {
        return _lineColor;
    }

    /**
     * \fn setLineColor
     * \param newLineColor The new color of the line.
     * \brief Setter of the lineColor attribute.
     * \details Sets the color of the line.
     * \n If the new color is equal to the current color, the function does nothing.
     * \n If the new color is different from the current color, the function sets the new color and emits the signal lineColorChanged().
    */
    void setLineColor(const QColor &newLineColor) {
        if (_lineColor == newLineColor)
            return;

        _lineColor = newLineColor;
        emit lineColorChanged();
    }

private:
    /**
     * \fn _lineWidth
     * \brief The width of the line.
    */
    qreal _lineWidth;

    /**
     * \fn _yScaleTop
     * \brief The top of the yScale.
    */
    qreal _yScaleTop;

    /**
     * \fn _yScaleBottom
     * \brief The bottom of the yScale.
    */
    qreal _yScaleBottom;

    /**
     * \fn _initialPoint
     * \brief The initial point of the line.
    */
    QPointF _initialPoint;

    /**
     * \fn _finalPoint
     * \brief The final point of the line.
    */
    QPointF _finalPoint;

    /**
     * \fn _lineColor
     * \brief The color of the line.
    */
    QColor _lineColor;

signals:

    /**
     * \fn initialPointChanged
     * \brief Signal emitted when the initial point of the line changes.
    */
    void initialPointChanged();

    /**
     * \fn finalPointChanged
     * \brief Signal emitted when the final point of the line changes.
    */
    void finalPointChanged();

    /**
     * \fn lineWidthChanged
     * \brief Signal emitted when the width of the line changes.
    */
    void lineWidthChanged();

    /**
     * \fn yScaleTopChanged
     * \brief Signal emitted when the top of the yScale changes.
    */
    void yScaleTopChanged();

    /**
     * \fn yScaleBottomChanged
     * \brief Signal emitted when the bottom of the yScale changes.
    */
    void yScaleBottomChanged();

    /**
     * \fn lineColorChanged
     * \brief Signal emitted when the color of the line changes.
    */
    void lineColorChanged();
};

#endif // IRACEMADASHEDLINE_H


