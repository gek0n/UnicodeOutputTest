@echo off
if "%1" == "" (set BUILD_DIR=build) else (set BUILD_DIR=build_%1)
if "%1" == "mingw32" (
  set GENERATOR="MinGW Makefiles"
  set MAKE_CMD="C:\MinGW\bin\mingw32-make" TestEncoding
  set RUN_CMD=.\TestEncoding.exe
) else (
  if "%1" == "mingw64" (
    set GENERATOR="MinGW Makefiles"
    set MAKE_CMD="C:\MinGW64\bin\mingw32-make" TestEncoding
    set RUN_CMD=.\TestEncoding.exe
  ) else (
    if "%1" == "vs2019" (
      set GENERATOR="Visual Studio 16 2019"
      call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
      set MAKE_CMD=msbuild TestEncoding.vcxproj
      set RUN_CMD=.\Debug\TestEncoding.exe
    ) else (
      if "%1" == "clang" (
        set GENERATOR="MinGW Makefiles"
        set MAKE_CMD=make TestEncoding
        set COMPILERS=-DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang
        set RUN_CMD=.\TestEncoding.exe
      ) else (
        if "%1" == "nmake" (
          set GENERATOR="NMake Makefiles"
          call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
          set MAKE_CMD=nmake TestEncoding
          set RUN_CMD=.\TestEncoding.exe
        ) else (
          echo Use "mingv", "vs2019" or "clang"
          exit 1
        )
      )
    )
  )
)

if "%2" == "WIDE" (
  set IS_WIDE=ON
) else (
  set IS_WIDE=OFF
)

mkdir %BUILD_DIR%
pushd %BUILD_DIR% && ^
cmake -DCMAKE_BUILD_TYPE=Debug -DIS_WIDE=%IS_WIDE% -G %GENERATOR% %COMPILERS% .. && ^
%MAKE_CMD% && ^
%RUN_CMD%
popd