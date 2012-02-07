/* Maciej Poleski (C) 2012 */

#ifndef CATEGORYWIDGET_HXX
#define CATEGORYWIDGET_HXX

#include <QtGui/QStackedWidget>

#include <vector>

#include <QtCore/QPointer>

#include <Wt/Dbo/Dbo>

class QHBoxLayout;
class QLineEdit;
class QPushButton;
class QLabel;
class QVBoxLayout;
class QGroupBox;

class Category;
class Group;

namespace GUI
{
class GroupWidget;

class CategoryWidget : public QStackedWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(CategoryWidget)
public:
    explicit CategoryWidget(Wt::Dbo::ptr<Category> category = static_cast<Category *>(nullptr), QWidget *parent = 0) throw();

    const Wt::Dbo::ptr<Category> category() const throw();
    Wt::Dbo::ptr<Category> category() throw();

signals:
    void categoryChanged();
    void storageRemoved();

public slots:
    void setCategory(Wt::Dbo::ptr<Category> category) throw();
    void addNewGroup() throw();

private slots:
    /**
     * @brief Przerysowuje widget
     *
     **/
    void repopulateWidget() throw();
    void connectSignalsAndSlots() throw();
    void updateCategoryName() throw();
    void connectSignalsForNewCategory() throw();
    void repopulateCategoryName() throw();
    void resizeAfterGuiCleanup() throw();
    void populateNewGroupWidget(Wt::Dbo::ptr<Group> group) throw();

private:
    Wt::Dbo::ptr<Category> p_category;

    QHBoxLayout *p_layout;
    std::vector<QPointer<GUI::GroupWidget>> p_groupWidgetList;
    QLineEdit *p_categoryNameLineEdit;
    QPushButton *p_addNewGroupButton;
    QLabel *p_noStorageLabel;
    QGroupBox *p_categoryWidget;
    QPushButton *p_deleteCategoryButton;
    QVBoxLayout *p_categoryHeaderLayout;
};

}

#endif // CATEGORYWIDGET_HXX
