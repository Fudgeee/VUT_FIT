library IEEE;
use IEEE.STD_LOGIC_1164.all;

package newspaper_pack is

type DIRECTION_T is 
(DIR_LEFT, DIR_RIGHT);

function GETCOLUMN (signal DATA : in std_logic_vector; COLID : in integer; ROWS : in integer) return std_logic_vector;

end newspaper_pack;

package body newspaper_pack is

	function GETCOLUMN (signal DATA : in std_logic_vector; COLID : in integer; ROWS : in integer) return std_logic_vector is
		variable result : std_logic_vector (0 to ROWS - 1);
		
		begin
			result := DATA ((COLID*ROWS mod DATA'length) to (((COLID + 1)*ROWS - 1) mod DATA'length));
			return result;
	end;

end newspaper_pack;