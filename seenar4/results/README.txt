=== ИНСТРУКЦИЯ ПО ИСПОЛЬЗОВАНИЮ РЕЗУЛЬТАТОВ ===

Созданные файлы:
1. trajectory.csv - данные оптимальной траектории
   Формат: time,velocity,altitude,distance,fuel,thrust,theta

2. plot.gp - скрипт для построения графиков в gnuplot
   Использование: gnuplot plot.gp
   Будут созданы графики:
   - trajectory_altitude_time.png
   - trajectory_velocity_time.png
   - trajectory_altitude_velocity.png
   - trajectory_fuel_time.png
   - trajectory_all.png (все графики вместе)

3. report.txt - отчет об оптимальной траектории
   Содержит статистику: время, расход, средние скорости

4. optimization_info.txt - информация о процессе оптимизации
   Описание алгоритма и параметров оптимизации

5. simple_trajectory.csv - данные простой траектории
6. simple_report.txt - отчет о простой траектории

=== КОМАНДЫ ДЛЯ ПОСТРОЕНИЯ ГРАФИКОВ ===
cd results
gnuplot plot.gp
