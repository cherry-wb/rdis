#ifndef rdis_HEADER
#define rdis_HEADER

#include "graph.h"
#include "loader.h"
#include "map.h"
#include "object.h"
#include "rdis_lua.h"
#include "tree.h"

#define RDIS_CALLBACK(XX) ((void (*) (void *)) XX)

struct _rdis_callback {
    const struct _object * object;
    uint64_t  identifier;
    void   (* callback) (void *);
    void    * data;
};

struct _rdis {
    const struct _object * object;

    struct _rdis_lua * rdis_lua;

    uint64_t           callback_counter;
    struct _map      * callbacks;

    void *           * console_data;
    void            (* console_callback) (void *, const char * string);

    _loader          * loader;
    struct _graph    * graph;
    struct _map      * labels;
    struct _tree     * function_tree;
    struct _map      * memory_map;
};

// rdis will assume control of the loader, and rdis will delete the loader
// when rdis itself is deleted
struct _rdis * rdis_create      (_loader * loader);
void           rdis_delete      (struct _rdis * rdis);
json_t *       rdis_serialize   (struct _rdis * rdis);
struct _rdis * rdis_deserialize (json_t * json);

void rdis_set_console (struct _rdis * rdis,
                       void (* console_callback) (void *, const char *),
                       void * console_data);
void rdis_console     (struct _rdis * rdis, const char * string);

// creates a user function based on the bytes found at address,
// updates graph, labels and function_tree appropriately
// and then calls callbacks
int rdis_user_function (struct _rdis * rdis, uint64_t address);

// returns callback identifier so callback can be removed later
uint64_t rdis_add_callback    (struct _rdis * rdis,
                               void (* callback) (void *),
                               void * data);
void     rdis_remove_callback (struct _rdis * rdis, uint64_t identifier);
void     rdis_callback        (struct _rdis * rdis);

struct _rdis_callback * rdis_callback_create (void (* callback) (void *),
                                              void * data);
void                    rdis_callback_delete (struct _rdis_callback * rc);
struct _rdis_callback * rdis_callback_copy   (struct _rdis_callback * rc);
int                     rdis_callback_cmp    (struct _rdis_callback * lhs,
                                              struct _rdis_callback * rhs);

#endif