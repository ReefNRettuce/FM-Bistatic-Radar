//==============================================================
//Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.1 (64-bit)
//Tool Version Limit: 2025.05
//Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
//Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
//
//==============================================================
`ifndef FIR_OPTIMIZED_ENV__SV                                                                                   
    `define FIR_OPTIMIZED_ENV__SV                                                                               
                                                                                                                    
                                                                                                                    
    class fir_optimized_env extends uvm_env;                                                                          
                                                                                                                    
        fir_optimized_virtual_sequencer fir_optimized_virtual_sqr;                                                      
        fir_optimized_config fir_optimized_cfg;                                                                         
                                                                                                                    
        svr_pkg::svr_env#(32) env_slave_svr_output_r;
        svr_pkg::svr_env#(32) env_master_svr_input_r;
                                                                                                                    
        fir_optimized_reference_model   refm;                                                                         
                                                                                                                    
        fir_optimized_subsystem_monitor subsys_mon;                                                                   
                                                                                                                    
        `uvm_component_utils_begin(fir_optimized_env)                                                                 
        `uvm_field_object (env_slave_svr_output_r,  UVM_DEFAULT | UVM_REFERENCE)
        `uvm_field_object (env_master_svr_input_r,  UVM_DEFAULT | UVM_REFERENCE)
        `uvm_field_object (refm, UVM_DEFAULT | UVM_REFERENCE)                                                       
        `uvm_field_object (fir_optimized_virtual_sqr, UVM_DEFAULT | UVM_REFERENCE)                                    
        `uvm_field_object (fir_optimized_cfg        , UVM_DEFAULT)                                                    
        `uvm_component_utils_end                                                                                    
                                                                                                                    
        function new (string name = "fir_optimized_env", uvm_component parent = null);                              
            super.new(name, parent);                                                                                
        endfunction                                                                                                 
                                                                                                                    
        extern virtual function void build_phase(uvm_phase phase);                                                  
        extern virtual function void connect_phase(uvm_phase phase);                                                
        extern virtual task          run_phase(uvm_phase phase);                                                    
                                                                                                                    
    endclass                                                                                                        
                                                                                                                    
    function void fir_optimized_env::build_phase(uvm_phase phase);                                                    
        super.build_phase(phase);                                                                                   
        fir_optimized_cfg = fir_optimized_config::type_id::create("fir_optimized_cfg", this);                           
                                                                                                                    
        fir_optimized_cfg.port_output_r_cfg.svr_type = svr_pkg::SVR_SLAVE ;
        env_slave_svr_output_r  = svr_env#(32)::type_id::create("env_slave_svr_output_r", this);
        uvm_config_db#(svr_pkg::svr_config)::set(this, "env_slave_svr_output_r*", "cfg", fir_optimized_cfg.port_output_r_cfg);
        fir_optimized_cfg.port_output_r_cfg.prt_type = svr_pkg::AP_VLD;
        fir_optimized_cfg.port_output_r_cfg.is_active = svr_pkg::SVR_ACTIVE;
        fir_optimized_cfg.port_output_r_cfg.spec_cfg = svr_pkg::NORMAL;
        fir_optimized_cfg.port_output_r_cfg.reset_level = svr_pkg::RESET_LEVEL_HIGH;
 
        fir_optimized_cfg.port_input_r_cfg.svr_type = svr_pkg::SVR_MASTER ;
        env_master_svr_input_r  = svr_env#(32)::type_id::create("env_master_svr_input_r", this);
        uvm_config_db#(svr_pkg::svr_config)::set(this, "env_master_svr_input_r*", "cfg", fir_optimized_cfg.port_input_r_cfg);
        fir_optimized_cfg.port_input_r_cfg.prt_type = svr_pkg::AP_NONE;
        fir_optimized_cfg.port_input_r_cfg.is_active = svr_pkg::SVR_ACTIVE;
        fir_optimized_cfg.port_input_r_cfg.spec_cfg = svr_pkg::NORMAL;
        fir_optimized_cfg.port_input_r_cfg.reset_level = svr_pkg::RESET_LEVEL_HIGH;
 



        refm = fir_optimized_reference_model::type_id::create("refm", this);


        uvm_config_db#(fir_optimized_reference_model)::set(this, "*", "refm", refm);


        `uvm_info(this.get_full_name(), "set reference model by uvm_config_db", UVM_LOW)


        subsys_mon = fir_optimized_subsystem_monitor::type_id::create("subsys_mon", this);


        fir_optimized_virtual_sqr = fir_optimized_virtual_sequencer::type_id::create("fir_optimized_virtual_sqr", this);
        `uvm_info(this.get_full_name(), "build_phase done", UVM_LOW)
    endfunction


    function void fir_optimized_env::connect_phase(uvm_phase phase);
        super.connect_phase(phase);


        fir_optimized_virtual_sqr.svr_port_output_r_sqr = env_slave_svr_output_r.s_agt.sqr;
        env_slave_svr_output_r.s_agt.mon.item_collect_port.connect(subsys_mon.svr_slave_output_r_imp);
 
        fir_optimized_virtual_sqr.svr_port_input_r_sqr = env_master_svr_input_r.m_agt.sqr;
        env_master_svr_input_r.m_agt.mon.item_collect_port.connect(subsys_mon.svr_master_input_r_imp);
 
        refm.fir_optimized_cfg = fir_optimized_cfg;
        `uvm_info(this.get_full_name(), "connect phase done", UVM_LOW)
    endfunction


    task fir_optimized_env::run_phase(uvm_phase phase);
        `uvm_info(this.get_full_name(), "fir_optimized_env is running", UVM_LOW)
    endtask


`endif
