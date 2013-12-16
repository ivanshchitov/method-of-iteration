#include "dialog.h"
#include "ui_dialog.h"
#include <QImage>
#include <QPixmap>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    initPhoto();
    initText();
    setWindowTitle("О программе");
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::initPhoto() {
    QImage *photo = new QImage;
    photo->load("://photo.jpg");
    ui->photoLabel->setPixmap(QPixmap::fromImage(*photo));
}

void Dialog::initText() {
    ui->textLabel->setText("Это приложение находит решение\nнелинейного уравнения вида x = g(x),\nиспользуя метод итераций.\n"
                            "Программа рисует численное\nрешение в зависимости от значений\nитерации,начальной точки,"
                            "пареметров\nфункции и выбранного параметра,\nопределяющего изображение.\n\n"
                            "\tСтудент: Щитов Иван\n\t   Группа: ИВТ-41СО\n\t\tЯрГУ");
}

void Dialog::on_buttonBox_rejected() {
    this->reject();
}
