## Machine de mesure

Container Linux Ubuntu

```text
Date : 2026-10-28 21:10 UTC
Système : Linux 6.18.54.1-microsoft-standard-WSL2 x86_64
Distribution : Ubuntu 24.04.3 LTS
CPU logiques (système) : 16
CPU : AMD Ryzen 7 8700F 8-Core Processor
Threads par cœur : 2
Cœurs par socket : 8
Sockets : 1
Fréquence maximale : non exposée par le système
CPU logiques disponibles pour ce processus : 16
RAM visible : 15.5 GiB
Compilateur par défaut : c++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0
```

À compléter : Debug/Release, machine native/VM/WSL/conteneur, charge concurrente.
La fréquence réelle varie avec la charge, le turbo et la température.

Debug : 7531 ms
Release : 6834 ms

## Question 1

```text
Preparing to parse ../WarAndPeace.txt (mode=freqstd N=4), containing 3235342 bytes
Total runtime (wall clock) : 6189 ms

Mode=partition threads=1 essai=1
Preparing to parse ../WarAndPeace.txt (mode=partition N=1), containing 3235342 bytes
Total runtime (wall clock) : 6385 ms
All files are identical

Mode=partition threads=1 essai=2
Preparing to parse ../WarAndPeace.txt (mode=partition N=1), containing 3235342 bytes
Total runtime (wall clock) : 6508 ms
All files are identical

Mode=partition threads=1 essai=3
Preparing to parse ../WarAndPeace.txt (mode=partition N=1), containing 3235342 bytes
Total runtime (wall clock) : 6325 ms
All files are identical

Mode=partition threads=4 essai=1
Preparing to parse ../WarAndPeace.txt (mode=partition N=4), containing 3235342 bytes
Total runtime (wall clock) : 6273 ms
All files are identical

Mode=partition threads=4 essai=2
Preparing to parse ../WarAndPeace.txt (mode=partition N=4), containing 3235342 bytes
Total runtime (wall clock) : 6334 ms
All files are identical

Mode=partition threads=4 essai=3
Preparing to parse ../WarAndPeace.txt (mode=partition N=4), containing 3235342 bytes
Total runtime (wall clock) : 6419 ms
All files are identical

Mode=partition threads=8 essai=1
Preparing to parse ../WarAndPeace.txt (mode=partition N=8), containing 3235342 bytes
Total runtime (wall clock) : 6284 ms
All files are identical

Mode=partition threads=8 essai=2
Preparing to parse ../WarAndPeace.txt (mode=partition N=8), containing 3235342 bytes
Total runtime (wall clock) : 6332 ms
All files are identical

Mode=partition threads=8 essai=3
Preparing to parse ../WarAndPeace.txt (mode=partition N=8), containing 3235342 bytes
Total runtime (wall clock) : 6284 ms
All files are identical

Mode=partition threads=16 essai=1
Preparing to parse ../WarAndPeace.txt (mode=partition N=16), containing 3235342 bytes
Total runtime (wall clock) : 6319 ms
All files are identical

Mode=partition threads=16 essai=2
Preparing to parse ../WarAndPeace.txt (mode=partition N=16), containing 3235342 bytes
Total runtime (wall clock) : 6541 ms
All files are identical

Mode=partition threads=16 essai=3
Preparing to parse ../WarAndPeace.txt (mode=partition N=16), containing 3235342 bytes
Total runtime (wall clock) : 6518 ms
All files are identical

```

## Question 2

L'utilisation de **[&, i]** permet de capturer l'indice de boucle afin que chaque
thread traite sa propre plage. La boucle de join s'assure que tout les threads fusionnent
et ne deviennent qu'un à la fin du processuss. Elle attend que chaque thread est finis
son travail.

Decommenté cette ligne cause une erreur :
````text
Preparing to parse /IdeaProjects/PSCR-TME/TME3//WarAndPeace.txt (mode=mt_naive N=4), containing 3235342 bytes
terminate called without an active exception

Process finished with exit code 134 (interrupted by signal 6:SIGABRT)
````

```text
Preparing to parse /IdeaProjects/PSCR-TME/TME3//WarAndPeace.txt (mode=mt_naive N=4), containing 3235342 bytes
Total runtime (wall clock) : 6272 ms
```

## Question 3

L'ajout de atomic ne suffit pas, on a toujours une erreur.

```text
Preparing to parse /IdeaProjects/PSCR-TME/TME3//WarAndPeace.txt (mode=mt_atomic N=4), containing 3235342 bytes

Process finished with exit code 139 (interrupted by signal 11:SIGSEGV)
```

## Question 4

Oui, un mutex peut protéger le compteur total sans atomic également.

