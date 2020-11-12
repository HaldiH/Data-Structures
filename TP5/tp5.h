//
// Created by hugo on 5/4/20.
//

#pragma once
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    uint id, age, seat_number;
    char *first_name, *last_name;
} passenger_t;

passenger_t *passenger_construct(uint id, const char *first_name, const char *last_name, uint age, uint seat_number);
void passenger_destroy(passenger_t *passenger);

int read_file(const char *filename, passenger_t **passenger_list, passenger_t **hash_table, uint hash_table_size, int (*callback)(passenger_t **, uint, passenger_t *));
int write_file(const char *filename, passenger_t **hash_table, uint hash_table_size);
uint codes(char *word);
uint codec(char c);
uint hashs(char *word, int m);
int simple_hash_table(passenger_t **hash_table, uint hash_table_size, passenger_t *);
int linear_probing(passenger_t **hash_table, uint mod, passenger_t *);
int quadratic_probing(passenger_t **hash_table, uint mod, passenger_t *);
int double_hashing(passenger_t **hash_table, uint mod, passenger_t *);
size_t parse_line(char **dest, const char *line, char separator, size_t cell_size);

/*
 * =================
 * || Definitions ||
 * =================
*/

passenger_t *passenger_construct(uint id, const char *first_name, const char *last_name, uint age, uint seat_number) {
    passenger_t *p = malloc(sizeof(passenger_t));
    p->id = id;
    p->first_name = malloc(strlen(first_name) * sizeof(char));
    strcpy(p->first_name, first_name);
    p->last_name = malloc(strlen(last_name) * sizeof(char));
    strcpy(p->last_name, last_name);
    p->age = age;
    p->seat_number = seat_number;
    return p;
}

void passenger_destroy(passenger_t *passenger) {
    free(passenger->first_name);
    free(passenger->last_name);
    free(passenger);
}

uint codec(char c) {
    if (c >= 'a' && c <= 'z')
        return c - 'a' + 1;
    else if (c >= 'A' && c <= 'Z')
        return c - 'A' + 1;
    return 0;
}

uint codes(char *word) {
    u_int64_t coded = 0;
    for (uint i = 0; i < strlen(word); i++) {
        /*uint char_coded = codec(word[i]);
        uint padding = floor(log10(char_coded)) + 1;
        coded = coded * pow(10, padding) + char_coded;*/

        coded += codec(word[i]) * pow(26, i);
    }
    return coded;
}

uint hashs(char *word, int m) {
    return codes(word) % m;
}

uint hashs2(char *word, int m) {
    uint hash = codes(word) % m;
    // hash must be prime with m
    // so if hash % m == 0 and m > 1, (hash % m + 1 % m) % m = (0 + 1) % m = 1
    // hash % m = 0 => (hash + 1) % m != 0
    return hash == 0 ? hash + 1 : hash;
}

size_t parse_line(char **dest, const char *line, const char separator, size_t cell_size) {
    size_t j = 0, k = 0;
    char cell[cell_size];
    for (size_t i = 0; line[i] != '\0'; i++) {
        if (line[i] == separator) {
            if (j != 0) {
                dest[k] = malloc(j * sizeof(char));
                strcpy(dest[k++], cell);
                memset(cell, 0, sizeof(cell));
            }
            j = 0;
            continue;
        }
        cell[j++] = line[i];
    }
    return k;
}

int simple_hash_table(passenger_t **hash_table, const uint hash_table_size, passenger_t *passenger) {
    uint hash = hashs(passenger->first_name, hash_table_size);
    if (hash_table[hash])
        printf("Collision\n");
    else {
        hash_table[hash] = passenger;
        //        printf("%u\n", hash);
    }
    return 0;
}

int linear_probing(passenger_t **hash_table, uint mod, passenger_t *passenger) {
    uint hash = hashs(passenger->first_name, mod);
    uint i = 0;
    uint probe;
    while (hash_table[(probe = (hash + i++) % mod)]) {
        printf("Collision. Probing of %u\n", i);
        if (i >= mod) {
            printf("Table is full\n");
            return 1;
        }
    }
    hash_table[probe] = passenger;
    return 0;
}

int quadratic_probing(passenger_t **hash_table, uint mod, passenger_t *passenger) {
    uint hash = hashs(passenger->first_name, mod);
    uint i = 0;
    uint probe;
    const int a1 = 10, a2 = 2;
    while (hash_table[(probe = (int) floor(hash + a1 * i + a2 * pow(i, 2)) % mod)]) {
        i++;
        printf("Collision. Probing of %u\n", i);
        if (i >= mod) {
            printf("Table is full\n");
            return 1;
        }
    }
    hash_table[probe] = passenger;
    return 0;
}

int double_hashing(passenger_t **hash_table, uint mod, passenger_t *passenger) {
    uint i = 0;
    uint probe;
    while (hash_table[(probe = (hashs(passenger->first_name, mod) + i * hashs2(passenger->first_name, mod)) % mod)]) {
        printf("Collision. Probing of %u\n", ++i);
        if (i >= mod) {
            printf("Cannot insert value\n");
            return 0;
        }
    }
    hash_table[probe] = passenger;
    return 0;
}

int read_file(const char *filename, passenger_t **passenger_list, passenger_t **hash_table, const uint hash_table_size, int (*callback)(passenger_t **, uint, passenger_t *)) {
    FILE *fp;
    if (!(fp = fopen(filename, "ro"))) {
        perror(filename);
        return EXIT_FAILURE;
    }

    char first_name[10], last_name[10], id[10], age[10], seat_number[10];
    bool bColumnName = true;
    for (uint i = 0; fscanf(fp, "%s %s %s %s %s", id, first_name, last_name, age, seat_number) != EOF; i++) {
        if (bColumnName) {
            i--;
            bColumnName = false;
            continue;
        }
        if (i >= hash_table_size)
            break;
        passenger_list[i] = passenger_construct(atoi(id), first_name, last_name, atoi(age), atoi(seat_number));
        if (callback(hash_table, hash_table_size, passenger_list[i]) != 0)
            break;
        printf("Added passenger %u\n", passenger_list[i]->seat_number);
    }
    fclose(fp);
    return EXIT_SUCCESS;
}

uint int_length(int n) {
    if (n == 0)
        return 1;
    return floor(log10(n)) + 1;
}

int write_file(const char *filename, passenger_t **hash_table, uint hash_table_size) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror(filename);
        return 1;
    }

    for (uint i = 0; i < hash_table_size; i++) {
        passenger_t *p = hash_table[i];
        if (!p)
            continue;
        // Index,id,first_name,last_name,age,seat_number
        char line[int_length(i) + int_length(p->id) + strlen(p->first_name) + strlen(p->last_name) + int_length(p->age) + int_length(p->seat_number) + 6];// 6 comma + 1 LF
        sprintf(line, "%i,%i,%s,%s,%i,%i\n", i, p->id, p->first_name, p->last_name, p->age, p->seat_number);
        fputs(line, fp);
    }

    return 0;
}
