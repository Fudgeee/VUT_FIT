----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    14:07:50 05/04/2022 
-- Design Name: 
-- Module Name:    sloupec - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.newspaper_pack.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity sloupec is
    Port ( CLK : in  STD_LOGIC;
           RESET : in  STD_LOGIC;
           STATE : out  STD_LOGIC_VECTOR;
           INIT_STATE : in  STD_LOGIC_VECTOR;
           NEIGH_LEFT : in  STD_LOGIC_VECTOR;
           NEIGH_RIGHT : in  STD_LOGIC_VECTOR;
           DIRECTION : in  DIRECTION_T;
           EN : in  STD_LOGIC);
end sloupec;

architecture Behavioral of sloupec is

begin

	process (CLK, RESET) is
	variable change : STD_LOGIC := '0';
	begin
		if rising_edge(CLK) then
			if RESET = '1' then
				change := '0';
			end if;
			if change = '0' then
				STATE <= INIT_STATE;
			end if;
			if EN = '1' then
				if DIRECTION = DIR_RIGHT then
					STATE <= NEIGH_RIGHT;
				else
					STATE <= NEIGH_LEFT;
				end if;
				change := '1';
			end if;
		end if;
	end process;
	
end Behavioral;

