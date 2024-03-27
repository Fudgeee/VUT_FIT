#!/usr/bin/env python3
##
# @file main.py
# @brief GUI of calculator
# @author Adrián Matušík
# @date April 2022
##

# Imports
import os
import tkinter as tk
from tkinter import FLAT, N, E, Label, RIGHT, END
import math_lib
import re

calculation = ""


##
# @brief function for adding pressed symbol into calculated string
# @param symbol pressed operator/digit
def add_to_calculation(symbol):
    global calculation
    calculation += str(symbol)
    text_calc.config(state='normal')
    text_calc.delete(1.0, "end")
    text_calc.insert(1.0, calculation)
    text_calc.config(state='disabled')


##
# @brief function for calculating result or throws errors
# @param calc equation to evaluate
def solve(calc):
    calc = calc.split()
    for i in range(0, len(calc)):
        if calc[i] == '-':
            if i - 1 < 0 or not re.search('[0-9|)]', calc[i - 1]):
                if re.search('[0-9]', calc[i + 1]):
                    calc[i] = calc[i] + calc[i + 1]
                    calc.pop(i + 1)
                    calc = [''] + calc
                elif re.search('[sin|cos|tan|log|%|(]', calc[i + 1]):
                    calc.insert(i, '0')
                    i += 1
    for i in range(0, len(calc)):
        if calc[i] == '(':
            R_bracket = False
            for j in range(i + 1, len(calc)):
                if calc[j] == ')':
                    calc[i] = solve(' '.join(calc[i + 1:j]))
                    R_bracket = True
                    for k in range(i, j):
                        calc.pop(k + 1)
                        calc = [''] + calc
                    break
            if not R_bracket:
                raise SyntaxError
    for i in range(0, len(calc)):
        if calc[i] == '\u03c0':
            calc[i] = str(math_lib.pi)
        if calc[i] == 'e':
            calc[i] = str(math_lib.e)
    for i in range(0, len(calc)):
        if calc[i] == 'log':
            calc[i] = str(math_lib.log(float(calc[i + 1])))
            calc.pop(i + 1)
            calc = [''] + calc
        if calc[i] == 'sin':
            calc[i] = str(math_lib.sin(float(calc[i + 1])))
            calc.pop(i + 1)
            calc = [''] + calc
        if calc[i] == 'cos':
            calc[i] = str(math_lib.cos(float(calc[i + 1])))
            calc.pop(i + 1)
            calc = [''] + calc
        if calc[i] == 'tan':
            calc[i] = str(math_lib.tan(float(calc[i + 1])))
            calc.pop(i + 1)
            calc = [''] + calc
        if calc[i] == '%':
            calc[i] = str(math_lib.mod(int(calc[i - 1]), int(calc[i + 1])))
            calc.pop(i + 1)
            calc.pop(i - 1)
            calc = ['', ''] + calc
        if calc[i] == '\u221a':
            calc[i] = str(math_lib.root(float(calc[i + 1]), int(calc[i - 1])))
            calc.pop(i + 1)
            calc.pop(i - 1)
            calc = ['', ''] + calc
        if calc[i] == '^':
            calc[i] = str(math_lib.pow(float(calc[i - 1]), int(calc[i + 1])))
            calc.pop(i + 1)
            calc.pop(i - 1)
            calc = ['', ''] + calc
        if calc[i] == '!':
            calc[i] = str(math_lib.factorial(int(calc[i - 1])))
            calc.pop(i - 1)
            calc = [''] + calc
        if calc[i] == '*':
            calc[i] = str(math_lib.mul(float(calc[i - 1]), float(calc[i + 1])))
            calc.pop(i + 1)
            calc.pop(i - 1)
            calc = ['', ''] + calc
        if calc[i] == '/':
            calc[i] = str(math_lib.div(float(calc[i - 1]), float(calc[i + 1])))
            calc.pop(i + 1)
            calc.pop(i - 1)
            calc = ['', ''] + calc

    for i in range(0, len(calc)):
        if calc[i] == '+':
            calc[i] = str(math_lib.add(float(calc[i - 1]), float(calc[i + 1])))
            calc.pop(i + 1)
            calc.pop(i - 1)
            calc = ['', ''] + calc
        if calc[i] == '-':
            calc[i] = str(math_lib.sub(float(calc[i - 1]), float(calc[i + 1])))
            calc.pop(i + 1)
            calc.pop(i - 1)
            calc = ['', ''] + calc
    return calc.pop()


