-- cpu.vhd: Simple 8-bit CPU (BrainF*ck interpreter)
-- Copyright (C) 2020 Brno University of Technology,
--                    Faculty of Information Technology
-- Author(s): DOPLNIT
--

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_arith.all;
use ieee.std_logic_unsigned.all;

-- ----------------------------------------------------------------------------
--                        Entity declaration
-- ----------------------------------------------------------------------------
entity cpu is
 port (
   CLK   : in std_logic;  -- hodinovy signal
   RESET : in std_logic;  -- asynchronni reset procesoru
   EN    : in std_logic;  -- povoleni cinnosti procesoru
 
   -- synchronni pamet ROM
   CODE_ADDR : out std_logic_vector(11 downto 0); -- adresa do pameti
   CODE_DATA : in std_logic_vector(7 downto 0);   -- CODE_DATA <- rom[CODE_ADDR] pokud CODE_EN='1'
   CODE_EN   : out std_logic;                     -- povoleni cinnosti
   
   -- synchronni pamet RAM
   DATA_ADDR  : out std_logic_vector(9 downto 0); -- adresa do pameti
   DATA_WDATA : out std_logic_vector(7 downto 0); -- ram[DATA_ADDR] <- DATA_WDATA pokud DATA_EN='1'
   DATA_RDATA : in std_logic_vector(7 downto 0);  -- DATA_RDATA <- ram[DATA_ADDR] pokud DATA_EN='1'
   DATA_WE    : out std_logic;                    -- cteni (0) / zapis (1)
   DATA_EN    : out std_logic;                    -- povoleni cinnosti 
   
   -- vstupni port
   IN_DATA   : in std_logic_vector(7 downto 0);   -- IN_DATA <- stav klavesnice pokud IN_VLD='1' a IN_REQ='1'
   IN_VLD    : in std_logic;                      -- data platna
   IN_REQ    : out std_logic;                     -- pozadavek na vstup data
   
   -- vystupni port
   OUT_DATA : out  std_logic_vector(7 downto 0);  -- zapisovana data
   OUT_BUSY : in std_logic;                       -- LCD je zaneprazdnen (1), nelze zapisovat
   OUT_WE   : out std_logic                       -- LCD <- OUT_DATA pokud OUT_WE='1' a OUT_BUSY='0'
 );
end cpu;


-- ----------------------------------------------------------------------------
--                      Architecture declaration
-- ----------------------------------------------------------------------------
architecture behavioral of cpu is
 -- zde dopiste potrebne deklarace signalu
 -- PC ----------
	signal pc_reg : std_logic_vector(11 downto 0);
	signal pc_inc : std_logic;
	signal pc_dec : std_logic;
	signal pc_ld : std_logic;
 -- RAS ----------
	signal ras_reg : std_logic_vector(191 downto 0);
	signal ras_push : std_logic;
	signal ras_pop : std_logic;
 -- CNT ----------
	signal cnt_reg : std_logic_vector(7 downto 0);
	signal cnt_inc : std_logic;
	signal cnt_dec : std_logic;
 -- PTR ----------
	signal ptr_reg : std_logic_vector(9 downto 0);
	signal ptr_inc : std_logic;
	signal ptr_dec : std_logic;
 -- STATES ----------
	type fsm_state is(
		s_start,
		s_fetch,
		s_decode,
		s_program_inc,
		s_program_dec,
		s_pointer_inc,
		s_pointer_dec,
		s_while_start,
		s_while_end,
		s_putchar,
		s_getchar,
		s_null,
		s_program_mux_inc,
		s_program_end_inc,
		s_program_mux_dec,
		s_program_end_dec,
		s_putchar_done,
		s_getchar_done,
		s_while_check,
		s_while_loop,
		s_while_en
	);
	signal state : fsm_state := s_start;
	signal nState : fsm_state;
 -- MUX ----------
	signal mux_sel : std_logic_vector(1 downto 0) := (others => '0');
