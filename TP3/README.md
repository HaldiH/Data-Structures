# Structures de Données - TP3

## Exercice 1

```plantuml
@startuml
class passenger_t {
    - id : uint
    - firstName : string
    - lastName : string
    - age : uint
    - seatNumber : uint
}

class uint

class "unsigned int" as unsigned_int <<primitive>>

hide uint circle
hide uint members
hide unsigned_int circle
hide unsigned_int members

uint ..|> unsigned_int

passenger_t --> uint

class forward_iterator_t {
    - next : forward_iterator_t
    - data
    + factory()
    + destructor()
    + data() : data
}

class forward_list_t {
    - begin : forward_iterator_t
    - end : forward_iterator_t
    -- Constructors and destructors --
    + factory()
    + destructor()
    -- Element access --
    + front() : data
    + back() : data
    + at(pos : int) : data
    -- Iterators --
    + begin() : forward_iterator_t
    + end() : forward_iterator_t
    -- Capacity --
    + empty() : bool
    -- Modifiers --
    + push_front(data)
    + push_back(data)
    + insert(pos : int, data)
    + pop(pos : int) : data
    + pop_front() : data
    + pop_back() : data
    + erase_after(first : forward_iterator_t,\n\
                  last : forward_iterator_t)
    -- Operations --
    + swap()
}

forward_list_t ..|> forward_iterator_t

@enduml
```

Pour compiler le code, il faut d'abord compiler les bibliothèques que l'on va utiliser aussi dans l'exercice suivant, puis l'exécutable principal:

```shell
gcc -Iinclude -c -fpic src/forward_list.c src/ex1.c
gcc -Iinclude -o ex1 src/main1.c ex1.o forward_list.o
```

## Exercice 2

Pour compiler le code, il faut d'abord compiler la bibliothèque `map`, puis compiler l'exécutable un utilisant les bibliothèques compilées dans le dernier exercice:

```shell
gcc -Iinclude -c -fpic src/map.c
gcc -Iinclude -o ex2 src/main2.c src/ex2.c src/map.c ex1.o forward_list.o
```
