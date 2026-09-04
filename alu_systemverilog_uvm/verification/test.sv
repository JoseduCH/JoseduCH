module test (
    vif_if vif
);

    timeunit 1ns;
    timeprecision 100ps;

initial begin
    $display("Begin of simulation");

    fork
        monitor_output();
    join_none

    reset();

    fork
        send_data_port();

    join_any

    #(20ns);
    $display("End of simulation at %0t.", $realtime);
    $finish;
end

task automatic reset();
vif.x_i = 16'b0;
vif.y_i = 16'b0;
vif.rst_i = 1'b1;

repeat (5) @(vif.cb);
vif.rst_i <= 1'b0;
endtask : reset

task automatic send_data_port();
for (int i = 0; i < 5; i++) begin
    @(vif.cb);
    vif.cb.x_i <= $urandom_range(0, 15);
    vif.cb.y_i <= $urandom_range(0, 15);
    vif.cb.zx_i <= '0;
    vif.cb.nx_i <= '1;
    vif.cb.zy_i <= '0;
    vif.cb.ny_i <= '0;
    vif.cb.f_i <= '1;
    vif.cb.no_i <= '1;
end
endtask : send_data_port

task automatic monitor_output();
    forever begin
        @(vif.cb);
        $display("[INFO:Gate Sumador]: %8t:, Rst = %d, A = %d, B = %d, out_o=%1d",
            $realtime, vif.rst_i, vif.x_i, vif.y_i, vif.out_o);
    end
endtask : monitor_output

endmodule : test