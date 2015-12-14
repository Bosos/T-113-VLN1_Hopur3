#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->windowSwitcher->setCurrentIndex(0);

    string fileLocation = "database.sqlite";
    this->serviceMan = new Service(fileLocation);

    ui->yearOfBirthField->setValidator(new QIntValidator(1000, 2015, this));
    ui->yearOfDeathField->setValidator(new QIntValidator(1000, 2015, this));
    ui->computerBuiltYearlineEdit->setValidator(new QIntValidator(1000, 2015, this));

    updateScientist();
    updateComputer();
    updateScientistUsers(0);
    updateComputerUsers(0);
    ui->scientistPicture->setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_scientistNameField_textEdited()
{
    updateScientist();
}

void MainWindow::on_sexComboBox_activated()
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

void MainWindow::on_scientistAboutField_textChanged()
{
    updateScientist();
}

void MainWindow::on_foundScientistTableView_clicked(const QModelIndex &index)
{
    // gerist eitthvað þegar það er bara smellt einusinni á reit?
}

void MainWindow::on_foundScientistTableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedID = index.sibling(row, 0).data().toInt();
    QString name = index.sibling(row,1).data().toString();
    QString sex = index.sibling(row,2).data().toString();
    QString birth = index.sibling(row,3).data().toString();
    QString death = index.sibling(row,4).data().toString();
    QString about = index.sibling(row,5).data().toString();

    int sexInt = 0;
    if (sex == "Female") { sexInt = 1; }
    else if (sex == "Male") { sexInt = 2; }

    ui->selectedScientistNameField->setText(name);
    ui->selectedScientistSexComboBox->setCurrentIndex(sexInt);
    ui->selectedScientistYearOfBirthField->setText(birth);
    ui->selectedScientistYearOfDeathField->setText(death);
    ui->selectedScientistAboutField->setPlainText(about);

    ui->selectedScientistComputerSearch->setHidden(true);
    ui->selectedScientistRemoAddButonWidget->setHidden(false);

    updateScientistProfilePicture();
    updateScinetistUsedComputers();
    ui->windowSwitcher->setCurrentIndex(1);
}

void MainWindow::on_editScientistpushButton_clicked()
{
    on_foundScientistTableView_doubleClicked (ui->foundScientistTableView->selectionModel()->currentIndex());
}

void MainWindow::on_selectedScientistAddComputer_released()
{
    ui->selectedScientistComputerSearch->setHidden(false);
    ui->selectedScientistRemoAddButonWidget->setHidden(true);
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
    ui->foundScientistTableView->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->search(getScientistFromInput()));
    ui->foundScientistTableView->setModel(sqlproxy);
    ui->foundScientistTableView->resizeColumnsToContents();
    ui->foundScientistTableView->horizontalHeader()->setStretchLastSection(true);
    ui->foundScientistTableView->setColumnHidden(0,true);
}

void MainWindow::updateScientistProfilePicture()
{
    QPixmap profilePicture = serviceMan->getScientistPicture(currentlySelectedID);

    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsView* view = new QGraphicsView(scene);
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(profilePicture);

    view->setDragMode(QGraphicsView::NoDrag);
    view->setEnabled(false);
    scene->addItem(item);

    ui->scientistPicture->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scientistPicture->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scientistPicture->setScene(scene);
    //ui->scientistPicture->fitInView(item,Qt::KeepAspectRatioByExpanding);

    ui->scientistPicture->show();
}

void MainWindow::updateScinetistUsedComputers()
{
    ui->selectedScientistComputerTable->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->searchComputerToScientist(currentlySelectedID));
    ui->selectedScientistComputerTable->setModel(sqlproxy);
    ui->selectedScientistComputerTable->resizeColumnsToContents();
    ui->selectedScientistComputerTable->horizontalHeader()->setStretchLastSection(true);
    ui->selectedScientistComputerTable->setColumnHidden(0, true);
}


