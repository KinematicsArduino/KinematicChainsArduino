/*
 * Limb.cpp
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#include <Limb.h>

Limb::Limb() {
	// TODO Auto-generated constructor stub

}

/*
* Updates the index value
* @param index, the index of the limb in mobile base
*/
void Limb::addIndex(int index){
	limbIndex = index;
}


/*
* Adds a link pointer to the link pointer array
* @param linkPTR, pointer to the link to add
* @param index, the index that the pointer is at
*/
void Limb::addLinkPtr(Link* linkPTR, int index){
	links[index] = linkPTR;
}


/*
* Updates the name value
* @param Name, the name of the limb
*/
void Limb::addName(const char* Name){
	limbName = Name;
}


/*
* Updates the size value
* @param size, the size of the link array
*/
void Limb::addSize(int size){
	numberOfLinks = size;
}

/*
* Updates the Transformation value
* @param limbRoot, the size of the link array
*/
void Limb::addTransformation(Transformation limbRoot){
	fiducialtoLimbRoot = limbRoot;
}

