@echo off
REM set "VS2019_HOME=C:\Program Files (x86)\Microsoft Visual Studio\2019\"
REM set "MINGW32_HOME=C:\MinGW\bin"
REM set "MINGW64_HOME=C:\MinGW64\bin"
REM set "CLANG_HOME=C:/LLVM/bin" REM Notice that CMAKE loves forward slashes
REM set "MAKE_HOME=C:\MinGW\bin"
REM set "NMAKE_HOME=C:\Program Files (x86)\Microsoft Visual Studio\2019\"
if "%1" == "" (set BUILD_DIR=build) else (set BUILD_DIR=build_%1)
if "%1" == "mingw32" (
  if "%MINGW32_HOME%" == "" (
    echo "Specify MINGW32_HOME variable before use"
    exit 2
  )
  set GENERATOR="MinGW Makefiles"
  set MAKE_CMD="%MINGW32_HOME%\mingw32-make" TestEncoding
  set RUN_CMD=.\TestEncoding.exe
) else (
  if "%1" == "mingw64" (
    if "%MINGW64_HOME%" == "" (
      echo "Specify MINGW64_HOME variable before use"
      exit 2
    )
    set GENERATOR="MinGW Makefiles"
    set MAKE_CMD="%MINGW64_HOME%\mingw32-make" TestEncoding
    set RUN_CMD=.\TestEncoding.exe
  ) else (
    if "%1" == "vs2019" (
      if "%VS2019_HOME%" == "" (
        echo "Specify VS2019_HOME variable before use"
        exit 2
      )
      set GENERATOR="Visual Studio 16 2019"
      call "%VS2019_HOME%\Community\VC\Auxiliary\Build\vcvars64.bat"
      set MAKE_CMD=msbuild TestEncoding.vcxproj
      set RUN_CMD=.\Debug\TestEncoding.exe
    ) else (
      if "%1" == "clang" (
        if "%CLANG_HOME%" == "" (
          echo "Specify CLANG_HOME variable before use"
          exit 2
        )
        if "%MAKE_HOME%" == "" (
          echo "Specify MAKE_HOME variable before use"
          exit 2
        )
        set GENERATOR="MinGW Makefiles"
        set MAKE_CMD=%MAKE_HOME%\make TestEncoding
        set COMPILERS=-DCMAKE_CXX_COMPILER="%CLANG_HOME%/clang++.exe" -DCMAKE_C_COMPILER="%CLANG_HOME%/clang.exe"
        set RUN_CMD=.\TestEncoding.exe
      ) else (
        if "%1" == "nmake" (
          if "%NMAKE_HOME%" == "" (
            echo "Specify NMAKE_HOME variable before use"
            exit 2
          )
          set GENERATOR="NMake Makefiles"
          call "%NMAKE_HOME%\Community\VC\Auxiliary\Build\vcvars64.bat"
          set MAKE_CMD=nmake TestEncoding
          set RUN_CMD=.\TestEncoding.exe
        ) else (
          echo Use "mingw32", "mingw64", "vs2019", "clang" or "nmake"
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