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

#include "mouseonlyslider.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class MainWindow;
class FrontendTest;

class Ui_MainWindow
{
    friend MainWindow;
    friend FrontendTest;

    Q_DECLARE_TR_FUNCTIONS(Ui_MainWindow);

protected:
    explicit Ui_MainWindow() //NOLINT(cppcoreguidelines-pro-type-member-init)
    : playIcon(":/play256.png"),
      pauseIcon(":/pause256.png")
    {
    }

private:
    QIcon playIcon;
    QIcon pauseIcon;

    QMenuBar * menubar{};
    QAction * loadMenuAction{};
    QAction * aboutMenuAction{};

    QWidget * centralwidget{};
    QVBoxLayout * mainLayout{};

    QCustomPlot * plot{};

    MouseOnlySlider * slider{};

    QFrame * controlFrame{};
    QHBoxLayout * controlLayout{};

    QPushButton * playPauseButton{};
    QPushButton * stopButton{};
    QPushButton * stepBackButton{};
    QPushButton * stepForwardButton{};
    QPushButton * slowerButton{};
    QSpinBox * intervalEdit{};
    QPushButton * fasterButton{};

public:
    void setupUi(QMainWindow * MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
        {
            MainWindow->setObjectName(QString::fromUtf8(u8"MainWindow"));
        }

        MainWindow->resize(728, 800); //NOLINT(cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers)

        setupMenuBar(MainWindow);

        centralwidget = new QWidget(MainWindow); //NOLINT(cppcoreguidelines-owning-memory
        centralwidget->setObjectName(QString::fromUtf8(u8"centralwidget"));

        mainLayout = new QVBoxLayout(centralwidget); //NOLINT(cppcoreguidelines-owning-memory
        mainLayout->setObjectName(QString::fromUtf8(u8"mainLayout"));

        plot = new QCustomPlot(centralwidget); //NOLINT(cppcoreguidelines-owning-memory)
        plot->setObjectName(QString::fromUtf8(u8"plot"));

        mainLayout->addWidget(plot);

        slider = new MouseOnlySlider(centralwidget); //NOLINT(cppcoreguidelines-owning-memory)
        slider->setObjectName(QString::fromUtf8(u8"slider"));
        slider->setOrientation(Qt::Orientation::Horizontal);

        mainLayout->addWidget(slider);

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
        playPauseButton->setIcon(playIcon);
        controlLayout->addWidget(playPauseButton);

        stopButton = new QPushButton(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        stopButton->setObjectName(QString::fromUtf8(u8"stopButton"));
        stopButton->setIcon(QIcon(":/stop256.png"));
        controlLayout->addWidget(stopButton);

        stepBackButton = new QPushButton(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        stepBackButton->setObjectName(QString::fromUtf8(u8"stepBackButton"));
        stepBackButton->setIcon(QIcon(":/back256.png"));
        controlLayout->addWidget(stepBackButton);

        stepForwardButton = new QPushButton(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        stepForwardButton->setObjectName(QString::fromUtf8(u8"stepForwardButton"));
        stepForwardButton->setIcon(QIcon(":/forward256.png"));
        controlLayout->addWidget(stepForwardButton);

        slowerButton = new QPushButton(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        slowerButton->setObjectName(QString::fromUtf8(u8"slowerButton"));
        slowerButton->setIcon(QIcon(":/slower256.png"));
        controlLayout->addWidget(slowerButton);

        intervalEdit = new QSpinBox(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        intervalEdit->setObjectName(QString::fromUtf8(u8"intervalEdit"));
        intervalEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
        intervalEdit->setSuffix(QString::fromUtf8(" ms"));
        intervalEdit->setMaximumWidth(60);
        intervalEdit->setAlignment(Qt::AlignHCenter);
        controlLayout->addWidget(intervalEdit);

        fasterButton = new QPushButton(controlFrame); //NOLINT(cppcoreguidelines-owning-memory)
        fasterButton->setObjectName(QString::fromUtf8(u8"fasterButton"));
        fasterButton->setIcon(QIcon(":/faster256.png"));
        controlLayout->addWidget(fasterButton);

        mainLayout->addWidget(controlFrame);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);
    } // setupUi

private:
    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "QtMolMove", nullptr));

        playPauseButton->setToolTip(QCoreApplication::translate("MainWindow", "Play / Pause", nullptr));
        stopButton->setToolTip(QCoreApplication::translate("MainWindow", "Stop", nullptr));
        stepBackButton->setToolTip(QCoreApplication::translate("MainWindow", "Step Back", nullptr));
        stepForwardButton->setToolTip(QCoreApplication::translate("MainWindow", "Step Forward", nullptr));
        slowerButton->setToolTip(QCoreApplication::translate("MainWindow", "Slower", nullptr));
        intervalEdit->setToolTip(QCoreApplication::translate("MainWindow", "Frame interval in milliseconds", nullptr));
        fasterButton->setToolTip(QCoreApplication::translate("MainWindow", "Faster", nullptr));
    } // retranslateUi

    void setupMenuBar(QMainWindow * MainWindow)
    {
        menubar = new QMenuBar(MainWindow); //NOLINT(cppcoreguidelines-owning-memory)
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 600, 21));

        auto loadMenuActionLabel = QCoreApplication::translate("MainWindow", "Load ...", nullptr);
        loadMenuAction = menubar->addAction(loadMenuActionLabel);
        loadMenuAction->setObjectName(QString::fromUtf8("load"));

        //: Arg 1 is a placeholder for the program name
        auto aboutActionLabelTemplate = QCoreApplication::translate("MainWindow", "About %1", nullptr);
        auto aboutActionLabel = aboutActionLabelTemplate.arg(QCoreApplication::translate("MainWindow", "QtMolMove", nullptr));
        aboutMenuAction = menubar->addAction(aboutActionLabel);
        aboutMenuAction->setObjectName(QString::fromUtf8("about"));
        MainWindow->setMenuBar(menubar);
    } // setupMenuBar
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
