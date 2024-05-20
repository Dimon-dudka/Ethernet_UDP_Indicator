#pragma once

#include <QWidget>
#include <QTimer>
#include <QColor>
#include <QPointer>
#include <QVBoxLayout>
#include <QLabel>

class exchange_status_widget : public QWidget
{
    Q_OBJECT
private:
    QPointer< QTimer> time_view;
    QPointer<QLabel> status_label;
    QPointer<QVBoxLayout>main_layout;

    int cycle;
    bool has_exchange;

private slots:

    void update_color_slot();

public slots:

    void set_exchange_slot(bool exchange);

public:
    exchange_status_widget(QWidget * parrent = 0);
};
