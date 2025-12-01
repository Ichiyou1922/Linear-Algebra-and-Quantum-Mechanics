set terminal pngcairo size 800,600 enhanced font "Arial,12"
set output "Bloch-Sphere.png"

set datafile separator ","
set title "Bloch Sphere Trajectory"
set xlabel "x"
set ylabel "y"
set zlabel "z"

set view 60, 30  # 視点変更
set xrange [-1:1]
set yrange [-1:1]
set zrange [-1:1]
set parametric
set urange [0:2*pi]
set vrange [-pi/2:pi/2]
set isosamples 20,20
# 球面の描画（薄い色で）
splot cos(v)*cos(u),cos(v)*sin(u),sin(v) with lines lc rgb "#dddddd" notitle, \
      "result.csv" using 1:2:3 with lines lw 3 lc rgb "red" title "Trajectory"
