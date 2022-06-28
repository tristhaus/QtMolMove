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

#include "mainwindow.h"
#include "mainwindow_ui.h"

#include <QMessageBox>
#include <utility>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->aboutMenuAction, &QAction::triggered, this, &MainWindow::OnAboutTriggered);
    connect(ui->playPauseButton, &QAbstractButton::pressed, this, &MainWindow::OnPlayPausePressed);
    connect(ui->stopButton, &QAbstractButton::pressed, this, &MainWindow::OnStopPressed);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ShowAboutDialog()
{
    auto messageBoxTitleTemplate = QCoreApplication::translate("MainWindow", "About %1", nullptr);
    auto messageBoxTitle = messageBoxTitleTemplate.arg(QCoreApplication::translate("MainWindow", "QtMolMove", nullptr));

    //: Arg 1 is a placeholder for the program name. Format is Qt Rich Text.
    auto messageBoxTextTemplate = QCoreApplication::translate("MainWindow", R"(A simple program to display 2D trajectories of spherical objects.<br /><br />%1 Copyright (C) 2022 and later, tristhaus<br />This program comes with ABSOLUTELY NO WARRANTY.<br />This is free software, and you are welcome to redistribute it under certain conditions. See provided LICENSE file for details.<br /><br />Graphical user interface built using <a href="https://doc.qt.io/">Qt</a>.<br /><a href="https://www.qcustomplot.com/">QCustomPlot</a> library (Version 2.1.0) by Emanuel Eichhammer used under the <a href="https://www.gnu.org/licenses/gpl-3.0.html">GPL v3</a>.)", nullptr);
    auto messageBoxText = messageBoxTextTemplate.arg(QCoreApplication::translate("MainWindow", "QtMolMove", nullptr));

    this->aboutMessageBox = std::make_unique<QMessageBox>(
                    QMessageBox::Icon::NoIcon,
                    messageBoxTitle,
                    messageBoxText);

    this->aboutMessageBox->setTextFormat(Qt::RichText);
    this->aboutMessageBox->setTextInteractionFlags(Qt::TextBrowserInteraction);

    this->aboutMessageBox->exec();

    this->aboutMessageBox.reset();
}

void MainWindow::ShowNotImplementedBox()
{
    QString messageBoxTitle = QString::fromUtf8("Not implemented");
    QString messageBoxText = QString::fromUtf8("Feature not yet implemented");

    auto box = std::make_unique<QMessageBox>(
                QMessageBox::Icon::Critical,
                messageBoxTitle,
                messageBoxText);

    box->exec();
}

void MainWindow::OnAboutTriggered()
{
    this->ShowAboutDialog();
}

void MainWindow::OnPlayPausePressed()
{
    this->ShowNotImplementedBox();
}

void MainWindow::OnStopPressed()
{
    this->ShowNotImplementedBox();
}
