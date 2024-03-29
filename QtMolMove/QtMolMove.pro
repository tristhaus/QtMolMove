#
# This file is part of QtMolMove.
#
# QtMolMove is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# QtMolMove is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with QtMolMove.  If not, see <http://www.gnu.org/licenses/>.
#
#

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

include(../Frontend/Frontend.pri)
include(../Backend/Backend.pri)

SOURCES += main.cpp

RC_ICONS = icon.ico

RESOURCES += \
    $$PWD/icon.ico \
    $$PWD/back256.png \
    $$PWD/faster256.png \
    $$PWD/forward256.png \
    $$PWD/pause256.png \
    $$PWD/play256.png \
    $$PWD/slower256.png \
    $$PWD/stop256.png

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

QMAKE_CXXFLAGS_RELEASE+= /Zi
QMAKE_LFLAGS_RELEASE+= /INCREMENTAL:NO /Debug /MAP
