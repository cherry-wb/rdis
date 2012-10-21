#ifndef rdgwindow_HEADER
#define rdgwindow_HEADER

#include <gtk/gtk.h>
#include <glib.h>

#include "graph.h"
#include "gui.h"
#include "rdgraph.h"
#include "tree.h"

#define RDGWINDOW_MAX_DEFAULT_WIDTH  880
#define RDGWINDOW_MAX_DEFAULT_HEIGHT 600

#define RDGWINDOW_NODE_COLOR_SELECT 1.0, 0.9, 0.9

struct _rdgwindow {
    GtkWidget         * window;
    GtkWidget         * scrolledWindow;
    GtkWidget         * imageEventBox;
    GtkWidget         * image;

    struct _gui       * gui;

    uint64_t            top_index;
    struct _rdg_graph * rdg_graph;

    struct _graph     * currently_displayed_graph;

    double image_drag_x;
    double image_drag_y;

    uint64_t 	   selected_node;
    struct _list * node_colors;
};



struct _rdgwindow * rdgwindow_create (struct _gui * gui, uint64_t top_index);
void                rdgwindow_delete (struct _rdgwindow * rdgwindow);
GtkWidget *         rdgwindow_window (struct _rdgwindow * rdgwindow);


// redraws the rdg_graph
void rdgwindow_image_update (struct _rdgwindow * rdgwindow);
// recreates the currently_displayed_graph from gui->graph,
// recreates the rdg_graph from the currently_displayed_graph,
// and redraws the graph
void rdgwindow_graph_update (struct _rdgwindow * rdgwindow);

gboolean rdgwindow_image_motion_notify_event (GtkWidget * widget,
                                              GdkEventMotion * event,
                                              struct _rdgwindow * rdgwindow);
gboolean rdgwindow_image_button_press_event  (GtkWidget * widget,
                                              GdkEventButton * event,
                                              struct _rdgwindow * inswindow);

// resets colors in node_colors, then recreates based of selected_node
void rdgwindow_color_node (struct _rdgwindow * rdgwindow);

#endif