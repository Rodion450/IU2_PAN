set terminal pngcairo font "Arial,12" size 800,600
set output "alpha.png"

set title "Угол атаки α(t)"
set xlabel "Время, с"
set ylabel "α, град"
set grid

plot "alpha.dat" using 1:2 with lines lw 2 title "α(t)"
