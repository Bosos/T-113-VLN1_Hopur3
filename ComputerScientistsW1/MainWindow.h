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
    void on_scientistAboutField_textChanged();
    void on_addScientistPushButton_released();
    void on_foundScientistTableView_clicked(const QModelIndex &index);
    void on_clearScientistPushButton_released();
    void on_selectedScientistOKPushButton_released();
    void on_selectedScientistAddComputer_released();
    void on_selectedScientistDeleteScientistPushButton_clicked();
    void on_selectedScientistComputerSearchDoneButton_clicked();
    void on_scientistChangePictureButton_clicked();
    void on_computerSelectedAddScientist_released();
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



    void on_computerSelectedDeleteComputerPushButton_released();

    void on_registeredScientists_clicked(const QModelIndex &index);

    void on_pushButton_released();

    void on_registeredComputers_clicked(const QModelIndex &index);

    void on_headTab_tabBarClicked(int index);

private:
    Ui::MainWindow *ui;
    DataManager* dataMan;
    int currentlySelectedID;
    void updateScientist();
    void updateScientistProfilePicture();
    ScientistSearch getScientistFromInput();

    void updateComputer();
    ComputerSearch getComputerFromInput();
    void updateScientistsWhoUsedComputer();
    void searchScientistsToComputer(int id);

    void updateScientistUsers(int id);
    void updateComputerUsers(int id);
    int currentlySelectedUserID;

};

#endif // MAINWINDOW_H
