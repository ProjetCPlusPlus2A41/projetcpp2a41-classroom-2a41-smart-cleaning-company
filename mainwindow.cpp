#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "livraison.h"
#include <QTableView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlError>
#include <QDate>
#include <QDateTimeEdit>
#include <QFileDialog>
#include <QFile>
#include <QPdfWriter>
#include <QPainter>
#include <QPageSize>
#include <QSqlQuery>
#include <QSqlRecord>

#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include <QFormLayout>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    livraison(new Livraison),
    model(nullptr),
    imageLabel(new QLabel(this))
{
    ui->setupUi(this);
    setupTableView();

    ui->lineEdit_id->setValidator(new QIntValidator(1, 999999, this)); // Only allow positive integers

    ui->lineEdit_montant->setValidator(new QDoubleValidator(0.1, 999999.99, 2, this));

    ui->lineEdit_recherche->setValidator(new QIntValidator(1, 999999, this));

    ui->lineEdit_IDS->setValidator(new QIntValidator(1, 999999, this));

        ui->dateTimeEdit->setMinimumDateTime(QDateTime::currentDateTime()); // No past dates
        ui->dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm"); // Date and time display format

    connect(ui->lineEdit_recherche, &QLineEdit::textChanged, this, &MainWindow::filtrerLivraison);

    connect(ui->pushButton_trier, &QPushButton::clicked, this, &MainWindow::trierParDate);

    connect(ui->pushButton_trierm, &QPushButton::clicked, this, &MainWindow::trierParMontant);

    connect(ui->pushButton_exporterexcel, &QPushButton::clicked, this, &MainWindow::exporterVersExcel);

    connect(ui->pushButton_exporterpdf, &QPushButton::clicked, this, &MainWindow::exporterVersPdf);

    connect(ui->pushButton_stat, &QPushButton::clicked ,this, &MainWindow::afficherStatistiques);

    connect(ui->pushButton_stat1, &QPushButton::clicked ,this, &MainWindow::afficherStatistiques1);

    connect(ui->pushButton_stat2, &QPushButton::clicked ,this, &MainWindow::afficherStatistiques2);

    connect(ui->pushButton_stat3, &QPushButton::clicked ,this, &MainWindow::afficherStatistiques3);

    connect(ui->pushButton_stat4, &QPushButton::clicked ,this, &MainWindow::afficherStatistiques4);

    connect(ui->pushButton_stat5, &QPushButton::clicked ,this, &MainWindow::afficherStatistiques5);

    connect(ui->comboBoxEtat1, &QComboBox::currentTextChanged, this, &MainWindow::filtrerParEtat);



    loadImage("C:/Users/Mega-PC/Downloads/Statistique-aide-decision.jpg");

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Configurer l'interface utilisateur
void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    QLabel *label = new QLabel("Bienvenue dans l'application!", centralWidget);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setBrush(Qt::lightGray);
    painter.drawRect(rect());
}

