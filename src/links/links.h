/**
 * @file links.h
 * @brief Handles the configuration and operations for network links.
 * 
 * This header provides the interface to manage network links between nodes.
 * It allows reading links from a configuration file, retrieving neighbor information,
 * and performing various link-related queries.
 */

#ifndef LINKS_H
#define LINKS_H

#include <stdbool.h>

/**
 * @struct Link
 * @brief Represents a connection between two nodes in the network.
 * 
 * The `Link` struct stores the source node (`from`), destination node (`to`),
 * and the cost associated with the connection.
 */
typedef struct {
    int from; /**< ID of the source node. */
    int to; /**< ID of the destination node. */
    int cost; /**< Cost of the connection between nodes. */
} Link;

/**
 * @brief Reads network links from a configuration file.
 * 
 * Loads the link data from a configuration file into memory, creating
 * a queue of `Link` objects that represent the network topology.
 * 
 * @note The file path is defined as a constant (`../config/enlaces.config`).
 */
void read_links_config();

/**
 * @brief Clears all stored network links and frees resources.
 * 
 * Releases the memory associated with the queue of links and
 * resets the internal state.
 */
void clear_links_config();

/**
 * @brief Checks if a node has any neighbors.
 * 
 * Determines whether the given node (`id`) is a source for at least
 * one connection in the network.
 * 
 * @param id The ID of the node to check.
 * @return `true` if the node has at least one neighbor, `false` otherwise.
 */
bool has_neighbor(int id);

/**
 * @brief Counts the number of neighbors for a given node.
 * 
 * Calculates how many outgoing connections exist for the given node (`id`).
 * 
 * @param id The ID of the node whose neighbors are to be counted.
 * @return The number of neighbors the given node has.
 */
int count_neighbors(int id);

/**
 * @brief Retrieves all neighbors of a given node.
 * 
 * Finds all the links originating from the specified node (`id`) and
 * returns them as an array of `Link` objects.
 * 
 * @param id The ID of the source node.
 * @return A dynamically allocated array of `Link` objects, or `NULL`
 * if the allocation fails. The caller is responsible for freeing the memory.
 */
Link *get_neighbors_by_id(int id);

/**
 * @brief Retrieves the first link originating from a specific node.
 * 
 * Searches for the first outgoing connection starting from the specified node (`id`).
 * 
 * @param id The ID of the source node.
 * @return A pointer to the `Link` object, or `NULL` if no match is found.
 */
Link *get_link_by_id(int id);

/**
 * @brief Checks if one node is a direct neighbor of another.
 * 
 * Determines whether there is a direct connection from `id_from` to `id_to`.
 * 
 * @param id_from The source node's ID.
 * @param id_to The destination node's ID.
 * @return `true` if a direct connection exists, `false` otherwise.
 */
bool is_neighbor(int id_from, int id_to);

#endif // LINKS_H