void MainWindow::on_addScientistPushButton_released()
{
    serviceMan->addScientist(getScientistFromInput());
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

void MainWindow::on_computerSelectedAddScientist_released()
{
    ui->computerSelectedScientistSearch->setHidden(!ui->computerSelectedScientistSearch->isHidden());
}

void MainWindow::on_selectedScientistComputerSearchDoneButton_clicked()
{
    ui->selectedScientistComputerSearch->setHidden(true);
    ui->selectedScientistRemoAddButonWidget->setHidden(false);
}

void MainWindow::on_selectedScientistDeleteScientistPushButton_clicked()
{
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, "title", "Testing dialogs", QMessageBox::Yes|QMessageBox::No).exec())
    {
        qDebug() << "Scientist deleted";
        ui->windowSwitcher->setCurrentIndex(0);
        serviceMan->deleteScientist(currentlySelectedID);
        updateScientist();
    }

    int ret = QMessageBox::warning(this,"Deleting the selected scientist", "Are you sure you want to delete " "?", "DELETE","Cancel" );

    qDebug() << ret;
}

void MainWindow::on_scientistChangePictureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));

    serviceMan->storeScientistPicture(fileName, currentlySelectedID);
    updateScientistProfilePicture();
}

void MainWindow::on_selectedScientistOKPushButton_clicked()
{
    ScientistSearch scientistSearch;

    scientistSearch.name = ui->selectedScientistNameField->text();
    scientistSearch.setSex(ui->selectedScientistSexComboBox->currentText());
    scientistSearch.birth = ui->selectedScientistYearOfBirthField->text();
    scientistSearch.death = ui->selectedScientistYearOfDeathField->text();
    scientistSearch.about = ui->selectedScientistAboutField->toPlainText();

    serviceMan->updateScientistDatabase(scientistSearch, currentlySelectedID);
    updateScientist();
    ui->windowSwitcher->setCurrentIndex(0);
}

void MainWindow::on_computerSelectedOKPushButton_clicked()
{
    ui->windowSwitcher->setCurrentIndex(0);
    ComputerSearch computerSearch;
    computerSearch.name = ui->computerSelectedNameField->text();
    computerSearch.setType(ui->computerSelectedTypeComboBox->currentText());
    computerSearch.buildYear = ui->computerSelectedComputerBuiltYearlineEdit->text();
    computerSearch.setWasItBuilt(ui->computerSelectedWasItBuiltComboBox->currentText());
    computerSearch.about = ui->computerSelectedAboutField->toPlainText();

    serviceMan->updateComputerDatabase(computerSearch, currentlySelectedID);
    updateComputer();
}

void MainWindow::updateComputer()
{
    ui->foundComputersTableView->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->searchComputer(getComputerFromInput()));
    ui->foundComputersTableView->setModel(sqlproxy);
    ui->foundComputersTableView->resizeColumnsToContents();
    ui->foundComputersTableView->horizontalHeader()->setStretchLastSection(true);
    ui->foundComputersTableView->setColumnHidden(0, true);
}

ComputerSearch MainWindow::getComputerFromInput()
{
    ComputerSearch compSearch;
    compSearch.name = ui->computerNameLineEdit->text();
    compSearch.setType(ui->computerSearchTypeComboBox->currentText());
    qDebug() << "the type selected " << compSearch.getType();
    compSearch.buildYear = ui->computerBuiltYearlineEdit->text();
    compSearch.setWasItBuilt(ui->computerSearchWasItBuiltComboBox->currentText());
    compSearch.about = ui->computerAboutlineEdit->text();

    return compSearch;
}

void MainWindow::on_computerNameLineEdit_textEdited()
{
    updateComputer();
}

void MainWindow::on_computerBuiltYearlineEdit_textEdited()
{
    updateComputer();
}

void MainWindow::on_computerSearchTypeComboBox_activated()
{
    updateComputer();
}

void MainWindow::on_computerSearchWasItBuiltComboBox_activated()
{
    updateComputer();
}

void MainWindow::on_clearComputerPushButton_clicked()
{
    ui->computerNameLineEdit->setText("");
    ui->computerBuiltYearlineEdit->setText("");
    ui->computerSearchWasItBuiltComboBox->setCurrentIndex(0);
    ui->computerSearchTypeComboBox->setCurrentIndex(0);
    ui->computerAboutlineEdit->setText("");

    updateComputer();
}

