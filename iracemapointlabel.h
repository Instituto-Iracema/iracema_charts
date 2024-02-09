#ifndef IRACEMAPOINTLABEL_H
#define IRACEMAPOINTLABEL_H

#include <QObject>
#include <QQuickItem>

/**
 * \class IracemaPointLabel
 * \brief A label for a point in a graph.
 * 
 * \startuml 
 * skinparam classAttributeIconSize 0
 * class IracemaPointLabel {
 *      + IracemaPointLabel()
 *      + IracemaPointLabel(QPointF graphPoint, QString text)
 *      + graphPoint()
 *      + setGraphPoint()
 *      + text()
 *      + setText()
 *      + {signal}graphPointChanged()
 *      + {signal}textChanged()
 *      - _graphPoint
 *      - _text
 * }
 * \enduml
*/
class IracemaPointLabel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QPointF graphPoint READ graphPoint WRITE setGraphPoint NOTIFY graphPointChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString upperText READ upperText WRITE setUpperText NOTIFY upperTextChanged)
    QML_NAMED_ELEMENT(IracemaPointLabel)

public:

    /**
     * \fn IracemaPointLabel
     * \brief Constructor of the class.
     * \param parent Parent of the QML type.
     * \details Constructs an IracemaPointLabel with an empty graphPoint, text and upperText.
     */
    explicit IracemaPointLabel(QQuickItem* parent = nullptr);

    /**
     * \fn IracemaPointLabel
     * \param graphPoint The point in the graph.
     * \param text The text to display.
     * \param upperText The upperText to display.
     * \brief Constructor.
     * \details Constructs an IracemaPointLabel with the given graphPoint, text and upperText.
     */
    IracemaPointLabel(QPointF graphPoint, QString text, QString upperText);

    /**
     * \fn graphPoint
     * \brief Returns the graphPoint.
     * \details Returns the graphPoint.
     * \return The graphPoint.
     */
    QPointF graphPoint() const {
        return _graphPoint;
    }

    /**
     * \fn setGraphPoint
     * \param newGraphPoint The new graphPoint.
     * \brief Sets the graphPoint.
     * \details If the graphPoint is the same as the current graphPoint, this function does nothing.
     * \n Else it sets the graphPoint to the new graphPoint and emits the graphPointChanged() signal.
     */
    void setGraphPoint(QPointF newGraphPoint) {
        if (_graphPoint == newGraphPoint)
        {
            return;
        }

        _graphPoint = newGraphPoint;
        emit graphPointChanged();
    }

    /**
     * \fn text
     * \brief Returns the text.
     * \details Returns the text.
     * \return The text.
     */
    const QString text() const {
        return _text;
    }

    /**
     * \fn setText
     * \param newText The new text.
     * \brief Sets the text.
     * \details If the text is the same as the current text, this function does nothing.
     * \n Else it sets the text to the new text and emits the textChanged() signal.
     */
    void setText(const QString &newText) {
        if (_text == newText)
        {
            return;
        }

        _text = newText;
        emit textChanged();
    }

    /**
     * \fn upperText
     * \brief Returns the upperText.
     * \details Returns the upperText.
     * \return The upperText.
     */
    const QString &upperText() const {
        return _upperText;
    }

    /**
     * \fn setUpperText
     * \param newUpperText The new upperText.
     * \brief Sets the upperText.
     * \details If the upperText is the same as the current upperText, this function does nothing.
     * \n Else it sets the upperText to the new upperText and emits the upperTextChanged() signal.
     */
    void setUpperText(const QString &newUpperText) {
        if (_upperText == newUpperText)
        {
            return;
        }

        _upperText = newUpperText;
        emit upperTextChanged();
    }

private:

    /**
     * \fn _graphPoint
     * \brief The point in the graph.
    */
    QPointF _graphPoint;

    /**
     * \fn _text
     * \brief The text to display.
    */
    QString _text;

    /**
     * \fn _upperText
     * \brief The upper text to display.
    */
    QString _upperText;

signals:

    /**
     * \fn graphPointChanged
     * \brief Emitted when the graphPoint changes.
     * \details Emitted when the graphPoint changes.
     */
    void graphPointChanged();

    /**
     * \fn textChanged
     * \brief Emitted when the text changes.
     * \details Emitted when the text changes.
     */
    void textChanged();

    /**
     * \fn upperTextChanged
     * \brief Emitted when the upperText changes.
     * \details Emitted when the upperText changes.
     */
    void upperTextChanged();
};

#endif // IRACEMAPOINTLABEL_H
