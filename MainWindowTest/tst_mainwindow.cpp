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
#include "../TestHelper/MemoryRepository.h"
#include "../TestHelper/TestRepository.h"

class FrontendTest : public QObject
{
    Q_OBJECT

private:
    const int SingleShotInterval = 1000;

public:
    FrontendTest();

private slots:
    static void ConstructionShallWorkCompletely();
#ifdef _USE_LONG_TEST
    void AboutButtonShallTriggerDialogAndOKShallClose();
    void OneFrameTrajectoryShallDisableAllButtons();
    void ThreeFrameTrajectoryShallTransitionStates();
    void LoadActionShallLoadFromRepository();
    void PlayShallRunToEnd();
    void PlayAndPauseShallYieldCorrectState();
    void PlayPausePlayShallRunToEnd();
    void PlayAndStopShallYieldCorrectState();
    void SlowerFasterAndEntryShallChangeInterval();
#endif // _USE_LONG_TEST
};

FrontendTest::FrontendTest()
= default;

void FrontendTest::ConstructionShallWorkCompletely() //NOLINT(google-readability-function-size, hicpp-function-size, readability-function-size)
{
    try
    {
        // Act
        MainWindow mw(std::make_shared<TestHelper::TestRepository>(4));

        // Assert
        QVERIFY2(mw.ui->menubar, qPrintable(QString::fromUtf8(u8"not menu bar")));
        QVERIFY2(mw.ui->loadMenuAction, qPrintable(QString::fromUtf8(u8"not created load menu action")));
        QVERIFY2(mw.ui->aboutMenuAction, qPrintable(QString::fromUtf8(u8"not created about menu action")));

        QVERIFY2(mw.ui->centralwidget, qPrintable(QString::fromUtf8(u8"not created central widget")));
        QVERIFY2(mw.ui->mainLayout, qPrintable(QString::fromUtf8(u8"not created main layout")));

        QVERIFY2(mw.ui->plot, qPrintable(QString::fromUtf8(u8"not created plot")));

        QVERIFY2(mw.ui->slider, qPrintable(QString::fromUtf8(u8"not created slider")));

        QVERIFY2(mw.ui->controlFrame, qPrintable(QString::fromUtf8(u8"not created control frame")));
        QVERIFY2(mw.ui->controlLayout, qPrintable(QString::fromUtf8(u8"not created control layout")));

        QVERIFY2(mw.ui->playPauseButton, qPrintable(QString::fromUtf8(u8"not created play/pause button")));
        QVERIFY2(mw.ui->stopButton, qPrintable(QString::fromUtf8(u8"not created stop button")));
        QVERIFY2(mw.ui->stepBackButton, qPrintable(QString::fromUtf8(u8"not created step back button")));
        QVERIFY2(mw.ui->stepForwardButton, qPrintable(QString::fromUtf8(u8"not created step forward button")));
        QVERIFY2(mw.ui->slowerButton, qPrintable(QString::fromUtf8(u8"not created slower button")));
        QVERIFY2(mw.ui->intervalEdit, qPrintable(QString::fromUtf8(u8"not created step interval edit")));
        QVERIFY2(mw.ui->fasterButton, qPrintable(QString::fromUtf8(u8"not created faster button")));
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
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(4));
    auto ui = mw.ui;

    // spy needed such that events actually happen
    QSignalSpy spyAboutAction(ui->aboutMenuAction, &QAction::triggered);

    bool actionFound = false;

    // Act
    bool aboutMessageBoxFound = false;
    bool aboutMessageBoxHasOneButton = false;
    QTimer::singleShot(SingleShotInterval, [&]()
    {
        aboutMessageBoxFound = mw.aboutMessageBox != nullptr;
        aboutMessageBoxHasOneButton = mw.aboutMessageBox->buttons().count() == 1 && mw.aboutMessageBox->buttons().first() != nullptr;
        if (aboutMessageBoxFound && aboutMessageBoxHasOneButton)
        {
            QTest::mouseClick(mw.aboutMessageBox->buttons().first(), Qt::LeftButton);
        }
    });

    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
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

    spyAboutAction.wait(100);

    // Assert
    QVERIFY2(actionFound, qPrintable(QString::fromUtf8(u8"no action found")));
    QVERIFY2(aboutMessageBoxFound, qPrintable(QString::fromUtf8(u8"aboutMessageBox not found")));
    QVERIFY2(aboutMessageBoxHasOneButton, qPrintable(QString::fromUtf8(u8"aboutMessageBox does not have exactly one button")));

    QVERIFY2(mw.aboutMessageBox == nullptr, qPrintable(QString::fromUtf8(u8"aboutMessageBox still reachable")));
}

