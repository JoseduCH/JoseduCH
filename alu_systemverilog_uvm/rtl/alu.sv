module alu #(
    parameter DataWidth = 4
)(
    input  logic                 clk_i,
    input  logic                 rst_i,
    input  logic [DataWidth-1:0] x_i,
    input  logic [DataWidth-1:0] y_i,
    input  logic                 zx_i,
    input  logic                 nx_i,
    input  logic                 zy_i,
    input  logic                 ny_i,
    input  logic                 f_i,
    input  logic                 no_i,
    output logic [DataWidth-1:0] out_o,
    output logic                 zr_o,
    output logic                 ng_o,
    output logic                 pos_o,
    output logic                 carry_o
);
localparam logic [5:0] ALU_ZERO = 6'b101010;
localparam logic [5:0] ALU_ONE  = 6'b111111;
localparam logic [5:0] ALU_MONE = 6'b111010;
localparam logic [5:0] ALU_X    = 6'b001100;
localparam logic [5:0] ALU_Y    = 6'b110000;
localparam logic [5:0] ALU_NOTX = 6'b001101;
localparam logic [5:0] ALU_NOTY = 6'b110001;
localparam logic [5:0] ALU_NEGX = 6'b001111;
localparam logic [5:0] ALU_NEGY = 6'b110011;
localparam logic [5:0] ALU_XP1 = 6'b011111;
localparam logic [5:0] ALU_YP1 = 6'b110111;
localparam logic [5:0] ALU_XM1 = 6'b001110;
localparam logic [5:0] ALU_YM1 = 6'b110010;
localparam logic [5:0] ALU_ADD = 6'b000010;
localparam logic [5:0] ALU_SUBXY = 6'b010011;
localparam logic [5:0] ALU_SUBYX = 6'b000111;
localparam logic [5:0] ALU_AND = 6'b000000;
localparam logic [5:0] ALU_OR = 6'b010101;

logic [5:0] inst;
logic [DataWidth-1:0] comb_out;
logic comb_zr;
logic comb_ng;
logic comb_pos;
logic comb_carry;
logic [DataWidth:0] temp;

assign inst = {zx_i, nx_i, zy_i, ny_i, f_i, no_i};

always_comb begin
	 temp = '0;
	 comb_carry = 1'b0;
    case (inst)
        ALU_ZERO: comb_out = '0;
        ALU_ONE:  comb_out = '1;
        ALU_MONE: comb_out = -1;
        ALU_X:    comb_out = x_i;
        ALU_Y:    comb_out = y_i;
        ALU_NOTX: comb_out = ~x_i;
        ALU_NOTY: comb_out = ~y_i;
        ALU_NEGX: comb_out = -x_i;
        ALU_NEGY: comb_out = -y_i;
        ALU_XP1: begin
            temp = x_i + 1'b1;
            comb_out = temp[DataWidth-1:0];
            comb_carry = temp[DataWidth];
        end
        ALU_YP1: begin
            temp = y_i + 1'b1;
            comb_out = temp[DataWidth-1:0];
            comb_carry = temp[DataWidth];
        end
        ALU_XM1: comb_out = x_i - 1;
        ALU_YM1: comb_out = y_i - 1;
        ALU_ADD: begin
            temp = x_i + y_i;
            comb_out = temp[DataWidth-1:0];
            comb_carry = temp[DataWidth];
        end
        ALU_SUBXY: comb_out = x_i - y_i;
        ALU_SUBYX: comb_out = y_i - x_i;
        ALU_AND: comb_out = x_i & y_i;
        ALU_OR: comb_out = x_i | y_i;
        default: comb_out = '0;
    endcase
    comb_zr = (comb_out == '0);
    comb_ng = comb_out[DataWidth-1];
    comb_pos = !comb_zr && !comb_ng;
end

always_ff @(posedge clk_i or posedge rst_i) begin
    if (rst_i) begin
        out_o   <= '0;
        zr_o    <= 1'b0;
        ng_o    <= 1'b0;
        pos_o   <= 1'b0;
        carry_o <= 1'b0;
    end else begin
        out_o   <= comb_out;
        zr_o    <= comb_zr;
        ng_o    <= comb_ng;
        pos_o   <= comb_pos;
        carry_o <= comb_carry;
    end
end

endmodule : alu