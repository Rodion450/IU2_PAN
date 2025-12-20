# GNUPLOT script for trajectory comparison
set terminal pngcairo size 1200,800 enhanced font 'Verdana,12'
set output 'TU-154_comparison.png'

set title 'TU-154 Trajectory Comparison (Variant 1)'
set xlabel 'Speed V (km/h)'
set ylabel 'Altitude H (m)'
set grid
set key top left
set datafile separator ','

# Plot with lines AND points
plot 'trajectory_min_time.csv' using 3:2 every ::1 \
     with linespoints lw 2 pt 7 ps 1.2 lc rgb 'red' \
     title 'Min Time (16.4694 min, 3073.79 kg)', \
     'trajectory_min_fuel.csv' using 3:2 every ::1 \
     with linespoints lw 2 pt 7 ps 1.2 lc rgb 'blue' \
     title 'Min Fuel (24.5052 min, 2950.21 kg)'