begin
 -- zde dopiste vlastni VHDL kod
 -- pri tvorbe kodu reflektujte rady ze cviceni INP, zejmena mejte na pameti, ze 
 --   - nelze z vice procesu ovladat stejny signal,
 --   - je vhodne mit jeden proces pro popis jedne hardwarove komponenty, protoze pak
 --   - u synchronnich komponent obsahuje sensitivity list pouze CLK a RESET a 
 --   - u kombinacnich komponent obsahuje sensitivity list vsechny ctene signaly.
 -- PC ----------
	pc: process (CLK, RESET, pc_reg, pc_inc, pc_dec, pc_ld) is
	begin
		if RESET = '1' then
			pc_reg <= (others => '0');
		elsif rising_edge(CLK) then
			if pc_inc = '1' then
				pc_reg <= pc_reg + 1;
			elsif pc_dec = '1' then
				pc_reg <= pc_reg - 1;
			elsif pc_ld = '1' then
				pc_reg <= ras_reg(191 downto 180);
			end if;
		end if;
	end process;
	CODE_ADDR <= pc_reg;
 -- RAS ----------
	ras: process(CLK, RESET) is
	begin
  		if (RESET='1') then
  		   	 ras_reg <= (others => '0');
  		elsif rising_edge(CLK) then
  		   	if ras_push = '1' then
   	      			ras_reg <= pc_reg & ras_reg(191 downto 12);
			elsif ras_pop = '1' then
				ras_reg <= ras_reg(179 downto 0) & "000000000000";
   	   	 	end if;
   		end if;
	end process;	
 -- PTR ----------
	ptr: process (CLK, RESET, ptr_reg, ptr_inc, ptr_dec) is
	begin
		if RESET = '1' then
			ptr_reg <= (others => '0');
		elsif rising_edge(CLK) then
			if ptr_inc = '1' then
				ptr_reg <= ptr_reg + 1;
			elsif ptr_dec = '1' then
				ptr_reg <= ptr_reg - 1;
			end if;
		end if;
	end process;
	DATA_ADDR <= ptr_reg;
 -- MUX ----------
	mx: process (CLK, RESET, mux_sel, IN_DATA, DATA_RDATA) is
	begin
		if RESET = '1' then
			DATA_WDATA <= (others => '0');
		elsif rising_edge(CLK) then
			case mux_sel is
				when "00" =>
					DATA_WDATA <= IN_DATA;
				when "01" =>
					DATA_WDATA <= DATA_RDATA + 1;
				when "10" =>
					DATA_WDATA <= DATA_RDATA - 1;
				when others =>
					DATA_WDATA <= (others => '0');
			end case;
		end if;
	end process;
 -- CNT ----------
	cnt: process (CLK, RESET, cnt_reg, cnt_inc, cnt_dec)
	begin
		if RESET = '1' then
			cnt_reg <= (others => '0');
		elsif rising_edge(CLK) then
			if cnt_inc = '1' then
				cnt_reg <= cnt_reg + 1;
			elsif cnt_dec = '1' then
				cnt_reg <= cnt_reg - 1;
			end if;
		end if;
	end process;
 -- FSM ----------
	state_logic: process (CLK, RESET, EN) is
	begin
		if RESET = '1' then
			state <= s_start;
		elsif rising_edge(CLK) then
			if EN = '1' then
				state <= nState;
			end if;
		end if;
	end process;
	fsm: process (state, OUT_BUSY, IN_VLD, CODE_DATA, DATA_RDATA) is
	begin
		pc_inc <= '0';
		pc_dec <= '0';
		pc_ld <= '0';
		ras_pop <= '0';
		ras_push <= '0';
		cnt_inc <= '0';
		cnt_dec <= '0';
		ptr_inc <= '0';
		ptr_dec <= '0';
		CODE_EN <= '0';
		DATA_EN <= '0';
		DATA_WE <= '0';
		IN_REQ <= '0';
		OUT_WE <= '0';
		mux_sel <= "00";
		case state is
			when s_start =>
				nState <= s_fetch;
			when s_fetch =>
				CODE_EN <= '1';
				nState <= s_decode;
			when s_decode =>
				case CODE_DATA is
					when X"3E" =>
						nState <= s_pointer_inc;
					when X"3C" =>
						nState <= s_pointer_dec;
					when X"2B" =>
						nState <= s_program_inc;
					when X"2D" =>
						nState <= s_program_dec;
					when X"5B" =>
						nState <= s_while_start;
					when X"5D" =>
						nState <= s_while_end;
					when X"2E" =>
						nState <= s_putchar;
					when X"2C" =>
						nState <= s_getchar;
					when X"00" =>
						nState <= s_null;
					when others =>
						pc_inc <= '1';
						nState <= s_fetch;
				end case;
			when s_pointer_inc =>
				pc_inc <= '1';
				ptr_inc <= '1';
				nState <= s_fetch;
			when s_pointer_dec =>
				pc_inc <= '1';
				ptr_dec <= '1';
				nState <= s_fetch;
			when s_program_inc =>
				DATA_EN <= '1';
				DATA_WE <= '0';
				nState <= s_program_mux_inc;
			when s_program_mux_inc =>
				mux_sel <= "01";
				nState <= s_program_end_inc;
			when s_program_end_inc =>
				DATA_EN <= '1';
				DATA_WE <= '1';
				pc_inc <= '1';
				nState <= s_fetch;
			when s_program_dec =>	
				DATA_EN <= '1';
				DATA_WE <= '0';
				nState <= s_program_mux_dec;
			when s_program_mux_dec =>
				mux_sel <= "10";
				nState <= s_program_end_dec;
			when s_program_end_dec =>
				DATA_EN <= '1';
				DATA_WE <= '1';
				pc_inc <= '1';
				nState <= s_fetch;
			when s_putchar =>
				DATA_EN <= '1';
				DATA_WE <= '0';
				nState <= s_putchar_done;	
			when s_putchar_done =>
				if OUT_BUSY = '1' then
					DATA_EN <= '1';
					DATA_WE <= '0';
					nState <= s_putchar_done;	
				else
				       	OUT_WE <= '1';
					OUT_DATA <= DATA_RDATA;
					pc_inc <= '1';
					nState <= s_fetch;
				end if;
			when s_getchar =>
				IN_REQ <= '1';
				mux_sel <= "00";
				nState <= s_getchar_done;
			when s_getchar_done =>
				if IN_VLD = '0' then
					IN_REQ <= '1';
					mux_sel <= "00";
					nState <= s_getchar_done;
				else
					DATA_EN <= '1';
					DATA_WE <= '1';
					pc_inc <= '1';
					nState <= s_fetch;
				end if;
			when s_while_start =>
				pc_inc <= '1';
				DATA_EN <= '1';
				DATA_WE <= '0';
				nState <= s_while_check;
			when s_while_check =>
				if DATA_RDATA = "00000000" then
					cnt_inc <= '1';
					nState <= s_while_loop;
				else
					ras_push <= '1';
					nState <= s_fetch;
				end if;
			when s_while_loop =>
				if cnt_reg /= "000000000000" then
					nState <= s_fetch;
				else
					CODE_EN <= '1';
					nState <= s_while_en;
				end if;
			when s_while_en =>
				if CODE_DATA = X"5B" then	
					cnt_inc <= '1';
				elsif CODE_DATA = X"5D" then
					cnt_dec <= '1';
				end if;
				pc_inc <= '1';
				nState <= s_while_loop;	
			when s_while_end =>
				if DATA_RDATA = "00000000" then
					pc_inc <= '1';
					ras_pop <= '1';
					nState <= s_fetch;
				else
					pc_ld <= '1';
					nState <= s_fetch;				
				end if;
			when s_null =>
				nState <= s_null;
			when others =>
		end case;
	end process;
end behavioral;
