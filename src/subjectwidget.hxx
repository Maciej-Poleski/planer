/* Maciej Poleski (C) 2012 */

#ifndef SUBJECTWIDGET_HXX
#define SUBJECTWIDGET_HXX

#include <QtGui/QStackedWidget>

#include <vector>

#include <Wt/Dbo/Dbo>

#include "subject.hxx"
#include "categorywidget.hxx"

namespace GUI
{

class SubjectWidget : public QStackedWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SubjectWidget)
public:
    explicit SubjectWidget(Wt::Dbo::ptr<Subject> subject = static_cast<Subject*>(nullptr), QWidget *parent = 0) throw();

    const Wt::Dbo::ptr<Subject> subject() const throw();
    Wt::Dbo::ptr<Subject> subject() throw();

signals:
    void subjectChanged();
    void storageRemoved();

public slots:
    void setSubject(Wt::Dbo::ptr<Subject> subject) throw();
    void addNewCategory() throw();

private slots:
    /**
     * @brief Przerysowuje widget
     *
     **/
    void repopulateWidget() throw();
    void connectSignalsAndSlots() throw();
    void updateSubjectName() throw();
    void connectSignalsForNewSubject() throw();
    void repopulateSubjectName() throw();
    void resizeAfterGuiCleanup() throw();
    void populateNewCategoryWidget(Wt::Dbo::ptr<Category> category) throw();

private:
    Wt::Dbo::ptr<Subject>  p_subject;

    QVBoxLayout *p_layout;
    std::vector<QPointer<CategoryWidget>> p_categoryWidgetList;
    QLineEdit *p_subjectNameLineEdit;
    QPushButton *p_addNewCategoryButton;
    QLabel *p_noStorageLabel;
    QGroupBox *p_subjectWidget;
    QPushButton *p_deleteSubjectButton;
    QHBoxLayout *p_subjectHeaderLayout;
};

}


#endif // SUBJECTWIDGET_HXX
