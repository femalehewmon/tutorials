int[] randomCounts;
boolean increaseCount = true;
int inceaseIndex = 0;

void setup() {
	size(640, 240);
	randomCounts = new int[20];
}

void draw() {
	background(255);

	// randomly increase value in count bin
	if (increaseCount)
	{
		increaseIndex = int(random(randomCounts.length));
		randomCounts[increaseIndex]++;
		if (randomCounts[increaseIndex] >= height)
		{
			increaseCount = false;
		}
	}

	// plot distribution
	int w = width/randomCounts.length;
	for (int x = 0; x < randomCounts.length; x++) {
		// highlight bar with increased count on this draw
		if (x == increaseIndex)
		{
			stroke(0);
			fill(330, 99, 42);
		}
		else
		{
			stroke(0);
			fill(175);
		}
		rect(x*w, height-randomCounts[x], w-1, randomCounts[x]);
	}
}
