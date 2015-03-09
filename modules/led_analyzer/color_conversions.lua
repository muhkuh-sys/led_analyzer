


	
require("1931_chromaTable")
require("tcs_chromaTable")


-- Returns LAB --

function XYZToLAB(x, y, z)
  local whiteX = 95.047
  local whiteY = 100.0
  local whiteZ = 108.883
  local x = xyz.x / whiteX
  local y = xyz.y / whiteY
  local z = xyz.z / whiteZ
  if x > 0.008856451679 then
    x = math.pow(x, 0.3333333333)
  else
    x = (7.787037037 * x) + 0.1379310345
  end
  if y > 0.008856451679 then
    y = math.pow(y, 0.3333333333)
  else
    y = (7.787037037 * y) + 0.1379310345
  end
  if z > 0.008856451679 then
    z = math.pow(z, 0.3333333333)
  else
    z = (7.787037037 * z) + 0.1379310345
  end
  local l = 116 * y - 16
  local a = 500 * (x - y)
  local b = 200 * (y - z)
  return {
    l = l,
    a = a,
    b = b
  }
end

-- Returns XYZ

function RGB2XYZ(r, g, b, rgb_workingspace)

-- r from 0.0 to 1.0
-- g from 0.0 to 1.0 
-- b from 0.0 to 1.0 



