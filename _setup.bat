:: _setup.bat
:: Hacky setup script to set workspace directory.

@echo off

FOR /F "tokens=* USEBACKQ" %%F IN (`cd`) DO (
SET CPP_WORKSPACE=%%F
)

echo Set CPP_WORKSPACE = %CPP_WORKSPACE%