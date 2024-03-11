#!/usr/bin/env python3
# Do souboru, nazvaného podle konvence isj_proj6_xnovak00.py, implementujte třídu Polynomial,
# která bude pracovat s polynomy reprezentovanými pomocí seznamů. Například 2x^3 - 3x + 1 bude
# reprezentováno jako [1,-3,0,2] (seznam začíná nejnižším řádem, i když se polynomy většinou zapisují opačně).

class Polynomial:
    # trieda polynomov s metodami inicializacie, vypisu, rovnosti,
    # suctu, nasobenia, umocnenia, derivacie, vycislenia polynomov
    def __init__(self, *args, **kwargs):  # inicializacia prvkov do pola
        self.coefficients = []
        for i in args:
            if isinstance(i, list):
                self.coefficients = i
        if len(self.coefficients) == 0:
            if args:
                self.coefficients = list(args)
            else:
                for name, value in kwargs.items():
                    for i in range(1 + int(name.split("x")[1]) - len(self.coefficients)):
                        self.coefficients.append(0)
                    self.coefficients[int(name.split("x")[1])] = value
        for i in range(len(self.coefficients) - 1, 0, -1):  # vymazanie nadbytocnych nul v najvyssich mocninach
            if self.coefficients[i] == 0:
                del self.coefficients[i]
            else:
                break

    def __str__(self):  # vypis polynomov
        polynom = ""
        if len(self.coefficients) == 0:  # polynom neobsahuje ziadny clen
            raise ValueError("Error: invalid polynom")
        if len(self.coefficients) == 1:  # polynom sa sklada len z absolutneho clena
            polynom += str(self.coefficients[0])
            return polynom
        else:
            for i in reversed(range(len(self.coefficients))):
                if self.coefficients[i] == 0:
                    continue  # preskocenie nuloveho koeficientu
                if polynom:
                    if self.coefficients[i] < 0:
                        polynom += " - "
                    else:
                        polynom += " + "
                if i == 0:
                    polynom += "{0}".format(str(abs(int((self.coefficients[0])))))
                    return polynom
                if i == 1:
                    if abs(self.coefficients[1]) == 1:
                        polynom += "x"
                    else:
                        polynom += "{0}x".format(str(abs(int(self.coefficients[1]))))
                else:
                    if abs(self.coefficients[i]) == 1:
                        polynom += "x^{0}".format(i)
                    else:
                        polynom += "{0}x^{1}".format(str(abs(int(self.coefficients[i]))), i)
            return polynom

    def __eq__(self, other):  # rovnost dvoch polynomov
        if len(self.coefficients) != len(other.coefficients):  # porovnanie dlzky polynomov
            return False
        for first_pol, second_pol in zip(self.coefficients, other.coefficients):
            if first_pol != second_pol:  # porovnanie samotnych clenov
                return False
        return True

    def __add__(self, other):  # sucet dvoch polynomov
        tmp = self.coefficients[:]
        i = 0
        for first_pol, second_pol in zip(self.coefficients, other.coefficients):
            tmp[i] = first_pol + second_pol
            i = i + 1
        if len(self.coefficients) < len(other.coefficients):
            for i in range(len(self.coefficients), len(other.coefficients)):
                tmp.append(other.coefficients[i])
        return Polynomial(tmp)

    def __mul__(self, other):  # sucin dvoch polynomov
        tmp = [0] * (len(self.coefficients) + len(other.coefficients) + 1)
        for i in range(len(self.coefficients)):
            for j in range(len(other.coefficients)):
                tmp[i + j] += self.coefficients[i] * other.coefficients[j]
        return Polynomial(tmp)

    def __pow__(self, n):  # umocnenie polynomov
        if n < 0:
            raise ValueError("Error: Negative power.")
        if n == 0:
            if len(self.coefficients) == 1 and self.coefficients[0] == 0:
                raise ValueError("Error: 0^0.")
            else:
                return 1
        if n == 1:
            return Polynomial(self.coefficients)
        if n > 1:
            tmp = self
            for i in range(1, n):
                tmp = tmp * self
            return Polynomial(tmp)

    def derivative(self):  # derivacia polynomu
        tmp = self.coefficients[:]
        if len(tmp) == 1:
            return 0
        del tmp[0]
        for i in range(len(tmp)):
            tmp[i] = tmp[i] * (i + 1)
        return Polynomial(tmp)

    def at_value(self, x_1, x_2=None):  # vycislenie polynomu pre dane x, pomocou hornerovho schema
        ret = 0
        for i in reversed(range(len(self.coefficients))):
            ret = (ret * x_1) + self.coefficients[i]
        if x_2:
            ret1 = 0
            for i in reversed(range(len(self.coefficients))):
                ret1 = (ret1 * x_2) + self.coefficients[i]
            return ret1 - ret
        return ret

