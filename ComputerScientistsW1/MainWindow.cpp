#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <Scientist.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    string fileLocation = "database.sqlite";
    this->dataMan = new DataManager(fileLocation);

    ui->setupUi(this);
    updateScientist();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_nameField_textChanged(const QString &arg1)
{
    updateScientist();
}

void MainWindow::on_sexComboBox_activated(const QString &arg1)
{
    updateScientist();
}

void MainWindow::on_yearOfBirthField_textChanged(const QString &arg1)
{
    updateScientist();
}

void MainWindow::on_yearOfDeathField_textChanged(const QString &arg1)
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

    ui->nameField->setText(name);
    //ui->sexComboBox->setAttribute();
    ui->yearOfBirthField->setText(birth);
    ui->yearOfDeathField->setText(death);
    ui->aboutField->setText(about);
}


ScientistSearch MainWindow::getScientistFromInput()
{
    ScientistSearch sciSearch;
    sciSearch.name = ui->nameField->text();
    sciSearch.setSex(ui->sexComboBox->currentText());
    sciSearch.birth = ui->yearOfBirthField->text();
    sciSearch.death = ui->yearOfDeathField->text();
    sciSearch.about = ui->aboutField->text();
    return sciSearch;
}

void MainWindow::updateScientist()
{
    ui->scientistTableView->setSortingEnabled(true);
    ui->scientistTableView->setModel(dataMan->search(getScientistFromInput()));
    ui->scientistTableView->resizeColumnsToContents();
}

void MainWindow::on_AddPushButton_released()
{
   dataMan->addScientist(getScientistFromInput());
    updateScientist();
}


