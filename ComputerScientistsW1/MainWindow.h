#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include "DataManager.h"
#include <SearchCriteria.h>
#include <Scientist.h>

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
    void on_scientistNameField_textEdited();
    void on_sexComboBox_activated(const QString &arg1);
    void on_yearOfBirthField_textEdited();
    void on_yearOfDeathField_textEdited();
    void on_addScientistPushButton_released();
    void on_scientistTableView_clicked(const QModelIndex &index);
    void on_clearScientistPushButton_released();
    void on_selectedScientistOKPushButton_released();
    void on_selectedScientistAddComputer_released();

private:
    Ui::MainWindow *ui;
    DataManager* dataMan;
    void updateScientist();
    ScientistSearch getScientistFromInput();

};

#endif // MAINWINDOW_H
