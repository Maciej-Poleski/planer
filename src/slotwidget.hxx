/* Maciej Poleski (C) 2011-2012 */

#ifndef SLOTWIDGET_HXX
#define SLOTWIDGET_HXX

#include <QtGui/QStackedWidget>

#include <Wt/Dbo/Dbo>

class QLabel;
class QComboBox;
class QHBoxLayout;
class QTimeEdit;
class QPushButton;

class Slot;

namespace GUI
{

class SlotWidget : public QStackedWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SlotWidget)
public:
    explicit SlotWidget(Wt::Dbo::ptr<Slot> slot = static_cast<Slot*>(nullptr), QWidget *parent = 0) throw();

    const Wt::Dbo::ptr<Slot> slot() const throw();
    Wt::Dbo::ptr<Slot> slot() throw();

signals:
    void slotChanged();
    void storageRemoved();

public slots:
    void setSlot(Wt::Dbo::ptr<Slot> slot) throw();

private slots:
    void populateWidget() throw();
    void repopulateWidget() throw();
    void updateDayStore(int index) throw();
    void updateTimeStore(const QTime &time) throw();
    void connectSignalsForNewSlot() throw();

private:
    void connectSignalsAndSlots() throw();

    Wt::Dbo::ptr<Slot> p_slot;

    QHBoxLayout *p_layout;
    QComboBox *p_dayComboBox;
    QTimeEdit *p_timeEdit;
    QPushButton *p_deleteButton;
    QLabel *p_noStorageLabel;
    QWidget *p_slotWidget;
};
}
#endif // SLOTWIDGET_HXX
