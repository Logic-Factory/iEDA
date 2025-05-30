#===========================================================
##   init flow config
#===========================================================
flow_init -config $::env(CONFIG_DIR)/flow_config.json

#===========================================================
##   read db config
#===========================================================
db_init -config $::env(CONFIG_DIR)/db_default_config.json -output_dir_path $::env(RESULT_DIR)

#===========================================================
##   reset data path
#===========================================================
source $::env(TCL_SCRIPT_DIR)/DB_script/db_path_setting.tcl

#===========================================================
##   reset lib
#===========================================================
source $::env(TCL_SCRIPT_DIR)/DB_script/db_init_lib.tcl

#===========================================================
##   reset sdc
#===========================================================
source $::env(TCL_SCRIPT_DIR)/DB_script/db_init_sdc.tcl

#===========================================================
##   read lef
#===========================================================
source $::env(TCL_SCRIPT_DIR)/DB_script/db_init_lef.tcl

#===========================================================
##   read def
#===========================================================
def_init -path $::env(RESULT_DIR)/iPL_result.def

#===========================================================
##   run CTS
#===========================================================
run_cts -config $::env(CONFIG_DIR)/cts_default_config.json -work_dir $::env(RESULT_DIR)/cts

feature_tool -path $::env(RESULT_DIR)/feature/icts.json -step CTS

#===========================================================
##   def & netlist
#===========================================================
def_save -path $::env(RESULT_DIR)/iCTS_result.def

#===========================================================
##   save netlist 
#===========================================================
netlist_save -path $::env(RESULT_DIR)/iCTS_result.v -exclude_cell_names {}

#===========================================================
##   report db summary
#===========================================================
report_db -path "$::env(RESULT_DIR)/report/cts_db.rpt"

#===========================================================
##   report CTS
#===========================================================
cts_report -path $::env(RESULT_DIR)/cts

feature_summary -path $::env(RESULT_DIR)/feature/summary_icts.json -step CTS

#===========================================================
##   Exit 
#===========================================================
flow_exit
