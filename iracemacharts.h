#ifndef IRACEMACHARTS_H
#define IRACEMACHARTS_H

#include <QQuickItem>

/**
 * \class IracemaCharts
 * \brief Used to instantiate the IracemaCharts QML type.
 * 
 * \startuml
 * skinparam classAttributeIconSize 0
 * class IracemaCharts {
 * }
 * IracemaCharts <|-- QQuickItem
 * \enduml
*/

class IracemaCharts : public QQuickItem
{
    Q_OBJECT
    Q_DISABLE_COPY(IracemaCharts)
    QML_NAMED_ELEMENT(IracemaCharts)

public:
    /***
     * \fn IracemaCharts
     * \brief Constructor.
     * \param parent The parent item.
     * \details Does nothing.
     * \warning By default, QQuickItem does not draw anything. If you subclass
     * \n QQuickItem to create a visual item, you will need to uncomment the
     * \n following line with setFlag function, and re-implement updatePaintNode()
    */
    explicit IracemaCharts(QQuickItem *parent = nullptr);
    /***
     * \fn ~IracemaCharts
     * \brief Destructor.
     * \details Does nothing.
    */
    ~IracemaCharts() override;
};

#endif // IRACEMACHARTS_H
