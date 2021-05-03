/*
 * Link.h
 *
 *  Created on: Apr 27, 2021
 *      Author: aksha
 */

#ifndef LIBRARIES_KINEMATICCHAINSARDUINO_LINK_H_
#define LIBRARIES_KINEMATICCHAINSARDUINO_LINK_H_

class Link {
private:
	int linkIndex;
	float DHParameters[4];
	int hardwareID;
public:
	Link();
	void addIndex(int index);
	void addDH(double* DH);
};

#endif /* LIBRARIES_KINEMATICCHAINSARDUINO_LINK_H_ */
