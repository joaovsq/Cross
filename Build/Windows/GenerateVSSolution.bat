@echo OFF

call %0\..\SetupVSEnvironment.bat

if not defined CROSS_CMAKE_GENERATOR (
  @echo Problem setting up Visual Studio compilation environment
  exit
)

@echo OFF

echo VS Environment setup finished !
echo %1
echo %2
echo %3

set CROSS_ROOT=%~1
set CROSS_SOLUTION_PATH=%~2
set CROSS_CMAKE_FLAGS="%3"

%CROSS_CMAKE% -E make_directory "%CROSS_SOLUTION_PATH%"
%CROSS_CMAKE% -E chdir "%CROSS_SOLUTION_PATH%" %CROSS_CMAKE% "%CROSS_ROOT% " %CROSS_CMAKE_FLAGS% -G %CROSS_CMAKE_GENERATOR% -A x64
