set moduleName fir_optimized
set isTopModule 1
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set isPipelined_legacy 1
set pipeline_type function
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set svuvm_can_support 1
set cdfgNum 2
set C_modelName {fir_optimized}
set C_modelType { void 0 }
set ap_memory_interface_dict [dict create]
set C_modelArgList {
	{ output_r int 32 regular {pointer 1}  }
	{ input_r int 32 regular  }
}
set hasAXIMCache 0
set l_AXIML2Cache [list]
set AXIMCacheInstDict [dict create]
set C_modelArgMapList {[ 
	{ "Name" : "output_r", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "input_r", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 9
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ output_r sc_out sc_lv 32 signal 0 } 
	{ output_r_ap_vld sc_out sc_logic 1 outvld 0 } 
	{ input_r sc_in sc_lv 32 signal 1 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "output_r", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_r", "role": "default" }} , 
 	{ "name": "output_r_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "output_r", "role": "ap_vld" }} , 
 	{ "name": "input_r", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "input_r", "role": "default" }}  ]}

set ArgLastReadFirstWriteLatency {
	fir_optimized {
		output_r {Type O LastRead -1 FirstWrite 7}
		input_r {Type I LastRead 1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_45 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_44 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_43 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_42 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_41 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_40 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_39 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_38 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_37 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_36 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_35 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_34 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_33 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_32 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_31 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_30 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_29 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_28 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_27 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_26 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_25 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_24 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_23 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_22 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_21 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_20 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_19 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_18 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_17 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_16 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_15 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_14 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_13 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_12 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_11 {Type IO LastRead -1 FirstWrite -1}
		p_ZZ13fir_optimizedPiiE9shift_reg_10 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_9 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_8 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_7 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_6 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_5 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_4 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_3 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_2 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg_1 {Type IO LastRead -1 FirstWrite -1}
		fir_optimized_int_int_shift_reg {Type IO LastRead -1 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "7", "Max" : "7"}
	, {"Name" : "Interval", "Min" : "3", "Max" : "3"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	output_r { ap_vld {  { output_r out_data 1 32 }  { output_r_ap_vld out_vld 1 1 } } }
	input_r { ap_none {  { input_r in_data 0 32 } } }
}

set maxi_interface_dict [dict create]

# RTL port scheduling information:
set fifoSchedulingInfoList { 
}

# RTL bus port read request latency information:
set busReadReqLatencyList { 
}

# RTL bus port write response latency information:
set busWriteResLatencyList { 
}

# RTL array port load latency information:
set memoryLoadLatencyList { 
}
