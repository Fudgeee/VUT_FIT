-- fsm.vhd: Finite State Machine
-- Author(s): Adrián Matušík <xmatus35@stud.fit.vutbr.cz>
--
library ieee;
use ieee.std_logic_1164.all;
-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity fsm is
port(
   CLK         : in  std_logic;
   RESET       : in  std_logic;

   -- Input signals
   KEY         : in  std_logic_vector(15 downto 0);
   CNT_OF      : in  std_logic;

   -- Output signals
   FSM_CNT_CE  : out std_logic;
   FSM_MX_MEM  : out std_logic;
   FSM_MX_LCD  : out std_logic;
   FSM_LCD_WR  : out std_logic;
   FSM_LCD_CLR : out std_logic
);
end entity fsm;

-- ---------------------------------------------------------------------------- 7605736424 
--                      Architecture declaration
-- ---------------------------------------------------------------------------- 76011472848
architecture behavioral of fsm is
   type t_state is (DEFAULT, C_7, C_76, C_760, C_7605, C_76057, C_760573, C_7605736,
							C_76057364, C_760573642, C_7605736424, C_7601, C_76011, C_760114,
							C_7601147, C_76011472, C_760114728, C_7601147284, C_76011472848,
							ERROR, ACCESS_DENIED, ACCESS_ALLOWED, FINISH);
   signal present_state, next_state : t_state;

begin
-- -------------------------------------------------------
sync_logic : process(RESET, CLK)
begin
   if (RESET = '1') then
      present_state <= DEFAULT;
   elsif (CLK'event AND CLK = '1') then
      present_state <= next_state;
   end if;
end process sync_logic;
-- -------------------------------------------------------
next_state_logic : process(present_state, KEY, CNT_OF)
begin
   case (present_state) is
   -- - - - - - - - - - - - - - - - - - - - - - -
   when DEFAULT =>
		if (KEY(7) = '1') then
			next_state <= C_7;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= DEFAULT;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - - 
   when C_7 =>
		if (KEY(6) = '1') then
			next_state <= C_76;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_7;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_76 =>
		if (KEY(0) = '1') then
			next_state <= C_760;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_76;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_760 =>
		if (KEY(5) = '1') then
			next_state <= C_7605;
		elsif (KEY(1) = '1') then
			next_state <= C_7601;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_760;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_7605 =>
		if (KEY(7) = '1') then
			next_state <= C_76057;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_7605;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_76057 =>
		if (KEY(3) = '1') then
			next_state <= C_760573;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_76057;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_760573 =>
		if (KEY(6) = '1') then
			next_state <= C_7605736;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_760573;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_7605736 =>
		if (KEY(4) = '1') then
			next_state <= C_76057364;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_7605736;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_76057364 =>
		if (KEY(2) = '1') then
			next_state <= C_760573642;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_76057364;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_760573642 =>
		if (KEY(4) = '1') then
			next_state <= C_7605736424;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_760573642;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
   when C_7605736424 =>
		if (KEY(15) = '1') then
         next_state <= ACCESS_ALLOWED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_7605736424;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - - 
   when C_7601 =>
		if (KEY(1) = '1') then
			next_state <= C_76011;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_7601;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
	when C_76011 =>
		if (KEY(4) = '1') then
			next_state <= C_760114;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_76011;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
	when C_760114 =>
		if (KEY(7) = '1') then
			next_state <= C_7601147;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_760114;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
	when C_7601147 =>
		if (KEY(2) = '1') then
			next_state <= C_76011472;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_7601147;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
	when C_76011472 =>
		if (KEY(8) = '1') then
			next_state <= C_760114728;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_76011472;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
	when C_760114728 =>
		if (KEY(4) = '1') then
			next_state <= C_7601147284;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_760114728;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
	when C_7601147284 =>
		if (KEY(8) = '1') then
			next_state <= C_76011472848;
      elsif (KEY(15) = '1') then
         next_state <= ACCESS_DENIED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_7601147284;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - -
	when C_76011472848 =>
		if (KEY(15) = '1') then
         next_state <= ACCESS_ALLOWED; 
		elsif (KEY(14 downto 0) /= "000000000000000") then
			next_state <= ERROR;
		else next_state <= C_76011472848;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - - 
   when ERROR =>
      next_state <= ERROR;
      if (KEY(15) = '1') then
         next_state <= ACCESS_DENIED;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - - 
   when ACCESS_DENIED =>
      next_state <= ACCESS_DENIED;
      if (CNT_OF = '1') then
         next_state <= FINISH;
      end if;
	-- - - - - - - - - - - - - - - - - - - - - - - 
   when ACCESS_ALLOWED =>
      next_state <= ACCESS_ALLOWED;
      if (CNT_OF = '1') then
         next_state <= FINISH;
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when FINISH =>
      next_state <= FINISH;
      if (KEY(15) = '1') then
         next_state <= DEFAULT; 
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when others =>
      null;
   end case;
end process next_state_logic;

-- -------------------------------------------------------
output_logic : process(present_state, KEY)
begin
   FSM_CNT_CE     <= '0';
   FSM_MX_MEM     <= '0';
   FSM_MX_LCD     <= '0';
   FSM_LCD_WR     <= '0';
   FSM_LCD_CLR    <= '0';

   case (present_state) is
	-- - - - - - - - - - - - - - - - - - - - - - - 
   when ACCESS_DENIED =>
      FSM_CNT_CE <= '1';
      FSM_MX_LCD <= '1';		
		if (CNT_OF = '0') then
         FSM_LCD_WR <= '1';
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when ACCESS_ALLOWED =>
      FSM_CNT_CE <= '1';
      FSM_MX_MEM <= '1';
      FSM_MX_LCD <= '1';
		if (CNT_OF = '0') then
         FSM_LCD_WR <= '1';
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when FINISH =>
      if (KEY(15) = '1') then
         FSM_LCD_CLR    <= '1';
      end if;
   -- - - - - - - - - - - - - - - - - - - - - - -
   when others =>
		if (KEY(15) = '1') then
         FSM_LCD_CLR <= '1';
      elsif (KEY(14 downto 0) /= "000000000000000") then
         FSM_LCD_WR <= '1';
      end if;
   end case;
end process output_logic;

end architecture behavioral;

