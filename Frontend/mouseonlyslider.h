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

#ifndef MOUSEONLYSLIDER_H
#define MOUSEONLYSLIDER_H

#include <QObject>
#include <QSlider>

/*!
 * \brief The MouseOnlySlider class is a QSlider that ignores keyboard input.
 */
class MouseOnlySlider : public QSlider
{
    Q_OBJECT
public:
    /*!
     * \brief Initializes a new instance.
     * \param parent The owning parent.
     */
    explicit MouseOnlySlider(QWidget* parent = nullptr)
        : QSlider(parent)
    {
        this->setPageStep(0);
        this->setSingleStep(0);
    }

protected:
    /*!
     * \reimp
     */
    void keyPressEvent(QKeyEvent *) override //NOLINT (hicpp-named-parameter)
    {
        // ignore all keyboard events
    }
};

#endif // MOUSEONLYSLIDER_H
