-- Citac s volitelnou frekvenci
-- IVH projekt - ukol2
-- autor: ???

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
-- v pripade nutnosti muzete nacist dalsi knihovny

entity counter is
	 Generic (
			CLK_PERIOD : time := 10 ns;
			OUT_PERIOD : time := 1000 ns);			
    Port ( CLK : in  STD_LOGIC;
           RESET : in  STD_LOGIC;
           EN : out  STD_LOGIC);
end counter;

architecture Behavioral of counter is

-- zde je funkce log2 z prednasek, pravdepodobne se vam bude hodit.
	function log2(A: integer) return integer is
		variable bits : integer := 0;
		variable b : integer := 1;
	begin
		while (b <= a) loop
			b := b * 2;
			bits := bits + 1;
		end loop;
		return bits;
	end function;
	
begin
-- citac bude mit 2 genericke parametry: periodu hodinoveho signalu (CLK_PERIOD) a vystupni
-- periodu (OUT_PERIOD) (obe dve zadane jako cas). Citac s periodou odpovidajici OUT_PERIOD
-- (t.j., napr za 1 ms) aktivuje na jeden hodinovy cyklus signal EN po dobu jednoho taktu CLK
-- reset je aktivni v 1: tj kdyz je reset = 1, tak se vymaze vnitrni citac
-- pro zjednoduseni pocitejte, ze OUT_PERIOD je delitelne CLK_PERIOD beze zbytku a je vetsi.

-- Signal EN bude aktivovany po 1 periodu hodinoveho vstupu CLK - k cemu vam staci pouze 
-- signal CLK a jeho priznak CLK'event. Genericke parametry OUT_PERIOD a CLK_FPERIOD slouzi pouze 
-- k vypoctu toho,  do kolika citac pocita. 

process(CLK,RESET)
variable c : integer := 0;
begin
if RESET = '1' then 
	EN <= '0';
	c := 0;
elsif CLK'event then
	if c = (OUT_PERIOD / CLK_PERIOD)*2 then
		EN <= '1';
		c := 1;
	else
		if c = 2 then
			EN <= '0';
		end if;
		c := c + 1;
	end if;
end if;
end process;
end Behavioral;