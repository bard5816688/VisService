#pragma once
#include "VisAlgorithmDefs.h"

VISALGORITHM_NAMESPACE_BEGIN

struct FeatureFlags
{
	unsigned int shape : 1;
	unsigned int is_convex : 1;
	unsigned int is_filled : 1;
	unsigned int is_connected4 : 1;
	unsigned int is_connected8 : 1;
	unsigned int is_thin : 1;
	unsigned int circularity : 1;
	unsigned int compactness : 1;
	unsigned int contlength : 1;
	unsigned int convexity : 1;
	unsigned int phi : 1;
	unsigned int elliptic_axis : 1;		  /* ra, rb                         */
	unsigned int elliptic_shape : 1;	  /* ra_, rb_                       */
	unsigned int excentricity : 1;		  /* anisometry,bulkiness,str_faktor*/
	unsigned int moments : 1;			  /* m11, m20, m02, ia, ib          */
	unsigned int center_area : 1;		  /* row, col, area                 */
	unsigned int smallest_rectangle1 : 1; /* row1,col1,row2,col2            */
	unsigned int smallest_rectangle2 : 1; /* row_rect, col_rect, phi_rect,  */
	/* length1, length2               */
	unsigned int smallest_circle : 1;	  /* row_circle, col_circle, radius */
	unsigned int min_max_chord : 1;		  /* longest/shortest run           */
	unsigned int min_max_chord_gap : 1;	  /* longest/shortest run (holes)   */
	unsigned int rectangularity : 1;
};

/* Shape feature caching inside the region structure                        */
struct RegFeature
{
	union
	{
		FeatureFlags single;
		long all; /* if possible use 64 bits!                     */
	} def;
	uint8_t shape; /* SHAPE_*										*/
	bool is_convex;
	bool is_filled;
	bool is_connected4;
	bool is_connected8;
	bool is_thin; /* one pixel thin                               */
	double circularity;
	double compactness;
	double contlength;
	double convexity;
	double phi;
	double ra, rb;	 /* elliptic_axis                                */
	double ra_, rb_; /* elliptic_shape                               */
	double anisometry, bulkiness, structure_factor;
	double m11, m20, m02, ia, ib; /*¾ØµÄÖµ										*/
	double row, col;
	int area;
	int row1, col1, row2, col2;
	double row_rect, col_rect, phi_rect, length1, length2;
	double row_circle, col_circle, radius;
	int min_chord, max_chord;
	int min_chord_gap, max_chord_gap;
	double rectangularity;
};

struct RegionRun
{
	int l_;	/* line number (row) of run				*/
	int cb_; /* column index of beginning of run	*/
	int ce_; /* column index of ending of run		*/
};

class VisRegion
{
public:
	VisRegion() = default;
	VisRegion(double row1, double column1, double row2, double column2);
	VisRegion(double row, double column, double radius);
	~VisRegion() = default;
private:
	int num_;						/* number of runs					*/
	int numMax_;					/* maximum number of runs			*/
	RegFeature feature_;			/* already processed features	*/
	std::shared_ptr<RegionRun> rl_; /* pointer on array of run lengths	*/
};

VISALGORITHM_NAMESPACE_END
