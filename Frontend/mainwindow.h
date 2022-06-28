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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FrontendTest;

class MainWindow : public QMainWindow //NOLINT (cppcoreguidelines-special-member-functions)
{
    Q_OBJECT

    friend FrontendTest;

private:
    Ui::MainWindow *ui;

    std::unique_ptr<QMessageBox> aboutMessageBox;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void ShowNotImplementedBox();
    void ShowAboutDialog();

private slots:
    void OnAboutTriggered();
    void OnPlayPausePressed();
    void OnStopPressed();
};

#endif // MAINWINDOW_H
