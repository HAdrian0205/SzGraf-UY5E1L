#include <stdio.h>
#include <stdlib.h>

typedef struct Brick{
	double ha;
	double hb;
	double hc;
} Brick;

Brick set_size();
double calc_volume(Brick hosszak);
double calc_surface(Brick hosszak);

int main() {
    Brick x;
    x = set_size();
	double volume = calc_volume(x);
	double surface = calc_surface(x);

	printf("Volume: %.2lf\n", volume);
	printf("Surface: %.2lf\n", surface);
    checkIfHasSquare(x);
	return 0;
}

Brick set_size() {
	Brick hosszak;
	int check = 0;

	do{
        if(check > 0){
            printf("Wrong values!\n");
        }
        printf("Enter the first length:\n");
        scanf("%lf", &hosszak.ha);
        printf("Enter the second length:\n");
        scanf("%lf", &hosszak.hb);
        printf("Enter the third length:\n");
        scanf("%lf", &hosszak.hc);
        check++;
	}while((hosszak.ha < 0) || (hosszak.hb < 0) || (hosszak.hc < 0));

	return hosszak;
}

double calc_volume(Brick hosszak){
    double volume = hosszak.ha*hosszak.hb*hosszak.hc;
    return volume;
}

double calc_surface(Brick hosszak){
    double surface = 2*(hosszak.ha*hosszak.hb+hosszak.hb*hosszak.hc+hosszak.hc*hosszak.ha);
    return surface;
}

void checkIfHasSquare(Brick hosszak){
    int checker = 0;

    if(hosszak.ha == hosszak.hb || hosszak.ha == hosszak.hc || hosszak.hb == hosszak.hc) {
       checker = 1;
    }

    if(!checker){
        printf("The rectangle doesn't have square(s) in it.");
    } else {
        printf("The rectangle does have square(s) in it.");
    }
}
