open_project fir_proj
set_top lec10ex1
add_files lec10ex1.c
add_files lec10ex1.h
add_files -tb lec10ex1_out_ref.dat
add_files -tb lec10ex1_test.c

open_solution "solution1"
set_part {xcvu9p-flga2104-1-i}
create_clock -period 25 -name default

#source "./fir_proj/solution1/directives.tcl"

csim_design
csynth_design
#cosim_design
#export_design -format ip_catalog
#
#Exit Vivada HLS
exit
