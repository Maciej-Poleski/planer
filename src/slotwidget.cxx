/* Maciej Poleski (C) 2011-2012 */

#include "slotwidget.hxx"

#include <utility>

#include <QtCore/QTimer>

#include <QtGui/QHBoxLayout>
#include <QtGui/QComboBox>
#include <QtGui/QTimeEdit>
#include <QtGui/QMessageBox>
#include <QtGui/QPushButton>
#include <QtGui/QLabel>
#include <QtGui/QFont>

#include "slot.hxx"

GUI::SlotWidget::SlotWidget(Wt::Dbo::ptr<Slot> slot, QWidget *parent) throw()
    : QStackedWidget(parent),
      p_slot(slot),
      p_dayComboBox(new QComboBox()),
      p_layout(new QHBoxLayout()),
      p_timeEdit(new QTimeEdit()),
      p_deleteButton(new QPushButton(tr("Delete"))),
      p_noStorageLabel(new QLabel("<font color=\"red\">" + tr("This widget hasn't storage") + "</font>")),
      p_slotWidget(new QWidget())
{
    p_layout->addWidget(p_dayComboBox);
    p_layout->addWidget(p_timeEdit);
    p_layout->addWidget(p_deleteButton);

    p_slotWidget->setLayout(p_layout);
    addWidget(p_noStorageLabel);
    addWidget(p_slotWidget);

    setCurrentWidget(slot == static_cast<Slot*>(nullptr) ? p_noStorageLabel : p_slotWidget);

    QTimer::singleShot(0, this, SLOT(populateWidget()));
}

void GUI::SlotWidget::setSlot(Wt::Dbo::ptr<Slot> slot) throw()
{
    if(p_slot != slot) {
        p_slot = slot;
        emit slotChanged();
        if(p_slot == static_cast<Slot*>(nullptr))
            emit storageRemoved();
    }
}

const Wt::Dbo::ptr<Slot> GUI::SlotWidget::slot() const throw()
{
    return p_slot;
}

Wt::Dbo::ptr<Slot> GUI::SlotWidget::slot() throw()
{
    return p_slot;
}

void GUI::SlotWidget::repopulateWidget() throw()
{
    if(p_slot != static_cast<Slot*>(nullptr)) {
        p_dayComboBox->setCurrentIndex(p_slot->day());
        p_timeEdit->setTime(QTime(p_slot->hour(), 0));
        setCurrentWidget(p_slotWidget);
    } else {
        setCurrentWidget(p_noStorageLabel);
    }
    resize(minimumSize());
}

void GUI::SlotWidget::populateWidget() throw()
{
    p_dayComboBox->addItem(tr("Monday"));
    p_dayComboBox->addItem(tr("Tuesday"));
    p_dayComboBox->addItem(tr("Wednesday"));
    p_dayComboBox->addItem(tr("Thursday"));
    p_dayComboBox->addItem(tr("Friday"));
    p_timeEdit->setDisplayFormat("hh");
    p_noStorageLabel->setAlignment(Qt::AlignCenter);
    connectSignalsAndSlots();
    repopulateWidget();
}

void GUI::SlotWidget::connectSignalsAndSlots() throw()
{
    connect(this, SIGNAL(slotChanged()), this, SLOT(repopulateWidget()));
    connect(this, SIGNAL(slotChanged()), this, SLOT(connectSignalsForNewSlot()));
    connect(p_dayComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateDayStore(int)));
    connect(p_timeEdit, SIGNAL(timeChanged(QTime)), this, SLOT(updateTimeStore(QTime)));
    connectSignalsForNewSlot();
}

void GUI::SlotWidget::connectSignalsForNewSlot() throw()
{
    if(p_slot != static_cast<Slot*>(nullptr)) {
        connect(p_slot.get(), SIGNAL(changed()), this, SLOT(repopulateWidget()));
        connect(p_slot.get(), SIGNAL(destroyed(QObject *)), this, SLOT(repopulateWidget()));
        connect(p_slot.get(), SIGNAL(destroyed(QObject *)), this, SIGNAL(storageRemoved()));
        connect(p_deleteButton, SIGNAL(clicked()), p_slot.get(), SLOT(deleteLater()));
    }
}

void GUI::SlotWidget::updateDayStore(int index) throw()
{
    if(p_slot != static_cast<Slot*>(nullptr)) {
        p_slot.modify()->setDay(static_cast<quint8>(index));
    }
}

void GUI::SlotWidget::updateTimeStore(const QTime &time) throw()
{
    if(!time.isValid() || time.minute() != 0 || time.second() != 0 || time.msec() != 0) {
        QMessageBox::critical(this, tr("Invalid time"), tr("Time is invalid"));
        return;
    }
    if(p_slot != static_cast<Slot*>(nullptr)) {
        p_slot.modify()->setHour(static_cast<quint8>(time.hour()));
    }
}

#include "moc_slotwidget.cpp"
