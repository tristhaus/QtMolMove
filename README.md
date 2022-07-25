# QtMolMove

Copyright tristhaus 2022 and later.

A simple program to display 2D trajectories of spherical objects, such as moving planets or a particle simulation.

![main](/../screenshot/screenshot.png?raw=true)

## For Users

This is beta status. For an example of a valid trajectory, see [example-trajectory.json](/DistributionItems/example-trajectory.json). The schema is defined in [trajectory.schema.json](/DistributionItems/trajectory.schema.json).

### Color Code

| ID | 0 | 1 | 2 | 3 | 4 |
| :--: | :--: | :--: | :--: | :--: | :--: |
| RGB Color | `4169e1` | `2f4f4f` | `800000` | `ffd700` | `00008b` |
|  | ![00](/../screenshot/00.png?raw=true) | ![01](/../screenshot/01.png?raw=true) | ![02](/../screenshot/02.png?raw=true) | ![03](/../screenshot/03.png?raw=true) | ![04](/../screenshot/04.png?raw=true) |

| ID | 5 | 6 | 7 | 8 | 9 |
| :--: | :--: | :--: | :--: | :--: | :--: |
| RGB Color | `00ffff` | `da70d6` | `2e8b57` | `00bfff` | `ff8c00` |
|  | ![05](/../screenshot/05.png?raw=true) | ![06](/../screenshot/06.png?raw=true) | ![07](/../screenshot/07.png?raw=true) | ![08](/../screenshot/08.png?raw=true) | ![09](/../screenshot/09.png?raw=true) |

| ID | 10 | 11 | 12 | 13 | 14 |
| :--: | :--: | :--: | :--: | :--: | :--: |
| RGB Color | `ff0000` | `0000ff` | `eee8aa` | `ff1493` | `808000` |
|  | ![10](/../screenshot/10.png?raw=true) | ![11](/../screenshot/11.png?raw=true) | ![12](/../screenshot/12.png?raw=true) | ![13](/../screenshot/13.png?raw=true) | ![14](/../screenshot/14.png?raw=true) |

| ID | 15 | 16 | 17 | 18 | 19 |
| :--: | :--: | :--: | :--: | :--: | :--: |
| RGB Color | `d8bfd8` | `ff00ff` | `00ff7f` | `f08080` | `adff2f` |
|  | ![15](/../screenshot/15.png?raw=true) | ![16](/../screenshot/16.png?raw=true) | ![17](/../screenshot/17.png?raw=true) | ![18](/../screenshot/18.png?raw=true) | ![19](/../screenshot/19.png?raw=true) |

## For Developers

I am currently not looking for contributors.

It is necessary to define `_SKIP_LONG_TEST` or `_USE_LONG_TEST` as additional arguments to `qmake`. [Google Test](https://github.com/google/googletest) must be available and the `GOOGLETEST_DIR` environment variable must be set to its root directory. `clang-tidy` has been added, be sure to configure QtCreator to use the [.clang-tidy](.clang-tidy) file.

The project is localized and you should build the translation to be included into the resource file of the frontend, which boils down to running `lrelease`. I suggest adding steps
  * `/path/to/lupdate-pro.exe -noobsolete -locations none /path/to/QtPollyNomSuper.pro`
  * `/path/to/lrelease-pro.exe /path/to/QtPollyNomSuper.pro`

to the build process.

## License

All source code licensed under GPL v3 (see LICENSE for terms), unless noted otherwise in the Attributions.

## Attributions

Icon (Letters "MM", particles, and planetary system) by tristhaus.

Graphical user interface built using [Qt](https://doc.qt.io/).

[QCustomPlot](https://www.qcustomplot.com/) library (Version 2.1.0) by Emanuel Eichhammer used under the [GPL v3](https://www.gnu.org/licenses/gpl-3.0.html).

JSON de/serialization via [rapidjson](https://rapidjson.org/) provided by THL A29 Limited, a Tencent company, and Milo Yip used under the [MIT license](http://opensource.org/licenses/MIT).

GoogleTest used under the following conditions:

```
Copyright 2008, Google Inc.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:

    * Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
copyright notice, this list of conditions and the following disclaimer
in the documentation and/or other materials provided with the
distribution.
    * Neither the name of Google Inc. nor the names of its
contributors may be used to endorse or promote products derived from
this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
```
