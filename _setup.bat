:: _setup.bat
:: Hacky setup script to set workspace directory.

FOR /F "tokens=* USEBACKQ" %%F IN (`cd`) DO (
SET CPP_WORKSPACE=%%F
)