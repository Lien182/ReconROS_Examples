ssh clienen@cc-9.cs.upb.de 'rm /upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_sobel/ -r -f'
rsync -r -v build.cfg src --exclude 'src/application' --exclude 'src/_build' clienen@cc-9.cs.upb.de:/upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_sobel
ssh -t clienen@cc-9.cs.upb.de 'screen bash -c "source /opt/Xilinx/Vivado/2017.1/settings64.sh; source bashinit; source git/ReconROS/tools/settings.sh; cd /upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_sobel/; rdk export_hw; rdk build_hw; exec bash"'
rsync -r -v clienen@cc-9.cs.upb.de:/upb/users/c/clienen/profiles/unix/imt/scratch/hw_build_sobel hw_build_sobel
