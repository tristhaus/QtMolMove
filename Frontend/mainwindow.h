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
#include <atomic>

#include "../Backend/FixedRepository.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FrontendTest;

class MainWindow : public QMainWindow //NOLINT (cppcoreguidelines-special-member-functions)
{
    Q_OBJECT

    friend FrontendTest;

private:
    std::shared_ptr<Backend::Repository> repository;
    std::shared_ptr<Backend::Repository> fixedRepository;
    Ui::MainWindow *ui;

    std::atomic_uint index;
    std::atomic_bool isPlaying;
    QTimer playTimer;
    std::atomic_bool sliderIsPressed;
    QTimer sliderTimer;
    /*!
     * \brief The wait time before updating on slider moving in milliseconds.
     */
    const int sliderTimerInterval;

    /*!
     * \brief The time between frames in milliseconds.
     */
    std::atomic_int playInterval;
    const int maxPlayInterval;
    const int minPlayInterval;

    std::unique_ptr<QMessageBox> aboutMessageBox;
    std::shared_ptr<Backend::Trajectory> trajectory;
    std::vector<QColor> colors;
    std::vector<QCPItemEllipse*> ellipses;

    /*!
     * \brief presetFilename allows to set a filename and
     *        thus circumvent the file dialog, e.g. for testing.
     */
    QString presetFilename;
public:
    explicit MainWindow(std::shared_ptr<Backend::Repository> repository, QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    void InitPlot();
    void Update();
    void UpdatePlot();
    void UpdateIntervalEdit();
    void LoadTrajectory();
    void LoadFixedTrajectory();
    void ShowAboutDialog();
    void StartPlaying();
    void StopPlaying();
    void ResetToBeginning();
    void BackOneFrame();
    void ForwardOneFrame();
    void MakeIntervalSlower();
    void MakeIntervalFaster();
    void HandleIntervalChange(int interval);
    void UpdateSliderRange(int maximumIndex);
    void BeginScrolling();
    void Scroll();
    void EndScrolling();
    QColor GetColorFor(int id);

private slots:
    void OnPlayTimerTimeout();
    void OnSliderTimerTimeout();
    void OnLoadTriggered();
    void OnLoadFixedTriggered();
    void OnAboutTriggered();
    void OnSliderPressed();
    void OnSliderMoved();
    void OnSliderReleased();
    void OnPlayPausePressed();
    void OnStopPressed();
    void OnStepBackPressed();
    void OnStepForwardPressed();
    void OnSlowerPressed();
    void OnFasterPressed();
    void OnIntervalEditValueChanged(int newValue);

private:
    /*!
     * \brief The Resetter class executes the contained action on destruction.
     *        The usual application is to reset something.
     */
    class Resetter
    {
    private:
        std::function<void()> action;

    public:
        /*!
         * \brief Initializes a new instance holding the supplied action.
         * \param action The action to store and execute on destruction.
         */
        explicit Resetter(std::function<void()> action) : action(std::move(action))
        {
        }
        ~Resetter()
        {
            this->action();
        }
        Resetter(const Resetter&) = delete;
        Resetter(Resetter&&) = delete;
        Resetter& operator=(const Resetter&) = delete;
        Resetter& operator=(Resetter&&) = delete;
    };
};

#endif // MAINWINDOW_H
