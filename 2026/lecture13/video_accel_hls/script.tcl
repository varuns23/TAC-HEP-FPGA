open_project video_accel_prj

set_top video_accel

add_files src/video_accel.cpp
add_files src/video_accel.h
add_files -tb src/video_accel_tb.cpp

open_solution "solution1"

set_part xcvu13p-fsga2577-2-e
create_clock -period 25

# Optional: add directives here (or keep in code)
# set_directive_pipeline "rgb2gray"
# set_directive_unroll "filter3x3/loop1"

csim_design
csynth_design
#cosim_design

#export_design -format ip_catalog

exit
