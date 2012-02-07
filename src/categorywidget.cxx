/* Maciej Poleski (C) 2012 */

#include "categorywidget.hxx"

#include <utility>

#include <QtCore/QTimer>
#include <QtCore/QString>

#include <QtGui/QVBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>

#include "category.hxx"
#include "groupwidget.hxx"
#include "slot.hxx"

using namespace Wt::Dbo;

GUI::CategoryWidget::CategoryWidget(Wt::Dbo::ptr< Category > category, QWidget *parent) throw():
    QStackedWidget(parent),
    p_category(category),
    p_layout(new QHBoxLayout()),
    p_groupWidgetList(),
    p_categoryNameLineEdit(new QLineEdit(category != static_cast<Category*>(nullptr) ? category->name() : "")),
    p_addNewGroupButton(new QPushButton(tr("Add &group"))),
    p_noStorageLabel(new QLabel("<font color=\"red\">" + tr("This widget hasn't storage") + "</font>")),
    p_categoryWidget(new QGroupBox()),
    p_deleteCategoryButton(new QPushButton(tr("Delete category"))),
    p_categoryHeaderLayout(new QVBoxLayout())
{
    p_categoryHeaderLayout->addWidget(p_categoryNameLineEdit);
    p_categoryHeaderLayout->addWidget(p_deleteCategoryButton);
    p_layout->addLayout(p_categoryHeaderLayout);
    p_layout->addStretch(1);
    p_layout->addWidget(p_addNewGroupButton);
    if(p_category != static_cast<Category*>(nullptr)) {
    for(ptr<Group> group: *p_category) {
            populateNewGroupWidget(group);
        }
    }
    p_categoryWidget->setLayout(p_layout);
    p_noStorageLabel->setAlignment(Qt::AlignCenter);
    addWidget(p_noStorageLabel);
    addWidget(p_categoryWidget);
    setCurrentWidget(category == static_cast<Category*>(nullptr) ? static_cast<QWidget *>(p_noStorageLabel) : static_cast<QWidget *>(p_categoryWidget));
    QTimer::singleShot(0, this, SLOT(connectSignalsAndSlots()));
    QTimer::singleShot(0, this, SLOT(repopulateWidget()));
}

void GUI::CategoryWidget::setCategory(Wt::Dbo::ptr< Category > category) throw()
{
    if(p_category != category) {
        p_category = category;
        emit categoryChanged();
        if(p_category == static_cast<Category*>(nullptr))
            emit storageRemoved();
    }
}

const ptr<Category> GUI::CategoryWidget::category() const throw()
{
    return p_category;
}

ptr<Category> GUI::CategoryWidget::category() throw()
{
    return p_category;
}

void GUI::CategoryWidget::repopulateWidget() throw()
{
    if(p_category != static_cast<Category*>(nullptr)) {
    for(QPointer<GUI::GroupWidget> w: p_groupWidgetList) {
            p_layout->removeWidget(w);
            w->deleteLater();
        }
        p_groupWidgetList.clear();
        repopulateCategoryName();
        if(p_category != static_cast<Category*>(nullptr)) {
        for(ptr<Group> group: *p_category) {
                populateNewGroupWidget(group);
            }
        }
        setCurrentWidget(p_categoryWidget);
        resize(sizeHint());
    } else {
        setCurrentWidget(p_noStorageLabel);
    }
}

void GUI::CategoryWidget::connectSignalsAndSlots() throw()
{
    connect(this, SIGNAL(categoryChanged()), this, SLOT(repopulateWidget()));
    connect(this, SIGNAL(categoryChanged()), this, SLOT(connectSignalsForNewCategory()));
    connect(p_categoryNameLineEdit, SIGNAL(editingFinished()), this, SLOT(updateCategoryName()));
    connect(p_addNewGroupButton, SIGNAL(clicked(bool)), this, SLOT(addNewGroup()));
    connectSignalsForNewCategory();
}

void GUI::CategoryWidget::connectSignalsForNewCategory() throw()
{
    if(p_category != static_cast<Category*>(nullptr)) {
        connect(p_category.get(), SIGNAL(destroyed()), this, SIGNAL(storageRemoved()));
        connect(p_category.get(), SIGNAL(destroyed()), this, SLOT(repopulateWidget()));
        connect(p_category.get(), SIGNAL(groupInserted(Wt::Dbo::ptr<Group>)), this, SLOT(populateNewGroupWidget(Wt::Dbo::ptr<Group>)));
        connect(p_category.get(), SIGNAL(nameChanged()), this, SLOT(repopulateCategoryName()));
        connect(p_deleteCategoryButton, SIGNAL(clicked(bool)), p_category.get(), SLOT(deleteLater()));
    }
}

void GUI::CategoryWidget::updateCategoryName() throw()
{
    if(p_category != static_cast<Category*>(nullptr)) {
        p_category.modify()->setName(p_categoryNameLineEdit->text());
    }
}

void GUI::CategoryWidget::addNewGroup() throw()
{
    p_category.modify()->insertGroup(new Group());
}

void GUI::CategoryWidget::repopulateCategoryName() throw()
{
    p_categoryNameLineEdit->setText(p_category.get() ? p_category->name() : "");
}

void GUI::CategoryWidget::populateNewGroupWidget(Wt::Dbo::ptr<Group> group) throw()
{
    GroupWidget *groupWidget = new GroupWidget(group);
    p_groupWidgetList.push_back(groupWidget);
    p_layout->insertWidget(p_layout->count() - 2, p_groupWidgetList.back());
    connect(groupWidget, SIGNAL(storageRemoved()), groupWidget, SLOT(deleteLater()));
    connect(groupWidget, SIGNAL(destroyed(QObject *)), this, SLOT(resizeAfterGuiCleanup()));
}

void GUI::CategoryWidget::resizeAfterGuiCleanup() throw()
{
    resize(minimumSize());
}

#include "moc_categorywidget.cpp"