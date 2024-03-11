----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    13:31:05 05/04/2022 
-- Design Name: 
-- Module Name:    fsm - Behavioral 
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity fsm is
    Port ( CLK : in  STD_LOGIC;
           RST : in  STD_LOGIC;
			  DIR : out DIRECTION_T;
			  stav : out STD_LOGIC;
			  posunute : in STD_LOGIC);
end fsm;

architecture Behavioral of fsm is

--Insert the following in the architecture before the begin keyword
   --Use descriptive names for the states, like st1_reset, st2_search
   type state_type is (st1_move_right, st2_move_left, st3_my_animation); 
   signal state, next_state : state_type; 
   --Declare internal signals for all outputs of the state-machine
   --signal A_i : std_logic;  -- example output signal
   --other outputs

begin

--Insert the following in the architecture after the begin keyword
   SYNC_PROC: process (CLK)
   begin
      if (CLK'event and CLK = '1') then
         if (RST = '1') then
            state <= st1_move_right;
         else
            state <= next_state;
         -- assign other outputs to internal signals
         end if;        
      end if;
   end process;
 
   --MEALY State-Machine - Outputs based on state and inputs
   --OUTPUT_DECODE: process (state, <input1>, <input2>, ...)
   --begin
      --insert statements to decode internal output signals
      --below is simple example
   --   if (state = st3_<name> and <input1> = '1') then
   --      A_i <= '1';
   --   else
   --      A_i <= '0';
   --   end if;
   --end process;
 
   NEXT_STATE_DECODE: process (CLK, state) is
   begin
		if rising_edge(CLK) then
			--declare default state for next_state to avoid latches
			next_state <= state;  --default is to stay in current state
			--insert statements to decode next_state
			--below is a simple example
		
			case (state) is
				when st1_move_right =>
					DIR <= DIR_RIGHT;
					stav <= '0';
					if posunute = '1' then
						next_state <= st2_move_left;
					end if;
				when st2_move_left =>
					DIR <= DIR_LEFT;
					stav <= '0';
					if posunute = '1' then
						next_state <= st3_my_animation;
					end if;
				when st3_my_animation =>
					DIR <= DIR_RIGHT;
					stav <= '1';
					if posunute = '1' then
						next_state <= st1_move_right;
					end if;
				when others =>
					next_state <= st1_move_right;
			end case; 
		end if;
   end process;

end Behavioral;

