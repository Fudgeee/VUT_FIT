----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    18:56:18 05/04/2022 
-- Design Name: 
-- Module Name:    rom - Behavioral 
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity rom16x8 is
	port(
		data : out std_logic_vector(127 downto 0);
		animacia : out std_logic_vector(127 downto 0));
end entity;

architecture rtl of rom16x8 is
	constant rom: std_logic_vector(127 downto 0) := ( "00000000"&
																		"00000000"&
																		"01111110"&
																		"00001000"&
																		"01111110"&
																		"00000000"&
																		"00011110"&
																		"01100000"&
																		"00011110"&
																		"00000000"&
																		"01111110"&
																		"00000000"&
																		"00000100"&
																		"01111100"&
																		"00000010"&
																		"00000010");
																		
		constant rom1: std_logic_vector(127 downto 0) := ( "00000000"&
																			"00000000"&
																			"01110000"&
																			"00011000"&
																			"01111101"&
																			"10110110"&
																			"10111100"&
																			"00111100"&
																			"00111100"&
																			"10111100"&
																			"10110110"&
																			"01111101"&
																			"00011000"&
																			"01110000"&
																			"00000000"&
																			"00000000");
		
begin

	data <= rom;
	animacia <= rom1;

end architecture;
