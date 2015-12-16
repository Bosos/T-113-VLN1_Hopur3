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
    void on_addComputerPushButton_clicked();
    void on_addScientistPushButton_clicked();
    void on_clearComputerPushButton_clicked();
    void on_clearScientistPushButton_clicked();
    void on_computerAboutlineEdit_textChanged();
    void on_computerBuiltYearlineEdit_textEdited();
    void on_computerNameLineEdit_textEdited();
    void on_computerSearchTypeComboBox_activated();
    void on_computerSearchWasItBuiltComboBox_activated();
    void on_computerSelectedAddScientist_clicked();
    void on_computerSelectedCancelPushButton_clicked();
    void on_computerSelectedChangePicturePushButton_clicked();
    void on_computerSelectedDeleteComputerPushButton_clicked();
    void on_computerSelectedOKPushButton_clicked();
    void on_computerSelectedScientistSearchAddPushButton_clicked();
    void on_computerSelectedScientistSearchDoneButton_clicked();
    void on_computerSelectedScientistSearchNameField_textChanged();
    void on_computerSelectedScientistSearchsexComboBox_currentIndexChanged();
    void on_computerSelectedScientistSearchTableView_clicked(const QModelIndex &index);
    void on_computerSelectedScientistSearchTableView_doubleClicked();
    void on_computerSelectedScientistSearchyearOfBirthField_textChanged();
    void on_computerSelectedScientistSearchyearOfDeathField_textChanged();
    void on_computerSelectedScientistSelectedRemoveSelectedButton_clicked();
    void on_computerSelectedScientistTable_clicked(const QModelIndex &index);
    void on_computerSelectedScientistTable_doubleClicked(const QModelIndex &index);
    void on_editScientistpushButton_clicked();
    void on_editSelectedComputerPushButton_clicked();
    void on_foundComputersTableView_doubleClicked(const QModelIndex &index);
    void on_foundComputersTableView_pressed();
    void on_foundScientistTableView_doubleClicked(const QModelIndex &index);
    void on_foundScientistTableView_pressed();
    void on_scientistAboutField_textChanged();
    void on_scientistChangeCancelpushButton_clicked();
    void on_scientistChangePictureButton_clicked();
    void on_scientistNameField_textEdited();
    void on_selectedScientistAddComputer_clicked();
    void on_selectedScientistComputerSearcAddpushButton_clicked();
    void on_selectedScientistComputerSearchBuiltYearField_textEdited();
    void on_selectedScientistComputerSearchDoneButton_clicked();
    void on_selectedScientistComputerSearchNameField_textChanged();
    void on_selectedScientistComputerSearchTableView_clicked(const QModelIndex &index);
    void on_selectedScientistComputerSearchTableView_doubleClicked();
    void on_selectedScientistComputerSearchTypeComboBox_currentIndexChanged();
    void on_selectedScientistComputerSearchWasItBuiltComboBox_currentIndexChanged();
    void on_selectedScientistComputerTable_clicked(const QModelIndex &index);
    void on_selectedScientistComputerTable_doubleClicked(const QModelIndex &index);
    void on_selectedScientistDeleteScientistPushButton_clicked();
    void on_selectedScientistOKPushButton_clicked();
    void on_selectedScientistRemoveSelectedComputerPushButton_clicked();
    void on_sexComboBox_activated();
    void on_yearOfBirthField_textEdited();
    void on_yearOfDeathField_textEdited();

private:
    Ui::MainWindow *ui;
    Service* serviceMan;
    int currentlySelectedUserID = 1;
    int currentlySelectedComputerID = 1;
    void searchScientistsToComputer(int id);
    int setWidth(int width);

    void updateScientist();
    void updateScientistProfilePicture();
    void updateScinetistUsedComputers();
    void updateSelectedScientistComputerSearchTableView();
    ScientistSearch getScientistFromInput();
    ComputerSearch getComputerFromScientistAddComputerInput();

    void updateComputer();
    void updateComputerProfilePicture();
    void updateScientistsWhoUsedComputer();
    void updateSelectedComputerScientistSearchTableView();
    ComputerSearch getComputerFromInput();
    ScientistSearch getScientistFromComputerAddScientistInput();
};

#endif // MAINWINDOW_H