void MainWindow::loadImage(const QString &imagePath) {
    QPixmap image(imagePath);

    if (image.isNull()) {
        ui->imageLabel->setText("Erreur de chargement de l'image");
        ui->imageLabel->setAlignment(Qt::AlignCenter);
    } else {
        // Redimensionner le QPixmap pour qu'il s'adapte au QLabel
        QPixmap scaledImage = image.scaled(ui->imageLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        ui->imageLabel->setPixmap(scaledImage);
        ui->imageLabel->setScaledContents(true); // Permet de redimensionner le QLabel si nécessaire
    }
}

void MainWindow::setupTableView() {
    model = new QSqlTableModel(this);

    model->setTable("LIVRAISON");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::EditKeyPressed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::on_pushButton_ajouter_clicked() {

    bool idOk;
    int id = ui->lineEdit_id->text().toInt(&idOk);
    if (!idOk || id <= 0) {
        QMessageBox::warning(this, "Erreur", "ID invalide. Veuillez entrer un nombre entier positif.");
        return;
    }

    QDateTime dateTime = ui->dateTimeEdit->dateTime();

    QString adresse = ui->lineEdit_adresse->text();
    if (adresse.isEmpty() || adresse.length() < 5) {
        QMessageBox::warning(this, "Erreur", "L'adresse doit contenir au moins 5 caractères.");
        return;
    }

    QString etat = ui->etatComboBox->currentText();
    if (etat.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "L'état doit être sélectionné.");
        return;
    }

    bool montantOk;
    float montant = ui->lineEdit_montant->text().toFloat(&montantOk);
    if (!montantOk || montant < 0) {
        QMessageBox::warning(this, "Erreur", "Montant invalide. Veuillez entrer un nombre valide et positif.");
        return;
    }

    Livraison l(id, dateTime, adresse, etat, montant);

    if (l.ajouter()) {
        QMessageBox::information(this, tr("Ajout réussi"), tr("Livraison ajoutée avec succès."), QMessageBox::Ok);
        setupTableView(); // Refresh the table view
    } else {
        QMessageBox::critical(this, tr("Échec de l'ajout"), tr("Erreur lors de l'ajout de la livraison."), QMessageBox::Ok);
    }
}


void MainWindow::on_pushButton_supprimer_clicked()
{
    int id = ui->lineEdit_IDS->text().toInt();
    Livraison l;

    if (l.supprimer(id)) {
        QMessageBox::information(this, tr("Suppression réussie"), tr("Livraison supprimée avec succès."), QMessageBox::Ok);
        setupTableView(); // Refresh the table view
    } else {
        QMessageBox::critical(this, tr("Échec de la suppression"), tr("Erreur lors de la suppression de la livraison."), QMessageBox::Ok);
    }
}

void MainWindow::on_pushButton_modifier_clicked() {
    if (model) {

        QString etat = ui->etatComboBox->currentText();

        if (etat != "en cours" && etat != "livré" && etat != "non livré") {
            QMessageBox::warning(this, "Erreur", "L'état doit être 'en cours', 'livré' ou 'non livré'.");
            return;
        }

        if (!model->submitAll()) {
            QMessageBox::warning(this, "Error", "Could not save changes: " + model->lastError().text());
        } else {
            QMessageBox::information(this, "Success", "Changes saved successfully!");
            setupTableView();
        }
    }
}

void MainWindow::filtrerLivraison(const QString &text)
{
    if (text.isEmpty()) {
        model->setFilter("");
    } else {

        QString filter = QString("ID_LIVRAISON LIKE '%1%'").arg(text);
        model->setFilter(filter);
    }
    model->select(); // Appliquer le filtre
}

void MainWindow::filtrerParEtat(const QString &etat)
{
    if (etat == "tous") {
        model->setFilter(""); // Affiche tous les enregistrements
    } if (etat.compare("en cours", Qt::CaseInsensitive) == 0) {
        model->setFilter("ETAT_LIVRAISON = 'en cours'");
    } if (etat.compare("livré", Qt::CaseInsensitive) == 0) {
        model->setFilter("ETAT_LIVRAISON = 'livré'");
    } if (etat.compare("non livré", Qt::CaseInsensitive) == 0) {
        model->setFilter("ETAT_LIVRAISON = 'non livré'");
    }

    model->select(); // Mettre à jour le modèle pour appliquer le filtre
}


void MainWindow::trierParDate()
{
    model->setSort(model->fieldIndex("DATE_LIVRAISON"), Qt::AscendingOrder);
    model->select();
}

void MainWindow::trierParMontant()
{
    model->setSort(model->fieldIndex("MONTANT_LIVRAISON"), Qt::AscendingOrder);
    model->select();
}


void MainWindow::exporterVersPdf()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter vers PDF"), "", tr("Fichiers PDF (*.pdf)"));
    if (fileName.isEmpty()) {
        return;
    }

    QPdfWriter pdfWriter(fileName);
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
    QPainter painter(&pdfWriter);
    int y = 200;

    // En-têtes de colonne
    painter.drawText(200, y, "ID_LIVRAISON");
    painter.drawText(2200, y, "DATE_LIVRAISON");
    painter.drawText(4200, y, "ADRESSE_LIVRAISON");
    painter.drawText(6200, y, "ETAT_LIVRAISON");
    painter.drawText(8200, y, "MONTANT_LIVRAISON");
    y += 500;

    // Récupérer et écrire les données
    QSqlQuery query("SELECT * FROM LIVRAISON");
    while (query.next()) {
        painter.drawText(200, y, query.value(0).toString());
        painter.drawText(2200, y, query.value(1).toString());
        painter.drawText(4200, y, query.value(2).toString());
        painter.drawText(6200, y, query.value(3).toString());
        painter.drawText(8200, y, query.value(4).toString());
        y += 250; // Ajustez y pour chaque ligne
    }

    painter.end();
    QMessageBox::information(this, tr("Succès"), tr("Les données ont été exportées avec succès."));
}

