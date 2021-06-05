cmd_/home/wankang/driver/modules.order := {   echo /home/wankang/driver/hellodev.ko; :; } | awk '!x[$$0]++' - > /home/wankang/driver/modules.order
