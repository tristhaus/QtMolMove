/*
 * This file is part of QtMolMove.
 *
 * QtMolMove is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * QtMolMove is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with QtMolMove.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class MainWindow;

class Ui_MainWindow
{
    friend MainWindow;

    Q_DECLARE_TR_FUNCTIONS(Ui_MainWindow);

protected:
    explicit Ui_MainWindow() = default; //NOLINT(cppcoreguidelines-pro-type-member-init)

private:

    QWidget *centralwidget{};
    QVBoxLayout *mainLayout{};

    QCustomPlot * plot{};

    QFrame * controlFrame{};
    QHBoxLayout * controlLayout{};

    QPushButton *playPauseButton{};
    QPushButton *stopButton{};

public:
    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
        {
            MainWindow->setObjectName(QString::fromUtf8(u8"MainWindow"));
        }

        MainWindow->resize(1200, 800); //NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

        centralwidget = new QWidget(MainWindow); //NOLINT(cppcoreguidelines-owning-memory
        centralwidget->setObjectName(QString::fromUtf8(u8"centralwidget"));

        mainLayout = new QVBoxLayout(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        mainLayout->setObjectName(QString::fromUtf8(u8"mainLayout"));

        plot = new QCustomPlot(centralwidget); //NOLINT(cppcoreguidelines-owning-memory)
        plot->setObjectName(QString::fromUtf8(u8"plot"));

        mainLayout->addWidget(plot);

        controlFrame = new QFrame(centralwidget); //NOLINT(cppcoreguidelines-owning-memory)
        controlFrame->setObjectName(QString::fromUtf8(u8"controlFrame"));
        controlFrame->setFrameShape(QFrame::StyledPanel);
        controlFrame->setFrameShadow(QFrame::Raised);

        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlFrame->sizePolicy().hasHeightForWidth());
        controlFrame->setSizePolicy(sizePolicy);

        controlLayout = new QHBoxLayout(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        controlLayout->setObjectName(QString::fromUtf8(u8"controlLayout"));

        playPauseButton = new QPushButton(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        playPauseButton->setObjectName(QString::fromUtf8(u8"playPauseButton"));
        controlLayout->addWidget(playPauseButton);

        stopButton = new QPushButton(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        stopButton->setObjectName(QString::fromUtf8(u8"stopButton"));
        controlLayout->addWidget(stopButton);

        mainLayout->addWidget(controlFrame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", u8"QtMolMove", nullptr));

        this->playPauseButton->setText(QCoreApplication::translate("MainWindow", u8"Play/Pause", nullptr));
        this->stopButton->setText(QCoreApplication::translate("MainWindow", u8"Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow
    {
    public:
        explicit MainWindow() = default;
    };
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