##
# @brief function for button "=", calculating result or catching exceptions
def evaluate():
    global calculation
    text_calc.config(state='normal')
    text_result.config(state='normal')
    try:
        calculation = solve(calculation)
        text_result.delete(0, END)
        text_result.insert(0, calculation)
    except ValueError:
        text_result.delete(0, END)
        text_result.insert(0, "ValueError")
    except ZeroDivisionError:
        text_result.delete(0, END)
        text_result.insert(0, "ZeroDivision")
    except SyntaxError:
        text_result.delete(0, END)
        text_result.insert(0, "MissingRightBracket")
    calculation = ""
    text_calc.config(state='disabled')
    text_result.config(state='readonly')


##
# @brief function for clearing display after pressing AC on calculator
def clear_all():
    global calculation
    calculation = ""
    text_calc.config(state='normal')
    text_result.config(state='normal')
    text_calc.delete(1.0, "end")
    text_result.delete(0, END)
    text_calc.config(state='disabled')
    text_result.config(state='readonly')


##
# @brief function for deleting last character after pressing C on calculator
def delete_last_char():
    global calculation
    if calculation[-1] == ' ':
        if calculation[-3] == ' ':
            calculation = calculation[:-3]
        else:
            calculation = calculation[:-5]
    else:
        calculation = calculation[:-1]
    text_calc.config(state='normal')
    text_calc.delete(1.0, "end")
    text_calc.insert(1.0, calculation)
    text_calc.config(state='disabled')


##
# @brief function for calling guide for our calculator after pressing "?" on calculator
def help_info():
    help_root = tk.Toplevel()
    help_root.title('Help')
    help_root.tk.call('wm', 'iconphoto', help_root._w, tk.PhotoImage(file='/usr/share/app-install/icons/toJeJedno/icon.png'))
    help_root.geometry()
    help_root.resizable(0, 0)

    help_1 = Label(help_root, text='sin, cos, tan - sine/cosine/tangens of number after', font=("Arial", 10))
    help_1.pack()
    help_2 = Label(help_root, text='log - logarithm of number after', font=("Arial", 10))
    help_2.pack()
    help_3 = Label(help_root, text='x^y - power of number before, number after determines which power ', font=("Arial", 10))
    help_3.pack()
    help_4 = Label(help_root, text='x\u221ay - root of number after, number before determines which root', font=("Arial", 10))
    help_4.pack()
    help_5 = Label(help_root, text='mod - returns rest after division', font=("Arial", 10))
    help_5.pack()
    help_6 = Label(help_root, text='n! - factorial of number before ', font=("Arial", 10))
    help_6.pack()
    help_7 = Label(help_root, text='DEL - delete last character', font=("Arial", 10))
    help_7.pack()
    help_8 = Label(help_root, text='AC - delete all', font=("Arial", 10))
    help_8.pack()
    help_9 = Label(help_root, text='+, -, x, / - plus/minus/multiplication/division', font=("Arial", 10))
    help_9.pack()
    help_10 = Label(help_root, text='= - calculates the result ', font=("Arial", 10))
    help_10.pack()
    help_root.mainloop()


