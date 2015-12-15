#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->windowSwitcher->setCurrentIndex(0);
    ui->editScientistpushButton->setDisabled(true);
    ui->editSelectedComputerPushButton->setDisabled(true);

    string fileLocation = "database.sqlite";
    this->serviceMan = new Service(fileLocation);

    ui->yearOfBirthField->setValidator(new QIntValidator(1000, 2015, this));
    ui->yearOfDeathField->setValidator(new QIntValidator(1000, 2015, this));
    ui->computerBuiltYearlineEdit->setValidator(new QIntValidator(1000, 2015, this));

    updateScientist();
    updateComputer();
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
    ui->editScientistpushButton->setDisabled(false);
}

void MainWindow::on_foundScientistTableView_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedUserID = index.sibling(row, 0).data().toInt();
    currentlySelectedComputerID = 0;
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
    ui->splitter_4->setSizes({250,5000});

    updateScientistProfilePicture();
    updateScinetistUsedComputers();
    ui->windowSwitcher->setCurrentIndex(1);
}

void MainWindow::on_editScientistpushButton_clicked()
{
    on_foundScientistTableView_doubleClicked (ui->foundScientistTableView->selectionModel()->currentIndex());
}

void MainWindow::on_selectedScientistAddComputer_clicked()
{
    ui->selectedScientistComputerSearch->setHidden(false);
    ui->selectedScientistRemoAddButonWidget->setHidden(true);
    updateSelectedScientistComputerSearchTableView();
    ui->selectedScientistComputerSearchNameField->setFocus();
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
    QPixmap profilePicture = serviceMan->getScientistPicture(currentlySelectedUserID);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(profilePicture);

    scene->addItem(item);

    ui->scientistPicture->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scientistPicture->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scientistPicture->setScene(scene);
    ui->scientistPicture->setFixedWidth(setWidth(profilePicture.width()));
    ui->scientistPicture->show();
}

void MainWindow::updateComputerProfilePicture()
{
    QPixmap profilePicture = serviceMan->getComputerPicture(currentlySelectedComputerID);
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(profilePicture);

    scene->addItem(item);

    ui->computerSelectedPicture->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->computerSelectedPicture->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->computerSelectedPicture->setScene(scene);
    ui->computerSelectedPicture->setFixedWidth(setWidth(profilePicture.width()));
    ui->computerSelectedPicture->show();
}

void MainWindow::updateScinetistUsedComputers()
{
    ui->selectedScientistComputerTable->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->searchComputerToScientist(currentlySelectedUserID));
    ui->selectedScientistComputerTable->setModel(sqlproxy);
    ui->selectedScientistComputerTable->resizeColumnsToContents();
    ui->selectedScientistComputerTable->horizontalHeader()->setStretchLastSection(true);
    ui->selectedScientistComputerTable->setColumnHidden(0, true);
}

void MainWindow::updateSelectedScientistComputerSearchTableView()
{
    ui->selectedScientistComputerSearchTableView->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->searchComputer(getComputerFromScientistAddComputerInput()));
    ui->selectedScientistComputerSearchTableView->setModel(sqlproxy);
    ui->selectedScientistComputerSearchTableView->resizeColumnsToContents();
    ui->selectedScientistComputerSearchTableView->horizontalHeader()->setStretchLastSection(true);
    ui->selectedScientistComputerSearchTableView->setColumnHidden(0, true);
}

void MainWindow::on_clearScientistPushButton_clicked()
{
    ui->scientistNameField->setText("");
    ui->sexComboBox->setCurrentIndex(0);
    ui->yearOfBirthField->setText("");
    ui->yearOfDeathField->setText("");
    ui->scientistAboutField->setText("");

    updateScientist();
}

void MainWindow::on_computerSelectedAddScientist_clicked()
{
    ui->computerSelectedScientistSearch->setHidden(false);
    ui->computerSelectedRemoAddButonWidget->setHidden(true);
    updateSelectedComputerScientistSearchTableView();
}

