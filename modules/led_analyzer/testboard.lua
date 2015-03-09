
--tTest[x][y]:
--		x = 1 .. number of detected ftdi devices 
--		y = 1 .. 16 sensors per device 
-- for example tTest[1] can contain 16 datasets
-- and 		   tTest[2] can contain 8 datasets
-- this would meen we test a board with 24 different LEDs

tTest = 
{
-- maximum of 16 entries per device 
[1] = { 
        [1] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
										   x = 0.3, y = 0.2, tol_xy = 0.05, LED_State = 0},
										   
		[2] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
									 	   tol_xy = 0.05, LED_State = 0},			
										   
		[3] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
										   tol_xy = 0.05, LED_State = 0},
										   
		[4] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
										   tol_xy = 0.05, LED_State = 0},
										   
		[5] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
										   tol_xy = 0.05, LED_State = 0},
										   
		[6] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
										   tol_xy = 0.05, LED_State = 0},
										   
		[7] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
										   tol_xy = 0.05, LED_State = 0},
										   
		[8] = {name = "TESTBOARD_LED_Gruen", dWavelength = 571.0, tol_nm = 9, sat = 95,  tol_sat = 10, LED_State = 0},
		
		[9] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
											tol_xy = 0.05, LED_State = 0},
												   
		[10] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
										    tol_xy = 0.05, LED_State = 0},
												   
		[11] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
											tol_xy = 0.05, LED_State = 0},
												   
		[12] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
											tol_xy = 0.05, LED_State = 0},
												   
		[13] = {name = "TESTBOARD_LED_Orange", dWavelength = 596, tol_nm = 5,sat = 70,  tol_sat = 5, LED_State = 0},
												  
		[14] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
											tol_xy = 0.05, LED_State = 0},
												   
		[15] = {name = "TESTBOARD_LED_Rot", dWavelength = 615 , tol_nm = 8, sat = 60,  tol_sat = 2, 
											tol_xy = 0.05, LED_State = 0},										   
		
		[16] = {name = "TESTBOARD_LED_Orange", dWavelength = 596, tol_nm = 5,sat = 70,  tol_sat = 5, LED_State = 0}
	
		},

  -- table for second device and so on ...., max 16 entries per device index
 [2] = {} 
			
                
}

