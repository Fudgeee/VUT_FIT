library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use work.newspaper_pack.ALL;
use IEEE.NUMERIC_STD.ALL;

architecture Behavioral of tlv_gp_ifc is
	signal en : std_logic := '0';
	signal A : std_logic_vector(3 downto 0) := "0001";
	signal R : std_logic_vector(7 downto 0) := "01011100";
	signal cnt_posuv : std_logic_vector(22 downto 0) := (others => '0');  -- 0.42s - 20MHz / 8388608 ~ 23b
	signal cnt : std_logic_vector(11 downto 0) := (others => '0');  -- 0.0002s - 20MHz / 4096 ~ 12b
	signal data : std_logic_vector(127 downto 0) := (others => '0');
	signal animacia : std_logic_vector(127 downto 0) := (others => '0');
	type stlpec is array (15 downto 0) of std_logic_vector(7 downto 0);
	signal display : stlpec := (others => (others => '0'));
	signal display2 : stlpec := (others => (others => '0'));
	signal DIR : DIRECTION_T := DIR_RIGHT;
	signal DIR1 : DIRECTION_T;
	signal posuv : STD_LOGIC_VECTOR(0 to 5) := (others => '0');
	signal stav : STD_LOGIC := '0';
	signal posunute : STD_LOGIC := '0';
	
component rom16x8 is
	port(
		data : out std_logic_vector;
		animacia : out std_logic_vector);
end component;

component sloupec is
	port ( 
		CLK : in  STD_LOGIC;
      RESET : in  STD_LOGIC;
      STATE : out  STD_LOGIC_VECTOR;
      INIT_STATE : in  STD_LOGIC_VECTOR;
      NEIGH_LEFT : in  STD_LOGIC_VECTOR;
      NEIGH_RIGHT : in  STD_LOGIC_VECTOR;
      DIRECTION : in  DIRECTION_T;
      EN : in  STD_LOGIC);
end component;

component fsm is
	port ( 
		CLK : in  STD_LOGIC;
      RST : in  STD_LOGIC;
		DIR : out DIRECTION_T;
		stav : out STD_LOGIC;
		posunute : in STD_LOGIC);
end component;

begin
	rom : rom16x8
	port map(
		data => data,
		animacia => animacia);
	
	vytvorenie_stlpcov : for i in 0 to 15 generate
		generovanie : sloupec
		port map(
			CLK => clk,
			RESET => reset,
			STATE => display(i),
			INIT_STATE => data(7+(i)*8 downto(i)*8),
			NEIGH_LEFT => display(conv_integer(std_logic_vector(to_unsigned(i,4)+1))),
			NEIGH_RIGHT => display(conv_integer(std_logic_vector(to_unsigned(i,4)-1))),
			DIRECTION => DIR,
			EN => en);
	
		generovanie_animacie : sloupec
		port map(
			CLK => clk,
			RESET => reset,
			STATE => display2(i),
			INIT_STATE => animacia(7+(i)*8 downto(i)*8),
			NEIGH_LEFT => display2(conv_integer(std_logic_vector(to_unsigned(i,4)+1))),
			NEIGH_RIGHT => display2(conv_integer(std_logic_vector(to_unsigned(i,4)-1))),
			DIRECTION => DIR,
			EN => en);
	end generate;
	
	automat : fsm
	port map(
		CLK => clk,
		RST => reset,
		DIR => DIR1,
		stav => stav,
		posunute => posunute);
		
	cnt_process : process (clk) is
	begin
		if rising_edge(clk) then
			cnt <= cnt + 1;
			en <= '0';
			posunute <= '0';
			DIR <= DIR1;
			if conv_integer(cnt) = 0 then
				A <= A + 1;
				if stav = '0' then
					R <= display(conv_integer(A));
				else
					R <= display2(conv_integer(A));
				end if;
			end if;
			cnt_posuv <= cnt_posuv + 1;
			if conv_integer(cnt_posuv) = 0 then
				en <= '1';
				posuv <= posuv + 1;
				if posuv = 47 then
					posunute <= '1';
					posuv <= "000000";
				end if;
			end if;
		end if;
	
	end process;

    -- mapovani vystupu
    -- nemenit
    X(6) <= A(3);
    X(8) <= A(1);
    X(10) <= A(0);
    X(7) <= '0'; -- en_n
    X(9) <= A(2);

    X(16) <= R(1);
    X(18) <= R(0);
    X(20) <= R(7);
    X(22) <= R(2);
  
    X(17) <= R(4);
    X(19) <= R(3);
    X(21) <= R(6);
    X(23) <= R(5);
end Behavioral;

