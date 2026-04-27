shader_type canvas_item;

uniform float intensity : hint_range(0, 1);
const vec2 center = vec2(0.5);
uniform float radius : hint_range(0., 0.5) = 0.25;
uniform float radius_i : hint_range(0., 0.5) = 0.25;
uniform vec2 high_center;
uniform vec3 main_col : source_color;
uniform vec3 sub_color : source_color;
uniform sampler2D noise : repeat_enable;

void vertex(){
	VERTEX += VERTEX * sin(TIME) * .1;
}

void fragment() {
	/// main shape
	COLOR.rgb = vec3(1.);
	float circle_main = step(distance(UV, center), radius);
	float circle_inner = smoothstep(radius_i, 1, distance(UV, center));
	float main_shape = circle_main * circle_inner;
	
	// hilight shape
	float hilight = (1. - distance(high_center, UV)) * main_shape;
	hilight *=  sin(TIME);
	
	//colors
	vec3 colors = main_shape * main_col + hilight * sub_color;
	colors *= vec3(3);
	
	//texture
	float texture_alpha = texture(noise, UV+ vec2(TIME * 0.3, TIME * 0.1)).x;
	
	COLOR.a = hilight + main_shape;
	COLOR.a *= intensity * texture_alpha;
	COLOR.rgb = colors;
}
