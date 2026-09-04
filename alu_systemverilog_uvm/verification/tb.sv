module tb;

    timeunit 1ns;
    timeprecision 100ps;
    parameter DataWidth = 16;

    logic clk_i = 0;
    int unsigned MainClkPeriod = 10;
    always #(MainClkPeriod/2) clk_i = ~clk_i;

    vif_if vif(clk_i);


    test top_test (vif);

    alu #(.DataWidth(DataWidth)) dut (
        .clk_i(vif.clk_i),
        .rst_i(vif.rst_i),
        .x_i(vif.x_i),
        .y_i(vif.y_i),
        .zx_i(vif.zx_i),
        .nx_i(vif.nx_i),
        .zy_i(vif.zy_i),
        .ny_i(vif.ny_i),
        .f_i(vif.f_i),
        .no_i(vif.no_i),
        .out_o(vif.out_o),
        .zr_o(vif.zr_o),
        .ng_o(vif.ng_o),
        .pos_o(vif.pos_o)
    );
    endmodule