void MainWindow::exporterVersExcel()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Exporter vers Excel"), "", tr("Fichiers CSV (*.csv)"));
    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Erreur"), tr("Impossible d'ouvrir le fichier."));
        return;
    }

    QTextStream out(&file);

    // Écrire les en-têtes de colonnes
    out << "ID_LIVRAISON,DATE_LIVRAISON,ADRESSE_LIVRAISON,ETAT_LIVRAISON,MONTANT_LIVRAISON\n";

    // Récupérer et écrire les données
    QSqlQuery query("SELECT * FROM LIVRAISON");
    while (query.next()) {
        //QString dateLivraison = QDateTime::fromString(query.value(1).toString(), "yyyy-MM-dd HH:mm:ss.zzz").toString("yyyy-MM-dd HH:mm");
        out << query.value(0).toString() << "," <<  query.value(1).toString() << "," << query.value(2).toString() << "," << query.value(3).toString() << "," << query.value(4).toString() << "\n";
    }

    file.close();
    QMessageBox::information(this, tr("Succès"), tr("Les données ont été exportées avec succès."));
}

/*void MainWindow::afficherStatistiques() {

    QLineSeries *series = new QLineSeries ();

    series->append(0, 7);
    series->append(1, 2);
    series->append(2, 9);
    series->append(3, 4);
    series->append(4, 5);
    series->append(5, 6);
    series->append(6, 7);
    series->append(7, 11);
    series->append(8, 9);
    series->append(9, 1);

    QChart *chart = new QChart() ;
    chart->setTheme(QChart::ChartTheme::ChartThemeBlueIcy);
    chart->legend()->hide ();
    chart->addSeries (series);
    chart->createDefaultAxes ();
    //chart->axes (Qt::Vertical).first ()->setRange (0, 12);
    //chart->axes (Qt::Horizontal).first ()->setRange(0, 11) ;
    chart->setVisible (true);

    QChartView *chartview = new QChartView(chart) ;
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setVisible (true);


}*/
void MainWindow::afficherStatistiques() {
    // Create a new line series
    QLineSeries *series = new QLineSeries();
    series->append(0, 7);
    series->append(1, 2);
    series->append(2, 9);
    series->append(3, 4);
    series->append(4, 5);
    series->append(5, 6);
    series->append(6, 7);
    series->append(7, 11);
    series->append(8, 9);
    series->append(9, 1);

    // Create a new chart
    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    // Customize chart appearance
    chart->setTitle("Statistiques des Livraisons");
    chart->setTitleFont(QFont("Arial", 14, QFont::Bold));
    chart->setBackgroundBrush(QBrush(QColor(240, 240, 240))); // Light gray background

    // Customize axes
    QValueAxis *axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    QValueAxis *axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());

    if (axisX) {
        axisX->setTitleText("Temps");
        axisX->setTitleFont(QFont("Arial", 12, QFont::Bold));
        axisX->setLabelsFont(QFont("Arial", 10)); // Corrected method
        axisX->setRange(0, 9);
    }

    if (axisY) {
        axisY->setTitleText("Montant");
        axisY->setTitleFont(QFont("Arial", 12, QFont::Bold));
        axisY->setLabelsFont(QFont("Arial", 10)); // Corrected method
        axisY->setRange(0, 12);
    }

    // Set line style and color
    QPen pen;
    pen.setColor(QColor(0, 120, 215)); // Blue color
    pen.setWidth(3);
    series->setPen(pen);
    series->setName("Montant des Livraisons");

    // Create the chart view and set its properties
    QChartView *chartview = new QChartView(chart);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setMinimumSize(800, 600); // Set minimum size for the chart view
    chartview->setVisible(true);

}



