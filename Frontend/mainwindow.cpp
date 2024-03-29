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

MainWindow::MainWindow(std::shared_ptr<Backend::Repository> repository, QWidget *parent)
    : QMainWindow(parent),
      repository(std::move(repository)),
      ui(new Ui::MainWindow),
      index(0),
      isPlaying(false),
      playTimer(QTimer(this)),
      sliderIsPressed(false),
      sliderTimer(QTimer(this)),
      sliderTimerInterval(10),
      playInterval(40),
      maxPlayInterval(2000),
      minPlayInterval(10)
{
    ui->setupUi(this);

    ui->intervalEdit->setMaximum(this->maxPlayInterval);
    ui->intervalEdit->setMinimum(this->minPlayInterval);

    connect(&(this->playTimer), &QTimer::timeout, this, &MainWindow::OnPlayTimerTimeout);
    this->playTimer.setSingleShot(false);
    this->playTimer.setInterval(this->playInterval);

    connect(&(this->sliderTimer), &QTimer::timeout, this, &MainWindow::OnSliderTimerTimeout);
    this->sliderTimer.setSingleShot(true);
    this->sliderTimer.setInterval(this->sliderTimerInterval);

    connect(ui->loadMenuAction, &QAction::triggered, this, &MainWindow::OnLoadTriggered);
    connect(ui->aboutMenuAction, &QAction::triggered, this, &MainWindow::OnAboutTriggered);
    connect(ui->slider, &QSlider::sliderPressed, this, &MainWindow::OnSliderPressed);
    connect(ui->slider, &QSlider::sliderMoved, this, &MainWindow::OnSliderMoved);
    connect(ui->slider, &QSlider::sliderReleased, this, &MainWindow::OnSliderReleased);
    connect(ui->playPauseButton, &QAbstractButton::pressed, this, &MainWindow::OnPlayPausePressed);
    connect(ui->stopButton, &QAbstractButton::pressed, this, &MainWindow::OnStopPressed);
    connect(ui->stepBackButton, &QAbstractButton::pressed, this, &MainWindow::OnStepBackPressed);
    connect(ui->stepForwardButton, &QAbstractButton::pressed, this, &MainWindow::OnStepForwardPressed);
    connect(ui->slowerButton, &QAbstractButton::pressed, this, &MainWindow::OnSlowerPressed);
    connect(ui->fasterButton, &QAbstractButton::pressed, this, &MainWindow::OnFasterPressed);
    connect(ui->intervalEdit, &QSpinBox::valueChanged, this, &MainWindow::OnIntervalEditValueChanged);

    this->InitPlot();

    this->Update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitPlot()
{
    auto plot = this->ui->plot;

    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");
    plot->xAxis->setRange(-10.0, 10.0);
    plot->yAxis->setRange(-10.0, 10.0);

    this->colors.push_back(QColor::fromRgb(0x41, 0x69, 0xe1)); //royalblue
    this->colors.push_back(QColor::fromRgb(0x2f, 0x4f, 0x4f)); //darkslategray
    this->colors.push_back(QColor::fromRgb(0x80, 0x00, 0x00)); //maroon
    this->colors.push_back(QColor::fromRgb(0xff, 0xd7, 0x00)); //gold
    this->colors.push_back(QColor::fromRgb(0x00, 0x00, 0x8b)); //darkblue

    this->colors.push_back(QColor::fromRgb(0x00, 0xff, 0xff)); //aqua
    this->colors.push_back(QColor::fromRgb(0xda, 0x70, 0xd6)); //orchid
    this->colors.push_back(QColor::fromRgb(0x2e, 0x8b, 0x57)); //seagreen
    this->colors.push_back(QColor::fromRgb(0x00, 0xbf, 0xff)); //deepskyblue
    this->colors.push_back(QColor::fromRgb(0xff, 0x8c, 0x00)); //darkorange

    this->colors.push_back(QColor::fromRgb(0xff, 0x00, 0x00)); //red
    this->colors.push_back(QColor::fromRgb(0x00, 0x00, 0xff)); //blue
    this->colors.push_back(QColor::fromRgb(0xee, 0xe8, 0xaa)); //palegoldenrod
    this->colors.push_back(QColor::fromRgb(0xff, 0x14, 0x93)); //deeppink
    this->colors.push_back(QColor::fromRgb(0x80, 0x80, 0x00)); //olive

    this->colors.push_back(QColor::fromRgb(0xd8, 0xbf, 0xd8)); //thistle
    this->colors.push_back(QColor::fromRgb(0xff, 0x00, 0xff)); //fuchsia
    this->colors.push_back(QColor::fromRgb(0x00, 0xff, 0x7f)); //springgreen
    this->colors.push_back(QColor::fromRgb(0xf0, 0x80, 0x80)); //lightcoral
    this->colors.push_back(QColor::fromRgb(0xad, 0xff, 0x2f)); //greenyellow
}

void MainWindow::Update()
{
    auto hasMultiframeTrajectory = this->trajectory != nullptr && this->trajectory->Frames().size() > 1;

    this->ui->slider->setEnabled(hasMultiframeTrajectory);

    this->ui->playPauseButton->setEnabled(hasMultiframeTrajectory && this->index + 1 < this->trajectory->Frames().size());
    this->ui->stopButton->setEnabled(hasMultiframeTrajectory && this->index > 0);
    this->ui->stepBackButton->setEnabled(!this->isPlaying && hasMultiframeTrajectory && this->index > 0);
    this->ui->stepForwardButton->setEnabled(!this->isPlaying && hasMultiframeTrajectory && this->index + 1 < this->trajectory->Frames().size());

    this->ui->playPauseButton->setIcon(
                this->isPlaying && hasMultiframeTrajectory && this->index + 1 < this->trajectory->Frames().size()
                ? this->ui->pauseIcon
                : this->ui->playIcon);

    this->ui->slowerButton->setEnabled(this->playInterval > this->minPlayInterval);
    this->ui->fasterButton->setEnabled(this->playInterval < this->maxPlayInterval);

    this->ui->slider->setValue(this->index);

    this->UpdateIntervalEdit();

    this->UpdatePlot();
}

void MainWindow::UpdatePlot()
{
    if (this->trajectory == nullptr)
    {
        return;
    }

    auto plot = this->ui->plot;

    if (ellipses.empty())
    {
        auto viewport = this->trajectory->Viewport();

        plot->xAxis->setRange(viewport.minX, viewport.maxX);
        plot->yAxis->setRange(viewport.minY, viewport.maxY);

        auto particles = this->trajectory->Particles();

        for (auto & particle : particles)
        {
            auto color = this->GetColorFor(particle.id);
            auto ellipse = new QCPItemEllipse(plot);
            ellipse->setPen(color);
            ellipse->setBrush(color);

            this->ellipses.push_back(ellipse);
        }
    }

    auto frames = this->trajectory->Frames();
    auto & frame = frames[this->index];
    auto particleSize = this->trajectory->ParticleSize();

    for (unsigned int particleIndex = 0; particleIndex < this->trajectory->ParticleCount(); ++particleIndex)
    {
        auto ellipse = this->ellipses[particleIndex];
        auto coordinate = frame.coordinates[particleIndex];

        ellipse->topLeft->setCoords(coordinate.x - particleSize, coordinate.y + particleSize);
        ellipse->bottomRight->setCoords(coordinate.x + particleSize, coordinate.y - particleSize);
    }

    plot->replot();
}

void MainWindow::UpdateIntervalEdit()
{
    this->ui->intervalEdit->setValue(this->playInterval);
}

void MainWindow::UpdateSliderRange(int maximumIndex)
{
    this->ui->slider->setMinimum(0);
    this->ui->slider->setMaximum(maximumIndex);
}

QColor MainWindow::GetColorFor(int id)
{
    return this->colors[id % this->colors.size()];
}

void MainWindow::ShowAboutDialog()
{
    auto messageBoxTitleTemplate = QCoreApplication::translate("MainWindow", "About %1", nullptr);
    auto messageBoxTitle = messageBoxTitleTemplate.arg(QCoreApplication::translate("MainWindow", "QtMolMove", nullptr));

    //: Arg 1 is a placeholder for the program name. Format is Qt Rich Text.
    auto messageBoxTextTemplate = QCoreApplication::translate("MainWindow", R"(A simple program to display 2D trajectories of spherical objects.<br /><br />%1 Copyright (C) 2022 and later, tristhaus<br />This program comes with ABSOLUTELY NO WARRANTY.<br />This is free software, and you are welcome to redistribute it under certain conditions. See provided LICENSE file for details.<br /><br />Graphical user interface built using <a href="https://doc.qt.io/">Qt</a>.<br /><a href="https://www.qcustomplot.com/">QCustomPlot</a> library (Version 2.1.0) by Emanuel Eichhammer used under the <a href="https://www.gnu.org/licenses/gpl-3.0.html">GPL v3</a>.<br />JSON de/serialization via <a href="https://rapidjson.org/">rapidjson</a> provided by THL A29 Limited, a Tencent company, and Milo Yip used under the <a href="http://opensource.org/licenses/MIT">MIT license</a>.)", nullptr);
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

void MainWindow::StartPlaying()
{
    this->isPlaying = true;
    this->playTimer.start();

    this->ForwardOneFrame();
}

void MainWindow::StopPlaying()
{
    this->isPlaying = false;
    this->playTimer.stop();

    this->Update();
}

void MainWindow::ResetToBeginning()
{
    if (this->isPlaying)
    {
        this->StopPlaying();
    }

    this->index = 0;

    this->Update();
}

void MainWindow::LoadTrajectory()
{
    Resetter resetter([&](){ this->presetFilename.clear(); });

    auto list = QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);
    auto folder = QString(list.first());

    const QString FileFilter = QString::fromUtf8(u8"(*.json)");

    QString fileName = !this->presetFilename.isEmpty() ? this->presetFilename : QFileDialog::getOpenFileName(this, u8"", folder, FileFilter, nullptr, QFileDialog::Options());

    if (fileName.isEmpty())
    {
        return;
    }

    try
    {
        auto filenameBytes = fileName.toUtf8();
        std::string filename(filenameBytes.constData(), filenameBytes.length());
        this->trajectory = this->repository->Load(filename);
        this->ellipses.clear();
        this->index = 0U;
        this->ui->plot->clearItems();
    }
    catch(std::exception & exception)
    {
        QString messageBoxTitle = QCoreApplication::translate("MainWindow", "Error", nullptr);
        QString messageBoxTextTemplate = QCoreApplication::translate("MainWindow", "On attempted load, error occurred:\n%1", nullptr);
        QString errorMesssage = QString::fromUtf8(exception.what());
        QString messageBoxText = messageBoxTextTemplate.arg(errorMesssage);

        auto errorBox = std::make_unique<QMessageBox>(
                    QMessageBox::Icon::Critical,
                    messageBoxTitle,
                    messageBoxText);

        errorBox->exec();

        errorBox.reset();

        return;
    }

    this->Update();
    this->UpdateSliderRange(static_cast<int>(this->trajectory->Frames().size()) - 1);
}

void MainWindow::BackOneFrame()
{
    if (this->index > 0)
    {
        --(this->index);

        this->Update();
    }
}

void MainWindow::ForwardOneFrame()
{
    if (this->index + 1 < this->trajectory->Frames().size())
    {
        ++(this->index);

        this->Update();
    }
}

void MainWindow::MakeIntervalSlower()
{
    this->playInterval = std::max(this->minPlayInterval, static_cast<int>(std::round(1.1 * this->playInterval)));

    this->UpdateIntervalEdit();
}

void MainWindow::MakeIntervalFaster()
{
    this->playInterval = std::min(this->maxPlayInterval, static_cast<int>(std::round(0.9 * this->playInterval)));

    this->UpdateIntervalEdit();
}

void MainWindow::HandleIntervalChange(int interval)
{
    this->playInterval = interval;

    this->playTimer.setInterval(this->playInterval);

    this->Update();
}

void MainWindow::BeginScrolling()
{
    this->sliderIsPressed = true;
}

void MainWindow::Scroll()
{
    this->sliderTimer.stop();
    this->sliderTimer.start();
}

void MainWindow::EndScrolling()
{
    this->sliderIsPressed = false;

    this->sliderTimer.stop();

    this->index = this->ui->slider->value();
    this->Update();

    if (this->isPlaying)
    {
        this->playTimer.stop();
        this->playTimer.start();
    }
}

void MainWindow::OnPlayTimerTimeout()
{
    if (this->sliderIsPressed)
    {
        return;
    }

    this->ForwardOneFrame();

    if (this->index + 1 >= this->trajectory->Frames().size())
    {
        this->StopPlaying();
    }
}

void MainWindow::OnSliderTimerTimeout()
{
    this->index = this->ui->slider->value();
    this->Update();
}

void MainWindow::OnLoadTriggered()
{
    this->LoadTrajectory();
}

void MainWindow::OnAboutTriggered()
{
    this->ShowAboutDialog();
}

void MainWindow::OnSliderPressed()
{
    this->BeginScrolling();
}

void MainWindow::OnSliderMoved()
{
    this->Scroll();
}

void MainWindow::OnSliderReleased()
{
    this->EndScrolling();
}

void MainWindow::OnPlayPausePressed()
{
    this->isPlaying ? this->StopPlaying() : this->StartPlaying();
}

void MainWindow::OnStopPressed()
{
    this->ResetToBeginning();
}

void MainWindow::OnStepBackPressed()
{
    this->BackOneFrame();
}

void MainWindow::OnStepForwardPressed()
{
    this->ForwardOneFrame();
}

void MainWindow::OnSlowerPressed()
{
    this->MakeIntervalSlower();
}

void MainWindow::OnFasterPressed()
{
    this->MakeIntervalFaster();
}

void MainWindow::OnIntervalEditValueChanged(int newValue)
{
    this->HandleIntervalChange(newValue);
}