```text
Preparing to parse /IdeaProjects/PSCR-TME/TME3//WarAndPeace.txt (mode=mt_mutex N=4), containing 3235342 bytes
Total runtime (wall clock) : 6484 ms
```

## Question 5

Cette méthode donne à chaque Thread un espace unique de travaille en mémoire.
Evitant alors toute collision d'accès simultanée. Chaque threads effectue son calcul
dans son coin, la somme est faites dans le thread principal.

```text
Preparing to parse /IdeaProjects/PSCR-TME/TME3//WarAndPeace.txt (mode=mt_hashes N=4), containing 3235342 bytes
Total runtime (wall clock) : 6743 ms
```

## Question 6

Après avoir implémenté la solution, on voit une erreur.
Les fichiers différents.

```text
Preparing to parse ../WarAndPeace.txt (mode=freqstd N=4), containing 3235342 bytes
Total runtime (wall clock) : 6526 ms

Mode=mt_hnaive threads=1 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hnaive N=1), containing 3235342 bytes
Total runtime (wall clock) : 6693 ms
All files are identical

Mode=mt_hnaive threads=1 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hnaive N=1), containing 3235342 bytes
Total runtime (wall clock) : 6624 ms
All files are identical

Mode=mt_hnaive threads=1 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hnaive N=1), containing 3235342 bytes
Total runtime (wall clock) : 6560 ms
All files are identical

Mode=mt_hnaive threads=4 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hnaive N=4), containing 3235342 bytes
Total runtime (wall clock) : 6393 ms
Files freqstd.freq and mt_hnaive.freq differ
```

## Question 7

L'atomic seul ne suffit pas.
L'atomic résout seulement le prolbème des deux threads qui incrémentent le même mot déjà présent.
Mais l'insertion d'un nouveau mot n'est pas protégé.

```text
Preparing to parse ../WarAndPeace.txt (mode=freqstd N=4), containing 3235342 bytes
Total runtime (wall clock) : 6711 ms

Mode=mt_hatomic threads=1 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=1), containing 3235342 bytes
Total runtime (wall clock) : 6637 ms
All files are identical

Mode=mt_hatomic threads=1 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=1), containing 3235342 bytes
Total runtime (wall clock) : 6714 ms
All files are identical

Mode=mt_hatomic threads=1 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=1), containing 3235342 bytes
Total runtime (wall clock) : 6697 ms
All files are identical

Mode=mt_hatomic threads=4 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=4), containing 3235342 bytes
Total runtime (wall clock) : 6527 ms
All files are identical

Mode=mt_hatomic threads=4 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=4), containing 3235342 bytes
Total runtime (wall clock) : 6436 ms
All files are identical

Mode=mt_hatomic threads=4 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=4), containing 3235342 bytes
Total runtime (wall clock) : 6430 ms
All files are identical

Mode=mt_hatomic threads=8 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=8), containing 3235342 bytes
Total runtime (wall clock) : 6432 ms
All files are identical

Mode=mt_hatomic threads=8 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hatomic N=8), containing 3235342 bytes
Total runtime (wall clock) : 6388 ms
Files freqstd.freq and mt_hatomic.freq differ
```

## Question 8

Cette version avec mutex MT fonctionne bien.
On obtient des performances assez similaire au freq standard.

```text
Preparing to parse ../WarAndPeace.txt (mode=freqstd N=4), containing 3235342 bytes
Total runtime (wall clock) : 6511 ms

Mode=mt_hmutex threads=1 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=1), containing 3235342 bytes
Total runtime (wall clock) : 6569 ms
All files are identical

Mode=mt_hmutex threads=1 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=1), containing 3235342 bytes
Total runtime (wall clock) : 6589 ms
All files are identical

Mode=mt_hmutex threads=1 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=1), containing 3235342 bytes
Total runtime (wall clock) : 6559 ms
All files are identical

Mode=mt_hmutex threads=4 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=4), containing 3235342 bytes
Total runtime (wall clock) : 6505 ms
All files are identical

Mode=mt_hmutex threads=4 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=4), containing 3235342 bytes
Total runtime (wall clock) : 6433 ms
All files are identical

Mode=mt_hmutex threads=4 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=4), containing 3235342 bytes
Total runtime (wall clock) : 6406 ms
All files are identical

Mode=mt_hmutex threads=8 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=8), containing 3235342 bytes
Total runtime (wall clock) : 6556 ms
All files are identical

Mode=mt_hmutex threads=8 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=8), containing 3235342 bytes
Total runtime (wall clock) : 6604 ms
All files are identical

Mode=mt_hmutex threads=8 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=8), containing 3235342 bytes
Total runtime (wall clock) : 6460 ms
All files are identical

Mode=mt_hmutex threads=16 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=16), containing 3235342 bytes
Total runtime (wall clock) : 6478 ms
All files are identical

Mode=mt_hmutex threads=16 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=16), containing 3235342 bytes
Total runtime (wall clock) : 6511 ms
All files are identical

Mode=mt_hmutex threads=16 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hmutex N=16), containing 3235342 bytes
Total runtime (wall clock) : 6511 ms
All files are identical
```

