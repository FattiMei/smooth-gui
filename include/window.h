#ifndef __WINDOW_H__
#define __WINDOW_H__


int  window_init(const char *title, int width, int height);
int  window_init_with_hints(const char *title, int width, int height);
void window_set_callbacks();
int  window_should_close();
void window_swap_buffers();
void window_poll_events();
void window_close();


#endif