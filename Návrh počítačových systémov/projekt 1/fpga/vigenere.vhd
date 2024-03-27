library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.std_logic_arith.all;
use IEEE.std_logic_unsigned.all;

-- rozhrani Vigenerovy sifry
entity vigenere is
   port(
         CLK : in std_logic;
         RST : in std_logic;
         DATA : in std_logic_vector(7 downto 0);
         KEY : in std_logic_vector(7 downto 0);

         CODE : out std_logic_vector(7 downto 0)
    );
end vigenere;

-- V souboru fpga/sim/tb.vhd naleznete testbench, do ktereho si doplnte
-- znaky vaseho loginu (velkymi pismeny) a znaky klice dle vaseho prijmeni.

architecture behavioral of vigenere is
    -- Sem doplnte definice vnitrnich signalu, prip. typu, pro vase reseni,
    -- jejich nazvy doplnte tez pod nadpis Vigenere Inner Signals v souboru
    -- fpga/sim/isim.tcl. Nezasahujte do souboru, ktere nejsou explicitne
    -- v zadani urceny k modifikaci.
	type tState is (add, sub);
	signal posuv: std_logic_vector(7 downto 0);
	signal pluskorekcia: std_logic_vector(7 downto 0);
	signal minuskorekcia: std_logic_vector(7 downto 0);	
	signal state: tState := add;
	signal nextstate: tState := sub;
	signal FSM: std_logic_vector(1 downto 0);
	signal hashtag: std_logic_vector(7 downto 0) := "00100011";

begin
    -- Sem doplnte popis obvodu. Doporuceni: pouzivejte zakladni obvodove prvky
    -- (multiplexory, registry, dekodery,...), jejich funkce popisujte pomoci
    -- procesu VHDL a propojeni techto prvku, tj. komunikaci mezi procesy,
    -- realizujte pomoci vnitrnich signalu deklarovanych vyse.
    -- DODRZUJTE ZASADY PSANI SYNTETIZOVATELNEHO VHDL KODU OBVODOVYCH PRVKU,
    -- JEZ JSOU PROBIRANY ZEJMENA NA UVODNICH CVICENI INP A SHRNUTY NA WEBU:
    -- http://merlin.fit.vutbr.cz/FITkit/docs/navody/synth_templates.html.
	stateproces: process (CLK, RST) is
	begin
		if (RST = '1') then
			state <= add;
		elsif rising_edge (CLK) then
			state <= nextstate;
		end if;
	end process;

	FSMproces: process (state, DATA, RST) is
	begin
		case state is
			when add =>
				nextstate <= sub;
				FSM <= "01"; 
			when sub =>
				nextstate <= add;
				FSM <= "10"; 
		end case;
		if (DATA > 47 and DATA < 58) then
			FSM <= "00";
		end if;
		if (RST = '1') then
			FSM <= "00";
		end if;
	end process;
	
	with FSM select
		CODE <= pluskorekcia when "01",
				  minuskorekcia when "10",
				  hashtag when others;
	
	posuvnyproces: process (KEY) is
	begin
		posuv <= KEY - 64;
	end process;

	plusovyproces: process (DATA, posuv) is
		variable tmp: std_logic_vector(7 downto 0);
	begin
		tmp := DATA + posuv;
		if (tmp > 90) then 
			tmp := tmp - 26;
		end if;	
		pluskorekcia <= tmp;
	end process;

	minusovyproces: process (DATA, posuv) is
		variable tmp: std_logic_vector(7 downto 0);
	begin
		tmp:= DATA - posuv;
		if (tmp < 65) then
			tmp := tmp + 26;
		end if;
		minuskorekcia <= tmp;
	end process;

end behavioral;
