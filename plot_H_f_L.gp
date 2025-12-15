set terminal pngcairo font "Arial,12" size 800,600
set output "H_f_L.png"

set xlabel "Дальность, м"
set ylabel "Высота, м"
set y2label "Расход топлива, кг"
set ytics nomirror
set y2tics
set grid

plot "trajectory.dat" using 1:2 with lines lw 2 title "H(L)" axis x1y1, \
     "trajectory.dat" using 1:3 with lines lw 2 lc rgb "red" title "f(L)" axis x1y2
