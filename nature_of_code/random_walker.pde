Walker w_int;
Walker w_float;

void setup() {
	size(640, 360);
	background(255);

	w_int = new Walker(color(0, 0, 0), Walker.INT_WALK);
	w_float = new Walker(color(255, 0, 0), Walker.FLOAT_WALK);
}

void draw() {
	// see a trail of random walk across the window
	w_int.step();
	w_int.display();
	w_float.step();
	w_float.display();
}

class Walker {

	float x;
	float y;
	color c_stroke;
	int walk_type;

	static int INT_WALK = 0;
	static int FLOAT_WALK = 1;

	public Walker(color c_stroke, int walk_type) {
		this.x = width / 2.0;
		this.y = height / 2.0;
		this.walk_type = walk_type;
		this.c_stroke = c_stroke;
	}

	void step() {
		float stepx;
		float stepy;
		if (walk_type == INT_WALK)
		{
			stepx = int(random(3)) - 1; //yields -1, 0, or 1
			stepy = int(random(3)) - 1;
		} 
		else if (walk_type == FLOAT_WALK)
		{
			stepx = random(-1, 1);
			stepy = random(-1, 1);
		}
		x += stepx;
		y += stepy;
	}

	void display() {
		stroke(c_stroke);
		point(x,y);
	}
}
