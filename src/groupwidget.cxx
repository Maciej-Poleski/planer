/* Maciej Poleski (C) 2011-2012 */

#include "groupwidget.hxx"

#include <utility>

#include <QtCore/QTimer>
#include <QtCore/QString>

#include <QtGui/QVBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>

#include "slot.hxx"
#include "slotwidget.hxx"

using namespace Wt::Dbo;

GUI::GroupWidget::GroupWidget(ptr< Group > group, QWidget *parent) throw():
    QStackedWidget(parent),
    p_group(group),
    p_layout(new QVBoxLayout()),
    p_slotWidgetList(),
    p_groupNameLineEdit(new QLineEdit(group != static_cast<Group*>(nullptr) ? group->getName() : "")),
    p_addNewSlotButton(new QPushButton(tr("Add &slot"))),
    p_noStorageLabel(new QLabel("<font color=\"red\">" + tr("This widget hasn't storage") + "</font>")),
    p_groupWidget(new QGroupBox()),
    p_deleteGroupButton(new QPushButton(tr("Delete group"))),
    p_groupHeaderLayout(new QHBoxLayout())
{
    p_groupHeaderLayout->addWidget(p_groupNameLineEdit);
    p_groupHeaderLayout->addWidget(p_deleteGroupButton);
    p_layout->addLayout(p_groupHeaderLayout);
    p_layout->addStretch(1);
    p_layout->addWidget(p_addNewSlotButton);
    if(p_group != static_cast<Group*>(nullptr)) {
        for(ptr<Slot> slot: *p_group) {
            populateNewSlotWidget(slot);
        }
    }
    p_groupWidget->setLayout(p_layout);
    p_noStorageLabel->setAlignment(Qt::AlignCenter);
    addWidget(p_noStorageLabel);
    addWidget(p_groupWidget);
    setCurrentWidget(group == static_cast<Group*>(nullptr) ? static_cast<QWidget *>(p_noStorageLabel) : static_cast<QWidget *>(p_groupWidget));
    QTimer::singleShot(0, this, SLOT(connectSignalsAndSlots()));
    QTimer::singleShot(0, this, SLOT(repopulateWidget()));
}

void GUI::GroupWidget::setGroup(ptr< Group > group) throw()
{
    if(p_group != group) {
        p_group = group;
        emit groupChanged();
        if(p_group == static_cast<Group*>(nullptr))
            emit storageRemoved();
    }
}

const Wt::Dbo::ptr<Group> GUI::GroupWidget::group() const throw()
{
    return p_group;
}

Wt::Dbo::ptr<Group> GUI::GroupWidget::group() throw()
{
    return p_group;
}

void GUI::GroupWidget::repopulateWidget() throw()
{
    if(p_group != static_cast<Group*>(nullptr)) {
    for(SlotWidget * w: p_slotWidgetList) {
            p_layout->removeWidget(w);
            w->deleteLater();
        }
        p_slotWidgetList.clear();
        repopulateGroupName();
        if(p_group != static_cast<Group*>(nullptr)) {
        for(ptr<Slot> slot: *p_group) {
                populateNewSlotWidget(slot);
            }
        }
        setCurrentWidget(p_groupWidget);
        resize(sizeHint());
    } else {
        setCurrentWidget(p_noStorageLabel);
    }
}

void GUI::GroupWidget::connectSignalsAndSlots() throw()
{
    connect(this, SIGNAL(groupChanged()), this, SLOT(repopulateWidget()));
    connect(this, SIGNAL(groupChanged()), this, SLOT(connectSignalsForNewGroup()));
    connect(p_groupNameLineEdit, SIGNAL(editingFinished()), this, SLOT(updateGroupName()));
    connect(p_addNewSlotButton, SIGNAL(clicked(bool)), this, SLOT(addNewSlot()));
    connectSignalsForNewGroup();
}

void GUI::GroupWidget::connectSignalsForNewGroup() throw()
{
    if(p_group != static_cast<Group*>(nullptr)) {
        connect(p_group.get(), SIGNAL(destroyed()), this, SIGNAL(storageRemoved()));
        connect(p_group.get(), SIGNAL(destroyed()), this, SLOT(repopulateWidget()));
        connect(p_group.get(), SIGNAL(slotInserted(Wt::Dbo::ptr<Slot>)), this, SLOT(populateNewSlotWidget(Wt::Dbo::ptr<Slot>)));
        connect(p_group.get(), SIGNAL(nameChanged()), this, SLOT(repopulateGroupName()));
        connect(p_deleteGroupButton,SIGNAL(clicked(bool)),p_group.get(),SLOT(deleteLater()));
    }
}

void GUI::GroupWidget::updateGroupName() throw()
{
    if(p_group != static_cast<Group*>(nullptr)) {
        p_group.modify()->setName(p_groupNameLineEdit->text());
    }
}

void GUI::GroupWidget::addNewSlot() throw()
{
    p_group.modify()->insertSlot(new Slot());
}

void GUI::GroupWidget::repopulateGroupName() throw()
{
    p_groupNameLineEdit->setText(p_group ? p_group->getName() : "");
}

void GUI::GroupWidget::populateNewSlotWidget(ptr<Slot> slot) throw()
{
    SlotWidget *slotWidget = new SlotWidget(slot);
    p_slotWidgetList.push_back(slotWidget);
    p_layout->insertWidget(p_layout->count() - 2, p_slotWidgetList.back());
    connect(slotWidget, SIGNAL(storageRemoved()), slotWidget, SLOT(deleteLater()));
    connect(slotWidget, SIGNAL(destroyed(QObject *)), this, SLOT(resizeAfterGuiCleanup()));
}

void GUI::GroupWidget::resizeAfterGuiCleanup() throw()
{
    resize(minimumSize());
}

#include "moc_groupwidget.cpp"
