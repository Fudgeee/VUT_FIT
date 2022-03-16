library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use work.newspaper_pack.ALL;

entity newspaper_pack_tb is
end newspaper_pack_tb;

architecture Behavioral of newspaper_pack_tb is
signal test_signal : std_logic_vector (0 to 11) := "101001100111";
signal test_signal2 : std_logic_vector (0 to 2);
signal test_signal3 : std_logic_vector ( 0 to 5);
signal test_signal4 : std_logic_vector ( 0 to 3);

begin

process
begin
test_signal2 <= GETCOLUMN (test_signal, 2, 3);
wait for 10ns;
assert (test_signal2 = "100") report "TEST 1: expected 100 / fail" severity note;
assert (test_signal2 /= "100") report "TEST 2: expected 100 / success" severity note;
assert (test_signal2 = "010") report "TEST 3: expected 100 / success" severity note;

test_signal3 <= GETCOLUMN (test_signal, 5, 6);
wait for 10ns;
assert (test_signal3 = "100111") report "TEST 4: expected 100111 / fail" severity note;
assert (test_signal3 /= "100111") report "TEST 5: expected 100111 / success" severity note;

test_signal4 <= GETCOLUMN (test_signal, 0, 4);
wait for 10ns;
assert (test_signal4 = "1010") report "TEST 6: expected 1010 / fail" severity note;
test_signal4 <= GETCOLUMN (test_signal, 2, 4);
wait for 10ns;
assert (test_signal4 /= "0111") report "TEST 7: expected 0111 / success" severity note;

wait;
end process;

end Behavioral;

