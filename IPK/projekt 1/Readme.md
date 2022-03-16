# Server v jazyku C komunikujúci prostredníctvom protokolu HTTP

## Autor : Adrián Matušík

### Použitie

Server dokáže užívateľovi poskytnúť:
* získanie doménového mena
* získanie informácí o CPU
* aktuálna záťaž CPU

### Spustenie

1. Stiahnite a extrahujte zazipovanú aplikáciu
2. V adresáry ju preložte pomocou:
```
$ make
```
3. Spustite aplikáciu na porte, na ktorom bude naslúchať požiadavkom:
```
$ ./hinfosvc <číslo portu>
```
### Použitie

```
$ GET http://localhost:<číslo portu>/hostname
$ GET http://localhost:<číslo portu>/cpu-name
$ GET http://localhost:<číslo portu>/load
```
V prípade, že by Vám príkaz "GET" nefungoval, použite príkaz "curl":
```
$ curl http://localhost:<číslo portu>/hostname
$ curl http://localhost:<číslo portu>/cpu-name
$ curl http://localhost:<číslo portu>/load
```