# TME2 : réponses et traces

Un titre par question. Sous chaque titre : la réponse si la question en demande une, et la trace de l'exécution
de votre code, collée telle quelle entre triples backquotes. On peut couper le milieu d'une trace longue, on garde
les dernières lignes, avec le temps d'exécution.

## Machine de mesure

Collez ici le bloc produit par `./machine-info.sh`, puis complétez le contexte de mesure.

## Question 1

```text
defrance@Carbone:~/Codium/PSCR-TME/TME2$ ./machine-info.sh 
## Machine de mesure
Date : 2026-09-30 14:18 UTC
Système : Linux 7.0.0-31-generic x86_64
Distribution : Ubuntu 26.04.1 LTS
CPU logiques (système) : 8
CPU : Intel(R) Core(TM) i5-8250U CPU @ 1.60GHz
Threads par cœur : 2
Cœurs par socket : 4
Sockets : 1
Fréquence maximale annoncée (MHz) : 3400.0000
CPU logiques disponibles pour ce processus : 8
RAM visible : 15.0 GiB
Compilateur par défaut : c++ (Ubuntu 15.2.0-16ubuntu1) 15.2.0
```


Il y a un total de de 565527 mots :
```text
Found a total of 565527 words.
Total runtime (wall clock) : 398 ms
```

## Question 2

| Test               | Interprétation                                                                                  | Temps  | Traces |
|--------------------|-------------------------------------------------------------------------------------------------|--------|--|
| `Debug`            | Le debug semble et très lent étant donné que le code est supervisé pour détecter toutes erreurs | 2119ms | Found a total of 565527 words. Total runtime (wall clock) : 2216 ms |
| `Release`          | En mode release, on a une vitesse ~8 fois supérieur !                                           | 292ms  | Found a total of 565527 words. Total runtime (wall clock) : 294 ms |
| `Debug NoPrints`   | On constate un léger gain de temps ~13%                                                         | 1856ms | Found a total of 565527 words. Total runtime (wall clock) : 2067 ms |
| `Release NoPrints` | On constate un léger gain de temps ~29%                                                         | 210ms  | Found a total of 565527 words. Total runtime (wall clock) : 262 ms |



## Question 3

Le programme arrive en ~ 2 secondes à parcourir les 0.5 M de mots.
Et à identifier les mots uniques.

```text
Found 20332 unique words.
Total runtime (wall clock) : 2113 ms
```


## Question 4



```text
Printing words and their frequency 
war :298
peace :114
toto :0
Total runtime (wall clock) : 2142 ms
```




## Question 5

## Question 6

## Question 7

## Question 8

## Question 9

## Question 10 (bonus)
