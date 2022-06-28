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

#if defined(_SKIP_LONG_TEST)
#elif defined(_USE_LONG_TEST)
#else
#error "you need to make a choice between using or skipping long tests, -D_USE_LONG_TEST -D_SKIP_LONG_TEST"
#endif

#include <QTest>
#include <QtTest>

#include "../Frontend/mainwindow.h"
#include "../Frontend/mainwindow_ui.h"

class FrontendTest : public QObject
{
    Q_OBJECT

private:
    const int SingleShotInterval = 1000;

public:
    FrontendTest();

private slots:
    static void ConstructionShallWorkCompletely() ;
#ifdef _USE_LONG_TEST
    void AboutButtonShallTriggerDialogAndOKShallClose();
#endif // _USE_LONG_TEST
};

FrontendTest::FrontendTest()
= default;

void FrontendTest::ConstructionShallWorkCompletely() //NOLINT(google-readability-function-size, hicpp-function-size, readability-function-size)
{
    try
    {
        // Act
        MainWindow mw;

        // Assert
        QVERIFY2(mw.ui->menubar, qPrintable(QString::fromUtf8(u8"not menu bar")));
        QVERIFY2(mw.ui->loadMenuAction, qPrintable(QString::fromUtf8(u8"not created load menu action")));
        QVERIFY2(mw.ui->aboutMenuAction, qPrintable(QString::fromUtf8(u8"not created about menu action")));

        QVERIFY2(mw.ui->centralwidget, qPrintable(QString::fromUtf8(u8"not created central widget")));
        QVERIFY2(mw.ui->mainLayout, qPrintable(QString::fromUtf8(u8"not created main layout")));

        QVERIFY2(mw.ui->plot, qPrintable(QString::fromUtf8(u8"not created plot")));

        QVERIFY2(mw.ui->controlFrame, qPrintable(QString::fromUtf8(u8"not created control frame")));
        QVERIFY2(mw.ui->controlLayout, qPrintable(QString::fromUtf8(u8"not created control layout")));

        QVERIFY2(mw.ui->playPauseButton, qPrintable(QString::fromUtf8(u8"not created play/pause button")));
        QVERIFY2(mw.ui->stopButton, qPrintable(QString::fromUtf8(u8"not created stop button")));
        QVERIFY2(mw.ui->stepBackButton, qPrintable(QString::fromUtf8(u8"not created step back button")));
        QVERIFY2(mw.ui->stepForwardButton, qPrintable(QString::fromUtf8(u8"not created step forward button")));

    }
    catch (std::exception & ex)
    {
        QFAIL(ex.what());
    }
    catch (...)
    {
        QFAIL(u8"unknown exception");
    }
}

#ifdef _USE_LONG_TEST

void FrontendTest::AboutButtonShallTriggerDialogAndOKShallClose()
{
    // Arrange
    MainWindow mw;
    auto ui = mw.ui;

    // spy needed such that events actually happen
    QSignalSpy spyAboutAction(ui->aboutMenuAction, &QAction::triggered);

    QVERIFY2(ui->plot->graphCount() == 0, "graphs found that should not be there");

    bool actionFound = false;

    // Act
    bool aboutMessageBoxFound = false;
    bool aboutMessageBoxHasOneButton = false;
    QTimer::singleShot(SingleShotInterval, [&]()
    {
        aboutMessageBoxFound = mw.aboutMessageBox != nullptr;
        aboutMessageBoxHasOneButton = mw.aboutMessageBox->buttons().count() == 1 && mw.aboutMessageBox->buttons().first() != nullptr;
        if(aboutMessageBoxFound && aboutMessageBoxHasOneButton)
        {
            QTest::mouseClick(mw.aboutMessageBox->buttons().first(), Qt::LeftButton);
        }
    });

    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, "menuBar not found");
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("about"))
            {
                actionFound = true;
                action->trigger();
                break;
            }
        }
    }

    spyAboutAction.wait();

    // Assert
    QVERIFY2(actionFound, qPrintable(QString::fromUtf8(u8"no action found")));
    QVERIFY2(aboutMessageBoxFound, qPrintable(QString::fromUtf8(u8"aboutMessageBox not found")));
    QVERIFY2(aboutMessageBoxHasOneButton, qPrintable(QString::fromUtf8(u8"aboutMessageBox does not have exactly one button")));

    QVERIFY2(mw.aboutMessageBox == nullptr, qPrintable(QString::fromUtf8(u8"aboutMessageBox still reachable")));
}

#endif // _USE_LONG_TEST

QTEST_MAIN(FrontendTest)

#include "tst_mainwindow.moc"
