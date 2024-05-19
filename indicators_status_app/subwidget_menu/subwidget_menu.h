#pragma once

#include <QWidget>
#include <QPointer>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QVBoxLayout>
#include <QVector>

class subwidget_menu : public QWidget
{
    Q_OBJECT
private:

    uint32_t index;

    QPointer<QVBoxLayout> main_layout;
    QPointer<QPushButton> apply_button;
    QPointer<QComboBox> power_box;
    QPointer<QLabel> serial_label,type_label,color_label,i_label,error_label,power_label;

private slots:

    void apply_slot();

public slots:

    void update_data_slot(QVector<uint32_t>new_data);

signals:

    void update_power_mode_signal(uint32_t,bool);   // index, value

public:
    subwidget_menu(QWidget * parrent = 0,uint32_t new_index = 0);
};
