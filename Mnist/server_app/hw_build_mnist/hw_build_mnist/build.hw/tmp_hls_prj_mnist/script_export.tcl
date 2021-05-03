

open_project hls
set_top rt_imp
add_files reconos_calls.h
add_files reconos_thread.h
add_files [ glob *.cpp ] -cflags "-I/upb/users/c/clienen/profiles/unix/imt/scratch/ros/include/ -I/upb/scratch/users/c/clienen/hw_build_mnist/build.msg/install/mnist_msgs/include/  -m32"
open_solution sol
set_part {xc7z100ffg900-2}
create_clock -period 10.0 -name default
source directives.tcl
csynth_design
export_design -format syn_dcp
exit
