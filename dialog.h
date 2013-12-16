#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;

private:
    void initPhoto();
    void initText();
};

#endif // DIALOG_H
