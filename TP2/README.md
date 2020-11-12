# Structures de données - TP2 - Haldi Hugo

Pour ce TP j'ai réalisé une bibliothèque de conteneurs (liste chaînée, pile, file) documentés dans des fichiers annexes.

## Exercice 1

1. Pour cet exercice, une pile peut être utilisée car avant de dépiler la catégorie, il faudra que toutes les sous-catégories soient dépilées, et pour chaque sous-catégorie, toutes les tâches devront être dépilées.
2. Diagramme ci-dessous:

```plantuml
@startuml
start
while (catégories?) is (disponible)
    :Afficher catégorie;
    while (sous-catégories?) is (disponibles)
        :Afficher sous-catégorie;
        while (tâches) is (disponible)
            :Afficher tâche;
            if (tâche OK?) then (non)
                :marque sous-catégorie\npas ok;
            else (oui)
            endif
        endwhile
        if (marqueur OK?) then (oui)
            :pop(sous-catégorie);
        else (non)
            :recommencer avec la\nmême sous-catégorie;
        endif
    endwhile
endwhile
stop
```

3. Pour compiler le programme de cet exercice:

```shell
gcc -o Exercise_1 -Iinclude/ Exercise_1.c
```

## Exercice 2

1. La structure à utiliser est une file (queue).
2. Diagramme ci-dessous:

```plantuml
@startuml
start
:Choisir 2 nombres\nau hasard m et n;
if (Salle pleine?) then (oui)
    :Ne pas faire\nentrer des personnes;
else (non)
    :faire entrer m\npersonnes;
endif
if (Salle vide) then (oui)
    :Personne ne sort;
else (non)
    :Faire sortir n\npersonnes;
endif
stop
@enduml
```

3. Pour compiler le programme:

```shell
gcc -o Exercise_2 -Iinclude Exercise_2.c forward_list.c queue.c
```