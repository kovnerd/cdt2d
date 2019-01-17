set term pdfcairo
set output "K_c.pdf"
set size 1, 1
set autoscale
unset log
unset label
set xtic auto
set ytic auto
set title "Finding K_c"
set xlabel "K_2" 
plot "../data_files/N_fOverN_i_4096.txt" using 1:2 title "N_f/N_i" with lines, "../data_files/avdeltaNOverN_4096.txt" using 1:2 title "<deltaN/N>" with lines 
set output
