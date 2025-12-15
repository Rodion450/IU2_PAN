set terminal pngcairo font "Arial,12" size 800,600
set output "H_V.png"

set title "Высота H(V)"
set xlabel "Скорость, км/ч"
set ylabel "Высота, м"
set grid

plot "trajectory.dat" using 4:2 with lines lw 2 title "H(V)"
