//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
//Tool Version Limit: 2025.05
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================

`ifndef FIR_OPTIMIZED_SUBSYSTEM_MONITOR_SV
`define FIR_OPTIMIZED_SUBSYSTEM_MONITOR_SV

`uvm_analysis_imp_decl(_svr_slave_output_r)
`uvm_analysis_imp_decl(_svr_master_input_r)

class fir_optimized_subsystem_monitor extends uvm_component;

    fir_optimized_reference_model refm;
    fir_optimized_scoreboard scbd;

    `uvm_component_utils_begin(fir_optimized_subsystem_monitor)
    `uvm_component_utils_end

    uvm_analysis_imp_svr_slave_output_r#(svr_pkg::svr_transfer#(32), fir_optimized_subsystem_monitor) svr_slave_output_r_imp;
    uvm_analysis_imp_svr_master_input_r#(svr_pkg::svr_transfer#(32), fir_optimized_subsystem_monitor) svr_master_input_r_imp;

    virtual function void build_phase(uvm_phase phase);
        super.build_phase(phase);
        if (!uvm_config_db#(fir_optimized_reference_model)::get(this, "", "refm", refm))
            `uvm_fatal(this.get_full_name(), "No refm from high level")
        `uvm_info(this.get_full_name(), "get reference model by uvm_config_db", UVM_MEDIUM)
        scbd = fir_optimized_scoreboard::type_id::create("scbd", this);
    endfunction

    virtual function void connect_phase(uvm_phase phase);
        super.connect_phase(phase);
    endfunction

    function new (string name = "", uvm_component parent = null);
        super.new(name, parent);
        svr_slave_output_r_imp = new("svr_slave_output_r_imp", this);
        svr_master_input_r_imp = new("svr_master_input_r_imp", this);
    endfunction

    virtual function void write_svr_slave_output_r(svr_transfer#(32) tr);
        refm.write_svr_slave_output_r(tr);
        scbd.write_svr_slave_output_r(tr);
    endfunction

    virtual function void write_svr_master_input_r(svr_transfer#(32) tr);
        refm.write_svr_master_input_r(tr);
        scbd.write_svr_master_input_r(tr);
    endfunction
endclass
`endif