## Question 9

Il n'est pas nécéssaire de cumuler les atomic et les mutex.
Les mutex assurent déjà la sécurité pour les incrémentations.

```text
Preparing to parse ../WarAndPeace.txt (mode=freqstd N=4), containing 3235342 bytes
Total runtime (wall clock) : 6517 ms

Mode=mt_hfine threads=1 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=1), containing 3235342 bytes
Total runtime (wall clock) : 6705 ms
All files are identical

Mode=mt_hfine threads=1 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=1), containing 3235342 bytes
Total runtime (wall clock) : 6761 ms
All files are identical

Mode=mt_hfine threads=1 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=1), containing 3235342 bytes
Total runtime (wall clock) : 6604 ms
All files are identical

Mode=mt_hfine threads=4 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=4), containing 3235342 bytes
Total runtime (wall clock) : 6470 ms
All files are identical

Mode=mt_hfine threads=4 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=4), containing 3235342 bytes
Total runtime (wall clock) : 6451 ms
All files are identical

Mode=mt_hfine threads=4 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=4), containing 3235342 bytes
Total runtime (wall clock) : 6451 ms
All files are identical

Mode=mt_hfine threads=8 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=8), containing 3235342 bytes
Total runtime (wall clock) : 6357 ms
All files are identical

Mode=mt_hfine threads=8 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=8), containing 3235342 bytes
Total runtime (wall clock) : 6320 ms
All files are identical

Mode=mt_hfine threads=8 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=8), containing 3235342 bytes
Total runtime (wall clock) : 6334 ms
All files are identical

Mode=mt_hfine threads=16 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=16), containing 3235342 bytes
Total runtime (wall clock) : 6367 ms
All files are identical

Mode=mt_hfine threads=16 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=16), containing 3235342 bytes
Total runtime (wall clock) : 6550 ms
All files are identical

Mode=mt_hfine threads=16 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_hfine N=16), containing 3235342 bytes
Total runtime (wall clock) : 6469 ms
All files are identical
```

## Question 10

Comme nous avons plus aucun compteurs, rien empêche deux threads d'incrémenter le mêmem mot.
Ce pourquoi l'atomic est nécéssaire.

```text
Preparing to parse ../WarAndPeace.txt (mode=freqstd N=4), containing 3235342 bytes
Total runtime (wall clock) : 6504 ms

Mode=mt_lf threads=1 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=1), containing 3235342 bytes
Total runtime (wall clock) : 6625 ms
All files are identical

Mode=mt_lf threads=1 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=1), containing 3235342 bytes
Total runtime (wall clock) : 6758 ms
All files are identical

Mode=mt_lf threads=1 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=1), containing 3235342 bytes
Total runtime (wall clock) : 6571 ms
All files are identical

Mode=mt_lf threads=4 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=4), containing 3235342 bytes
Total runtime (wall clock) : 6409 ms
All files are identical

Mode=mt_lf threads=4 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=4), containing 3235342 bytes
Total runtime (wall clock) : 6375 ms
All files are identical

Mode=mt_lf threads=4 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=4), containing 3235342 bytes
Total runtime (wall clock) : 6402 ms
All files are identical

Mode=mt_lf threads=8 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=8), containing 3235342 bytes
Total runtime (wall clock) : 6334 ms
All files are identical

Mode=mt_lf threads=8 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=8), containing 3235342 bytes
Total runtime (wall clock) : 6434 ms
All files are identical

Mode=mt_lf threads=8 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=8), containing 3235342 bytes
Total runtime (wall clock) : 6366 ms
All files are identical

Mode=mt_lf threads=16 essai=1
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=16), containing 3235342 bytes
Total runtime (wall clock) : 6365 ms
All files are identical

Mode=mt_lf threads=16 essai=2
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=16), containing 3235342 bytes
Total runtime (wall clock) : 6357 ms
All files are identical

Mode=mt_lf threads=16 essai=3
Preparing to parse ../WarAndPeace.txt (mode=mt_lf N=16), containing 3235342 bytes
Total runtime (wall clock) : 6346 ms
All files are identical
```

## Question 11

```text
Trace à compléter.
```
