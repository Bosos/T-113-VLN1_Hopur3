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
    updateComputer();
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
    ui->foundScientistTableView->setModel(dataMan->search(getScientistFromInput()));
    ui->foundScientistTableView->resizeColumnsToContents();
    ui->foundScientistTableView->setColumnHidden(0,true);
}

void MainWindow::updateScientistProfilePicture()
{
    QPixmap profilePicture = dataMan->getScientistPicture(currentlySelectedID);

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
    }
    int ret = QMessageBox::warning(this,"Hello fish","Are you sure you want to delete this scientist?","DELETE","Cancel" );

    qDebug() << ret;
}

void MainWindow::on_scientistChangePictureButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("Images (*.png *.xpm *.jpg)"));

    dataMan->storeScientistPicture(fileName, currentlySelectedID);
    updateScientistProfilePicture();
}

void MainWindow::on_computerSelectedOKPushButton_clicked()
{
    ui->windowSwitcher->setCurrentIndex(0);
    ComputerSearch comp;
    comp.name = ui->computerSelectedNameField->text();
    comp.setType(ui->computerSelectedTypeComboBox->currentText());
    comp.buildYear = ui->computerSelectedComputerBuiltYearlineEdit->text();
    comp.setWasItBuilt(ui->computerSelectedWasItBuiltComboBox->currentText());
    comp.about = ui->computerAboutlineEdit->text();

    dataMan->updateComputerDatabase(comp, currentlySelectedID);
    updateComputer();
}

void MainWindow::updateComputer()
{
    ui->foundComputersTableView->setSortingEnabled(true);
    ui->foundComputersTableView->setModel(dataMan->searchComputer(getComputerFromInput()));
    ui->foundComputersTableView->resizeColumnsToContents();
    ui->foundComputersTableView->setColumnHidden(0, true);
}

ComputerSearch MainWindow::getComputerFromInput()
{
    ComputerSearch compSearch;
    compSearch.name = ui->computerNameLineEdit->text();
    compSearch.setType(ui->computerSearchTypeComboBox->currentText());
    compSearch.buildYear = ui->computerBuiltYearlineEdit->text();
    compSearch.setWasItBuilt(ui->computerSearchWasItBuiltComboBox->currentText());
    compSearch.about = ui->computerAboutlineEdit->text();

    return compSearch;
}

void MainWindow::on_computerNameLineEdit_textEdited(const QString &arg1)
{
    updateComputer();
}

void MainWindow::on_computerBuiltYearlineEdit_textEdited(const QString &arg1)
{
    updateComputer();
}

void MainWindow::on_computerSearchTypeComboBox_activated(const QString &arg1)
{
    updateComputer();
}

void MainWindow::on_computerSearchWasItBuiltComboBox_activated(const QString &arg1)
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
    dataMan->addComputer(getComputerFromInput());
    updateComputer();
}
