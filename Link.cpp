/*
 * Link.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <Link.h>

Link::Link() {
	// TODO Auto-generated constructor stub

}

void Link::addIndex(int index){
	linkIndex =  index;
}
void Link::addDH(double* DH){
	for(int i = 0; i < 4; i++){
		DHParameters[i] =DH[i];
	}

}
void Link::addHardwareID(int ID){
	hardwareID = ID;
}
