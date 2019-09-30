@echo OFF

call %0\..\SetupVSEnvironment.bat

if not defined CROSS_CMAKE_GENERATOR (
  @echo Problem setting up Visual Studio compilation environment
  exit /b 1
)

set CROSS_CMAKE_FLAGS=%2
set CROSS_CMAKE_FLAGS=%CROSS_CMAKE_FLAGS:\=%
set CROSS_CMAKE_FLAGS=%CROSS_CMAKE_FLAGS:"=%

%CROSS_CMAKE% %0\..\..\..\..\ %CROSS_CMAKE_FLAGS% -G %CROSS_CMAKE_GENERATOR% -A x64

echo ---------- CROSS Build Phase 1 STARTING ----------

:: Note, we're building LibCpuId as it uses masm as getting XamlFactory load errors if delayed
:: msbuild /m CROSS.sln /t:LibCpuId /t:CROSSNETNative /p:Configuration=%1 /p:Platform=x64
msbuild /m CROSS.sln /t:LibCpuId /p:Configuration=%1 /p:Platform=x64
