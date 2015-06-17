

-- tTest
--		device 1 
--				  sensor 1 
--					...
--				  sensor 16 
--
--		device 2  
--				  sensor 1 
--					...
--				  sensor 16 
--
--		   ... 

tTest = 
{
-- maximum of 16 entries per device 
	[0] = { 
			[1]  =  {name = "", nm = 571, tol_nm = 10, sat = 100, tol_sat = 10, lux = 1500, tol_lux = 250},
							   		
			[2]  =  {name = "", nm = 588, tol_nm = 8, sat = 100,   tol_sat = 5,  lux = 850, tol_lux = 150},			
	--						   		                               
	--		[3]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[4]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
    --                                                                        
	--		[5]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[6]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[7]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[8]  =  {name = "", nm = 550, tol_nm = 9, sat = 95,   tol_sat = 10, lux = 0.0005, tol_lux = 20},
	--		                                                                
			[9]  =  {name = "", nm = 612, tol_nm = 8, sat = 100,   tol_sat = 5,  lux = 1400, tol_lux = 300},
	--						   		                         
			[10] =  {name = "", nm = 521, tol_nm = 8, sat = 100,   tol_sat = 5,  lux = 7800, tol_lux = 2000}
	--						   		                         
	--		[11] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		      							   		                         
	--		[12] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[13] =  {name = "", nm = 550, tol_nm = 5, sat = 70,   tol_sat = 5,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[14] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[15] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},										   
	--		                                                                
	--		[16] =  {name = "", nm = 550, tol_nm = 5, sat = 70,   tol_sat = 5,  lux = 0.0005, tol_lux = 20}										  
		 },
		 

	[3] = { 
			[1]  =  {name = "", nm = 520, tol_nm = 10, sat = 100, tol_sat = 10, lux = 10000, tol_lux = 2000}
							   		 
	--		[2]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},			
	--						   		                               
	--		[3]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[4]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
    --                                                                        
	--		[5]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[6]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[7]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[8]  =  {name = "", nm = 550, tol_nm = 9, sat = 95,   tol_sat = 10, lux = 0.0005, tol_lux = 20},
	--		                                                                
	--		[9]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[10] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[11] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		      							   		                         
	--		[12] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[13] =  {name = "", nm = 550, tol_nm = 5, sat = 70,   tol_sat = 5,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[14] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[15] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},										   
	--		                                                                
	--		[16] =  {name = "", nm = 550, tol_nm = 5, sat = 70,   tol_sat = 5,  lux = 0.0005, tol_lux = 20}		
		 },
		 
	[2] = { 
			[1]  =  {name = "", nm = 520, tol_nm = 10, sat = 100, tol_sat = 10, lux = 1200, tol_lux = 250}
							   		
	--		[2]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},			
	--						   		                               
	--		[3]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[4]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
    --                                                                        
	--		[5]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[6]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[7]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                               
	--		[8]  =  {name = "", nm = 550, tol_nm = 9, sat = 95,   tol_sat = 10, lux = 0.0005, tol_lux = 20},
	--		                                                                
	--		[9]  =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[10] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[11] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		      							   		                         
	--		[12] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[13] =  {name = "", nm = 550, tol_nm = 5, sat = 70,   tol_sat = 5,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[14] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},
	--						   		                         
	--		[15] =  {name = "", nm = 550, tol_nm = 8, sat = 60,   tol_sat = 2,  lux = 0.0005, tol_lux = 20},										   
	--		                                                                
	--		[16] =  {name = "", nm = 550, tol_nm = 5, sat = 70,   tol_sat = 5,  lux = 0.0005, tol_lux = 20}		
		 }
}

