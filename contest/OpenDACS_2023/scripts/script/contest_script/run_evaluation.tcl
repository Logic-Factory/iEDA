#===========================================================
##   init flow config from sky130 gcd scripts
#===========================================================
flow_init -config ./../../../scripts/design/sky130_gcd/iEDA_config/flow_config.json

#===========================================================
##   read db config from sky130 gcd scripts
#===========================================================
db_init -config ./../../../scripts/design/sky130_gcd/iEDA_config/db_default_config.json

#===========================================================
##   reset data path
#===========================================================
source ./script/DB_script/db_path_setting.tcl

#===========================================================
##   reset lib
#===========================================================
source ./script/DB_script/db_init_lib.tcl

#===========================================================
##   reset sdc
#===========================================================
source ./script/DB_script/db_init_sdc.tcl

#===========================================================
##   read lef
#===========================================================
source ./script/DB_script/db_init_lef.tcl

#===========================================================
##   read def of contest result
#===========================================================
def_init -path ./result/output/output.def

#===========================================================
##   run evaluation
#===========================================================
run_contest_evaluation -guide ./result/output/output.guide -report ./result/report/evaluation.rpt

#===========================================================
##   Exit 
#===========================================================
flow_exit