##
# @brief function implementing keyboard input
def keydown(ch):
    if re.search('[0-9]', ch.char):
        add_to_calculation(ch.char)
    if re.search('[+|\-|*|/]', ch.char):
        add_to_calculation(' ' + ch.char + ' ')
    if re.search('\r', ch.char):
        evaluate()
    if re.search('\.', ch.char):
        add_to_calculation(ch.char)
    if re.search('\x08', ch.char):
        delete_last_char()


##
# @brief creating window for calculator and setting up attributes of window
root = tk.Tk()
root.title('Calculator')
root.tk.call('wm', 'iconphoto', root._w, tk.PhotoImage(file='/usr/share/app-install/icons/toJeJedno/icon.png'))
root.configure(bg="#8f9191")
root.geometry("380x348")
root.resizable(0, 0)
root.bind("<KeyPress>", keydown)

##
# @brief initialization of display
text_bg = tk.Frame(root, height=3, width=18, bg="#17aee2", relief=FLAT)
text_bg.grid(row=0, columnspan=5)
text_calc = tk.Text(text_bg, height=2, width=18, font=("Arial", 24), fg="black", bg="#17aee2", relief=FLAT, state='disabled')
text_calc.grid(row=0, columnspan=4)
text_calc.config(borderwidth=-1)
btn_help = tk.Button(text_bg, text="?", command=lambda: help_info(), width=3, font=("Arial", 14), fg="black", bg="#17aee2", relief=FLAT, highlightthickness=0, bd=0)
btn_help.grid(row=0, column=4, sticky=N + E)
text_result = tk.Entry(text_bg, width=20, font=("Arial", 24), fg="black", bg="#17aee2", relief=FLAT, justify=RIGHT, state='readonly', readonlybackground="#17aee2", highlightthickness=0, bd=0)
text_result.grid(row=1, columnspan=5)