void FrontendTest::OneFrameTrajectoryShallDisableAllButtons()
{
    // Arrange
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(1));
    auto ui = mw.ui;
    mw.presetFilename = QString::fromUtf8("does not matter");

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);

    bool actionFound = false;

    // Act
    bool hasNoItemsBeforeLoading = ui->plot->itemCount() == 0;

    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                actionFound = true;
                action->trigger();
                break;
            }
        }
    }

    spyLoadAction.wait(100);

    bool hasItemsAfterLoading = ui->plot->itemCount() > 0;

    bool playPauseButtonDisabled = !ui->playPauseButton->isEnabled();
    bool stopButtonDisabled = !ui->stopButton->isEnabled();
    bool stepBackButtonDisabled = !ui->stepBackButton->isEnabled();
    bool stepForwardButtonDisabled = !ui->stepForwardButton->isEnabled();

    // Assert
    QVERIFY2(hasNoItemsBeforeLoading, qPrintable(QString::fromUtf8(u8"no items found in plot")));
    QVERIFY2(actionFound, qPrintable(QString::fromUtf8(u8"no action found")));
    QVERIFY2(hasItemsAfterLoading, qPrintable(QString::fromUtf8(u8"no items found in plot")));

    QVERIFY2(playPauseButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for playPauseButton")));
    QVERIFY2(stopButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stopButton")));
    QVERIFY2(stepBackButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepBackButton")));
    QVERIFY2(stepForwardButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepForwardButton")));
}

void FrontendTest::ThreeFrameTrajectoryShallTransitionStates()
{
    // Arrange
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(3));
    auto ui = mw.ui;
    mw.presetFilename = QString::fromUtf8("does not matter");

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);
    QSignalSpy spyStepBackButton(ui->stepBackButton, &QAbstractButton::pressed);
    QSignalSpy spyStepForwardButton(ui->stepForwardButton, &QAbstractButton::pressed);

    bool actionFound = false;

    // Act
    bool hasNoItemsBeforeLoading = ui->plot->itemCount() == 0;

    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                actionFound = true;
                action->trigger();
                break;
            }
        }
    }

    spyLoadAction.wait(100);

    bool hasItemsAfterLoading = ui->plot->itemCount() > 0;

    // Assert
    QVERIFY2(hasNoItemsBeforeLoading, qPrintable(QString::fromUtf8(u8"no items found in plot")));
    QVERIFY2(actionFound, qPrintable(QString::fromUtf8(u8"no action found")));
    QVERIFY2(hasItemsAfterLoading, qPrintable(QString::fromUtf8(u8"no items found in plot")));

    { // stage 1 : after loading
        bool playPauseButtonEnabled = ui->playPauseButton->isEnabled();
        bool stopButtonDisabled = !ui->stopButton->isEnabled();
        bool stepBackButtonDisabled = !ui->stepBackButton->isEnabled();
        bool stepForwardButtonEnabled = ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for playPauseButton")));
        QVERIFY2(stopButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stopButton")));
        QVERIFY2(stepBackButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepForwardButton")));
    }

    // Act
    QTest::mouseClick(mw.ui->stepForwardButton, Qt::LeftButton);

    { // stage 2 : one step forward taken
        bool playPauseButtonEnabled = ui->playPauseButton->isEnabled();
        bool stopButtonEnabled = ui->stopButton->isEnabled();
        bool stepBackButtonEnabled = ui->stepBackButton->isEnabled();
        bool stepForwardButtonEnabled = ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for playPauseButton")));
        QVERIFY2(stopButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stopButton")));
        QVERIFY2(stepBackButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepForwardButton")));
    }

    // Act
    QTest::mouseClick(mw.ui->stepForwardButton, Qt::LeftButton);

    { // stage 3 : on last frame
        bool playPauseButtonDisabled = !ui->playPauseButton->isEnabled();
        bool stopButtonEnabled = ui->stopButton->isEnabled();
        bool stepBackButtonEnabled = ui->stepBackButton->isEnabled();
        bool stepForwardButtonDisabled = !ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for playPauseButton")));
        QVERIFY2(stopButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stopButton")));
        QVERIFY2(stepBackButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepForwardButton")));
    }

    // Act
    QTest::mouseClick(mw.ui->stepBackButton, Qt::LeftButton);

    { // stage 4 : on middle frame again
        bool playPauseButtonEnabled = ui->playPauseButton->isEnabled();
        bool stopButtonEnabled = ui->stopButton->isEnabled();
        bool stepBackButtonEnabled = ui->stepBackButton->isEnabled();
        bool stepForwardButtonEnabled = ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for playPauseButton")));
        QVERIFY2(stopButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stopButton")));
        QVERIFY2(stepBackButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepForwardButton")));
    }

    // Act
    QTest::mouseClick(mw.ui->stepBackButton, Qt::LeftButton);

    { // stage 5 : back on first frame
        bool playPauseButtonEnabled = ui->playPauseButton->isEnabled();
        bool stopButtonDisabled = !ui->stopButton->isEnabled();
        bool stepBackButtonDisabled = !ui->stepBackButton->isEnabled();
        bool stepForwardButtonEnabled = ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for playPauseButton")));
        QVERIFY2(stopButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stopButton")));
        QVERIFY2(stepBackButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepForwardButton")));
    }
}

void FrontendTest::LoadActionShallLoadFromRepository()
{
    // Arrange
    Backend::Viewport viewport(-10.0, 10.0, -10.0, 10.0);

    auto particles = std::vector<Backend::Particle>
    {
            Backend::Particle(1),
            Backend::Particle(2)
    };

    auto frames = std::vector<Backend::Frame>
    {
            Backend::Frame(std::vector<Backend::Coordinate> { Backend::Coordinate(-6.0, 4.0), Backend::Coordinate( 6.0, -4.0) }),
            Backend::Frame(std::vector<Backend::Coordinate> { Backend::Coordinate(-3.0, 4.0), Backend::Coordinate( 3.0, -4.0) }),
            Backend::Frame(std::vector<Backend::Coordinate> { Backend::Coordinate( 3.0, 4.0), Backend::Coordinate(-3.0, -4.0) }),
            Backend::Frame(std::vector<Backend::Coordinate> { Backend::Coordinate( 6.0, 4.0), Backend::Coordinate(-6.0, -4.0) })
    };

    auto trajectory = std::make_shared<Backend::Trajectory>(1.25, viewport, particles, frames);

    auto repository = std::make_shared<TestHelper::MemoryRepository>();

    std::string identifier = "something";

    repository->Save(identifier, trajectory);

    MainWindow mw(repository);
    auto ui = mw.ui;

    // Act
    bool stepNotPossible = !mw.ui->stepForwardButton->isEnabled();

    mw.presetFilename = QString::fromUtf8(identifier);

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);

    bool actionFound = false;

    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                actionFound = true;
                action->trigger();
                break;
            }
        }
    }

    spyLoadAction.wait(100);

    bool stepPossible = mw.ui->stepForwardButton->isEnabled();

    QVERIFY2(stepNotPossible, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepForwardButton")));
    QVERIFY2(stepPossible, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepForwardButton")));
}

void FrontendTest::PlayShallRunToEnd()
{
    // Arrange
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(5));
    mw.playInterval = 50;
    auto ui = mw.ui;
    mw.presetFilename = QString::fromUtf8("does not matter");

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);
    QSignalSpy spyPlayPauseButton(ui->playPauseButton, &QAbstractButton::pressed);

    // Act
    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                action->trigger();
                break;
            }
        }
    }

    spyLoadAction.wait(100);

    QTest::mouseClick(mw.ui->playPauseButton, Qt::LeftButton);
    spyPlayPauseButton.wait();

    // Assert
    {
        bool playPauseButtonDisabled = !ui->playPauseButton->isEnabled();
        bool stopButtonEnabled = ui->stopButton->isEnabled();
        bool stepBackButtonEnabled = ui->stepBackButton->isEnabled();
        bool stepForwardButtonDisabled = !ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for playPauseButton")));
        QVERIFY2(stopButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stopButton")));
        QVERIFY2(stepBackButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepForwardButton")));
    }
}

void FrontendTest::PlayAndPauseShallYieldCorrectState()
{
    // Arrange
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(20));
    mw.playInterval = 50;
    auto ui = mw.ui;
    mw.presetFilename = QString::fromUtf8("does not matter");

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);
    QSignalSpy spyPlayPauseButton(ui->playPauseButton, &QAbstractButton::pressed);

    // Act
    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                action->trigger();
                break;
            }
        }
    }

    spyLoadAction.wait(100);

    QTest::mouseClick(mw.ui->playPauseButton, Qt::LeftButton);
    spyPlayPauseButton.wait(100);

    QThread::msleep(500);

    QTest::mouseClick(mw.ui->playPauseButton, Qt::LeftButton);
    spyPlayPauseButton.wait(100);

    // Assert
    {
        bool playPauseButtonEnabled = ui->playPauseButton->isEnabled();
        bool stopButtonEnabled = ui->stopButton->isEnabled();
        bool stepBackButtonEnabled = ui->stepBackButton->isEnabled();
        bool stepForwardButtonEnabled = ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for playPauseButton")));
        QVERIFY2(stopButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stopButton")));
        QVERIFY2(stepBackButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepForwardButton")));
    }
}

void FrontendTest::PlayPausePlayShallRunToEnd()
{
    // Arrange
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(20));
    mw.playInterval = 50;
    auto ui = mw.ui;
    mw.presetFilename = QString::fromUtf8("does not matter");

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);
    QSignalSpy spyPlayPauseButton(ui->playPauseButton, &QAbstractButton::pressed);

    // Act
    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                action->trigger();
                break;
            }
        }
    }

    spyLoadAction.wait(100);

    QTest::mouseClick(mw.ui->playPauseButton, Qt::LeftButton);
    spyPlayPauseButton.wait(100);

    QThread::msleep(500);

    QTest::mouseClick(mw.ui->playPauseButton, Qt::LeftButton);
    spyPlayPauseButton.wait(100);

    QTest::mouseClick(mw.ui->playPauseButton, Qt::LeftButton);
    spyPlayPauseButton.wait();

    // Assert
    {
        bool playPauseButtonDisabled = !ui->playPauseButton->isEnabled();
        bool stopButtonEnabled = ui->stopButton->isEnabled();
        bool stepBackButtonEnabled = ui->stepBackButton->isEnabled();
        bool stepForwardButtonDisabled = !ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for playPauseButton")));
        QVERIFY2(stopButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stopButton")));
        QVERIFY2(stepBackButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepForwardButton")));
    }
}

void FrontendTest::PlayAndStopShallYieldCorrectState()
{
    // Arrange
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(20));
    mw.playInterval = 50;
    auto ui = mw.ui;
    mw.presetFilename = QString::fromUtf8("does not matter");

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);
    QSignalSpy spyPlayPauseButton(ui->playPauseButton, &QAbstractButton::pressed);
    QSignalSpy spyStopButton(ui->stopButton, &QAbstractButton::pressed);

    // Act
    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                action->trigger();
                break;
            }
        }
    }

    spyLoadAction.wait(100);

    QTest::mouseClick(mw.ui->playPauseButton, Qt::LeftButton);
    spyPlayPauseButton.wait(100);

    QThread::msleep(200);

    QTest::mouseClick(mw.ui->stopButton, Qt::LeftButton);
    spyStopButton.wait(100);

    // Assert
    {
        bool playPauseButtonEnabled = ui->playPauseButton->isEnabled();
        bool stopButtonDisabled = !ui->stopButton->isEnabled();
        bool stepBackButtonDisabled = !ui->stepBackButton->isEnabled();
        bool stepForwardButtonEnabled = ui->stepForwardButton->isEnabled();

        // Assert
        QVERIFY2(playPauseButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for playPauseButton")));
        QVERIFY2(stopButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stopButton")));
        QVERIFY2(stepBackButtonDisabled, qPrintable(QString::fromUtf8(u8"incorrect state (enabled) for stepBackButton")));
        QVERIFY2(stepForwardButtonEnabled, qPrintable(QString::fromUtf8(u8"incorrect state (disabled) for stepForwardButton")));
    }
}

void FrontendTest::SlowerFasterAndEntryShallChangeInterval()
{
    // Arrange
    MainWindow mw(std::make_shared<TestHelper::TestRepository>(20));
    mw.playInterval = 50;
    auto ui = mw.ui;
    mw.presetFilename = QString::fromUtf8("does not matter");

    // spy needed such that events actually happen
    QSignalSpy spyLoadAction(ui->loadMenuAction, &QAction::triggered);
    QSignalSpy spySlowerButton(ui->slowerButton, &QAbstractButton::pressed);
    QSignalSpy spyIntervalEdit(ui->intervalEdit, &QSpinBox::valueChanged);
    QSignalSpy spyFasterButton(ui->fasterButton, &QAbstractButton::pressed);

    // Act
    auto menuBar = ui->menubar;
    QVERIFY2(menuBar != nullptr, qPrintable(QString::fromUtf8(u8"menuBar not found")));
    if (menuBar != nullptr)
    {
        auto actions = menuBar->actions();
        for (auto action : actions)
        {
            if (action->objectName() == QString::fromUtf8("load"))
            {
                action->trigger();
                break;
            }
        }
    }

    int displayValue = ui->intervalEdit->value();
    int internalValue = mw.playInterval;

    spyLoadAction.wait(100);

    QTest::mouseClick(mw.ui->slowerButton, Qt::LeftButton);
    spySlowerButton.wait(100);

    QThread::msleep(200);

    // Assert
    {
        int newDisplayValue = ui->intervalEdit->value();
        int newInternalValue = mw.playInterval;

        bool internalValueIsHigher = newInternalValue > internalValue;
        bool displayValueIsHigher = newDisplayValue > displayValue;
        bool valuesAreSynced = newDisplayValue == newInternalValue;

        // Assert
        QVERIFY2(internalValueIsHigher, qPrintable(QString::fromUtf8(u8"internal value is not higher")));
        QVERIFY2(displayValueIsHigher, qPrintable(QString::fromUtf8(u8"display value is not higher")));
        QVERIFY2(valuesAreSynced, qPrintable(QString::fromUtf8(u8"values are not synced")));
    }

    displayValue = ui->intervalEdit->value();
    internalValue = mw.playInterval;

    QTest::mouseClick(mw.ui->fasterButton, Qt::LeftButton);
    spyFasterButton.wait(100);

    // Assert
    {
        int newDisplayValue = ui->intervalEdit->value();
        int newInternalValue = mw.playInterval;

        bool displayValueIsLower = newDisplayValue < displayValue;
        bool internalValueIsLower = newInternalValue < internalValue;
        bool valuesAreSynced = newDisplayValue == newInternalValue;

        // Assert
        QVERIFY2(displayValueIsLower, qPrintable(QString::fromUtf8(u8"display value is not lower")));
        QVERIFY2(internalValueIsLower, qPrintable(QString::fromUtf8(u8"internal value is not lower")));
        QVERIFY2(valuesAreSynced, qPrintable(QString::fromUtf8(u8"values are not synced")));
    }

    QTest::keySequence(ui->intervalEdit, QKeySequence(QKeySequence::StandardKey::SelectAll));
    QTest::keyClicks(ui->intervalEdit, QString("324"));

    // Assert
    {
        int newDisplayValue = ui->intervalEdit->value();
        int newInternalValue = mw.playInterval;

        bool displayValueIsCorrect = newDisplayValue == 324;
        bool internalValueIsCorrect = newInternalValue == 324;

        // Assert
        QVERIFY2(displayValueIsCorrect, qPrintable(QString::fromUtf8(u8"display value is not correct")));
        QVERIFY2(internalValueIsCorrect, qPrintable(QString::fromUtf8(u8"internal value is not correct")));
    }
}

#endif // _USE_LONG_TEST

QTEST_MAIN(FrontendTest)

#include "tst_mainwindow.moc"
