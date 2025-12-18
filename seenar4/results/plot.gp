# Скрипт gnuplot для построения графиков траектории
# Создан автоматически

# 1. График высоты от времени
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'trajectory_altitude_time.png'
set title 'Высота от времени'
set xlabel 'Время, с'
set ylabel 'Высота, м'
set grid
plot 'results/trajectory.csv' using 1:3 with lines title 'Высота'

# 2. График скорости от времени
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'trajectory_velocity_time.png'
set title 'Скорость от времени'
set xlabel 'Время, с'
set ylabel 'Скорость, м/с'
set grid
plot 'results/trajectory.csv' using 1:2 with lines title 'Скорость'

# 3. График высоты от скорости (основной)
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'trajectory_altitude_velocity.png'
set title 'Траектория: высота от скорости'
set xlabel 'Скорость, м/с'
set ylabel 'Высота, м'
set grid
plot 'results/trajectory.csv' using 2:3 with lines title 'Траектория'

# 4. График расхода топлива от времени
set terminal pngcairo size 800,600 enhanced font 'Arial,12'
set output 'trajectory_fuel_time.png'
set title 'Расход топлива от времени'
set xlabel 'Время, с'
set ylabel 'Расход топлива, кг'
set grid
plot 'results/trajectory.csv' using 1:5 with lines title 'Расход топлива'

# 5. Все графики на одном изображении
set terminal pngcairo size 1200,800 enhanced font 'Arial,10'
set output 'trajectory_all.png'
set multiplot layout 2,2 title 'Параметры траектории'
set title 'Высота от времени'
plot 'results/trajectory.csv' using 1:3 with lines
set title 'Скорость от времени'
plot 'results/trajectory.csv' using 1:2 with lines
set title 'Траектория: высота от скорости'
plot 'results/trajectory.csv' using 2:3 with lines
set title 'Расход топлива от времени'
plot 'results/trajectory.csv' using 1:5 with lines
unset multiplot