local r_n = r
local g_n = g
local b_n = b

 if r_n>0.04045 then
	r_n = math.pow((r_n + 0.055) / 1.055, 2.4)
 else r_n = r_n / 12.92
 end
	
 if g_n > 0.04045 then
    g_n = math.pow((g_n + 0.055) / 1.055, 2.4)
 else
    g_n = g_n / 12.92
 end
	
	
  if b_n > 0.04045 then
    b_n = math.pow((b_n + 0.055) / 1.055, 2.4)
  else
    b_n = b_n / 12.92
  end
  
  
 local x,y,z
 local tSourceWhite = {}
 local tDestWhite = {}
 local tXYZ = {}
 
 
 -- globale Variable tRefWhite 
 
  
  -- sRGB, Observer = 2°, Illuminant = D65
  
  
  -- Hier kann man noch was drehen-- 
  -- CIE Standard Observer 2 °, Daylight
  if rgb_workingspace == 'sRGB' then 
	   --Source White in XYZ units not Yxy units !
	   tRefWhite = {x = 0.312727, y=0.329023}
	   x = r_n * 0.4124564 + g_n * 0.3575761 + b_n * 0.1804375
	   y = r_n * 0.2126729 + g_n * 0.7151522 + b_n * 0.0721750
	   z = r_n * 0.0193339 + g_n * 0.1191920 + b_n * 0.9503041
	   tXYZ = {x = x, y = y, z = z}
	 
  -- CIE RGB, Observer = 2°, Illuminant = E
  elseif rgb_workingspace == 'CIE_RGB' then
 	   tRefWhite = {x = 0.3333, y=0.3333}
	   x = r_n * 0.4887180 + g_n * 0.3106803  + b_n * 0.2006017
	   y = r_n * 0.1762044 + g_n * 0.8129847  + b_n * 0.0108109
	   z = r_n * 0.0000000 + g_n * 0.0102048  + b_n * 0.989795
	   tXYZ = {x = x, y = y, z = z}
	   
  -- Apple RGB, Observer = 2°, Illuminant = D65 
  elseif rgb_workingspace == 'Apple_RGB' then
 	   tRefWhite = {x = 0.312727, y=0.329023}
	   x = r_n *0.4497288 + g_n * 0.3162486  + b_n *0.1844926
	   y = r_n *0.2446525 + g_n * 0.6720283  + b_n *0.0833192
	   z = r_n *0.0251848 + g_n * 0.1411824  + b_n *0.9224628
	   tXYZ = {x = x, y = y, z = z}
	  
   -- Best RGB, Observer = 2°, Illuminant = D50
  elseif rgb_workingspace == 'Best_RGB' then 
      tRefWhite = {x = 0.34567, y= 0.35850}
	   x = r_n * 0.6326696  + g_n * 0.2045558  + b_n * 0.1269946
       y = r_n * 0.2284569  + g_n * 0.7373523  + b_n * 0.0341908
       z = r_n * 0.0000000  + g_n * 0.0095142  + b_n * 0.8156958
	   tXYZ = {x = x, y = y, z = z}
	   
   -- Beta RGB , Observere 2°, Illuminant D50 
  elseif rgb_workingspace == 'Beta_RGB' then 
      tRefWhite = {x = 0.34567, y= 0.35850}
	   x = r_n * 0.6712537  + g_n * 0.1745834  + b_n * 0.1183829
       y = r_n * 0.3032726  + g_n * 0.6637861  + b_n * 0.0329413
       z = r_n * 0.0000000  + g_n * 0.0407010  + b_n * 0.7845090
	   
 
	   tXYZ = {x = x, y = y, z = z}
	  
   -- Bruce RGB, Observer 2°, Illuminant D65 
  elseif rgb_workingspace == 'Bruce_RGB' then 
         tRefWhite = {x = 0.312727, y=0.329023}
	   x = r_n *  0.4674162  + g_n * 0.2944512  + b_n * 0.1886026
       y = r_n *  0.2410115  + g_n * 0.6835475  + b_n * 0.0754410
       z = r_n *  0.0219101  + g_n * 0.0736128  + b_n * 0.9933071
	   
	   tXYZ = {x = x, y = y, z = z}
	   
   -- Color Match RGB, Observer = 2°, Illuminant = D50
  elseif rgb_workingspace == 'D50' then 
       tRefWhite = {x = 0.34567, y= 0.35850}
	   x = r_n * 0.5093439  + g_n * 0.3209071  + b_n * 0.1339691
       y = r_n * 0.2748840  + g_n * 0.6581315  + b_n * 0.0669845
       z = r_n * 0.0242545  + g_n * 0.1087821  + b_n * 0.6921735
	   tXYZ = {x = x, y = y, z = z}

   -- NTSCRGB, Observer = 2°, Illuminant = C
  elseif rgb_workingspace == 'NTSC_RGB' then 
       tRefWhite = {x = 0.31006, y = 0.31616}
	   x = r_n * 0.6068909  + g_n * 0.1735011  + b_n * 0.2003480
       y = r_n * 0.2989164  + g_n * 0.5865990  + b_n * 0.1144845
       z = r_n * 0.0000000  + g_n * 0.0660957  + b_n * 1.1162243
	   tXYZ = {x = x, y = y, z = z}	   
	   
   -- NTSCRGB, Observer = 2°, Illuminant = C
   elseif rgb_workingspace == 'PAL_RGB' then 
       tRefWhite = {x = 0.31273, y=0.32902}
	   x = r_n * 0.4306190   + g_n * 0.3415419  + b_n * 0.1783091
       y = r_n * 0.2220379   + g_n * 0.7066384  + b_n * 0.0713236
       z = r_n * 0.0201853   + g_n * 0.1295504  + b_n * 0.9390944
	   tXYZ = {x = x, y = y, z = z}	   
	   
	    
	 
  -- Adobe RGB using D65 as reference white -- 
  elseif rgb_workingspace == "Adobe" then
        tRefWhite = {x = 0.312727, y=0.329023}
		x = r_n * 0.5767309 + g_n * 0.1855540  + b_n *  0.1881852
		y = r_n * 0.2973769 + g_n * 0.6273491  + b_n *  0.0752741
		z = r_n * 0.0270343 + g_n * 0.0706872  + b_n *  0.9911085
		tXYZ = {x = x, y = y, z = z}
  end
   
  
  return x, y, z 
  
   	

 end
 
 -- X,Y,Z in the nominal range [0.0, 1.0]
 function XYZ2Yxy(X, Y, Z)
	
	

	
	local Y = Y
	local x = X / ( X + Y + Z )
	local y = Y / ( X + Y + Z )
	
	return Y, x, y
end

	
 
 -- Returns HSV value of RGB inputs --
 -- @param r,g,b: Red, Green and Blue values from 0 to 1 
 -- @return H,S,V --> Hue, Saturation and Value from 0 to 360, 0 to 100, and 0 to 100 
 function RGB2HSV(r, g, b)
  local r = r
  local g = g
  local b = b
  
  if r > 1.0 then
	r = 1.0 
  end
  
  if g > 1.0 then
	g = 1.0 
  end

  if b > 1.0 then
  b = 1.0 
  end
  
  local max = math.max(r, g, b)
  local min = math.min(r, g, b)
  local v = max
  local d = max - min
  local s
  if max == 0 then
    s = 0
  else
    s = d / max
  end
  
  local h = 0
  if max ~= min then
    local _exp_0 = max
    if r == _exp_0 then
      h = (g - b) / d + ((function()
        if g < b then
          return 6
        else
          return 0
        end
      end)())
    elseif g == _exp_0 then
      h = (b - r) / d + 2
    elseif b == _exp_0 then
      h = (r - g) / d + 4
    end
    h = h / 6
  end
  
  -- H Value from 0 to 360 °
 -- S Value from 0 to 100
 -- V Value from 0 to 100 
  
  return h*360, s*100, v*100
  