void MainWindow::on_foundComputersTableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedID = index.sibling(row, 0).data().toInt();
    QString name = index.sibling(row,1).data().toString();
    QString type = index.sibling(row,2).data().toString();
    QString buildYear = index.sibling(row,3).data().toString();
    QString wasBuilt = index.sibling(row,4).data().toString();
    QString about = index.sibling(row,5).data().toString();

    updateScientistsWhoUsedComputer();

    int typeInt = 0;
    int builtInt = 0;
    if (type == "Electronic") { typeInt = 1; }
    else if (type == "Mecanic") { typeInt = 2; }
    else if (type == "Transistor") { typeInt = 3; }
    else if (type == "Electromechanical") { typeInt = 4; }
    if ( wasBuilt == "Yes") { builtInt = 1; }
    else if (wasBuilt == "No") { builtInt = 2; }

    ui->computerSelectedNameField->setText(name);
    ui->computerSelectedTypeComboBox->setCurrentIndex(typeInt);
    ui->computerSelectedComputerBuiltYearlineEdit->setText(buildYear);
    ui->computerSelectedWasItBuiltComboBox->setCurrentIndex(builtInt);
    ui->computerSelectedAboutField->setPlainText(about);

    ui->computerSelectedScientistSearch->setHidden(true);
    ui->computerSelectedRemoAddButonWidget->setHidden(false);

    ui->windowSwitcher->setCurrentIndex(2);
}

void MainWindow::on_addComputerPushButton_released()
{
    serviceMan->addComputer(getComputerFromInput());
    updateComputer();
}

void MainWindow::on_computerSelectedDeleteComputerPushButton_released()
{
    ui->windowSwitcher->setCurrentIndex(0);
    serviceMan->deleteComputer(currentlySelectedID);
    updateComputer();
}

void MainWindow::updateScientistsWhoUsedComputer()
{
    ui->computerSelectedScientistTable->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->searchScientistToComputer(currentlySelectedID));
    ui->computerSelectedScientistTable->setModel(sqlproxy);
    ui->computerSelectedScientistTable->resizeColumnsToContents();
    ui->computerSelectedScientistTable->horizontalHeader()->setStretchLastSection(true);
    ui->computerSelectedScientistTable->setColumnHidden(0, true);
}

void MainWindow::on_registeredScientists_clicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedUserID = index.sibling(row, 0).data().toInt();

    updateComputerUsers(currentlySelectedUserID);
}

void MainWindow::updateComputerUsers(int id)
{
    ui->registeredComputers->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);

    if(id != 0)
    {
        sqlproxy->setSourceModel(serviceMan->searchComputerToScientist(id));
    }
    else
    {
        ComputerSearch comp;
        comp.name = "";
        comp.setType("");
        comp.setWasItBuilt("");
        comp.buildYear = "";
        comp.about = "";

        sqlproxy->setSourceModel(serviceMan->searchComputer(comp));
    }

    ui->registeredComputers->setModel(sqlproxy);
    ui->registeredComputers->resizeColumnsToContents();
    ui->registeredComputers->setColumnHidden(0, true);
    ui->registeredComputers->setColumnHidden(2, true);
    ui->registeredComputers->setColumnHidden(4, true);
    ui->registeredComputers->setColumnHidden(5, true);
}

void MainWindow::on_pushButton_released()
{
    updateComputerUsers(0);
    updateScientistUsers(0);
    currentlySelectedUserID = 0;
}

void MainWindow::on_registeredComputers_clicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedUserID = index.sibling(row, 0).data().toInt();

    updateScientistUsers(currentlySelectedUserID);
}

void MainWindow::updateScientistUsers(int id)
{
    ui->registeredScientists->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);

    if(id != 0)
    {
        sqlproxy->setSourceModel(serviceMan->searchScientistToComputer(id));
    }
    else
    {
        ScientistSearch scientist;
        scientist.name = "";
        scientist.setSex("");
        scientist.birth = "";
        scientist.death = "";
        scientist.about = "";

        sqlproxy->setSourceModel(serviceMan->search(scientist));
    }

    ui->registeredScientists->setModel(sqlproxy);
    ui->registeredScientists->resizeColumnsToContents();
    ui->registeredScientists->setColumnHidden(0, true);
    ui->registeredScientists->setColumnHidden(2, true);
    ui->registeredScientists->setColumnHidden(4, true);
    ui->registeredScientists->setColumnHidden(5, true);
}

void MainWindow::on_headTab_tabBarClicked(int index)
{
    currentlySelectedUserID = 0;
    updateScientistUsers(0);
    updateComputerUsers(0);
}

