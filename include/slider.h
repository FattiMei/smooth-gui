#ifndef __SLIDER_H__
#define __SLIDER_H__


struct Slider {
	// dimensioni del rettangolo che è lo slider
	unsigned int x, y, w, h;

	// in [0, 1]
	float state;
};


void slider_init();
void slider_update(struct Slider *S, float xpos);
void slider_render(struct Slider *S);


#endif