void MainWindow::afficherStatistiques1(){
QSplineSeries *series = new QSplineSeries ();
series->append (0, 10);
series->append (1, 5);
series->append (2, 13);
series->append (3, 25);
series->append (4, 10);
series->append(5, 4);
series->append(6, 9);
series->append(7, 5);
series->append(8, 12);
series->append(9, 18);
QChart *chart = new QChart();
chart->legend()->hide() ;
chart->addSeries(series);
chart->createDefaultAxes ();
//chart->axes (Qt::Vertical).first()->setRange(0, 30) ;
//chart->axes (Qt::Horizontal).first()->setRange(0, 11);
chart->setVisible (true);
QChartView *Chartview = new QChartView(chart);
Chartview->setRenderHint(QPainter::Antialiasing);
Chartview->setVisible(true);
Chartview->setMinimumSize(800, 600); // largeur, hauteur
}

void MainWindow::afficherStatistiques2(){
    QBarSeries *series = new QBarSeries();

QBarSet *set_1 = new QBarSet("Livraison with CleaNovate");
set_1->append (55);
set_1->append (80);
set_1->append(90);
set_1->append (70);
set_1->append(65);
series->append (set_1);
QChart *chart = new QChart();
chart->addSeries(series);
chart->setTitle("livraison");
chart->setAnimationOptions(QChart::SeriesAnimations);

QStringList Subjectname;
Subjectname.append("Livraison standard");
Subjectname.append("Livraison express ");
Subjectname.append ("Livraison par drone");
Subjectname.append ("Livraison internationale ");
Subjectname.append ("Livraison par abonnement");
QBarCategoryAxis *axisX = new QBarCategoryAxis () ;
axisX->append (Subjectname);
chart->addAxis(axisX, Qt::AlignBottom);
series->attachAxis(axisX);

QValueAxis *axisY = new QValueAxis ();
axisY->setRange(0, 100);
chart->addAxis (axisY, Qt::AlignLeft);
series->attachAxis(axisY);

chart->setTheme(QChart::ChartTheme::ChartThemeBlueNcs);
chart->legend()->setVisible(true);
chart->legend()->setAlignment(Qt::AlignBottom);
chart->setVisible(true);

QChartView *Chartview = new QChartView(chart);
Chartview->setRenderHint(QPainter::Antialiasing);
Chartview->setVisible(true);
Chartview->setMinimumSize(800, 600); // largeur, hauteur
}