##
# @brief initialization of grid with buttons
btn_sin = tk.Button(root, text="sin", command=lambda: add_to_calculation(" sin "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_sin.grid(row=4, column=0, padx=0, pady=2)
btn_cos = tk.Button(root, text="cos", command=lambda: add_to_calculation(" cos "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_cos.grid(row=4, column=1, padx=0, pady=2)
btn_tan = tk.Button(root, text="tan", command=lambda: add_to_calculation(" tan "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_tan.grid(row=4, column=2, padx=0, pady=2)
btn_log = tk.Button(root, text="log", command=lambda: add_to_calculation(" log "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_log.grid(row=4, column=3, padx=0, pady=2)
btn_x2 = tk.Button(root, text="x ^ y", command=lambda: add_to_calculation(" ^ "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_x2.grid(row=4, column=4, padx=0, pady=2)

btn_sqrt = tk.Button(root, text="x \u221a y", command=lambda: add_to_calculation(" \u221a "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_sqrt.grid(row=5, column=0, padx=0, pady=2)
btn_open = tk.Button(root, text="(", command=lambda: add_to_calculation(" ( "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_open.grid(row=5, column=1, padx=0, pady=2)
btn_close = tk.Button(root, text=")", command=lambda: add_to_calculation(" ) "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_close.grid(row=5, column=2, padx=0, pady=2)
btn_mod = tk.Button(root, text="mod", command=lambda: add_to_calculation(" % "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_mod.grid(row=5, column=3, padx=0, pady=2)
btn_fact = tk.Button(root, text="n!", command=lambda: add_to_calculation(" ! "), width=4, font=("Arial", 14), fg="white", bg="#465657")
btn_fact.grid(row=5, column=4, padx=0, pady=2)

btn_7 = tk.Button(root, text="7", command=lambda: add_to_calculation(7), width=4, font=("Arial", 14), fg="white", bg="black")
btn_7.grid(row=6, column=0, padx=0, pady=2)
btn_8 = tk.Button(root, text="8", command=lambda: add_to_calculation(8), width=4, font=("Arial", 14), fg="white", bg="black")
btn_8.grid(row=6, column=1, padx=0, pady=2)
btn_9 = tk.Button(root, text="9", command=lambda: add_to_calculation(9), width=4, font=("Arial", 14), fg="white", bg="black")
btn_9.grid(row=6, column=2, padx=0, pady=2)
btn_clr = tk.Button(root, text="DEL", command=delete_last_char, width=4, font=("Arial", 14), fg="white", bg="#ff6800")
btn_clr.grid(row=6, column=3, padx=0, pady=2)
btn_backspace = tk.Button(root, text="AC", command=clear_all, width=4, font=("Arial", 14), fg="white", bg="#ff6800")
btn_backspace.grid(row=6, column=4, padx=0, pady=2)

btn_4 = tk.Button(root, text="4", command=lambda: add_to_calculation(4), width=4, font=("Arial", 14), fg="white", bg="black")
btn_4.grid(row=7, column=0, padx=0, pady=2)
btn_5 = tk.Button(root, text="5", command=lambda: add_to_calculation(5), width=4, font=("Arial", 14), fg="white", bg="black")
btn_5.grid(row=7, column=1, padx=0, pady=2)
btn_6 = tk.Button(root, text="6", command=lambda: add_to_calculation(6), width=4, font=("Arial", 14), fg="white", bg="black")
btn_6.grid(row=7, column=2, padx=0, pady=2)
btn_mul = tk.Button(root, text="x", command=lambda: add_to_calculation(" * "), width=4, font=("Arial", 14), fg="white", bg="black")
btn_mul.grid(row=7, column=3, padx=0, pady=2)
btn_div = tk.Button(root, text="/", command=lambda: add_to_calculation(" / "), width=4, font=("Arial", 14), fg="white", bg="black")
btn_div.grid(row=7, column=4, padx=0, pady=2)

btn_1 = tk.Button(root, text="1", command=lambda: add_to_calculation(1), width=4, font=("Arial", 14), fg="white", bg="black")
btn_1.grid(row=8, column=0, padx=0, pady=2)
btn_2 = tk.Button(root, text="2", command=lambda: add_to_calculation(2), width=4, font=("Arial", 14), fg="white", bg="black")
btn_2.grid(row=8, column=1, padx=0, pady=2)
btn_3 = tk.Button(root, text="3", command=lambda: add_to_calculation(3), width=4, font=("Arial", 14), fg="white", bg="black")
btn_3.grid(row=8, column=2, padx=0, pady=2)
btn_plus = tk.Button(root, text="+", command=lambda: add_to_calculation(" + "), width=4, font=("Arial", 14), fg="white", bg="black")
btn_plus.grid(row=8, column=3, padx=0, pady=2)
btn_minus = tk.Button(root, text="-", command=lambda: add_to_calculation(" - "), width=4, font=("Arial", 14), fg="white", bg="black")
btn_minus.grid(row=8, column=4, padx=0, pady=2)

btn_pi = tk.Button(root, text="\u03c0", command=lambda: add_to_calculation("\u03c0"), width=4, font=("Arial", 14), fg="white", bg="black")
btn_pi.grid(row=9, column=0, padx=0, pady=2)
btn_0 = tk.Button(root, text="0", command=lambda: add_to_calculation(0), width=4, font=("Arial", 14), fg="white", bg="black")
btn_0.grid(row=9, column=1, padx=0, pady=2)
btn_e = tk.Button(root, text="e", command=lambda: add_to_calculation("e"), width=4, font=("Arial", 14), fg="white", bg="black")
btn_e.grid(row=9, column=2, padx=0, pady=2)
btn_dot = tk.Button(root, text=".", command=lambda: add_to_calculation("."), width=4, font=("Arial", 14), fg="white", bg="black")
btn_dot.grid(row=9, column=3, padx=0, pady=2)
btn_eval = tk.Button(root, text="=", command=evaluate, width=4, font=("Arial", 14), fg="white", bg="#17aee2")
btn_eval.grid(row=9, column=4, padx=0, pady=2)

root.mainloop()
