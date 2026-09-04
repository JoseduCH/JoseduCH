# Parameterizable ALU with SystemVerilog Verification

## Overview

This project presents the design, verification, and FPGA implementation of a parameterizable Arithmetic Logic Unit (ALU) developed in SystemVerilog.

The ALU supports multiple arithmetic and logical operations and includes status flags for zero, negative, and positive results.

A modular verification environment inspired by the principles of the Universal Verification Methodology (UVM) was developed to validate the functionality of the design. The project was also synthesized and implemented on an Altera/Intel DE2-115 FPGA development board.

The project was developed as part of the Embedded Systems Engineering program at Universidad Politécnica de Yucatán.

---

## Objectives

The main objectives of this project were:

- Design a parameterizable ALU using SystemVerilog.
- Implement arithmetic and logical operations.
- Generate status flags based on the ALU output.
- Develop a modular verification environment.
- Apply verification concepts inspired by UVM.
- Simulate the design using a Linux-based workflow.
- Synthesize and implement the design on an FPGA.
- Analyze the timing performance of the synthesized circuit.
- Demonstrate the operation of the ALU on a DE2-115 development board.

---

## ALU Architecture

The ALU receives two input operands and a set of control signals that determine the operation to be performed.

### Inputs

- `x_i`: First input operand.
- `y_i`: Second input operand.
- `zx_i`: Zero the first operand.
- `nx_i`: Negate the first operand.
- `zy_i`: Zero the second operand.
- `ny_i`: Negate the second operand.
- `f_i`: Select arithmetic or logical operation.
- `no_i`: Negate the final output.

The width of the operands is configurable through the `DataWidth` parameter.

### Outputs

- `out_o`: ALU result.
- `zr_o`: Zero flag.
- `ng_o`: Negative flag.
- `pos_o`: Positive flag.

The parameterizable architecture allows the ALU to be adapted to different operand widths without changing the main design structure.

---

## Supported Operations

The ALU supports the following operations:

| Operation | Description |
|-----------|-------------|
| `0` | Constant zero |
| `1` | Constant one |
| `-1` | Constant negative one |
| `x` | First operand |
| `y` | Second operand |
| `!x` | Bitwise NOT of the first operand |
| `!y` | Bitwise NOT of the second operand |
| `-x` | Two's complement negation of the first operand |
| `-y` | Two's complement negation of the second operand |
| `x + y` | Addition |
| `x - y` | Subtraction |
| `y - x` | Reverse subtraction |
| `x & y` | Bitwise AND |
| `x \| y` | Bitwise OR |

---

## Status Flags

The ALU generates three status flags:

### Zero Flag

The `zr_o` flag is asserted when the output is equal to zero.

### Negative Flag

The `ng_o` flag is asserted when the result is negative.

### Positive Flag

The `pos_o` flag is asserted when the result is positive.

These flags provide additional information about the result of each operation and can be used by other digital systems or control units.

---

## Verification Environment

A modular verification environment was developed to validate the ALU functionality.

The verification structure separates the design under test from the stimulus generation, signal monitoring, and test execution.

The environment includes:

- A virtual interface.
- A top-level testbench.
- Test stimulus.
- Signal monitoring.
- Expected-result generation.
- Comparison between expected and actual results.

This structure helps keep the verification components independent from the ALU implementation and makes the environment easier to maintain and extend.

### Verification Structure

```text
Testbench
   |
   +-- Virtual Interface
   |
   +-- Test Stimulus
   |
   +-- ALU Design Under Test
   |
   +-- Output Monitoring
   |
   +-- Expected vs. Actual Comparison
