#ifndef CG_OUTPUT_H
#define CG_OUTPUT_H

#include <wayland-server-core.h>
#include <wlr/types/wlr_output.h>
#include <wlr/types/wlr_output_damage.h>

#include "server.h"
#include "view.h"

struct cg_output {
	struct cg_server *server;
	struct wlr_output *wlr_output;
	struct wlr_output_damage *damage;
	struct wl_list link; // cg_server::outputs

	struct wl_listener mode;
	struct wl_listener transform;
	struct wl_listener destroy;
	struct wl_listener damage_frame;
	struct wl_listener damage_destroy;

	struct {
		struct wl_signal mode;
		struct wl_signal transform;
		struct wl_signal destroy;
	} events;
};

typedef void (*cg_surface_iterator_func_t)(struct cg_output *output, struct wlr_surface *surface, struct wlr_box *box,
					   void *user_data);

struct cg_output *output_init(struct cg_server *server, struct wlr_output *wlr_output, enum wl_output_transform output_transform);
void output_surface_for_each_surface(struct cg_output *output, struct wlr_surface *surface, double ox, double oy,
				     cg_surface_iterator_func_t iterator, void *user_data);
void output_view_for_each_popup(struct cg_output *output, struct cg_view *view, cg_surface_iterator_func_t iterator,
				void *user_data);
void output_drag_icons_for_each_surface(struct cg_output *output, struct wl_list *drag_icons,
					cg_surface_iterator_func_t iterator, void *user_data);
void output_damage_surface(struct cg_output *output, struct wlr_surface *surface, double lx, double ly, bool whole);
void output_set_window_title(struct cg_output *output, const char *title);

#endif
