#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include <QMainWindow>
#include <SearchCriteria.h>
#include <Scientist.h>
#include <QMessageBox>
#include <QFileDialog>
#include <QGraphicsPixmapItem>
#include "service.h"

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
    void on_addScientistPushButton_clicked();
    void on_foundScientistTableView_clicked(const QModelIndex &index);
    void on_clearScientistPushButton_clicked();
    void on_selectedScientistAddComputer_clicked();
    void on_selectedScientistDeleteScientistPushButton_clicked();
    void on_selectedScientistComputerSearchDoneButton_clicked();
    void on_scientistChangePictureButton_clicked();
    void on_computerSelectedAddScientist_clicked();
    void on_computerSelectedOKPushButton_clicked();
    void on_foundScientistTableView_doubleClicked(const QModelIndex &index);
    void on_editScientistpushButton_clicked();
    void on_computerNameLineEdit_textEdited();
    void on_computerBuiltYearlineEdit_textEdited();
    void on_computerSearchTypeComboBox_activated();
    void on_computerSearchWasItBuiltComboBox_activated();
    void on_clearComputerPushButton_clicked();
    void on_foundComputersTableView_doubleClicked(const QModelIndex &index);
    void on_addComputerPushButton_clicked();
    void on_computerSelectedDeleteComputerPushButton_clicked();

    void on_selectedScientistOKPushButton_clicked();

    void on_selectedScientistComputerSearchNameField_textChanged();

    void on_selectedScientistComputerSearchBuiltYearField_textEdited();

    void on_selectedScientistComputerSearchTypeComboBox_currentIndexChanged();

    void on_selectedScientistComputerSearcAddpushButton_clicked();

    void on_selectedScientistComputerSearchTableView_clicked(const QModelIndex &index);

    void on_selectedScientistComputerTable_clicked(const QModelIndex &index);

    void on_selectedScientistRemoveSelectedComputerPushButton_clicked();

    void on_selectedScientistComputerSearchWasItBuiltComboBox_currentIndexChanged();

    void on_foundComputersTableView_clicked(const QModelIndex &index);

    void on_computerSelectedChangePicturePushButton_clicked();

    void on_selectedScientistComputerSearchTableView_doubleClicked(const QModelIndex &index);

    void on_selectedScientistComputerTable_doubleClicked(const QModelIndex &index);

    void on_computerSelectedScientistSearchNameField_textChanged(const QString &arg1);

    void on_computerSelectedScientistSearchsexComboBox_currentIndexChanged(const QString &arg1);

    void on_computerSelectedScientistSearchyearOfBirthField_textChanged(const QString &arg1);

    void on_computerSelectedScientistSearchyearOfDeathField_textChanged(const QString &arg1);

    void on_computerSelectedScientistSearchAddPushButton_clicked();

    void on_computerSelectedScientistSearchTableView_clicked(const QModelIndex &index);

    void on_computerSelectedScientistSearchDoneButton_clicked();

    void on_computerSelectedScientistTable_clicked(const QModelIndex &index);

    void on_computerSelectedScientistSelectedRemoveSelectedButton_clicked();


    void on_editSelectedComputerPushButton_clicked();

    void on_computerAboutlineEdit_textChanged();

private:
    Ui::MainWindow *ui;
    Service* serviceMan;
    int currentlySelectedUserID = 1;
    int currentlySelectedComputerID = 1;
    void updateScientist();
    void updateScientistProfilePicture();
    void updateScinetistUsedComputers();
    void updateSelectedScientistComputerSearchTableView();
    ScientistSearch getScientistFromInput();
    ComputerSearch getComputerFromScientistAddComputerInput();


    void updateComputer();
    ComputerSearch getComputerFromInput();
    void updateScientistsWhoUsedComputer();
    void searchScientistsToComputer(int id);
    void updateComputerProfilePicture();
    //void updateScientistUsers(int id);
    //void updateComputerUsers(int id);
    int currentlySelectedUserIDForUsers;

    void updateSelectedComputerScientistSearchTableView();
    ScientistSearch getScientistFromComputerAddScientistInput();

    int setWidth(int width);
};

#endif // MAINWINDOW_H
