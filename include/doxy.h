/* functions_doxygen.h */

#ifndef CUB3D_FUNCTIONS_DOXYGEN_H
#define CUB3D_FUNCTIONS_DOXYGEN_H

/**
 * @brief Adjusts a coordinate for mirroring based on specified conditions.
 *

	* This function adjusts the given coordinate 'x' for mirroring effects based on the
 * specified mirroring plane ('x' or 'y'), the mirroring angle,
	and the direction

	* determined by the 'ray_direction' function. The adjustment ensures proper mirroring
 * behavior for rendering in a 2D space.
 *
 * @param x Original coordinate to be adjusted.
 * @param width Width of the mirroring region or surface.
 * @param angle Angle associated with the mirroring.
 * @param plane Mirroring plane ('x' or 'y') along which adjustment is applied.
 *
 * @return Adjusted coordinate after considering mirroring conditions.
 */
double					adjust_mirroring(double x, double width, double angle,
							char plane);
							
#endif // CUB3D_FUNCTIONS_DOXYGEN_H
