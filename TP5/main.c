#include "tp5.h"

#define HASH_TABLE_SIZE 1000
#define PASSENGER_LIST_SIZE 100000

int main(int argc, char *argv[]) {
    const char *filename = "data.csv";
    // Simple hash table
    {
        passenger_t *passenger_list[PASSENGER_LIST_SIZE];
        passenger_t *hash_table[HASH_TABLE_SIZE] = {NULL};
        read_file(filename, passenger_list, hash_table, HASH_TABLE_SIZE, simple_hash_table);
        write_file("output_simple_hash.csv", hash_table, HASH_TABLE_SIZE);
    }

    // Linear probing hash table
    {
        passenger_t *passenger_list[PASSENGER_LIST_SIZE];
        passenger_t *hash_table[HASH_TABLE_SIZE] = {NULL};
        read_file(filename, passenger_list, hash_table, HASH_TABLE_SIZE, linear_probing);
        write_file("output_linear_probing.csv", hash_table, HASH_TABLE_SIZE);
    }

    // Quadratic probing hash table
    {
        passenger_t *passenger_list[PASSENGER_LIST_SIZE];
        passenger_t *hash_table[HASH_TABLE_SIZE] = {NULL};
        read_file(filename, passenger_list, hash_table, HASH_TABLE_SIZE, quadratic_probing);
        write_file("output_quadratic_probing.csv", hash_table, HASH_TABLE_SIZE);
    }

    // Double hashing
    {
        passenger_t *passenger_list[PASSENGER_LIST_SIZE];
        passenger_t *hash_table[HASH_TABLE_SIZE] = {NULL};
        read_file(filename, passenger_list, hash_table, HASH_TABLE_SIZE, double_hashing);
        write_file("output_double_hashing.csv", hash_table, HASH_TABLE_SIZE);
    }
}