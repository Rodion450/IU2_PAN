@echo off
echo Running GNUPLOT scripts for TU-154...
echo.
echo 1. Comparison plot
gnuplot plot_comparison.gp
echo 2. Min time plot
gnuplot plot_min_time.gp
echo 3. Min fuel plot
gnuplot plot_min_fuel.gp
echo.
echo Plots created:
echo - TU-154_comparison.png
echo - TU-154_min_time.png
echo - TU-154_min_fuel.png
echo.
pause
