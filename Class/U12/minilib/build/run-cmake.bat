@IF "%SWO3_LIBS_DIR%"=="" set SWO3_LIBS_DIR=C:\public\SWO3\SWO3_LIBS
cmake.exe -DVCPKG_TARGET_TRIPLET="x64-windows" -DCMAKE_TOOLCHAIN_FILE="%SWO3_LIBS_DIR%\scripts\buildsystems\vcpkg.cmake" -G"Visual Studio 16 2019" ..
PAUSE