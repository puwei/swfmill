#ifndef SWF_SHAPEMAKER_H
#define SWF_SHAPEMAKER_H

//#include "SWF.h"

namespace SWF {

class ShapeItem;
template <class T> class List;

class Point {
	public:
		double x, y;
		
		Point( double _x=0, double _y=0 ) {
			x = _x; y = _y;
		}
		Point( const Point& p ) {
			x=p.x; y=p.y;
		}
		const Point operator -( const Point& p ) const {
			Point p2(x-p.x, y-p.y);
			return p2;
		}
		Point operator =( const Point& p ) {
			x=p.x; y=p.y;
			return *this;
		}
};

class Bezier {
	public:
		Point p0, p1, p2, p3;
		Bezier() { ; }
		Bezier( const Point& _p0, const Point& _p1, const Point& _p2, const Point& _p3 )
			: p0(_p0), p1(_p1), p2(_p2), p3(_p3) { ; }
		Bezier &set( const Point& _p0, const Point& _p1, const Point& _p2, const Point& _p3 ) {
			p0 = _p0; p1 = _p1; p2 = _p2; p3 = _p3;
			return *this;
		}
};

class ShapeMaker {
	public:
		ShapeMaker( List<ShapeItem>* edges, double fx = 1, double fy = 1, double ofsx = 0, double ofsy = 0 );
	
		void setup( double x=0, double y=0, int fillStyle0=-1, int fillStyle1=-1, int lineStyle=-1 );
		void lineTo( double x, double y );
		void curveTo( double cx, double cy, double ax, double ay );
		void cubicTo( double x1, double y1, double x2, double y2, double ax, double ay );
		void close();
		void finish();
	
		void setupR( double x=0, double y=0, int fillStyle0=-1, int fillStyle1=-1, int lineStyle=-1 );
		void lineToR( double x, double y );
		void curveToR( double cx, double cy, double ax, double ay );
	
		double getLastX() { return lastx; }
		double getLastY() { return lasty; }
	
	protected:
		void cubicToRec( const Point& a, const Point& b, const Point& c, const Point& d, double k, int iteration=0 );
	
		List<ShapeItem>* edges;
		double factorx, factory;
		double offsetx, offsety;
		double lastx, lasty;
		double diffx, diffy;
	
		// rounding error accumulation compensation
		double roundx, roundy;
		int roundX( double x ) { return round( x, &roundx ); }
		int roundY( double y ) { return round( y, &roundy ); }
		int round( double v, double *acc ) {
				int r = (int)v;
				*acc += v-(double)r;
				while( *acc >= 1.0 ) {
					*acc -= 1.0;
					r++;
				}
				while( *acc <= 1.0 ) {
					*acc += 1.0;
					r--;
				}
				return r;
			}
		void roundReset() {
			roundx = roundy = 0;
			}
};

	
}
#endif