void MainWindow::afficherStatistiques3(){
    QBarSeries *series = new QBarSeries();

QBarSet *set_1 = new QBarSet("Livraison with CleaNovate");
set_1->append (55);
set_1->append (80);
set_1->append(90);
set_1->append (60);
set_1->append(65);
set_1->setColor(Qt::green);

QBarSet *set_2 = new QBarSet("Livraison with cleanify");
set_2->append (35);
set_2->append (40);
set_2->append(50);
set_2->append (70);
set_2->append(35);
set_2->setColor(Qt::red);

QBarSet *set_3 = new QBarSet("Livraison with nadhefni");
set_3->append (15);
set_3->append (20);
set_3->append(30);
set_3->append (20);
set_3->append(25);
set_3->setColor(Qt::blue);


series->append (set_1);
series->append (set_2);
series->append (set_3);

QChart *chart = new QChart();
chart->addSeries(series);
chart->setTitle("Students Data");
chart->setTheme(QChart::ChartTheme::ChartThemeHighContrast);
chart->setAnimationOptions(QChart::SeriesAnimations);

QStringList Subjectname;
Subjectname.append("Livraison standard");
Subjectname.append("Livraison express ");
Subjectname.append ("Livraison par drone");
Subjectname.append ("Livraison internationale ");
Subjectname.append ("Livraison par abonnement");
QBarCategoryAxis *axisX = new QBarCategoryAxis () ;
axisX->append (Subjectname);
chart->addAxis(axisX, Qt::AlignBottom);
series->attachAxis(axisX);

QValueAxis *axisY = new QValueAxis ();
axisY->setRange(0, 100);
chart->addAxis (axisY, Qt::AlignLeft);
series->attachAxis(axisY);

chart->legend()->setVisible(true);
//chart->legend()->setAlignment(Qt::AlignBottom);
chart->legend()->setAlignment(Qt::AlignLeft);
chart->setTheme(QChart::ChartTheme::ChartThemeBrownSand);
chart->setVisible(true);

QChartView *Chartview = new QChartView(chart);
Chartview->setRenderHint(QPainter::Antialiasing);
Chartview->setVisible(true);
Chartview->setMinimumSize(800, 600); // largeur, hauteur
}

void MainWindow::afficherStatistiques4(){
    QPieSeries *series = new QPieSeries();

series->append ("Livraison standard",30);
series->append ("Livraison express",10);
series->append("Livraison par drone",0);
series->append ("Livraison internationale",20);
series->append("Livraison par abonnement",20);

QPieSlice *slice_1 = series->slices().at(0);
slice_1->setExploded(true);
slice_1->setLabelVisible(true);
slice_1->setPen(QPen(Qt::red,1));
slice_1->setBrush(Qt::red);

QPieSlice *slice_2 = series->slices().at(1);
slice_2->setExploded(true);
slice_2->setLabelVisible(true);
slice_2->setPen(QPen(Qt::green,1));
slice_2->setBrush(Qt::green);

QPieSlice *slice_3 = series->slices().at(4);
slice_3->setExploded(true);
slice_3->setLabelVisible(true);
slice_3->setPen(QPen(Qt::blue,1));
slice_3->setBrush(Qt::blue);

QChart *chart = new QChart() ;
chart->addSeries (series);
chart->setTitle("CleaNovate");
chart->setTheme(QChart::ChartTheme::ChartThemeBlueCerulean);
//chart->setTheme(QChart::ChartTheme::ChartThemeHighContrast);
chart->legend()->hide ();
chart->setVisible (true);

QChartView *Chartview = new QChartView(chart);
Chartview->setRenderHint(QPainter::Antialiasing);
Chartview->setVisible(true);
Chartview->setMinimumSize(800, 600); // largeur, hauteur
}

void MainWindow::afficherStatistiques5(){
    QPieSeries *series = new QPieSeries();

    series->setHoleSize(0.25);

QPieSlice *slice_1 = series->append("Livraison par drone",30);
slice_1->setExploded(true);
slice_1->setLabelVisible(true);
slice_1->setPen(QPen(Qt::cyan,1));
slice_1->setBrush(Qt::cyan);

series->append("Livraison par abonnement",10);

QPieSlice *slice_3 = series->append("Livraison express",20);
slice_3->setExploded(true);
slice_3->setLabelVisible(true);
slice_3->setPen(QPen(Qt::red,1));
slice_3->setBrush(Qt::red);

series->append("Livraison standard",10);
series->append("Livraison internationale",10);

QChart *chart = new QChart() ;
chart->addSeries (series);
chart->legend()->setVisible(true);
chart->setTitle("CleaNovate");
chart->setTheme(QChart::ChartTheme::ChartThemeDark);
chart->legend()->setAlignment(Qt::AlignBottom);
chart->setVisible (true);

QChartView *Chartview = new QChartView(chart);
Chartview->setRenderHint(QPainter::Antialiasing);
Chartview->setVisible(true);
Chartview->setMinimumSize(800, 600); // largeur, hauteur
}