void MainWindow::on_selectedScientistComputerSearchDoneButton_clicked()
{
    ui->selectedScientistComputerSearch->setHidden(true);
    ui->selectedScientistRemoAddButonWidget->setHidden(false);
}

void MainWindow::on_selectedScientistDeleteScientistPushButton_clicked()
{
    int ret = QMessageBox::warning(this,"Deleting the selected scientist", "Are you sure you want to delete " "?", "DELETE","Cancel" );
    if (ret) { return; }
    qDebug() << "Scientist deleted";
    ui->windowSwitcher->setCurrentIndex(0);
    serviceMan->deleteScientist(currentlySelectedUserID);
    updateScientist();
    qDebug() << ret;
}

void MainWindow::on_scientistChangePictureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));

    serviceMan->storeScientistPicture(fileName, currentlySelectedUserID);
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

    serviceMan->updateScientistDatabase(scientistSearch, currentlySelectedUserID);
    updateScientist();
    ui->editScientistpushButton->setDisabled(true);
    ui->windowSwitcher->setCurrentIndex(0);
}

void MainWindow::on_computerSelectedOKPushButton_clicked()
{
    ComputerSearch computerSearch;

    computerSearch.name = ui->computerSelectedNameField->text();
    computerSearch.setType(ui->computerSelectedTypeComboBox->currentIndex());
    computerSearch.buildYear = ui->computerSelectedComputerBuiltYearlineEdit->text();
    computerSearch.setWasItBuilt(ui->computerSelectedWasItBuiltComboBox->currentIndex());
    computerSearch.about = ui->computerSelectedAboutField->toPlainText();

    serviceMan->updateComputerDatabase(computerSearch, currentlySelectedComputerID);
    updateComputer();
    ui->editSelectedComputerPushButton->setDisabled(true);
    ui->windowSwitcher->setCurrentIndex(0);
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
    ComputerSearch computerSearch;
    computerSearch.name = ui->computerNameLineEdit->text();
    computerSearch.setType(ui->computerSearchTypeComboBox->currentIndex());
    computerSearch.buildYear = ui->computerBuiltYearlineEdit->text();
    computerSearch.setWasItBuilt(ui->computerSearchWasItBuiltComboBox->currentIndex());
    computerSearch.about = ui->computerAboutlineEdit->text();
    return computerSearch;
}

ComputerSearch MainWindow::getComputerFromScientistAddComputerInput()
{
    ComputerSearch computerSearch;
    computerSearch.name = ui->selectedScientistComputerSearchNameField->text();
    computerSearch.setType(ui->selectedScientistComputerSearchTypeComboBox->currentIndex());
    computerSearch.buildYear = ui->selectedScientistComputerSearchBuiltYearField->text();
    computerSearch.setWasItBuilt(ui->selectedScientistComputerSearchWasItBuiltComboBox->currentIndex());
    computerSearch.about = ui->computerAboutlineEdit->text();

    return computerSearch;
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

void MainWindow::on_computerAboutlineEdit_textChanged()
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
    currentlySelectedComputerID = index.sibling(row, 0).data().toInt();
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
    else if (type == "Other") { typeInt = 5; }
    if ( wasBuilt == "Built") { builtInt = 1; }
    else if (wasBuilt == "Not built") { builtInt = 2; }

    ui->computerSelectedNameField->setText(name);
    ui->computerSelectedTypeComboBox->setCurrentIndex(typeInt);
    ui->computerSelectedComputerBuiltYearlineEdit->setText(buildYear);
    ui->computerSelectedWasItBuiltComboBox->setCurrentIndex(builtInt);
    ui->computerSelectedAboutField->setPlainText(about);

    ui->computerSelectedScientistSearch->setHidden(true);
    ui->computerSelectedRemoAddButonWidget->setHidden(false);

    updateComputerProfilePicture();
    ui->splitter_3->setSizes({250,5000});

    ui->windowSwitcher->setCurrentIndex(2);
}

