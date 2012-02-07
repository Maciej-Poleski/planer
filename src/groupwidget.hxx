/* Maciej Poleski (C) 2011-2012 */

#ifndef GROUPWIDGET_HXX
#define GROUPWIDGET_HXX


#include <QtGui/QStackedWidget>

#include <vector>

#include <QtCore/QPointer>

#include <Wt/Dbo/Dbo>

#include "group.hxx"

class QLabel;
class QVBoxLayout;
class QLineEdit;
class QPushButton;
class QGroupBox;
class QHBoxLayout;

namespace GUI
{

class SlotWidget;

/**
 * @brief Widget prezentujący sloty w danej grupie.
 **/
class GroupWidget : public QStackedWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(GroupWidget)
public:
    explicit GroupWidget(Wt::Dbo::ptr<Group> group = static_cast<Group*>(nullptr), QWidget *parent = 0) throw();

    const Wt::Dbo::ptr<Group> group() const throw();
    Wt::Dbo::ptr<Group> group() throw();

signals:
    void groupChanged();
    void storageRemoved();

public slots:
    void setGroup(Wt::Dbo::ptr<Group> group) throw();
    void addNewSlot() throw();

private slots:
    /**
     * @brief Przerysowuje widget
     *
     **/
    void repopulateWidget() throw();
    void connectSignalsAndSlots() throw();
    void updateGroupName() throw();
    void connectSignalsForNewGroup() throw();
    void repopulateGroupName() throw();
    void resizeAfterGuiCleanup() throw();
    void populateNewSlotWidget(Wt::Dbo::ptr< Slot > slot) throw();

private:
    Wt::Dbo::ptr<Group> p_group;

    QVBoxLayout *p_layout;
    std::vector<SlotWidget *> p_slotWidgetList;
    QLineEdit *p_groupNameLineEdit;
    QPushButton *p_addNewSlotButton;
    QLabel *p_noStorageLabel;
    QGroupBox *p_groupWidget;
    QPushButton *p_deleteGroupButton;
    QHBoxLayout *p_groupHeaderLayout;
};

}
#endif // GROUPWIDGET_HXX
