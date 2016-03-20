Walker w_int;
Walker w_float;
Walker w_down_right;

void setup() {
	size(640, 360);
	background(255);

	w_int = new Walker(color(0, 0, 0), Walker.INT_WALK);
	w_float = new Walker(color(255, 0, 0), Walker.FLOAT_WALK);
	w_down_right = new Walker(color(0, 255, 0), Walker.DOWN_RIGHT_WALK);
}

void draw() {
	// see a trail of random walk across the window
	w_int.step();
	w_int.display();
	w_float.step();
	w_float.display();
	w_down_right.step();
	w_down_right.display();
}

class Walker {

	float x;
	float y;
	color c_stroke;
	int walk_type;

	static int INT_WALK = 0;
	static int FLOAT_WALK = 1;
	static int DOWN_RIGHT_WALK = 1;

	public Walker(color c_stroke, int walk_type) {
		this.x = width / 2.0;
		this.y = height / 2.0;
		this.walk_type = walk_type;
		this.c_stroke = c_stroke;
	}

	void step() {
		float stepx;
		float stepy;
		switch (walk_type)
		{
			case INT_WALK:
				stepx = int(random(3)) - 1; //yields -1, 0, or 1
				stepy = int(random(3)) - 1;
				break;
			case FLOAT_WALK:
				stepx = random(-1, 1);
				stepy = random(-1, 1);
				break;
			case DOWN_RIGHT_WALK:
				// higher probability of >= 1
				stepx = int(random(4)) - 1;
				if ( stepx > 1 ) {
					stepx = 1;
				}
				// higher probability of <= -1
				stepy = int(random(4)) - 2;
				if ( stepy < -1 ) {
					stepy = -1;
				}
				break;

		}
		x += stepx;
		y += stepy;
	}

	void display() {
		stroke(c_stroke);
		point(x,y);
	}
}
