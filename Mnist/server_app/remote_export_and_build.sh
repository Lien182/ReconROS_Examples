ssh clienen@cc-9.cs.upb.de 'rm /upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_mnist/ -r -f'
rsync -r -v build.cfg src build.msg --exclude 'src/application' --exclude 'src/_build' clienen@cc-9.cs.upb.de:/upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_mnist
ssh -t clienen@cc-9.cs.upb.de 'screen bash -c "source /opt/Xilinx/Vivado/2017.1/settings64.sh; source bashinit; source git/ReconROS/tools/settings.sh; cd /upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_mnist/; source ../ros_dashing/dashing/local_setup.bash; source build.msg/install/local_setup.bash; rdk export_hw; rdk build_hw;  exec bash"'
rsync -r -v clienen@cc-9.cs.upb.de:/upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_mnist hw_build_mnist
