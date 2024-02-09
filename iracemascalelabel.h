#ifndef IRACEMASCALELABEL_H
#define IRACEMASCALELABEL_H

#include <QQuickItem>

/**
 * \class IracemaScaleLabel
 * \brief A label for a scale in a graph.
 * 
 * \startuml 
 * skinparam classAttributeIconSize 0
 * class IracemaScaleLabel {
 *      + IracemaScaleLabel()
 *      + scalePoint()
 *      + setScalePoint()
 *      + scaleText()
 *      + setScaleText()
 *      + {signal}scalePointChanged()
 *      + {signal}scaleTextChanged()
 *      - _scalePoint
 *      - _scaleText
 * }
 * \enduml
 */
class IracemaScaleLabel : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int scalePoint READ scalePoint WRITE setScalePoint NOTIFY scalePointChanged)
    Q_PROPERTY(QString scaleText READ scaleText WRITE setScaleText NOTIFY scaleTextChanged)
    QML_NAMED_ELEMENT(IracemaScaleLabel)

public:

    /**
     * \fn IracemaScaleLabel
     * \brief Constructor of the class.
     * \param parent Parent of the QML type.
     * \details Constructs an IracemaScaleLabel with an empty scalePoint and scaleText.
     */
    explicit IracemaScaleLabel(QQuickItem* parent = nullptr);

    /**
     * \fn scalePoint
     * \brief Returns the scalePoint.
     * \details Returns the scalePoint.
     * \return The scalePoint.
     */
    int scalePoint() const {
        return _scalePoint;
    }

    /**
     * \fn setScalePoint
     * \param newScalePoint The new scalePoint.
     * \brief Sets the scalePoint.
     * \details If the new scalePoint is equal to the old scalePoint, nothing happens.
     * \n else the scalePoint is set to the new scalePoint and the scalePointChanged() signal is emitted.
     */
    void setScalePoint(int newScalePoint) {
        if (_scalePoint == newScalePoint)
        {
            return;
        }

        _scalePoint = newScalePoint;
        emit scalePointChanged();
    }

    /**
     * \fn scaleText
     * \brief Returns the scaleText.
     * \details If the scaleText is empty, it is set to the scalePoint.
     * \return The scaleText.
     */
    const QString scaleText() {
        if (_scaleText.isEmpty())
        {
            _scaleText = QString::number(_scalePoint);
        }

        return _scaleText;
    }

    /**
     * \fn setScaleText
     * \param newScaleText The new scaleText.
     * \brief Sets the scaleText.
     * \details If the new scaleText is equal to the old scaleText, nothing happens.
     * \n else the scaleText is set to the new scaleText and the scaleTextChanged() signal is emitted.
     */
    void setScaleText(const QString &newScaleText) {
        if (_scaleText == newScaleText)
        {
            return;
        }

        _scaleText = newScaleText;
        emit scaleTextChanged();
    }

private:

    /**
     * \fn _scalePoint
     * \brief The point in the scale.
    */
    int _scalePoint;

    /**
     * \fn _scaleText
     * \brief The text of the scale.
    */
    QString _scaleText;

signals:

    /**
     * \fn scalePointChanged
     * \brief Emitted when the scalePoint changes.
     * \details Emitted when the scalePoint changes.
     */
    void scalePointChanged();

    /**
     * \fn scaleTextChanged
     * \brief Emitted when the scaleText changes.
     * \details Emitted when the scaleText changes.
     */
    void scaleTextChanged();
};

#endif // IRACEMASCALELABEL_H
