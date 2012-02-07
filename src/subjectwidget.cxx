/* Maciej Poleski (C) 2012 */

#include "subjectwidget.hxx"

#include <utility>

#include <QtCore/QTimer>
#include <QtCore/QString>

#include <QtGui/QVBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QGroupBox>
#include <QtGui/QLabel>

#include "category.hxx"
#include "group.hxx"
#include "slot.hxx"

using namespace Wt::Dbo;

GUI::SubjectWidget::SubjectWidget(ptr<Subject> subject, QWidget *parent) throw():
    QStackedWidget(parent),
    p_subject(subject),
    p_layout(new QVBoxLayout()),
    p_categoryWidgetList(),
    p_subjectNameLineEdit(new QLineEdit(subject != static_cast<Subject*>(nullptr) ? subject->name() : "")),
    p_addNewCategoryButton(new QPushButton(tr("Add &category"))),
    p_noStorageLabel(new QLabel("<font color=\"red\">" + tr("This widget hasn't storage") + "</font>")),
    p_subjectWidget(new QGroupBox()),
    p_deleteSubjectButton(new QPushButton(tr("Delete subject"))),
    p_subjectHeaderLayout(new QHBoxLayout())
{
    p_subjectHeaderLayout->addWidget(p_subjectNameLineEdit);
    p_subjectHeaderLayout->addWidget(p_deleteSubjectButton);
    p_layout->addLayout(p_subjectHeaderLayout);
    p_layout->addStretch(1);
    p_layout->addWidget(p_addNewCategoryButton);
    if(p_subject != static_cast<Subject*>(nullptr)) {
    for(ptr<Category> category: *p_subject) {
            populateNewCategoryWidget(category);
        }
    }
    p_subjectWidget->setLayout(p_layout);
    p_noStorageLabel->setAlignment(Qt::AlignCenter);
    addWidget(p_noStorageLabel);
    addWidget(p_subjectWidget);
    setCurrentWidget(subject == static_cast<Subject*>(nullptr) ? static_cast<QWidget *>(p_noStorageLabel) : static_cast<QWidget *>(p_subjectWidget));
    QTimer::singleShot(0, this, SLOT(connectSignalsAndSlots()));
    QTimer::singleShot(0, this, SLOT(repopulateWidget()));
}

void GUI::SubjectWidget::setSubject(ptr<Subject> subject) throw()
{
    if(p_subject != subject) {
        p_subject = subject;
        emit subjectChanged();
        if(p_subject == static_cast<Subject*>(nullptr))
            emit storageRemoved();
    }
}

const ptr<Subject> GUI::SubjectWidget::subject() const throw()
{
    return p_subject;
}

ptr<Subject> GUI::SubjectWidget::subject() throw()
{
    return p_subject;
}

void GUI::SubjectWidget::repopulateWidget() throw()
{
    if(p_subject != static_cast<Subject*>(nullptr)) {
    for(CategoryWidget * w: p_categoryWidgetList) {
            p_layout->removeWidget(w);
            w->deleteLater();
        }
        p_categoryWidgetList.clear();
        repopulateSubjectName();
        if(p_subject != static_cast<Subject*>(nullptr)) {
        for(ptr<Category> category: *p_subject) {
                populateNewCategoryWidget(category);
            }
        }
        setCurrentWidget(p_subjectWidget);
        resize(sizeHint());
    } else {
        setCurrentWidget(p_noStorageLabel);
    }
}

void GUI::SubjectWidget::connectSignalsAndSlots() throw()
{
    connect(this, SIGNAL(subjectChanged()), this, SLOT(repopulateWidget()));
    connect(this, SIGNAL(subjectChanged()), this, SLOT(connectSignalsForNewSubject()));
    connect(p_subjectNameLineEdit, SIGNAL(editingFinished()), this, SLOT(updateSubjectName()));
    connect(p_addNewCategoryButton, SIGNAL(clicked(bool)), this, SLOT(addNewCategory()));
    connectSignalsForNewSubject();
}

void GUI::SubjectWidget::connectSignalsForNewSubject() throw()
{
    if(p_subject != static_cast<Subject*>(nullptr)) {
        connect(p_subject.get(), SIGNAL(destroyed()), this, SIGNAL(storageRemoved()));
        connect(p_subject.get(), SIGNAL(destroyed()), this, SLOT(repopulateWidget()));
        connect(p_subject.get(), SIGNAL(categoryInserted(Wt::Dbo::ptr<Category>)), this, SLOT(populateNewCategoryWidget(Wt::Dbo::ptr<Category>)));
        connect(p_subject.get(), SIGNAL(nameChanged()), this, SLOT(repopulateSubjectName()));
        connect(p_deleteSubjectButton, SIGNAL(clicked(bool)), p_subject.get(), SLOT(deleteLater()));
    }
}

void GUI::SubjectWidget::updateSubjectName() throw()
{
    if(p_subject != static_cast<Subject*>(nullptr)) {
        p_subject.modify()->setName(p_subjectNameLineEdit->text());
    }
}

void GUI::SubjectWidget::addNewCategory() throw()
{
    p_subject.modify()->insertCategory(new Category());
}

void GUI::SubjectWidget::repopulateSubjectName() throw()
{
    p_subjectNameLineEdit->setText(p_subject ? p_subject->name() : "");
}

void GUI::SubjectWidget::populateNewCategoryWidget(ptr<Category> category) throw()
{
    CategoryWidget *categoryWidget = new CategoryWidget(category);
    p_categoryWidgetList.push_back(categoryWidget);
    p_layout->insertWidget(p_layout->count() - 2, p_categoryWidgetList.back());
    connect(categoryWidget, SIGNAL(storageRemoved()), categoryWidget, SLOT(deleteLater()));
    connect(categoryWidget, SIGNAL(destroyed(QObject *)), this, SLOT(resizeAfterGuiCleanup()));
}

void GUI::SubjectWidget::resizeAfterGuiCleanup() throw()
{
    resize(minimumSize());
}

#include "moc_subjectwidget.cpp"
