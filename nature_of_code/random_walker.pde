Walker w;

void setup() {
	size(640, 360);
	background(255);

	w = new Walker();
}

void draw() {
	// see a trail of random walk across the window
	w.step();
	w.display();
}

class Walker {

	public Walker() {
		x = width/2;
		y = height/2;
	}

	void step() {
		int choice = int(random(4));
		switch( choice )
		{
			case 0:
				x++;
				break;
			case 1:
				x--;
				break;
			case 2:
				y++;
				break;
			default:
				y--;
		}
	}

	void display() {
		stroke(0);
		point(x,y);
	}
}
