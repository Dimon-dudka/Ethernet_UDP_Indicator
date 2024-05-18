#pragma once

#include <QWidget>
#include <QLabel>
#include <QList>
#include <QPointer>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QVector>
#include <QVBoxLayout>

class indicator_subwidget:public QWidget
{
    Q_OBJECT
private:

    quint16 indicator_index;

    QPointer<QLabel> number_of_indicator_label;
    QPointer<QComboBox> is_available_box,type_box,power_box,color_box;
    QPointer<QLineEdit> serial_num_line_edit,error_line_edit,i_line_edit;
    QPointer<QPushButton> apply_button;

    QPointer<QVBoxLayout> main_layout;

private slots:

    void apply_slot();

public slots:

    void update_info_slot(QVector<uint32_t> new_data);

signals:

    // Index; Available; Serial; Type; Power; Color; I; Error
    void changes_signal(QVector<uint32_t>);
    void error_message_signal(QString);

public:
    indicator_subwidget(QWidget *parrent = 0, uint32_t index = 0);
};
