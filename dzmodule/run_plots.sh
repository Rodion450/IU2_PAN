#!/bin/bash
echo "Запуск GNUPLOT скриптов для ТУ-154..."
echo
echo "1. Сравнительный график"
gnuplot plot_comparison.gp
echo "2. График минимального времени"
gnuplot plot_min_time.gp
echo "3. График минимального расхода топлива"
gnuplot plot_min_fuel.gp
echo
echo "Созданы графики:"
echo "- TU-154_comparison.png"
echo "- TU-154_min_time.png"
echo "- TU-154_min_fuel.png"
