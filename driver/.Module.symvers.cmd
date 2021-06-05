cmd_/home/wankang/driver/Module.symvers := sed 's/ko$$/o/' /home/wankang/driver/modules.order | scripts/mod/modpost -m -a   -o /home/wankang/driver/Module.symvers -e -i Module.symvers   -T -
