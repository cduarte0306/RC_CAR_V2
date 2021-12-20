
//`#start header` -- edit after this line, do not edit this line
// ========================================
//
// Copyright YOUR COMPANY, THE YEAR
// All Rights Reserved
// UNPUBLISHED, LICENSED SOFTWARE.
//
// CONFIDENTIAL AND PROPRIETARY INFORMATION
// WHICH IS THE PROPERTY OF your company.
//
// ========================================
`include "cypress.v"
//`#end` -- edit above this line, do not edit this line
// Generated on 10/14/2020 at 19:29
// Component: component01
module component01 (RPM_Out, Reset_Out, Clock, Pulse_In, Reset);
    output reg [7:0] RPM_Out = 8'b0,
    output reg Reset_Out,
    input      Clock,
    input      Pulse_In,
    input      Reset;
    reg [7:0] pulse_count;
    reg [7:0] count;
    reg [6:0] accum;

    localparam MAX_COUNT = 200;

    //        Your code goes here
    always @ (posedge Pulse_In ) 
        pulse_count <= pulse_count + 1;
    end
    
    always @ (posedge Clock or negedge Reset) begin
        if(!Reset) begin // If reset equals 0 at the negative edge
            count <= 0;
            accum <= 0; //Resets both the count and accum registers
            Reset_Out <= 0;
            pulse_count <= 0;
        end
        else begin
            count <= count + 1;
            if(count == 200) begin
                accum <= accum + 1;
                if(accum >= 50) begin
                    Reset_Out <= 1;
                    RPM_Out <= pulse_count;
            end
            
        end
    end
    
    
       
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
