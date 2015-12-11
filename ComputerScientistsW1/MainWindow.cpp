#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->windowSwitcher->setCurrentIndex(0);

    string fileLocation = "database.sqlite";
    this->dataMan = new DataManager(fileLocation);

    updateScientist();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scientistNameField_textEdited()
{
    updateScientist();
}

void MainWindow::on_sexComboBox_activated(const QString &arg1)
{
    updateScientist();
}

void MainWindow::on_yearOfBirthField_textEdited()
{
    updateScientist();
}

void MainWindow::on_yearOfDeathField_textEdited()
{
    updateScientist();
}

void MainWindow::on_scientistTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QString name = index.sibling(row,0).data().toString();
    QString sex = index.sibling(row,1).data().toString();
    QString birth = index.sibling(row,2).data().toString();
    QString death = index.sibling(row,3).data().toString();
    QString about = index.sibling(row,4).data().toString();
    int sexInt = 0;
    if (sex == "F") { sexInt = 1; }
    else if (sex == "M") { sexInt = 2; }

    ui->selectedScientistNameField->setText(name);
    ui->selectedScientistSexComboBox->setCurrentIndex(sexInt);
    ui->selectedScientistYearOfBirthField->setText(birth);
    ui->selectedScientistYearOfDeathField->setText(death);
    ui->selectedScientistAboutField->setPlainText(about);

    ui->selectedScientistComputerSearch->setHidden(true);
    ui->windowSwitcher->setCurrentIndex(1);
}
void MainWindow::on_selectedScientistAddComputer_released()
{
    ui->selectedScientistComputerSearch->setHidden(!ui->selectedScientistComputerSearch->isHidden());
}


ScientistSearch MainWindow::getScientistFromInput()
{
    ScientistSearch sciSearch;
    sciSearch.name = ui->scientistNameField->text();
    sciSearch.setSex(ui->sexComboBox->currentText());
    sciSearch.birth = ui->yearOfBirthField->text();
    sciSearch.death = ui->yearOfDeathField->text();
    sciSearch.about = ui->scientistAboutField->text();
    return sciSearch;
}

void MainWindow::updateScientist()
{
    ui->scientistTableView->setSortingEnabled(true);
    ui->scientistTableView->setModel(dataMan->search(getScientistFromInput()));
    ui->scientistTableView->resizeColumnsToContents();
}

void MainWindow::on_addScientistPushButton_released()
{
   dataMan->addScientist(getScientistFromInput());
    updateScientist();
}

void MainWindow::on_clearScientistPushButton_released()
{
    ui->scientistNameField->setText("");
    ui->sexComboBox->setCurrentIndex(0);
    ui->yearOfBirthField->setText("");
    ui->yearOfDeathField->setText("");
    ui->scientistAboutField->setText("");
}

void MainWindow::on_selectedScientistOKPushButton_released()
{
    ui->windowSwitcher->setCurrentIndex(0);
}
