
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
module component01 (
	output reg [7:0] RPM_Out,
    output reg Reset_Out,
	input      Clock,
	input wire Pulse_In,
	input      Reset
);
    reg [7:0] pulse_count;
    reg [7:0] count;
    reg [6:0] accum;
    //`#start body` -- edit after this line, do not edit this line

    //        Your code goes here
    always @ (posedge Pulse_In ) begin
        pulse_count <= pulse_count + 1;
        //RPM_Out <= pulse_count;
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
                    RPM_Out[0] <= pulse_count[0];
                    RPM_Out[1] <= pulse_count[1];
                    RPM_Out[2] <= pulse_count[2];
                    RPM_Out[3] <= pulse_count[3];
                    RPM_Out[4] <= pulse_count[4];
                    RPM_Out[5] <= pulse_count[5];
                    RPM_Out[6] <= pulse_count[6];
                    RPM_Out[7] <= pulse_count[7];
                end
            end
            
        end
    end
    
    
       
//`#end` -- edit above this line, do not edit this line
endmodule
//`#start footer` -- edit after this line, do not edit this line
//`#end` -- edit above this line, do not edit this line
