#include "slider.h"


static GLint slider_program;
static GLint u_state;
static GLint u_sliderPosition;
static GLint u_sliderDimension;


GLbyte slider_vertex_shader_src[] = R"(
	void main() {
		vec2 uv = vec2(
			gl_VertexID & 1,
			(gl_VertexID >> 1) & 1
		);

		gl_Position = vec4(uv * 2.0 - 1.0, 0.0, 1.0);
	}
)";


GLbyte slider_fragment_shader_src[] = R"(
	precision mediump float;

	uniform vec2 sliderPosition;
	uniform vec2 sliderDimension;
	uniform float state;

	#define BACKGROUND_COLOR vec4(0.0, 0.0, 0.0, 1.0)
	#define FOREGROUND_COLOR vec4(0.5, 0.2, 0.6, 1.0)

	void main() {
		float cutoff = sliderPosition.x + state * sliderDimension.x;

		if (gl_FragCoord.x < cutoff) {
			gl_FragColor = FOREGROUND_COLOR;
		}
		else {
			gl_FragColor = BACKGROUND_COLOR;
		}
	}
)";


void slider_update(struct Slider *S, float xpos) {
	float newstate = (xpos - S->x) / (float) S->w;

	if (newstate < 0.0f) newstate = 0.0f;
	else if (newstate > 1.0f) newstate = 1.0f;

	S->state = newstate;
}


void slider_render(struct Slider *S) {
	glViewport(S->x, S->y, S->x + S->w, S->y + S->h);

	glUseProgram(slider_program);

	glUniform1f(u_state, S->state);
	glUniform2f(u_sliderPosition, S->x, S->y);
	glUniform2f(u_sliderDimension, S->w, S->h);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
