# GNUPLOT script for single trajectory
set terminal pngcairo size 800,600 enhanced
set output 'TU-154_single.png'

set title 'TU-154 - Minimize Fuel'
set xlabel 'Speed V (km/h)'
set ylabel 'Altitude H (m)'
set grid
set datafile separator ','
plot 'trajectory_min_fuel.csv' every ::1 using 3:2 with linespoints \
     lw 2 pt 7 ps 1 title 'Flight path'