end
 
function MultMatVec(mat, vec)

	local v = {x = 0,y=0,z=0}

	v.x = mat[1][1]*vec.x + mat[1][2]*vec.y + mat[1][3]*vec.z
	v.y = mat[2][1]*vec.x + mat[2][2]*vec.y + mat[2][3]*vec.z
	v.z = mat[3][1]*vec.x + mat[3][2]*vec.y + mat[3][3]*vec.z

	return v 
end 

function MultMatMat(mat1, mat2)
	
	local M  = {[1] = {}, [2] = {}, [3] = {}}

	M[1] ={[1] = mat1[1][1]*mat2[1][1] + mat1[1][2]*mat2[2][1] + mat1[1][3]*mat2[3][1],
		   [2] = mat1[1][1]*mat2[1][2] + mat1[1][2]*mat2[2][2] + mat1[1][3]*mat2[3][2],
		   [3] = mat1[1][1]*mat2[1][3] + mat1[1][2]*mat2[2][3] + mat1[1][3]*mat2[3][3]}
	
	M[2] ={[1] = mat1[2][1]*mat2[1][1] + mat1[2][2]*mat2[2][1] + mat1[2][3]*mat2[3][1],
		   [2] = mat1[2][1]*mat2[1][2] + mat1[2][2]*mat2[2][2] + mat1[2][3]*mat2[3][2],
		   [3] = mat1[2][1]*mat2[1][3] + mat1[2][2]*mat2[2][3] + mat1[2][3]*mat2[3][3]} 

	M[3] ={[1] = mat1[3][1]*mat2[1][1] + mat1[3][2]*mat2[2][1] + mat1[3][3]*mat2[3][1],
		   [2] = mat1[3][1]*mat2[1][2] + mat1[3][2]*mat2[2][2] + mat1[3][3]*mat2[3][2],
		   [3] = mat1[3][1]*mat2[1][3] + mat1[3][2]*mat2[2][3] + mat1[3][3]*mat2[3][3]}		


	return M

end 
 
-- function chromatic addaption --
function chromatic_adaption(tSourceWhite, tDestWhite, tXYZ, mode)

	local M  = {[1] = {}, [2] = {}, [3] = {}}
	local Mi = {[1] = {}, [2] = {}, [3] = {}}
	local Mcone = {[1] = {}, [2] = {}, [3] = {}}
	
	if mode == "XYZ_Scaling" then
	
		M[1] ={[1] = 1.0000000, [2] = 0.0000000, [3] = 0.0000000}
		M[2] ={[1] = 0.0000000, [2] = 1.0000000, [3] = 0.0000000}
		M[3] ={[1] = 0.0000000, [2] = 0.0000000, [3] = 1.0000000}
		
		Mi[1] ={[1] = 1.0000000, [2] = 0.0000000, [3] = 0.0000000}
		Mi[2] ={[1] = 0.0000000, [2] = 1.0000000, [3] = 0.0000000}
		Mi[3] ={[1] = 0.0000000, [2] = 0.0000000, [3] = 1.0000000}
	
	elseif mode == "Bradford" then
	
		M[1] ={[1] =  0.8951000, [2] =  0.2664000, [3] =  -0.1614000}
		M[2] ={[1] = -0.7502000, [2] =  1.7135000, [3] =   0.0367000}
		M[3] ={[1] =  0.0389000, [2] = -0.0685000, [3] =   1.0296000}	
		                              
		Mi[1] ={[1] = 0.9869929,  [2] =  -0.1470543 ,[3] =  0.1599627}
		Mi[2] ={[1] = 0.4323053,  [2] =  0.5183603  , [3] =  0.0492912}
		Mi[3] ={[1] = -0.0085287, [2] =  0.0400428  , [3] =  0.9684867}			
	
	
	elseif mode == "Von_Kries" then 
		--could implement von kries
		--not really needed as we dont use chromatic adaption 
	
	end 
	
	-- 3x1 vectors 
	local cone_source = MultMatVec(M, tSourceWhite)
	local cone_dest   = MultMatVec(M, tDestWhite)
	
	-- 3x3 matrice 
 	Mcone[1] ={[1] = cone_dest.x / cone_source.x, [2] = 0.0000000, [3] = 0.0000000}
	Mcone[2] ={[1] = 0.0000000, [2] = cone_dest.y / cone_source.y, [3] = 0.0000000}
	Mcone[3] ={[1] = 0.0000000, [2] = 0.0000000, [3] = cone_dest.z / cone_source.z}
	
	local Mtemp = MultMatMat(Mi, Mcone)
	
	local M_Transformation = MultMatMat(Mtemp, M)
	
	local xyz_dest = MultMatVec(M_Transformation, tXYZ)
	
	return xyz_dest.x, xyz_dest.y, xyz_dest.z
	
	


