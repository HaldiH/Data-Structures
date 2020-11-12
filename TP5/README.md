---
author: Hugo Haldi
date: 11 Mai 2020
title: 'Sctructures de Données - TP5'
---

## Compilation du code

Cette implémentation lit un fichier `data.csv` et sort 4 fichiers: `output_simple_hash.csv`, `output_linear_probing.csv`, `output_quadratic_probing.csv` et `output_double_hashing.csv`. Le fichier `main.c` est séparé en 4 parties, qui peuvent être commentées pour n'obtenir qu'un seul type de hachage.

Pour compiler le code :

``` {.shell}
gcc -o TP5 main.c -lm
```

## Réponses aux questions

a.  La fonction `codes(char *word)` permet de coder une chaîne de caractère en nombre. La fonction `hashs(char *word, int m)` permet d'obtenir un digest du mot avec un modulo.

b.  La fonction `simple_hash_table` lit un passager, calcule son digest avec `hashs` et essaie de le stocker à l'index digest dans une table. Si il y a déjà un passager stocké à cet index, on indique qu'il y a eu une collision mais on passe le passager. Lorsqu'on exécute cette méthode, le fichier `output_simple_hash.csv` permet de visionner la table de hachage.

c.  Pour le probing linéaire, on utilise la fonction `linear_probing`. On essaie d'insérer le passager à l'index $(\text{digest} + i) \mod m$, et si $i$ dépasse $m$, on arrête car la table est pleine. On peut visionner la table de hachage avec le fichier `output_linear_probing.csv`.

d.  La méthode `quadratic_probing` permet de générer un digest et de le stocker à l'index $\text{digest}$. Si il y a déjà un passager à cet index, on incrémente $i$ et on calcule le nouvel index avec : $i = (\text{digest}+a_1i+a_2i^2) \mod m$.

e.  La méthode `double_hashing` calule un index où stocker le passager dans la table avec deux fonctions de hash différentes de cette manière : $\text{index}=(\text{hash}_1(\text{mot})+i \cdot \text{hash}_2(\text{mot})) \mod m$. Si à cet index il y a déjà un passager, on incrémente $i$ jusqu'à qu'il n'y en ait plus.\
    $\text{hash}_2$ doit être premier avec $m$ car si $H_2 \mod m = 0$, alors $i\cdot H_2 \mod m = 0$.\
    Pour se faire, on incrémente $H_2$ de 1. En effet si m > 1 :\
    $H \mod m = 0 \implies (H \mod m + 1 \mod m) \mod m = (0 + 1) \mod m = 1$
