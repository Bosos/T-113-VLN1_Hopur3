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
    ui->selectedScientistRemoAddButonWidget->setHidden(false);

    ui->windowSwitcher->setCurrentIndex(1);
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
    if(!fileName.isEmpty())
    {
        QImage image(fileName);

        if(image.isNull())
        {
            QMessageBox::information(this,"Image Viewer","Error Displaying image");
            return;
        }
            QGraphicsScene* scene = new QGraphicsScene();
            QGraphicsView* view = new QGraphicsView(scene);

            view->setDragMode(QGraphicsView::NoDrag);
            view->setEnabled(false);
            QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
            QRect rect(0,0,138,178);
            item->setPixmap(item->pixmap().scaled(138,178,Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));

            item->setPixmap(item->pixmap().copy(rect));

            scene->addItem(item);

            ui->scientistPicture->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ui->scientistPicture->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
            ui->scientistPicture->setScene(scene);
            //ui->scientistPicture->fitInView(item,Qt::KeepAspectRatioByExpanding);

            ui->scientistPicture->show();
    }
}


