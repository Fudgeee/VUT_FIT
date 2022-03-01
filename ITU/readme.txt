Autoři
    Jakub Komárek xkomar33@stud.fit.vutbr.cz 
    Matušík Adrián xmatus35@stud.fit.vutbr.cz 
    Backa Marián xbacka01@stud.fit.vutbr.cz
 
Struktura projektu:
    app - umístění pro presentry,controlery,šablony
    vendor - knihovny frameworku
    www - css, js, naja, img
    sql - script pro incializaci databáze

Softwarové požadavky:
    PHP > 7.3.X
    Apache2 > 2.2.X
    Mysq > 8.X.X
    Ubuntu > 18.X či jiný linux

Konfigurace databáze:
    Přihlásit se do databáze - Adminer, PhpMyAdmin
    Provést import ze souboru sql/import.sql

Instalace:
    Překopírovat obsah adresáře do /var/www/ (umístění pro apache2 - může se na vaší stanici lišit).
    V souboru app/config/local.neon zeditovat přihlášovací údaje k databázy.
    Správně nakonfigurovat Apache2. Na hostigu obvykle není potřeba