# Instance třídy bude možné vytvářet několika různými způsoby:
# pol1 = Polynomial([1, -3, 0, 2])
# pol2 = Polynomial(1, -3, 0, 2)
# pol3 = Polynomial(x0=1, x3=2, x1=-3)


'''# Volání funkce print() vypíše polynom v obvyklém formátu:
>>> print(pol2)
2x^3 - 3x + 1

# Bude možné porovnávat vektory porovnávat:
>>> pol1 == pol2
True

# Polynomy bude možné sčítat a umocňovat nezápornými celými čísly:
>>> print(Polynomial(1,-3,0,2) + Polynomial(0, 2, 1))
2x^3 + x^2 - x + 1
>>> print(Polynomial(-1, 1) ** 2)
x^2 - 2x  + 1

# A budou fungovat metody derivative() - derivace a at_value() - hodnota polynomu pro zadané x - obě pouze vrací výsledek, nemění samotný polynom:
>>> print(pol1.derivative())
6x^2 - 3
>>> print(pol1.at_value(2))
11
>>> print(pol1.at_value(2,3))
35
# (pokud jsou zadány 2 hodnoty, je výsledkem rozdíl mezi hodnotou at_value() druhého a prvního parametru - může sloužit pro výpočet určitého integrálu, ale ten nemá být implementován)

# Maximální hodnocení bude vyžadovat, abyste:
# - uvedli "shebang" jako v předchozích projektech
# - důsledně používali dokumentační řetězce a komentovali kód
# - nevypisovali žádné ladicí/testovací informace při běžném "import isj_proj6_xnovak00"
# - zajistili, že následující platí:'''


def test():
    assert str(Polynomial(0, 1, 0, -1, 4, -2, 0, 1, 3, 0)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial([-5, 1, 0, -1, 4, -2, 0, 1, 3, 0])) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x - 5"
    assert str(Polynomial(x7=1, x4=4, x8=3, x9=0, x0=0, x5=-2, x3=-1, x1=1)) == "3x^8 + x^7 - 2x^5 + 4x^4 - x^3 + x"
    assert str(Polynomial(x2=0)) == "0"
    assert str(Polynomial(x0=0)) == "0"
    assert Polynomial(x0=2, x1=0, x3=0, x2=3) == Polynomial(2, 0, 3)
    assert Polynomial(x2=0) == Polynomial(x0=0)
    assert str(Polynomial(x0=1)+Polynomial(x1=1)) == "x + 1"
    assert str(Polynomial([-1, 1, 1, 0])+Polynomial(1, -1, 1)) == "2x^2"
    pol1 = Polynomial(x2=3, x0=1)
    pol2 = Polynomial(x1=1, x3=0)
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(pol1+pol2) == "3x^2 + x + 1"
    assert str(Polynomial(x0=-1, x1=1)**1) == "x - 1"
    assert str(Polynomial(x0=-1, x1=1)**2) == "x^2 - 2x + 1"
    pol3 = Polynomial(x0=-1, x1=1)
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(pol3**4) == "x^4 - 4x^3 + 6x^2 - 4x + 1"
    assert str(Polynomial(x0=2).derivative()) == "0"
    assert str(Polynomial(x3=2, x1=3, x0=2).derivative()) == "6x^2 + 3"
    assert str(Polynomial(x3=2, x1=3, x0=2).derivative().derivative()) == "12x"
    pol4 = Polynomial(x3=2, x1=3, x0=2)
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert str(pol4.derivative()) == "6x^2 + 3"
    assert Polynomial(-2, 3, 4, -5).at_value(0) == -2
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3) == 20
    assert Polynomial(x2=3, x0=-1, x1=-2).at_value(3, 5) == 44
    pol5 = Polynomial([1, 0, -2])
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-2.4) == -10.52
    assert pol5.at_value(-1, 3.6) == -23.92
    assert pol5.at_value(-1, 3.6) == -23.92


if __name__ == '__main__':
    test()