void MainWindow::on_addScientistPushButton_clicked()
{
    ScientistSearch sci = getScientistFromInput();
    vector<QString> errMessages= serviceMan->scientistExists(sci);
    if(errMessages.size() > 0)
    {
        QString completeMessage;
        while(errMessages.size() > 0)
        {
            completeMessage += " " + errMessages.back() + "\n";
            errMessages.pop_back();
        }
        qDebug() << completeMessage;
        // Please find a better heading than 'Double Scientist'
        int ret = QMessageBox::warning(this,"Wrong input", completeMessage, "OK" );
        if (ret) { return; }
    }
    else
    {
        serviceMan->addScientist(sci);
        updateScientist();
    }
}

void MainWindow::on_addComputerPushButton_clicked()
{
    ComputerSearch computerSearch = getComputerFromInput();
    vector<QString> errMessages = serviceMan->computerExists(computerSearch);
    if(errMessages.size() > 0)
    {
        QString completeMessage;
        while(errMessages.size() > 0)
        {
            completeMessage += " " + errMessages.back() + "\n";
            errMessages.pop_back();
        }
        qDebug() << completeMessage;
        int ret = QMessageBox::warning(this,"Wrong input", completeMessage, "OK" );
        if (ret) { return; }
    }
    else
    {
        serviceMan->addComputer(computerSearch);
        updateComputer();
    }
}

void MainWindow::on_computerSelectedDeleteComputerPushButton_clicked()
{
    int ret = QMessageBox::warning(this,"Deleting the selected computer", "Are you sure you want to delete " "?", "DELETE","Cancel" );
    if (ret) { return; }

    ui->windowSwitcher->setCurrentIndex(0);
    serviceMan->deleteComputer(currentlySelectedComputerID);
    updateComputer();
}

void MainWindow::updateScientistsWhoUsedComputer()
{
    ui->computerSelectedScientistTable->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->searchScientistToComputer(currentlySelectedComputerID));
    ui->computerSelectedScientistTable->setModel(sqlproxy);
    ui->computerSelectedScientistTable->resizeColumnsToContents();
    ui->computerSelectedScientistTable->horizontalHeader()->setStretchLastSection(true);
    ui->computerSelectedScientistTable->setColumnHidden(0, true);
}

void MainWindow::on_selectedScientistComputerSearchNameField_textChanged()
{
    updateSelectedScientistComputerSearchTableView();
}

void MainWindow::on_selectedScientistComputerSearchBuiltYearField_textEdited()
{
    updateSelectedScientistComputerSearchTableView();
}

void MainWindow::on_selectedScientistComputerSearchWasItBuiltComboBox_currentIndexChanged()
{
    updateSelectedScientistComputerSearchTableView();
}

void MainWindow::on_selectedScientistComputerSearchTypeComboBox_currentIndexChanged()
{
    updateSelectedScientistComputerSearchTableView();
}

void MainWindow::on_selectedScientistComputerSearcAddpushButton_clicked()
{
    serviceMan->addCSRelation(currentlySelectedUserID,currentlySelectedComputerID);
    updateScinetistUsedComputers();
}

void MainWindow::on_selectedScientistComputerSearchTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedComputerID = index.sibling(row, 0).data().toInt();
}

void MainWindow::on_selectedScientistComputerTable_clicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedComputerID = index.sibling(row, 0).data().toInt();
    on_selectedScientistComputerSearchDoneButton_clicked();
}

void MainWindow::on_selectedScientistComputerTable_doubleClicked(const QModelIndex &index)
{
    on_foundComputersTableView_doubleClicked(index);
}

void MainWindow::on_selectedScientistRemoveSelectedComputerPushButton_clicked()
{
    serviceMan->removeCSRelation(currentlySelectedUserID,currentlySelectedComputerID);
    updateScinetistUsedComputers();
}