end 
 
 
-- Returns the angle between two vectors -- 
function get_angle(v1, v2)
	local absv1 = math.sqrt(math.pow(v1.x, 2) + math.pow(v1.y, 2))
	local absv2 = math.sqrt(math.pow(v2.x, 2) + math.pow(v2.y, 2))
	local scalarprodukt = (v1.x * v2.x) + (v1.y * v2.y)
	
	return  math.acos( ( scalarprodukt / (absv1 * absv2)))
end  

-- calculate the length of a direction vector
-- length means absolute distance from .x .y coordinates to whitePoint.x .y 
function get_length(directionVector)
	return math.sqrt(math.pow(directionVector.x,2) + math.pow(directionVector.y,2)) 
end 
 
 
--Returns the dominant wavelength of input parameters x,y (CIE 1931 - 2°Deg - chromaticity)
--negative when direction vector towards purpurline 
function Yxy2wavelength(x,y)

	
	local min_angle = 2*math.pi -- Set the initial min angle to a max value
	local cur_angle = 2*math.pi -- Set the initial current angle to a max value 
	local length = 0.1 
	local saturation = 0.1 
	

	-- use global tRefWhite table to get ur refwhite values which depend on the rgb work space 
	local refWhitex = tRefWhite.x
	local refWhitey = tRefWhite.y 
	
	 
	
	
	local wavelength = 0 
		
	-- Construct direction vector from current input values
	local t_curDirVector = {}
		  t_curDirVector.x = (x-refWhitex)
		  t_curDirVector.y = (y-refWhitey)
		  
	length = get_length(t_curDirVector)
	--print(length)
	-- This means color is very close to white point, i.e. very low saturation at all
	-- In this case return 0, otherwise one might return a valid wavelength -- 

		  
	local t_reverseDirVector = {}
		  t_reverseDirVector.x = 0
		  t_reverseDirVector.y = 0 
	
	-- Construct your spectral line directionvector table --
	local t_CIEdirVector = {}
	for i=1,817 do
		t_CIEdirVector[i] = {}
	end 
	-- Fill the vector table which now contains direction vectors from 1505 entries of the
	-- CIE 1931 table (tChromaticity) to the whitepoint
	for i=1,817 do
		t_CIEdirVector[i].x = tTCS_Chromaticity[i].x - refWhitex -- x value of direction vector
		t_CIEdirVector[i].y = tTCS_Chromaticity[i].y - refWhitey -- y value of direction vector	
	end
	
	
	
	-- Algorithm determines which direction vector in the t_CIEdirVector is closest to the direction vector
	-- given by the current x,y pair
	
	-- Get smalest angle variance 
	for i=1,817 do
		cur_angle = math.abs(get_angle(t_curDirVector, t_CIEdirVector[i]))
		if cur_angle < min_angle then
			min_angle = cur_angle
		end 
	end 
	
	
	
	for i=1, 817 do
		if min_angle == math.abs(get_angle(t_curDirVector, t_CIEdirVector[i])) then
			saturation = get_length(t_curDirVector) / get_length(t_CIEdirVector[i])
			if saturation < 0.01 then 
				return 0, 0 
			else 
				return  tTCS_Chromaticity[i].nm, saturation 
			end 
		end 
	end 
	

	return 0, 0
	
end
 