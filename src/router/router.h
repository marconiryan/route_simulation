/**
 * @file router.h
 * @brief Manages the configuration and retrieval of router information.
 * 
 * This header defines the `Router` structure and the functionality
 * for reading router configurations, clearing allocated resources, and
 * retrieving information about specific routers by their IDs.
 */

#ifndef ROUTER_H
#define ROUTER_H

/**
 * @brief The ID of the current server.
 * 
 * This global variable represents the unique identifier of the server instance.
 * It is used to differentiate this server from other routers in the system.
 */
extern int SERVER_ID;

/**
 * @struct Router
 * @brief Represents a network router.
 */
typedef struct {
    int id; /**< Unique identifier of the router. */
    char ip[16]; /**< IP address of the router (e.g., "192.168.1.1"). */
    int port; /**< Port number associated with the router. */
} Router;

/**
 * @brief Reads and parses the router configuration file.
 * 
 * This function reads router information from a configuration file and populates the
 * global router structures. The router associated with `SERVER_ID` is stored separately,
 * while the other routers are added to a queue for further processing.
 * 
 * @note The path of the configuration file is defined as `../config/roteador.config`.
 * 
 * @warning If the configuration file cannot be opened or parsed, appropriate error
 * messages will be printed to stderr.
 */
void read_router_config();

/**
 * @brief Frees all resources allocated for storing router information.
 * 
 * This function clears the allocated memory for the global router variables
 * and the queue of other routers.
 * 
 * After calling this function, the global `SERVER_ROUTER` and `Routers` structures
 * will be set to `NULL`.
 */
void clear_router_config();

/**
 * @brief Retrieves a router by its ID.
 * 
 * Searches through the global list of routers to find a router with the
 * specified ID.
 * 
 * @param id The unique identifier of the router to be retrieved.
 * @return A pointer to the `Router` object if found, or `NULL` if no router
 * with the specified ID exists.
 */
Router *get_router_by_id(int id);

#endif // ROUTER_H
