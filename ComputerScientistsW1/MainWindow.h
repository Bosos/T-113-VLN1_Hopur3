#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DataManager.h"
#include <SearchCriteria.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_scientistNameField_textChanged(const QString &arg1);
    void on_sexComboBox_activated(const QString &arg1);
    void on_yearOfBirthField_textChanged(const QString &arg1);
    void on_yearOfDeathField_textChanged(const QString &arg1);
    void on_addScientistPushButton_released();
    void on_scientistTableView_clicked(const QModelIndex &index);
    void on_clearScientistPushButton_released();
    void on_selectScientistPushButton_released();
    void on_selectedScientistOKPushButton_released();


private:
    Ui::MainWindow *ui;
    DataManager* dataMan;
    void updateScientist();
    ScientistSearch getScientistFromInput();

};

#endif // MAINWINDOW_H
