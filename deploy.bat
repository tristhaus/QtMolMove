set PATH=%PATH%;C:\Qt\6.0.3\msvc2019_64\bin

IF EXIST .\Deploy-Release (
    rmdir .\Deploy-Release /s /q
)
md .\Deploy-Release

windeployqt --dir .\Deploy-Release --no-translations ..\build-QtMolMoveSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtMolMove\release\QtMolMove.exe
copy ..\build-QtMolMoveSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtMolMove\release\QtMolMove.exe .\Deploy-Release\
copy .\LICENSE .\Deploy-Release\
copy .\README.md .\Deploy-Release\
copy .\LIESMICH.md .\Deploy-Release\
copy .\DistributionItems\example-trajectory.json .\Deploy-Release\
copy .\DistributionItems\trajectory.schema.json .\Deploy-Release\

IF EXIST .\Deploy-Release-PDB (
    rmdir .\Deploy-Release-PDB /s /q
)
md .\Deploy-Release-PDB

windeployqt --pdb --dir .\Deploy-Release-PDB --no-translations ..\build-QtMolMoveSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtMolMove\release\QtMolMove.exe
copy ..\build-QtMolMoveSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtMolMove\release\QtMolMove.exe .\Deploy-Release-PDB\
copy ..\build-QtMolMoveSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtMolMove\release\QtMolMove.map .\Deploy-Release-PDB\
copy ..\build-QtMolMoveSuper-Desktop_Qt_6_0_3_MSVC2019_64bit-Release\QtMolMove\release\QtMolMove.pdb .\Deploy-Release-PDB\
copy .\LICENSE .\Deploy-Release-PDB\
copy .\README.md .\Deploy-Release-PDB\
copy .\LIESMICH.md .\Deploy-Release-PDB\
copy .\DistributionItems\example-trajectory.json .\Deploy-Release-PDB\
copy .\DistributionItems\trajectory.schema.json .\Deploy-Release-PDB\
