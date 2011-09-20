using System;
using System.Collections.Generic;
using System.Text;
using TPB3D.Maths.ALGLIB;
using OpenTK;

namespace TPB3D.Maths {
	
    /// <summary>
    /// A Catmull-Rom Spline
    /// </summary>
    public class Spline {
        private List<Vector3> _points;
        private alglib.pspline3interpolant interpolant;

        /// <summary>
        /// The number of control points on this spline
        /// </summary>
        public int numPoints {
            get;
            private set;
        }

        /// <summary>
        /// The length of this spline
        /// </summary>
        public double length {
            get;
            private set;
        }

        public List<Vector3> points { 
            get{
                return _points;
            }
            set {
                _points = value;
                calcSpline();
            }
        }

        public Spline(List<Vector3> list) {
            _points = list;
            calcSpline();
        }
        
        private void calcSpline() {
            numPoints = _points.Count;
            if(_points[0] == _points[numPoints]) {
                alglib.pspline3buildperiodic(pointsToXY(), numPoints, 2, 0, out interpolant);
            } else {
                alglib.pspline3build(pointsToXY(), numPoints, 2, 0, out interpolant);
            }
            length = alglib.pspline3arclength(interpolant, 0, 1);
        }

        private double[,] pointsToXY() {
            double[,] XY = new double[numPoints,3];
            int i = 0;
            foreach(Vector3 point in _points) {
                XY[i, 0] = point.X;
                XY[i, 1] = point.Y;
                XY[i, 2] = point.Z;
                i++;
	        }
            return XY;
        }
    }
}