void MainWindow::on_foundComputersTableView_clicked(const QModelIndex &index)
{
    ui->editSelectedComputerPushButton->setDisabled(false);
}

void MainWindow::on_computerSelectedChangePicturePushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));

    serviceMan->storeComputerPicture(fileName, currentlySelectedComputerID);
    updateComputerProfilePicture();
}

void MainWindow::on_selectedScientistComputerSearchTableView_doubleClicked(const QModelIndex &index)
{
    on_selectedScientistComputerSearcAddpushButton_clicked();
}

void MainWindow::updateSelectedComputerScientistSearchTableView()
{
    ui->computerSelectedScientistSearchTableView->setSortingEnabled(true);
    QSortFilterProxyModel *sqlproxy = new QSortFilterProxyModel(this);
    sqlproxy->setSourceModel(serviceMan->search(getScientistFromComputerAddScientistInput()));
    ui->computerSelectedScientistSearchTableView->setModel(sqlproxy);
    ui->computerSelectedScientistSearchTableView->resizeColumnsToContents();
    ui->computerSelectedScientistSearchTableView->horizontalHeader()->setStretchLastSection(true);
    ui->computerSelectedScientistSearchTableView->setColumnHidden(0, true);
}

ScientistSearch MainWindow::getScientistFromComputerAddScientistInput()
{
    ScientistSearch sci;
    sci.name = ui->computerSelectedScientistSearchNameField->text();
    sci.birth = ui->computerSelectedScientistSearchyearOfBirthField->text();
    sci.death = ui->computerSelectedScientistSearchyearOfDeathField->text();
    sci.setSex(ui->computerSelectedScientistSearchsexComboBox->currentText());

    return sci;
}
void MainWindow::on_computerSelectedScientistSearchNameField_textChanged(const QString &arg1)
{
    updateSelectedComputerScientistSearchTableView();
}

void MainWindow::on_computerSelectedScientistSearchsexComboBox_currentIndexChanged(const QString &arg1)
{
    updateSelectedComputerScientistSearchTableView();
}

void MainWindow::on_computerSelectedScientistSearchyearOfBirthField_textChanged(const QString &arg1)
{
    updateSelectedComputerScientistSearchTableView();
}

void MainWindow::on_computerSelectedScientistSearchyearOfDeathField_textChanged(const QString &arg1)
{
    updateSelectedComputerScientistSearchTableView();
}

void MainWindow::on_computerSelectedScientistSearchAddPushButton_clicked()
{
    serviceMan->addCSRelation(currentlySelectedUserID,currentlySelectedComputerID);
    updateScientistsWhoUsedComputer();
}

void MainWindow::on_computerSelectedScientistSearchTableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedUserID = index.sibling(row, 0).data().toInt();
}

void MainWindow::on_computerSelectedScientistSearchDoneButton_clicked()
{
    ui->computerSelectedScientistSearch->setHidden(true);
    ui->computerSelectedRemoAddButonWidget->setHidden(false);
}

void MainWindow::on_computerSelectedScientistTable_clicked(const QModelIndex &index)
{
    int row = index.row();
    currentlySelectedUserID = index.sibling(row, 0).data().toInt();
}

void MainWindow::on_computerSelectedScientistSelectedRemoveSelectedButton_clicked()
{
    serviceMan->removeCSRelation(currentlySelectedUserID,currentlySelectedComputerID);
    updateScientistsWhoUsedComputer();
}
int MainWindow::setWidth(int width)
{
    if (width < 350) {return width;}
    return 350;
}

void MainWindow::on_editSelectedComputerPushButton_clicked()
{
    on_foundComputersTableView_doubleClicked(ui->foundComputersTableView->selectionModel()->currentIndex());
}

void MainWindow::on_computerSelectedScientistTable_doubleClicked(const QModelIndex &index)
{
    on_foundScientistTableView_doubleClicked(index);
}
