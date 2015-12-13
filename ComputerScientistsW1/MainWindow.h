#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include "DataManager.h"
#include <SearchCriteria.h>
#include <Scientist.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsPixmapItem>

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
    void on_sexComboBox_activated();
    void on_yearOfBirthField_textEdited();
    void on_yearOfDeathField_textEdited();
    void on_addScientistPushButton_released();
    void on_foundScientistTableView_clicked(const QModelIndex &index);
    void on_clearScientistPushButton_released();
    void on_selectedScientistOKPushButton_released();
    void on_selectedScientistAddComputer_released();
    void on_computerSelectedAddScientist_released();
    void on_selectedScientistDeleteScientistPushButton_clicked();
    void on_scientistChangePictureButton_clicked();
    void on_selectedScientistComputerSearchDoneButton_clicked();
    void on_computerSelectedOKPushButton_clicked();
    void on_foundScientistTableView_doubleClicked(const QModelIndex &index);
    void on_editScientistpushButton_clicked();

    void on_computerNameLineEdit_textEdited();

    void on_computerBuiltYearlineEdit_textEdited();

    void on_computerSearchTypeComboBox_activated();

    void on_computerSearchWasItBuiltComboBox_activated();

    void on_clearComputerPushButton_clicked();

    void on_foundComputersTableView_doubleClicked(const QModelIndex &index);

    void on_addComputerPushButton_released();


private:
    Ui::MainWindow *ui;
    DataManager* dataMan;
    int currentlySelectedID;
    void updateScientist();
    void updateScientistProfilePicture();
    ScientistSearch getScientistFromInput();

    void updateComputer();
    ComputerSearch getComputerFromInput();


};

#endif // MAINWINDOW_H
