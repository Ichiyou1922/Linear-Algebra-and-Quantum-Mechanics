# plot_save.gp
set terminal pngcairo size 800,600 enhanced font "Arial,12"
set output "rabi_oscillation.png"

set datafile separator ","
set title "Rabi Oscillation with Detuning"
set xlabel "Time t"
set ylabel "Probability P_0 = |<0|psi(t)>|^2"

set yrange [-0.1:1.1]
set grid

# --- 理論曲線の定義 ---
Omega = 1.0
Delta = 2.0  # 課題に合わせて変更せよ (共鳴時は 0.0)

# 一般化ラビ周波数
Omega_tilde = sqrt(Omega**2 + Delta**2)

# 理論式: P_0(t) = 1 - P_flip(t)
# P_flip(t) = (Omega^2 / Omega_tilde^2) * sin^2(Omega_tilde * t / 2)
# よって P_0(t) は以下の通り:
theory(t) = 1.0 - (Omega**2 / Omega_tilde**2) * (sin(Omega_tilde * t / 2.0))**2

# --- プロット実行 ---
# Simulation: 赤線, Theory: 青破線
plot "result.csv" using 1:2 skip 1 with lines lc rgb "red" lw 2 title "Simulation (RK4)", \
     theory(x) with lines dt 2 lc rgb "blue" lw 2 title "Theory"
